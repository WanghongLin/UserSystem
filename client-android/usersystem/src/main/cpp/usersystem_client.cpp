//
// Created by Wanghong Lin on 2019-10-25.
//

#include "usersystem_client.h"
#include "usersystem_client_proxy.h"

template<typename RESPONSE>
jbyteArray ToJByteArray(JNIEnv* env, const RESPONSE& response) {
    auto data = new jbyte[response.ByteSize()];
    response.SerializeToArray(data, response.ByteSize());

    auto array = env->NewByteArray(response.ByteSize());
    env->SetByteArrayRegion(array, 0, response.ByteSize(), data);
    delete[] data;

    return array;
}

extern "C" jlong Java_com_wanghong_grpc_usersystem_UserSystemNative_naInit(JNIEnv* env, jobject callingObj,
                                                                           jstring host, jint port,
                                                                           jstring certificate) {
    return UserSystemClientProxy::getInstance()->newClient(env, callingObj, host, port, certificate);
}

extern "C" jbyteArray
Java_com_wanghong_grpc_usersystem_UserSystemNative_naRegister(JNIEnv* env, jobject callingObj,
                                                              jstring username, jstring password,
                                                              jstring device_id, jint platform) {
    usersystem::RegisterResponse response;

    auto client = UserSystemClientProxy::getInstance()->getClient(env, callingObj);
    if (client != nullptr) {
        auto name = env->GetStringUTFChars(username, 0);
        auto pass = env->GetStringUTFChars(password, 0);
        auto device = env->GetStringUTFChars(device_id, 0);

        response = client->Register(name, pass, device, usersystem::Platform(platform));

        env->ReleaseStringUTFChars(username, name);
        env->ReleaseStringUTFChars(password, pass);
        env->ReleaseStringUTFChars(device_id, device);
    } else {
        response.mutable_response()->set_code(usersystem::ResponseCode::ERROR_ANDROID_JNI_CALL);
        response.mutable_response()->set_message("JNI Call Error: no client found");
    }

    return ToJByteArray(env, response);
}

extern "C" jbyteArray
Java_com_wanghong_grpc_usersystem_UserSystemNative_naLogin(JNIEnv* env, jobject callingObj,
                                                           jstring username, jstring password,
                                                           jstring device_id, jint platform) {
    usersystem::LoginResponse response;

    auto client = UserSystemClientProxy::getInstance()->getClient(env, callingObj);
    if (client) {
        auto name = env->GetStringUTFChars(username, 0);
        auto pass = env->GetStringUTFChars(password, 0);
        auto device = env->GetStringUTFChars(device_id, 0);

        response = client->Login(name, pass, device, usersystem::Platform(platform));

        env->ReleaseStringUTFChars(username, name);
        env->ReleaseStringUTFChars(password, pass);
        env->ReleaseStringUTFChars(device_id, device);
    } else {
        response.mutable_response()->set_code(usersystem::ResponseCode::ERROR_ANDROID_JNI_CALL);
        response.mutable_response()->set_message("JNI Call Error: no client found");
    }

    return ToJByteArray(env, response);
}

extern "C" jbyteArray
Java_com_wanghong_grpc_usersystem_UserSystemNative_naCheckLogin(JNIEnv* env, jobject callingObj,
                                                                jstring username, jstring token,
                                                                jstring device_id, jint platform) {
    usersystem::CheckLoginResponse response;

    auto client = UserSystemClientProxy::getInstance()->getClient(env, callingObj);
    if (client) {
        auto name = env->GetStringUTFChars(username, 0);
        auto tk = env->GetStringUTFChars(token, 0);
        auto id = env->GetStringUTFChars(device_id, 0);

        response = client->CheckLogin(name, tk, id, usersystem::Platform(platform));

        env->ReleaseStringUTFChars(username, name);
        env->ReleaseStringUTFChars(token, tk);
        env->ReleaseStringUTFChars(device_id, id);
    } else {
        response.mutable_response()->set_code(usersystem::ResponseCode::ERROR_ANDROID_JNI_CALL);
        response.mutable_response()->set_message("JNI Call Error: no client found");
    }

    return ToJByteArray(env, response);
}

extern "C" jbyteArray Java_com_wanghong_grpc_usersystem_UserSystemNative_naLogout(JNIEnv* env, jobject callingObj,
                                                                                  jstring username, jstring token) {
    usersystem::CommonResponse response;

    ALOGD(TAG, "%s", __PRETTY_FUNCTION__);
    auto client = UserSystemClientProxy::getInstance()->getClient(env, callingObj);
    if (client) {
        auto name = env->GetStringUTFChars(username, 0);
        auto tk = env->GetStringUTFChars(token, 0);
        response = client->Logout(name, tk);
        env->ReleaseStringUTFChars(username, name);
        env->ReleaseStringUTFChars(token, tk);
    } else {
        response.set_code(usersystem::ResponseCode::ERROR_ANDROID_JNI_CALL);
        response.set_message("JNI Call Error: no client found");
    }

    return ToJByteArray(env, response);
}

