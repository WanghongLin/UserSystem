project(server)

set(CMAKE_CXX_STANDARD 11)

include(../common/common.cmake)

if (NOT DEFINED MYSQL_CONNECTOR)
    set(MYSQL_CONNECTOR "$ENV{HOME}/Downloads/mysql-connector-c++-8.0.18-macos10.14-x86-64bit")
endif ()

message("Use mysql connector in ${MYSQL_CONNECTOR}")

include_directories(${MYSQL_CONNECTOR}/include)
link_directories(${MYSQL_CONNECTOR}/lib64)
link_libraries(mysqlcppconn8)

add_executable(server ${COMMON_FILES} UserSystemImpl.cpp MySQLDbConnector.cpp server.cpp)
