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
// Created by Wanghong Lin on 2019/10/31.
//

#include <cstdlib>
#include <iostream>
#include <chrono>
#include "UserSystemClient.h"

int main(int argc, char* argv[])
{
    UserSystemClient client(
            grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
            );

    auto deviceID = std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto rsp = client.Login("john", "123456", deviceID, usersystem::Platform::Type_Desktop);

    std::cout << "Login response " << rsp.response().code() << ' ' << rsp.response().message() << std::endl;
    if (rsp.response().code() == usersystem::ResponseCode::OK) {
        auto response = client.CheckLogin("john", rsp.token(), deviceID, usersystem::Platform::Type_Desktop);
        std::cout << "CheckLogin response " << response.response().code() << ' ' << response.response().message() << std::endl;
    }

    return EXIT_SUCCESS;
}