Cross platform user login system based on gRPC
======

A user register/login system based on gRPC C++, the client also implement in C++ and Android/iOS can share a same code base.

Just a simple demo application, including the following features

* user register
* user login
* user logout
* client can received logout event if the same user login from a different new device
* sensitive data is protected by `sslserver`/`sslchannel` only if client connect to server by hostname, fallback to `insecureserver`/`insecurechannel` if client connect to server by IP address which means the system is vulnerable 
* use mysql and mysqlx api for data persistence

Quick Guide
------
For server deployment, just run
```
docker-compose up
```

Server setup
------

Android setup
------
In order to make `SerializeToByte` in C++ and `parseFrom(byte array)` in Java works, the protobuf format type

should keep the same, both should use `protobuf` or `protobuf-lite`. For android, add protoc command option 

`--java_out=lite:${OUTPUT_DIR}` and `optimize_for = LITE_RUNTIME` declaration option to make both C++ and Java 
use the lite version.

Build `grpc++` for android `arm64-v8a`, and use the following command to copy all static archives
to android studio project.

```bash
$ find . -name "*.a" -exec cp {} /path/to/android/project/usersystem/libs/arm64-v8a/ \;
```

The order of prebuilt static library when adding to android project, `libgpr`/`libssl`/`libcrypto` should place
after `libgrpc++` and `libgrpc`, otherwise the linker will report strange symbols undefined error.

Build android project, and use the following command to generate necessary JNI binding

```bash
$ javah -o usersystem/src/main/cpp/usersystem_client.h \
    -classpath usersystem/build/tmp/kotlin-classes/debug \
    com.wanghong.grpc.usersystem.UserSystemNative
``` 

Reference
------
* [Generating a self-signed certificate using OpenSSL](https://www.ibm.com/support/knowledgecenter/en/SSMNED_5.0.0/com.ibm.apic.cmc.doc/task_apionprem_gernerate_self_signed_openSSL.html)
* [How to create a self-signed certificate with OpenSSL](https://stackoverflow.com/questions/10175812/how-to-create-a-self-signed-certificate-with-openssl)

##### MySQL Reference
* [MySQL Connector C++ in Github](https://github.com/mysql/mysql-connector-cpp)
* [Install MySQL Connector C++ in Ubuntu](https://stackoverflow.com/questions/51117349/cannot-install-mysql-connector-c-correctly-in-my-ubuntu)
* [MySQL Connector/C++ 8.0 Developer Guide](https://dev.mysql.com/doc/connector-cpp/8.0/en/)
* [MySQL Connector/C++ Documentation](https://dev.mysql.com/doc/dev/connector-cpp/8.0/)
* [Working with documents](https://docs.oracle.com/cd/E17952_01/x-devapi-userguide-en/devapi-users-working-with-documents.html)

##### Android Reference
* [Build gRPC C++ for Android](https://stackoverflow.com/questions/54052229/build-grpc-c-for-android-using-ndk-arm-linux-androideabi-clang-compiler)
* [Protobuf Java lite](https://github.com/protocolbuffers/protobuf/blob/master/java/lite.md)
* [Connect gRPC ssl server with IP address error](https://blog.csdn.net/u011627161/article/details/87936361)
* [gRPC server ssl with IP error](https://zhuanlan.zhihu.com/p/35507832)