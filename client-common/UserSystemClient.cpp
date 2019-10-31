//
// Created by Wanghong Lin on 2019/10/22.
//

#include "UserSystemClient.h"

void FillGRPCError(usersystem::CommonResponse* response, const grpc::Status result)
{
    response->set_code(usersystem::ResponseCode::ERROR_GRPC_ERROR);
    response->set_grpc_error_code(result.error_code());
    response->set_grpc_error_message(result.error_message());
    response->set_grpc_error_details(result.error_details());
}

usersystem::RegisterResponse UserSystemClient::Register(const std::string& username, const std::string& password,
                                                        const std::string& device_id, usersystem::Platform platform) {
    usersystem::RegisterRequest request;
    request.set_username(username);
    request.set_password(password);
    request.set_device_id(device_id);
    request.set_platform(platform);

    usersystem::RegisterResponse response;
    grpc::ClientContext context;

    auto result = _stub->Register(&context, request, &response);
    if (!result.ok()) {
        std::cerr << __PRETTY_FUNCTION__ << " rpc error" << std::endl;
        FillGRPCError(response.mutable_response(), result);
    }
    if (response.response().code() != usersystem::ResponseCode::OK) {
        std::cerr << __PRETTY_FUNCTION__ << " error: "
                  << response.response().code() << ' '
                  << response.response().message() << std::endl;
    }

    return response;
}

usersystem::LoginResponse UserSystemClient::Login(const std::string& username, const std::string& password,
                                                  const std::string& device_id, usersystem::Platform platform) {
    usersystem::LoginRequest request;
    request.set_username(username);
    request.set_password(password);
    request.set_device_id(device_id);
    request.set_platform(platform);

    usersystem::LoginResponse response;

    grpc::ClientContext context;

    auto result = _stub->Login(&context, request, &response);
    if (!result.ok()) {
        std::cerr << __PRETTY_FUNCTION__ << ' ' << "rpc error" << std::endl;
        FillGRPCError(response.mutable_response(), result);
    }

    if (response.response().code() != usersystem::ResponseCode::OK) {
        std::cerr << __PRETTY_FUNCTION__ << " error: "
                  << response.response().code() << ' '
                  << response.response().message() << std::endl;
    }
    return response;
}

usersystem::CheckLoginResponse
UserSystemClient::CheckLogin(const std::string& username, const std::string& token,
                             const std::string& device_id, usersystem::Platform platform) {
    usersystem::CheckLoginRequest request;
    request.set_username(username);
    request.set_token(token);
    request.set_device_id(device_id);
    request.set_from_platform(platform);

    grpc::ClientContext context;
    auto reader = _stub->CheckLogin(&context, request);

    usersystem::CheckLoginResponse response;
    reader->Read(&response);
    std::cout << "Check Login return " << response.response().code() << ' ' << response.response().message() << std::endl;

    auto result = reader->Finish();
    if (!result.ok()) {
        std::cerr << __PRETTY_FUNCTION__ << " rpc error" << std::endl;
        FillGRPCError(response.mutable_response(), result);
    }

    return response;
}

usersystem::CommonResponse UserSystemClient::Logout(const std::string& username, const std::string& token) {
    usersystem::LogoutRequest request;
    request.set_username(username);
    request.set_token(token);

    grpc::ClientContext context;
    usersystem::CommonResponse response;
    auto result = _stub->Logout(&context, request, &response);
    if (!result.ok()) {
        std::cerr << __PRETTY_FUNCTION__ << " rpc error" << std::endl;
        FillGRPCError(&response, result);
    }

    return response;
}
