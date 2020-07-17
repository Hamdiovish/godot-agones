#!/bin/bash

wget https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/protobuf-all-3.6.1.zip && \
unzip -d . protobuf-all-3.6.1.zip && \
cd protobuf-3.6.1 && \ 
echo "--- installing protobuf ---" && \
./autogen.sh && ./configure --disable-shared --enable-static --with-pic --prefix=/root/tmp/protobuf-3.6.1/out && \
make -j4 && make install
