cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test_mysql)

add_subdirectory(third_party/easyloggingpp)
list(APPEND COMMON_SOURCES ${Easyloggingpp_SOURCE_DIR}/src/easylogging++.cc)
include_directories(${Easyloggingpp_SOURCE_DIR}/src)



set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64)
add_subdirectory(/usr/local/mysql/connector-c++-/lib64/debug/libmysqlcppconn8.so.2.8.0.21)
list(APPEND COMMON_SOURCES /usr/local/mysql/connector-c++-/include/mysqlx/xdeevapi.h)
include_directories(/usr/local/mysql/connector-c++-/include/)

add_executable(test_mysql test.cpp)

target_link_libraries(main mysqlx)
target_compile_features(main PRIVATE cxx_range_for)
