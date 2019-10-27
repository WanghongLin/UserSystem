load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "server",
    srcs = ["server.cpp", "UserSystemImpl.cpp", "UserSystemImpl.h", "Utils.h",
            "MySQLDbConnector.cpp", "MySQLDbConnector.h", "AbstractDbConnector.h"],

    copts = ["-Iigrpc++", "-Iimysql", "-Iiopenssl", "-Iipb", "-Ijwt-cpp", "-I."],
    copts = ["-I${HOME}/Developments/Homebrew/Cellar/grpc/1.23.0_3/include",
             "-Ijwt-cpp",
             "-I${HOME}/Downloads/mysql-connector-c++-8.0.18-macos10.14-x86-64bit/include",
             "-I${HOME}/Developments/Homebrew/Cellar/openssl/1.0.2s/include",
             "-I${HOME}/Developments/github/grpc/third_party/protobuf/out/include",
             ],
    linkopts = ["-L${HOME}/Developments/Homebrew/Cellar/grpc/1.23.0_3/lib -lgrpc++",
                "-L${HOME}/Downloads/mysql-connector-c++-8.0.18-macos10.14-x86-64bit -lmysqlcppconn8"],

    deps = ["//common:common"]
)