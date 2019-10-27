# Copyright 2019 The gRPC Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# a modification version of https://github.com/grpc/grpc-docker-library/blob/master/1.21.0/cxx/Dockerfile
# add MySQL connectors cpp and bazel support

FROM debian:stretch

RUN apt-get update --fix-missing && apt-get install -y \
  build-essential autoconf libtool git pkg-config curl \
  automake libtool curl make g++ unzip cmake wget libssl-dev openjdk-8-jdk \
  && apt-get clean

# install protobuf first, then grpc
ENV GRPC_RELEASE_TAG v1.23.x
RUN git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc /var/local/git/grpc && \
    cd /var/local/git/grpc && \
    git submodule update --init && \
    echo "--- installing protobuf ---" && \
    cd third_party/protobuf && \
    git submodule update --init && \
    ./autogen.sh && ./configure --enable-shared && \
    make -j$(nproc) && make -j$(nproc) check && make install && make clean && ldconfig && \
    echo "--- installing grpc ---" && \
    cd /var/local/git/grpc && \
    make -j$(nproc) && make install && make clean && ldconfig && \
    rm -rf /var/local/git/grpc

RUN git clone https://github.com/mysql/mysql-connector-cpp.git /var/local/git/mysql-connector-cpp && \
    cd /var/local/git/mysql-connector-cpp && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . -- -j$(nproc) && \
    cmake --build . --target install -- -j$(nproc) && \
    ldconfig /usr/local/mysql/connector-c++-8.0/lib64 && \
    rm -rf /var/local/git/mysql-connector-cpp

RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | \
    tee /etc/apt/sources.list.d/bazel.list && curl https://bazel.build/bazel-release.pub.gpg | apt-key add - && \
    apt-get update && apt-get install -y bazel && \
    apt-get clean

RUN git clone https://github.com/WanghongLin/UserSystem /var/local/git/UserSystem && \
    cd /var/local/git/UserSystem && \
    mkdir build && \
    cd build && \
    cmake -DMYSQL_CONNECTOR=/usr/local/mysql/connector-c++-8.0 .. && \
    make server -j$(nproc)

CMD ["/var/local/git/UserSystem/build/server/server"]
