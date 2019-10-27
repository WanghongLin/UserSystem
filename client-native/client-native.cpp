//
// Created by Wanghong Lin on 2019/10/22.
//

#include <cstdlib>
#include "UserSystemClient.h"
#include <chrono>

const char* CERT_PEM = R"cert(
-----BEGIN CERTIFICATE-----
MIIDYjCCAkoCCQDV3wW+0eb8yDANBgkqhkiG9w0BAQsFADBzMQswCQYDVQQGEwJD
TjESMBAGA1UECAwJR3Vhbmdkb25nMREwDwYDVQQHDAhTaGVuemhlbjESMBAGA1UE
CgwJTXlDb21wYW55MRUwEwYDVQQLDAxNeURlcGFydG1lbnQxEjAQBgNVBAMMCWxv
Y2FsaG9zdDAeFw0xOTEwMjMwMjQ0MzZaFw0yMDEwMjIwMjQ0MzZaMHMxCzAJBgNV
BAYTAkNOMRIwEAYDVQQIDAlHdWFuZ2RvbmcxETAPBgNVBAcMCFNoZW56aGVuMRIw
EAYDVQQKDAlNeUNvbXBhbnkxFTATBgNVBAsMDE15RGVwYXJ0bWVudDESMBAGA1UE
AwwJbG9jYWxob3N0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy3vs
3ad/oZjaQ5UbNyhB+US0ZoSjFDZYi0Dh9zmZvAlu+rvAVVssOGMldX6IESS4IEit
gNToPLaFX7s4/4yPyRELxAyFs08C1Sxv3Ka391xwzEot21Q9qfZ4+KsFp4nbAAWi
zqMqLCQfxIcXzhkqzQmdJUCZCXPmXbQW0YervmNH4l2o4PPwHmvCGGSaGxalEVGi
18+fIHflqMdYztoeycms5PEICMg4SczqB36emYp47sJcbmCWpdYSXBzttWgk0CKY
gvWc9LLpGj9tgeywDRrrqyCYQK8+4847SSfws6Q38VzZ91uKxric9Q70cyGo3o0E
RsIEYbmViq2HqabaIwIDAQABMA0GCSqGSIb3DQEBCwUAA4IBAQCjSQzPB3NuuIxW
OmVGfjXAWSqKueoszeqA9NBpuIKngQVRE0zBOA1lPGwP5Yo23Xb43SXgIE7sKwKI
NqeYaNKPO9yzqEEua6iTgYDaxwVY84FRT7Qya3d9jlf8gRKRFFiby4h/SOQkGuoo
SL+88RkDGjYdssUpm2/EC6QgJD94rDic5/nmCWUVvLSCnKbObf4pTHRsWyhvfUjI
n9rKUlpQvdLaF4W6USEx58xDPcm2vX/3FSx1eZ+E+c8NMTo4a0B4F8G88rZ9E7Gj
E+F7JWwE/NY93GoDP1/zllJc+QPKhAR7TEKFT9h2yvxGDU4Rv6ZTUDB53I/Exq3x
ZbCrPrna
-----END CERTIFICATE-----
)cert";

static std::string GenerateTimestampDeviceID()
{
    return std::to_string(std::chrono::system_clock().now().time_since_epoch().count());
}

int main(int argc, char* argv[])
{

    grpc::SslCredentialsOptions credentialsOptions;
    credentialsOptions.pem_root_certs = std::string(CERT_PEM);

    UserSystemClient user_client(
            grpc::CreateChannel("localhost:50051", /*grpc::SslCredentials(credentialsOptions)*/ grpc::InsecureChannelCredentials())
    );

    std::string username("john");
    std::string password("123456");
    std::string device_id = GenerateTimestampDeviceID();

    auto response = user_client.Register(username, password, device_id, usersystem::Platform::Type_Desktop);

    if (response.response().code() == usersystem::ResponseCode::ERROR_REGISTER_USERNAME_HAS_BEEN_TAKEN) {
        std::cerr << "Register received already exists " <<  response.response().code() << std::endl;
    } else {
        std::cout << "Register received success " << response.usermodel().username() << ' '
                  << response.usermodel().id() << std::endl;
    }

    auto loginResponse = user_client.Login("john", "123456", device_id, usersystem::Platform::Type_Desktop);

    if (loginResponse.response().code() == usersystem::ResponseCode::OK) {
        std::cout << "Login success " << loginResponse.usermodel().username() << ' '
                  << loginResponse.token() << std::endl;
    } else {
        if (loginResponse.response().code() == usersystem::ResponseCode::ERROR_LOGIN_WRONG_USERNAME) {
            std::cerr << "Login register required" << std::endl;
        } else if (loginResponse.response().code() == usersystem::ResponseCode::ERROR_LOGIN_WRONG_PASSWORD) {
            std::cerr << "Login wrong password" << std::endl;
        }
    }

    // auto checkResult = user_client.CheckLogin("john", loginResponse.token(), device_id, usersystem::Platform::Type_Desktop);
    // std::cout << "Check result " << checkResult.response().message() << ' ' << checkResult.response().code() << std::endl;
    user_client.Logout(username);

    return EXIT_SUCCESS;
}