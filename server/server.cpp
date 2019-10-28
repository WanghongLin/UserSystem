//
// Created by Wanghong Lin on 2019/10/22.
//

#include <iostream>
#include "UserSystemImpl.h"

static const char* CERT_PEM = R"cert(
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

static const char* KEY_PEM = R"key(
-----BEGIN PRIVATE KEY-----
MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDLe+zdp3+hmNpD
lRs3KEH5RLRmhKMUNliLQOH3OZm8CW76u8BVWyw4YyV1fogRJLggSK2A1Og8toVf
uzj/jI/JEQvEDIWzTwLVLG/cprf3XHDMSi3bVD2p9nj4qwWnidsABaLOoyosJB/E
hxfOGSrNCZ0lQJkJc+ZdtBbRh6u+Y0fiXajg8/Aea8IYZJobFqURUaLXz58gd+Wo
x1jO2h7Jyazk8QgIyDhJzOoHfp6ZinjuwlxuYJal1hJcHO21aCTQIpiC9Zz0suka
P22B7LANGuurIJhArz7jzjtJJ/CzpDfxXNn3W4rGuJz1DvRzIajejQRGwgRhuZWK
rYepptojAgMBAAECggEBAKdT7OAI0QeNrk5M2uhsjnPwb3iuMXx5hC5e2HJ4R1c9
WqmMowiNxLtJrJAF0NZoH5FMsoByk9b5MIwcZS6f480v20EIGxnsKyQpOoN0BWu/
9HHJvhPSHjMZnzi9ShUPY6uM9uh9fDx4KDdv779nKq8Y7MSpbi87w3/ii7EZo70W
ZtO3FXTZA6VWjpsyTbH8MpCXEzHrE4C5i6TqEW9lN9X3UJpVr4aTmC/CroLPerDN
azYUtEYjfwBSpdzN6j1rq8EehjrcUxDA0afekol44rAY1sfZJ2F5HlzRlmjPsuPh
la3Gn3TPzE7kzVSIhrgObtEAltRvftCuKW/V24A37sECgYEA9FvAtYZ9TOAKd9R7
fwYWEk4xo3IUpmvwOycbblceJoOskQFPh5DyA6/d2usUfQXnVDsyayW8Eahwu4H9
Fk9Ydr38PkhlrfGrQ798p3sVGsQwuMx9+DTjeKLxNDMtp++0Ru30XD2xmTHe3lCB
69Vbt47rhZPGWGgvltIuDKvoq7sCgYEA1S2pFi62IvT846bYIjmbrPEZezjR/nHG
Sp2wmRRidb26k6T5S+Qle751hJ/3wdk34gKp59iE4KHhHsOIhbKbaFCJxMK2BXwf
ofgWdhvD0kXz85fbYn1OLcfKGzwGzqrL9xi+rHOI6iiFUoVci/eas6fWDWkYptzX
yzzS9G98QLkCgYEAuRXmWZiMv/XS+ADRqd0KSsM/hfWa/pMzWxq8BE+oXrPNuees
PZrkNTa4bGEzG5+lIH/WKKJkWVukR+KluIhREV/F98cOfTpX5vDbkmAAFE4WOWNq
5t3oji+dU1SQeGtvuWnzdQqlwsura+i+/8qTte1jJ8JOshf4M9zvVFnB2pECgYB9
NOBG4xCe331YyDnRgDxrCwCIWwsbgv+P+6YpgsuBk/ntlcvGQy2wzGCBkOMXu9kS
qbXZMlZ5CRsL0pRw0kJstkD0i9gUyJ5bpzaqEAynh+aMf/ielDJCuUF/VXY6FB7P
9nynFQSpYztLCIEexELcmgsivUN5XeRwvjy4zHISIQKBgQCg2PZK8WTNU7JFo+Xc
oX2Q/hXfxnw30ex0CFh0Wcp9p1n8BtHhq4HQChRnJi2X2luhbwxPE0wtD7K0zSfP
PaEAg98A97pUViVnBxjgkOhnaS9o0Pk1zXGX/pa38R/5X8D8zSJpzzV+XQZv9Joc
UZj0IsTK+lwzX+FkrN5Z5lQdvQ==
-----END PRIVATE KEY-----
)key";

constexpr auto DEFAULT_DB_URL = "mysqlx://root:example@db";

void RunServer(bool enableSsl, std::string& dbUrl)
{
    std::string server_address("0.0.0.0:50051");
    UserSystemImpl service(dbUrl);

    grpc::SslServerCredentialsOptions::PemKeyCertPair pemKeyCertPair;
    pemKeyCertPair.private_key = std::string(KEY_PEM);
    pemKeyCertPair.cert_chain = std::string(CERT_PEM);
    grpc::SslServerCredentialsOptions credentialsOptions;
    credentialsOptions.pem_root_certs = "";
    credentialsOptions.pem_key_cert_pairs.emplace_back(pemKeyCertPair);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, enableSsl ?
                                             grpc::SslServerCredentials(credentialsOptions) :
                                             grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    std::cout << "Use db url " << dbUrl << std::endl;

    server->Wait();
}

static void ShowUsage()
{
    std::cout << "Simple user system application\n"
              << "Usage:\n"
              << "\tserver [OPTION...]\n\n"
              << "Help Options:\n"
              << "\t-h, --help\tShow this help\n\n"
              << "Application Options:\n"
              << "\t--enable-ssl\tUse ssl certificate, DO NOT support connect from IP address\n"
              << "\t--db-url\tDatabase url connect information, e.g mysqlx://root:password@db_host\n"
              << std::endl;
    std::exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
        ShowUsage();
    }

    // ssl server didn't support connect from IP address
    bool sslSupport = false;
    std::string dbUrl(DEFAULT_DB_URL);
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "--enable-ssl") {
            sslSupport = true;
        }

        if (std::string(argv[i]) == "--db-url" && (i+1) < argc) {
            dbUrl = std::string(argv[i+1]);
        }
    }

    RunServer(sslSupport, dbUrl);
    return EXIT_SUCCESS;
}
