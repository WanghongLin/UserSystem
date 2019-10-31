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

package com.wanghong.grpc.usersystem

import android.app.Service
import android.content.Intent
import android.os.*
import com.wanghong.grpc.usersystem.proto.*

interface UserSystemCallback {
    fun onConnected() {}
    fun onRegistered(registerResponse: RegisterResponse) {}
    fun onLogin(loginResponse: LoginResponse) {}
    fun onCheckLogin(checkLoginResponse: CheckLoginResponse) {}
    fun onLogout(commonResponse: CommonResponse) {}
}

class UserSystemService : Service() {

    private var serviceHandlerThread: HandlerThread = HandlerThread("user_system_service_thread").also { it.start() }
    private var checkLoginHandlerThread: HandlerThread = HandlerThread("check_login_thread").also { it.start() }
    private lateinit var userSystemNative: UserSystemNative

    private val userSystemBinder = UserSystemBinder()

    init {
        connect("192.168.43.27", 50051, "");
    }

    override fun onBind(intent: Intent): IBinder = userSystemBinder

    private fun connect(host: String, port: Int, certificate: String) {
        if (!::userSystemNative.isInitialized) {
            userSystemNative = UserSystemNative.createClient(host, port, certificate)
        }
    }

    fun isConnected() = ::userSystemNative.isInitialized

    fun register(username: String, password: String, deviceId: String, platform: Platform, userSystemCallback: UserSystemCallback) {
        Handler(serviceHandlerThread.looper).post {
            val registerResponse = userSystemNative.register(username, password, deviceId, platform.ordinal)
            Handler(Looper.getMainLooper()).post {
                userSystemCallback.onRegistered(registerResponse)
            }
        }
    }

    fun login(username: String, password: String, deviceId: String, platform: Platform, userSystemCallback: UserSystemCallback) {
        Handler(serviceHandlerThread.looper).post {
            val loginResponse = userSystemNative.login(username, password, deviceId, platform.ordinal)
            Handler(Looper.getMainLooper()).post {
                userSystemCallback.onLogin(loginResponse)
            }
        }
    }

    fun checkLogin(username: String, token: String, deviceId: String, platform: Platform, userSystemCallback: UserSystemCallback) {
        Handler(checkLoginHandlerThread.looper).post {
            val checkLoginResponse = userSystemNative.checkLogin(username, token, deviceId, platform.ordinal)
            Handler(Looper.getMainLooper()).post {
                userSystemCallback.onCheckLogin(checkLoginResponse)
            }
        }
    }

    fun logout(username: String, token: String, userSystemCallback: UserSystemCallback) {
        Handler(serviceHandlerThread.looper).post {
            val commonResponse = userSystemNative.logout(username, token)
            Handler(Looper.getMainLooper()).post {
                userSystemCallback.onLogout(commonResponse)
            }
        }
    }

    inner class UserSystemBinder : Binder() {
        fun getService(): UserSystemService {
            return this@UserSystemService
        }
    }
}
