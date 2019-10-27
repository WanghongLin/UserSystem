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

package com.wanghong.grpc

import android.app.Application
import android.content.Context
import android.content.SharedPreferences
import android.provider.Settings
import androidx.core.content.edit
import com.wanghong.grpc.usersystem.proto.CommonResponse

/**
 * Created by wanghonglin on 2019-10-26 12:48.
 */

const val PREF_NAME_USER = "pref_user"
const val PREF_KEY_USERNAME = "pref_key_username"
const val PREF_KEY_USER_ID = "pref_key_user_id"
const val PREF_KEY_TOKEN = "pref_key_token"
const val GLOBAL_TAG = "gRPCApp"

fun Application.getUserPreference(): SharedPreferences = this.getSharedPreferences(PREF_NAME_USER, Context.MODE_PRIVATE)

fun Application.saveUserAuthInfo(username: String, userId: String, token: String) {
    getUserPreference().edit {
        putString(PREF_KEY_USERNAME, username)
        putString(PREF_KEY_USER_ID, userId)
        putString(PREF_KEY_TOKEN, token)
    }
}

fun Application.clearUserAuthInfo() {
    getUserPreference().edit {
        remove(PREF_KEY_USERNAME)
        remove(PREF_KEY_USER_ID)
        remove(PREF_KEY_TOKEN)
    }
}

fun Application.getAndroidID(): String {
    return Settings.Secure.getString(this.contentResolver, Settings.Secure.ANDROID_ID)
}

fun CommonResponse.displayMessage(): String {
    return "${this.code}: ${this.message}\n" +
            "gRPC ${this.grpcErrorCode}: ${this.grpcErrorMessage} ${this.grpcErrorDetails}"
}
