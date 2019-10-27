//
// Created by Wanghong Lin on 2019-10-25.
//

#ifndef CLIENT_ANDROID_USERSYSTEM_CLIENT_PROXY_H
#define CLIENT_ANDROID_USERSYSTEM_CLIENT_PROXY_H

#include "UserSystemClient.h"
#include <string>
#include <unordered_map>
#include <atomic>
#include <jni.h>
#include <android/log.h>

#define ALOGD(LOG_TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGE(LOG_TAG, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static constexpr auto TAG = "gRPCApp";

class UserSystemClientProxy {

public:
    static UserSystemClientProxy* getInstance() {
        if (_instance == nullptr) {
            _instance = new UserSystemClientProxy;
        }
        return _instance;
    }

    long newClient(JNIEnv* env, jobject callingObj, jstring host, jint port, jstring certificate);
    UserSystemClient* getClient(JNIEnv* env, jobject callingObj);

private:
    static UserSystemClientProxy* _instance;
    std::unordered_map<long, UserSystemClient*> _clients;
    std::mutex _mutex;
    std::atomic_long _handle;
};


#endif //CLIENT_ANDROID_USERSYSTEM_CLIENT_PROXY_H
