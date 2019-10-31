#!/bin/sh

# Run this script every time the proto file changed

# for grpc 1.23.0_3 use combine with protobuf version 3.8
export PATH=grpc_prebuilt/bin:$PATH

protoc -I. \
    --grpc_out=common --cpp_out=common \
    --java_out=lite:client-android/usersystem/src/main/java \
    --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` usersystem.proto

javah -o client-android/usersystem/src/main/cpp/usersystem_client.h \
    -cp client-android/usersystem/build/tmp/kotlin-classes/debug \
    com.wanghong.grpc.usersystem.UserSystemNative
