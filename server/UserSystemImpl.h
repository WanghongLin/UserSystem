//
// Created by Wanghong Lin on 2019/10/22.
//

#ifndef USERSYSTEM_USERSYSTEMIMPL_H
#define USERSYSTEM_USERSYSTEMIMPL_H

#include <grpcpp/grpcpp.h>
#include <grpc++/grpc++.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include "usersystem.pb.h"
#include "usersystem.grpc.pb.h"
#include "MySQLDbConnector.h"

class UserSystemImpl : public usersystem::UserSystem::Service {

public:
    explicit UserSystemImpl(const std::string& dbUrl) : _dbUrl(dbUrl) /* : _dbConnector(new MySQLDbConnector)*/ {}

    grpc::Status
    Register(::grpc::ServerContext *context, const usersystem::RegisterRequest *request, usersystem::RegisterResponse *response) override;

    grpc::Status
    Login(::grpc::ServerContext *context, const usersystem::LoginRequest *request, usersystem::LoginResponse *response) override;

    grpc::Status CheckLogin(::grpc::ServerContext *context, const ::usersystem::CheckLoginRequest *request,
                            ::grpc::ServerWriter<::usersystem::CheckLoginResponse> *writer) override;

    grpc::Status Logout(::grpc::ServerContext *context, const ::usersystem::LogoutRequest *request,
                        ::usersystem::CommonResponse *response) override;

    ~UserSystemImpl() override {
        // if (!_dbConnector) {
        //    delete _dbConnector;
        //    _dbConnector = nullptr;
        // }
    }
private:
    // FIXME: can not shared across multiple threads
    // AbstractDbConnector* _dbConnector;
    std::string _dbUrl;
    std::mutex _checkLoginMutex;
    std::condition_variable _checkLoginCV;
};


#endif //USERSYSTEM_USERSYSTEMIMPL_H
