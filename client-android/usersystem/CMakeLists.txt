# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

include_directories(./grpc++/include)
include_directories(../../client-common)
include_directories(../../common)

add_library( # Specifies the name of the library.
        usersystem_client

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/usersystem_client.cpp
        src/main/cpp/usersystem_client_proxy.cpp
        ../../client-common/UserSystemClient.cpp
        ../../common/usersystem.grpc.pb.cc
        ../../common/usersystem.pb.cc)

set(PREBUILT_STATIC_LIBS
        libgrpc++
        libgrpc
        libprotobuf
        libgpr
        libaddress_sorting
        libssl
        libcrypto
        libcares
        libz
        )

        foreach(LIB ${PREBUILT_STATIC_LIBS})
    add_library(${LIB} STATIC IMPORTED)
    set_target_properties(
            ${LIB} PROPERTIES IMPORTED_LOCATION
            ../../../../grpc++/libs/${ANDROID_ABI}/${LIB}.a)
    target_link_libraries(usersystem_client ${LIB})
endforeach(LIB)

find_library(log-lib log)
target_link_libraries(usersystem_client ${log-lib})

set_target_properties(usersystem_client PROPERTIES
        LINK_FLAGS "-Wl,--whole-archive"
        )
set_target_properties(usersystem_client PROPERTIES
        LINK_FLAGS "-Wl,--allow-multiple-definition"
        )
