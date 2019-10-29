#!/usr/bin/env bash

_project_root=$(pwd)

# build mysql connector
git submodule update --init

_with_ssl=
_ncpu=2

if [[ "$OSTYPE" == "linux-gnu" ]];then
    _ncpu=$(nproc)
elif [[ "$OSTYPE" == "darwin"* ]];then
    _with_ssl="-DWITH_SSL=`brew --prefix`/Cellar/openssl/1.0.2s .."
    _ncpu=$(sysctl -n hw.ncpu)
fi

cd ${_project_root}/mysql-connector-cpp

cmake -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=`pwd`/out \
    ${_with_ssl}

cmake --build . --target install -- -j${_ncpu}

# build our application, server side
cd ${_project_root} && mkdir cmake-build && cd cmake-build && \
    cmake -DMYSQL_CONNECTOR=${_project_root}/mysql-connector-cpp/build/out .. && \
    cmake --build . -- -j${_ncpu}
