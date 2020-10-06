cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test_mysql)

add_subdirectory(third_party/easyloggingpp)
list(APPEND COMMON_SOURCES ${Easyloggingpp_SOURCE_DIR}/src/easylogging++.cc)
include_directories(${Easyloggingpp_SOURCE_DIR}/src)
add_subdirectory(/usr/local/mysql/connector-c++-/include/mysqlx)
list(APPEND COMMON_SOURCES /usr/local/mysql/connector-c++-/include/mysqlx/xdeevapi.h)
include_directories(/usr/local/mysql/connector-c++-/include/)

add_executable(test_mysql test.cpp)
