cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(test_mysql)

add_subdirectory(third_party/easyloggingpp)
list(APPEND COMMON_SOURCES ${Easyloggingpp_SOURCE_DIR}/src/easylogging++.cc)
include_directories(${Easyloggingpp_SOURCE_DIR}/src)

include_directories(${test_mysql_SOURCE_DIR})
add_executable(test_mysql
  ${COMMON_SOURCES}
  test.cpp
)
target_include_directories(test_mysql PRIVATE "usr/local/mysql/connector-c++-")
