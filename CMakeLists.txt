cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_library(MYSQL mysql HINTS /usr/local/mysql)
project(test_mysql)

add_subdirectory(third_party/easyloggingpp)
list(APPEND COMMON_SOURCES ${Easyloggingpp_SOURCE_DIR}/src/easylogging++.cc)
include_directories(${Easyloggingpp_SOURCE_DIR}/src)
add_subdirectory(${MYSQL})
include_directories(${Easyloggingpp_SOURCE_DIR}/connector-c++-)

add_executable(test_mysql test.cpp)
