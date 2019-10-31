/*
 * Copyright 2019 wanghonglin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Created by wanghonglin on 2019-10-25 09:49.
 */

package com.wanghong.grpc.usersystem

import com.wanghong.grpc.usersystem.proto.*

private const val CERTIFICATE = "-----BEGIN CERTIFICATE-----\n" +
        "MIIDYjCCAkoCCQDV3wW+0eb8yDANBgkqhkiG9w0BAQsFADBzMQswCQYDVQQGEwJD\n" +
        "TjESMBAGA1UECAwJR3Vhbmdkb25nMREwDwYDVQQHDAhTaGVuemhlbjESMBAGA1UE\n" +
        "CgwJTXlDb21wYW55MRUwEwYDVQQLDAxNeURlcGFydG1lbnQxEjAQBgNVBAMMCWxv\n" +
        "Y2FsaG9zdDAeFw0xOTEwMjMwMjQ0MzZaFw0yMDEwMjIwMjQ0MzZaMHMxCzAJBgNV\n" +
        "BAYTAkNOMRIwEAYDVQQIDAlHdWFuZ2RvbmcxETAPBgNVBAcMCFNoZW56aGVuMRIw\n" +
        "EAYDVQQKDAlNeUNvbXBhbnkxFTATBgNVBAsMDE15RGVwYXJ0bWVudDESMBAGA1UE\n" +
        "AwwJbG9jYWxob3N0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy3vs\n" +
        "3ad/oZjaQ5UbNyhB+US0ZoSjFDZYi0Dh9zmZvAlu+rvAVVssOGMldX6IESS4IEit\n" +
        "gNToPLaFX7s4/4yPyRELxAyFs08C1Sxv3Ka391xwzEot21Q9qfZ4+KsFp4nbAAWi\n" +
        "zqMqLCQfxIcXzhkqzQmdJUCZCXPmXbQW0YervmNH4l2o4PPwHmvCGGSaGxalEVGi\n" +
        "18+fIHflqMdYztoeycms5PEICMg4SczqB36emYp47sJcbmCWpdYSXBzttWgk0CKY\n" +
        "gvWc9LLpGj9tgeywDRrrqyCYQK8+4847SSfws6Q38VzZ91uKxric9Q70cyGo3o0E\n" +
        "RsIEYbmViq2HqabaIwIDAQABMA0GCSqGSIb3DQEBCwUAA4IBAQCjSQzPB3NuuIxW\n" +
        "OmVGfjXAWSqKueoszeqA9NBpuIKngQVRE0zBOA1lPGwP5Yo23Xb43SXgIE7sKwKI\n" +
        "NqeYaNKPO9yzqEEua6iTgYDaxwVY84FRT7Qya3d9jlf8gRKRFFiby4h/SOQkGuoo\n" +
        "SL+88RkDGjYdssUpm2/EC6QgJD94rDic5/nmCWUVvLSCnKbObf4pTHRsWyhvfUjI\n" +
        "n9rKUlpQvdLaF4W6USEx58xDPcm2vX/3FSx1eZ+E+c8NMTo4a0B4F8G88rZ9E7Gj\n" +
        "E+F7JWwE/NY93GoDP1/zllJc+QPKhAR7TEKFT9h2yvxGDU4Rv6ZTUDB53I/Exq3x\n" +
        "ZbCrPrna\n" +
        "-----END CERTIFICATE-----"

class UserSystemNative private constructor() {
    init {
        System.loadLibrary("usersystem_client")
    }

    companion object {
        /**
         * Create a client to host/port with pem ssl certificate
         * @param host host name
         * @param port port number
         * @param certificate ssl certificate
         *
         * @return a [UserSystemNative] client
         */
        fun createClient(host: String = "localhost", port: Int = 50051, certificate: String = CERTIFICATE) = UserSystemNative().also {
            it.nativeHandleID = it.naInit(host, port, if (certificate.isEmpty()) CERTIFICATE else certificate)
        }
    }

    private var nativeHandleID : Long = 0
    private external fun naInit(host: String, port: Int, certificate: String): Long
    private external fun naRegister(username: String, password: String, deviceId: String, platform: Int): ByteArray
    private external fun naLogin(username: String, password: String, deviceId: String, platform: Int): ByteArray
    private external fun naCheckLogin(username: String, token: String, deviceId: String, platform: Int): ByteArray
    private external fun naLogout(username: String, token: String): ByteArray

    /**
     * Call gRPC to register
     * @param username the username, can not empty
     * @param password the password, can not empty
     *
     * @return a register response [RegisterResponse]
     */
    fun register(username: String, password: String, deviceId: String, platform: Int) = RegisterResponse.parseFrom(naRegister(username, password, deviceId, platform))
    /**
     * Call gRPC to login
     * @param username username
     * @param password password
     * @param deviceId the device id, usually android id
     * @param platform one of value from [Platform]
     */
    fun login(username: String, password: String, deviceId: String, platform: Int) = LoginResponse.parseFrom(naLogin(username, password, deviceId, platform))

    /**
     * Call gRPC to check login status, this call will be blocked if current login is valid
     * client can wait for login event from other device in blocked call
     *
     * @param username username
     * @param token current login JWT token
     * @param deviceId device id
     * @param platform one of value from [Platform]
     */
    fun checkLogin(username: String, token: String, deviceId: String, platform: Int) = CheckLoginResponse.parseFrom(naCheckLogin(username, token, deviceId, platform))

    fun logout(username: String, token: String) = CommonResponse.parseFrom(naLogout(username, token))
}