//
// Copyright 2019 Wanghong Lin
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//         http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
//         limitations under the License.
//
// Created by Wanghong Lin on 2019/10/24.
//

#ifndef USERSYSTEM_UTILS_H
#define USERSYSTEM_UTILS_H

#include <chrono>
#include <string>
#include <sstream>
#include "usersystem.pb.h"
#include "mysqlx/xdevapi.h"
#include <openssl/sha.h>

struct Utils {

    /**
     * Get current time in milliseconds
     * @return time in milliseconds since epoch 1970-01-01 00:00:00
     */
    static uint64_t CurrentTimeMillis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
    }

    /**
     * Convert a user model to a json string for database persistence
     * @param userModel user model
     * @return a json string
     */
    static std::string ToJsonString(const usersystem::UserModel& userModel) {
        std::stringstream ss;
        ss << '{'
           << R"("username":")" << userModel.username() << "\","
           << R"("password":")" << userModel.password() << "\","
           << R"("id":")" << userModel.id() << "\","
           << R"("create_at_millis":)" << userModel.create_at_millis() << ","
           << R"("update_at_millis":)" << userModel.update_at_millis()
           << '}';
        return ss.str();
    }

    /**
     * Convert a user login history model to json string for database persistence
     * @param userLoginHistoryModel login history model
     * @return a json string
     */
    static std::string ToJsonString(const usersystem::UserLoginHistoryModel& userLoginHistoryModel) {
        std::stringstream ss;
        ss << '{'
           << R"("id":")" << userLoginHistoryModel.id() << "\","
           << R"("username":")" << userLoginHistoryModel.username() << "\","
           << R"("token":")" << userLoginHistoryModel.token() << "\","
           << R"("device_id":")" << userLoginHistoryModel.device_id() << "\","
           << R"("from_platform":)" << userLoginHistoryModel.from_platform() << ","
           << R"("is_valid":)" << std::boolalpha << userLoginHistoryModel.is_valid() << ","
           << R"("create_at_millis":)" << userLoginHistoryModel.create_at_millis() << ","
           << R"("update_at_millis":)" << userLoginHistoryModel.update_at_millis() << ","
           << R"("expire_at_millis":)" << userLoginHistoryModel.expire_at_millis()
           << '}';
        return ss.str();
    }

    static usersystem::UserModel UserModelFromDbDoc(const mysqlx::DbDoc& dbDoc) {
        usersystem::UserModel userModel;

        userModel.set_id(dbDoc["_id"].get<std::string>());
        userModel.set_username(dbDoc["username"].get<std::string>());
        userModel.set_password(dbDoc["password"].get<std::string>());
        userModel.set_update_at_millis(dbDoc["update_at_millis"].get<uint64_t>());
        userModel.set_create_at_millis(dbDoc["create_at_millis"].get<uint64_t>());

        return userModel;
    }

    static usersystem::UserLoginHistoryModel UserLoginHistoryModelFromDbDoc(const mysqlx::DbDoc& dbDoc) {
        usersystem::UserLoginHistoryModel historyModel;

        historyModel.set_id(dbDoc["_id"].get<std::string>());
        historyModel.set_username(dbDoc["username"].get<std::string>());
        historyModel.set_token(dbDoc["token"].get<std::string>());
        historyModel.set_device_id(dbDoc["device_id"].get<std::string>());
        historyModel.set_from_platform(usersystem::Platform(dbDoc["from_platform"].get<int>()));
        historyModel.set_is_valid(dbDoc["is_valid"].get<bool>());
        historyModel.set_create_at_millis(dbDoc["create_at_millis"].get<uint64_t>());
        historyModel.set_update_at_millis(dbDoc["update_at_millis"].get<uint64_t>());
        historyModel.set_expire_at_millis(dbDoc["expire_at_millis"].get<uint64_t>());

        return historyModel;
    }

    /**
     * A simple method for password hashing
     * @param input password input
     * @return a hash result
     */
    static std::string SHA256(const std::string& input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input.c_str(), input.length());
        SHA256_Final(hash, &sha256);

        std::string output = "";
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            output += ToHex(hash[i]);
        }
        return output;
    }

private:
    static std::string ToHex(unsigned char s) {
        std::stringstream ss;
        ss << std::hex << (int) s;
        return ss.str();
    }

};

#endif //USERSYSTEM_UTILS_H
