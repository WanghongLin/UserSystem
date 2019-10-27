//
// Created by Wanghong Lin on 2019/10/23.
//

#ifndef USERSYSTEM_ABSTRACTDBCONNECTOR_H
#define USERSYSTEM_ABSTRACTDBCONNECTOR_H

#include <string>
#include <memory>
#include <vector>
#include "usersystem.pb.h"

class AbstractDbConnector {

public:
    virtual usersystem::UserModel CreateUser(const usersystem::UserModel& from) = 0;
    virtual usersystem::ResponseCode UpdateUser(const usersystem::UserModel& from) = 0;
    virtual usersystem::UserModel FetchUser(const std::string& username) = 0;
    virtual usersystem::ResponseCode RemoveUser(const std::string& username) = 0;

    virtual usersystem::UserLoginHistoryModel CreateLoginHistory(const usersystem::UserLoginHistoryModel& from) = 0;
    virtual usersystem::ResponseCode UpdateLoginHistory(const usersystem::UserLoginHistoryModel& from) = 0;
    virtual usersystem::UserLoginHistoryModel FetchLoginHistory(const std::string& username) = 0;
    virtual usersystem::ResponseCode RemoveUserLoginHistory(const std::string& historyId) = 0;

    virtual ~AbstractDbConnector() {}
};

#endif //USERSYSTEM_ABSTRACTDBCONNECTOR_H
