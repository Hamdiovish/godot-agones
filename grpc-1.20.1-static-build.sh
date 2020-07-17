#!/bin/bash

git clone -b v1.20.1 --depth=5 https://github.com/grpc/grpc && \
cd grpc && \
git submodule update --init && \
echo "--- installing protobuf ---" && \
cd third_party/protobuf && \
./autogen.sh && ./configure --enable-static --with-pic --prefix=/root/tmp/protobuf && \
make -j6 && make install && \
export CFLAGS=-Wno-error && export CXXFLAGS=-Wno-error && \
echo "--- installing grpc ---" && \
cd .. && \
cd .. && \
make -j4 && make install && make clean && ldconfig
