FROM debian:stable

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libssl-dev \
    git


WORKDIR /
RUN git clone https://github.com/mysql/mysql-connector-cpp.git
RUN mkdir -p mysql-connector-cpp/build

WORKDIR /mysql-connector-cpp/build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=/usr/lib
RUN cmake --build .
RUN cmake --build . --target install

WORKDIR /
RUN rm -rf \
    mysql-connector-cpp
