#!/usr/bin/env bash

__ScriptVersion="0.0.1"

#===  FUNCTION  ================================================================
#         NAME:  usage
#  DESCRIPTION:  Display usage information.
#===============================================================================
function usage ()
{
    echo "Usage :  $0 [options] [--]

    Options:
    -h|help       Display this message
    -v|version    Display script version"

}    # ----------  end of function usage  ----------

#-----------------------------------------------------------------------
#  Handle command line arguments
#-----------------------------------------------------------------------

_use_bazel=
while getopts ":hvb" opt
do
  case $opt in

    h|help     )  usage; exit 0   ;;

    v|version  )  echo "$0 -- Version $__ScriptVersion"; exit 0   ;;
    b|bazel    )  _use_bazel=1 ;;

    * )  echo -e "\n  Option does not exist : $OPTARG\n"
	  usage; exit 1   ;;

  esac    # --- end of case ---
done
shift $(($OPTIND-1))

_project_root=$(pwd)

_with_ssl=
_ncpu=2

if [[ "$OSTYPE" == "linux-gnu" ]];then
    _ncpu=$(nproc)
    # linux docker we already have grpc and protobuf installed
    git -c submodule."grpc".update=none submodule update --init
elif [[ "$OSTYPE" == "darwin"* ]];then
    _with_ssl="-DWITH_SSL=`brew --prefix openssl`"
    _ncpu=$(sysctl -n hw.ncpu)

    cd ${_project_root}/grpc
    git submodule update --init --recursive
    LIBTOOL=glibtool LIBTOOLIZE=glibtoolize make prefix=`pwd`/out install -j8

    # build and install protobuf
    cd third_party/protobuf
    ./configure --prefix=`pwd`/../../out
    make -j8 install

    export PATH=${_project_root}/grpc/out/bin:$PATH
fi

# build mysql connector
cd ${_project_root}/mysql-connector-cpp && mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=`pwd`/out \
    ${_with_ssl} ..

cmake --build . --target install -- -j${_ncpu}

# build our application, server side
cd ${_project_root}
protoc -I. \
    --grpc_out=common --cpp_out=common \
    --java_out=lite:client-android/usersystem/src/main/java \
    --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` usersystem.proto

if [[ $_use_bazel == "1" ]];then
    bazel build //:server
else
    cd ${_project_root} && mkdir -p cmake-build
    cd cmake-build

    cmake -DMYSQL_CONNECTOR=${_project_root}/mysql-connector-cpp/build/out ..
    cmake --build . -- -j${_ncpu}
fi
