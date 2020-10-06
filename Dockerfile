FROM debian:stable

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libssl-dev \
    git


WORKDIR /
RUN git clone --depth 1 https://github.com/mysql/mysql-connector-cpp.git
RUN mkdir -p mysql-connector-cpp/build

WORKDIR /mysql-connector-cpp/build
RUN cmake ..
RUN cmake --build . --config Release
RUN cmake --build . --target install --config Release
RUN ls /usr/local/mysql/connector-c++-/include/mysqlx
RUN ls /usr/local/mysql

WORKDIR /
ARG CACHE_DATE=2020-10-06
RUN git clone https://github.com/HikaruG/test_mysqlxapi.git


WORKDIR /test_mysqlxapi
RUN git submodule update --init --recursive
RUN mkdir build && cd build && cmake ..
RUN cd build && cmake -P cmake_install.cmake && ls
RUN cd build && cat Makefile

WORKDIR /test_mysqlxapi/build
RUN make
RUN ls build/
WORKDIR /
RUN rm -rf \
    mysql-connector-cpp
