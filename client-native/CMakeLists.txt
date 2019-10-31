project(client-native)

include(../common/common.cmake)
include_directories(../client-common)

add_executable(client-native client-native.cpp ../client-common/UserSystemClient.cpp ${COMMON_FILES})
add_executable(TestingLogin TestingLogin.cpp ../client-common/UserSystemClient.cpp ${COMMON_FILES})
add_executable(TestingRegister TestingRegister.cpp ../client-common/UserSystemClient.cpp ${COMMON_FILES})
add_test(NAME login COMMAND TestingLogin)
add_test(NAME register COMMAND TestingRegister)