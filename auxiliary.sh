#!/usr/bin/env bash

# auxiliary command

if [[ -f certificate/cert.pem && -f certificate/key.pem ]];then
    printf "\e[32mUse private/public key under certificate\e[0m\n"
else
    printf "\e[31mRequest certificate from openssl\e[0m\n"
    openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 365 -out cert.pem \
        -subj '/C=CN/ST=Guangdong/L=Shenzhen/O=MyCompany/OU=MyDepartment/CN=localhost'
fi
# mysql-connector-c++

# CMAKE_INSTALL_RPATH
# build gRPC configuration for Android
cmake .. -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-21 \
    -DANDROID_STL=c++_shared \
    -DRUN_HAVE_STD_REGEX=0 \
    -DRUN_HAVE_POSIX_REGEX=0 \
    -DRUN_HAVE_STEADY_CLOCK=0 \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=`pwd`/out \
    -D_gRPC_PLATFORM_ANDROID=ON \
    -DgRPC_BUILD_CODEGEN=OFF \
    -DgRPC_BUILD_TESTS=OFF \
    -Dprotobuf_BUILD_TESTS=OFF \
    -Dprotobuf_BUILD_CONFORMANCE=OFF \
    -Dprotobuf_BUILD_EXAMPLES=OFF \
    -DANDROID_LINKER_FLAGS="-landroid -llog"
    #-DgRPC_USE_PROTO_LITE=1
    #-Dprotobuf_BUILD_PROTOC_BINARIES=OFF
    #-Dprotobuf_BUILD_SHARED_LIBS=ON
    #-DCMAKE_CXX_STANDARD_LIBRARIES="-llog -lc++_static"
    #-DANDROID_LINKER_FLAGS="-landroid -llog"
