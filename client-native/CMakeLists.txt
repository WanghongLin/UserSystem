project(client-native)

include(../common/common.cmake)
include_directories(../client-common)

add_executable(client-native client-native.cpp ../client-common/UserSystemClient.cpp ${COMMON_FILES})