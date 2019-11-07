//
// Created by Wanghong Lin on 2019/10/22.
//

#include "UserSystemImpl.h"
#include "jwt-cpp/jwt.h"
#include "Utils.h"
#include <thread>

constexpr auto TOKEN_VALID_DURATION = 180 * 24 * 60 * 60;

template<typename REQUEST>
usersystem::UserLoginHistoryModel CreateLoginHistoryModel(const std::string& subject, const REQUEST* request)
{
    auto token = jwt::create()
            .set_issuer("auth0")
            .set_subject(subject)
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{TOKEN_VALID_DURATION})
            .sign(jwt::algorithm::hs256{"secret"});

    usersystem::UserLoginHistoryModel historyModel;

    historyModel.set_token(token);
    historyModel.set_username(request->username());
    historyModel.set_device_id(request->device_id());
    historyModel.set_from_platform(request->platform());
    historyModel.set_is_valid(true);
    historyModel.set_create_at_millis(Utils::CurrentTimeMillis());
    historyModel.set_expire_at_millis(Utils::CurrentTimeMillis());
    historyModel.set_update_at_millis(Utils::CurrentTimeMillis());

    return historyModel;
}

grpc::Status UserSystemImpl::Register(::grpc::ServerContext *context,
                                      const usersystem::RegisterRequest *request,
                                      usersystem::RegisterResponse *response) {
    std::cout << __FUNCTION__ << " from " << context->peer() << ' ' << request->username() << ' ' << request->device_id() << std::endl;
    MySQLDbConnector _dbConnector(_dbUrl);
    if (request->username().empty() || request->password().empty()) {
        response->mutable_response()->set_code(usersystem::ResponseCode::ERROR_REGISTER_EMPTY_USERNAME_PASSWORD);
        return grpc::Status::OK;
    }

    auto user = _dbConnector.FetchUser(request->username());
    if (!user.id().empty()) {
        response->mutable_response()->set_code(usersystem::ResponseCode::ERROR_REGISTER_USERNAME_HAS_BEEN_TAKEN);
        response->mutable_response()->set_message(context->peer());
        return grpc::Status::OK;
    }

    usersystem::UserModel userModel;
    userModel.set_username(request->username());
    // TODO: bcrypt encode password
    // FIXME: use more sophisticated hash method, e.g bcrypt password encoder
    userModel.set_password(Utils::SHA256(request->password()));
    userModel.set_create_at_millis(Utils::CurrentTimeMillis());
    userModel.set_update_at_millis(Utils::CurrentTimeMillis());

    auto result = _dbConnector.CreateUser(userModel);

    // also perform login for new create user
    // the client no need to request again just for login
    auto loginHistoryModel = CreateLoginHistoryModel(context->peer(), request);
    _dbConnector.CreateLoginHistory(loginHistoryModel);

    response->mutable_response()->set_code(usersystem::ResponseCode::OK);
    response->mutable_usermodel()->set_username(result.username());
    response->mutable_usermodel()->set_id(result.id());
    response->set_token(loginHistoryModel.token());

    return grpc::Status::OK;
}

grpc::Status
UserSystemImpl::Login(::grpc::ServerContext *context, const usersystem::LoginRequest *request,
                      usersystem::LoginResponse *response) {

    MySQLDbConnector _dbConnector(_dbUrl);
    std::cout << __FUNCTION__ << " from " << context->peer() << ' ' << request->username() << std::endl;
    if (request->username().empty()) {
        response->mutable_response()->set_code(usersystem::ResponseCode::ERROR_LOGIN_WRONG_USERNAME);
        return grpc::Status::OK;
    }

    auto user = _dbConnector.FetchUser(request->username());
    if (user.id().empty()) {
        response->mutable_response()->set_code(usersystem::ResponseCode::ERROR_LOGIN_WRONG_USERNAME);
        response->mutable_response()->set_message("User not exists");
        return grpc::Status::OK;
    }

    auto password = Utils::SHA256(request->password());
    if (password != user.password()) {
        response->mutable_response()->set_code(usersystem::ResponseCode::ERROR_LOGIN_WRONG_PASSWORD);
        response->mutable_response()->set_message("Username and password not match");
        return grpc::Status::OK;
    }

//    auto token = jwt::create()
//            .set_issuer("auth0")
//            .set_issued_at(std::chrono::system_clock::now())
//            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{TOKEN_VALID_DURATION})
//            .sign(jwt::algorithm::hs256{"secret"});

    usersystem::UserLoginHistoryModel historyModel = CreateLoginHistoryModel(context->peer(), request);

//    historyModel.set_token(token);
//    historyModel.set_username(request->username());
//    historyModel.set_device_id(request->device_id());
//    historyModel.set_from_platform(request->platform());
//    historyModel.set_create_at_millis(Utils::CurrentTimeMillis());
//    historyModel.set_expire_at_millis(Utils::CurrentTimeMillis());
//    historyModel.set_update_at_millis(Utils::CurrentTimeMillis());

    // invalid the last login record
    auto lastRecord = _dbConnector.FetchLoginHistory(request->username());
    if (lastRecord.username() == request->username() && lastRecord.is_valid() && !lastRecord.id().empty()) {
        lastRecord.set_is_valid(false);
        _dbConnector.UpdateLoginHistory(lastRecord);
    }

    auto result = _dbConnector.CreateLoginHistory(historyModel);

    response->mutable_response()->set_code(usersystem::ResponseCode::OK);
    response->mutable_usermodel()->set_username(user.username());
    response->mutable_usermodel()->set_id(user.id());
    response->mutable_usermodel()->set_phone_number(context->peer());
    response->set_token(historyModel.token());

    std::unique_lock<std::mutex> lck(_checkLoginMutex);
    _checkLoginCV.notify_all();
    lck.unlock();

    return grpc::Status::OK;
}

grpc::Status UserSystemImpl::CheckLogin(::grpc::ServerContext *context, const ::usersystem::CheckLoginRequest *request,
                                        ::grpc::ServerWriter<::usersystem::CheckLoginResponse> *writer) {
    MySQLDbConnector _dbConnector(_dbUrl);
    std::cout << __FUNCTION__ << " from " << context->peer() << ' ' << request->username() << ' ' << request->device_id() << std::endl;

    if (request->username().empty() || request->device_id().empty() || request->token().empty()) {
        usersystem::CheckLoginResponse response;
        response.mutable_response()->set_code(usersystem::ResponseCode::ERROR_LOGIN_STATUS_INVALID);
        writer->Write(response);
        return grpc::Status::OK;
    }

    do {
        // check last login history match
        auto lastRecord = _dbConnector.FetchLoginHistory(request->username());
        if (lastRecord.username() == request->username() &&
            lastRecord.token() == request->token() &&
            lastRecord.device_id() == request->device_id() &&
            lastRecord.from_platform() == request->from_platform() &&
            lastRecord.is_valid()) {

            std::unique_lock<std::mutex> lck(_checkLoginMutex);
            _checkLoginCV.wait(lck);
            lck.unlock();
        } else {
            usersystem::CheckLoginResponse response;
            response.mutable_response()->set_code(usersystem::ResponseCode::ERROR_LOGIN_STATUS_INVALID);
            response.mutable_response()->set_message(context->peer());
            writer->Write(response);
            return grpc::Status::OK;
        }
    } while (true);
}

grpc::Status UserSystemImpl::Logout(::grpc::ServerContext *context, const ::usersystem::LogoutRequest *request,
                                    ::usersystem::CommonResponse *response) {
    std::cout << __FUNCTION__ << " from " << context->peer() << ' ' << request->username() << std::endl;
    if (request->username().empty()) {
        response->set_code(usersystem::ERROR_INVALID_USERNAME);
        return grpc::Status::OK;
    }

    MySQLDbConnector dbConnector(_dbUrl);
    auto result = dbConnector.FetchLoginHistory(request->username());
    // FIXME: use jwt to verify token
    auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256 { "secret" })
            .with_issuer("auth0");
    auto decoded_token = jwt::decode(request->token());
    try {
        verifier.verify(decoded_token);
        std::cout << __FUNCTION__ << " verify ok" << std::endl;
    } catch (jwt::token_verification_exception& e) {
        std::cerr << __FUNCTION__ << " verify failed " << e.what() << std::endl;
    }

    if (result.username() == request->username() && result.token() == request->token()) {
        result.set_is_valid(false);
        dbConnector.UpdateLoginHistory(result);

        std::unique_lock<std::mutex> lck(_checkLoginMutex);
        _checkLoginCV.notify_all();
        lck.unlock();

        response->set_code(usersystem::OK);
        response->set_message("Logout ok");
        return grpc::Status::OK;
    } else {
        response->set_code(usersystem::ERROR_INVALID_USERNAME);
    }

    return grpc::Status::OK;
}
