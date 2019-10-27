//
// Created by Wanghong Lin on 2019-10-25.
//

#include "usersystem_client_proxy.h"

UserSystemClientProxy* UserSystemClientProxy::_instance = nullptr;

long UserSystemClientProxy::newClient(JNIEnv* env, jobject callingObj, jstring host, jint port,
                                      jstring certificate) {
    const char* hostName = env->GetStringUTFChars(host, 0);
    const char* cert = env->GetStringUTFChars(certificate, 0);

    std::string target = std::string(hostName) + ':' + std::to_string(port);

    grpc::SslCredentialsOptions credentialsOptions;
    credentialsOptions.pem_root_certs = std::string(cert);

    ALOGD(TAG, "New client for target %s", target.c_str());
    auto client = new UserSystemClient(
            grpc::CreateChannel(target, /*grpc::SslCredentials(credentialsOptions)*/ grpc::InsecureChannelCredentials())
    );

    auto handle = _handle++;
    std::unique_lock<std::mutex> lck(_mutex);
    _clients[handle] = client;
    lck.unlock();

    env->ReleaseStringUTFChars(host, hostName);
    env->ReleaseStringUTFChars(certificate, cert);
    return handle;
}

UserSystemClient* UserSystemClientProxy::getClient(JNIEnv *env, jobject callingObj) {
    auto clz = env->GetObjectClass(callingObj);
    if (!clz) {
        return nullptr;
    }
    auto field = env->GetFieldID(clz, "nativeHandleID", "J");
    if (!field) {
        return nullptr;
    }

    auto handle = env->GetLongField(callingObj, field);
    std::lock_guard<std::mutex> lck(_mutex);
    auto client = _clients.find(handle);
    if (client == _clients.end()) {
        ALOGE(TAG, "No client found for %ld", handle);
        return nullptr;
    }
    return client->second;
}
