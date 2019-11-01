#!/bin/sh

DYLD_LIBRARY_PATH=grpc_prebuilt/lib:mysqlcppconn_prebuilt/lib64 \
    cmake-build/server/server
