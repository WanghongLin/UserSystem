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

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.provider.Settings
import android.view.View
import androidx.appcompat.app.AlertDialog
import com.wanghong.grpc.usersystem.UserSystemCallback
import com.wanghong.grpc.usersystem.proto.CheckLoginResponse
import com.wanghong.grpc.usersystem.proto.CommonResponse
import com.wanghong.grpc.usersystem.proto.Platform
import com.wanghong.grpc.usersystem.proto.ResponseCode
import kotlinx.android.synthetic.main.activity_main.*


class MainActivity : BaseActivity() {

    private var manuallyLogout = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        mainButtonLogout.setOnClickListener { performLogout() }

        val token = application.getUserPreference().getString(PREF_KEY_TOKEN, "")
        val username = application.getUserPreference().getString(PREF_KEY_USERNAME, "")
        if (token == null || token.isEmpty() || username == null || username.isEmpty()) {
            LoginActivity.start(this)
            finish()
        }
    }

    override fun onUserSystemServiceConnected() {
        super.onUserSystemServiceConnected()

        // FIXME: better put to background threads
        val token = application.getUserPreference().getString(PREF_KEY_TOKEN, "")
        val username = application.getUserPreference().getString(PREF_KEY_USERNAME, "")
        val userID = application.getUserPreference().getString(PREF_KEY_USER_ID, "")
        val androidID = Settings.Secure.getString(contentResolver, Settings.Secure.ANDROID_ID)

        if (token == null || token.isEmpty() || username == null || username.isEmpty()) {
            LoginActivity.start(this)
            finish()
        } else {
            mainTextUsername.text = username
            mainTextUserID.text = userID
            mainTextAndroidID.text = androidID
            mainTextToken.text = token

            userSystemService.checkLogin(username, token, androidID, Platform.Type_Android, userSystemCallback)
        }
    }

    private val userSystemCallback = object : UserSystemCallback {
        override fun onCheckLogin(checkLoginResponse: CheckLoginResponse) {
            super.onCheckLogin(checkLoginResponse)
            if (checkLoginResponse.response.code == ResponseCode.ERROR_LOGIN_STATUS_INVALID
                && !manuallyLogout) {
                application.clearUserAuthInfo()
                AlertDialog.Builder(this@MainActivity)
                    .setTitle(R.string.app_name)
                    .setMessage(R.string.login_from_other_device)
                    .setPositiveButton(R.string.ok) { dialog, _ -> dialog?.dismiss() }
                    .setOnDismissListener {
                        LoginActivity.start(this@MainActivity)
                        finish()
                    }
                    .setCancelable(false)
                    .show()
            }
        }

        override fun onLogout(commonResponse: CommonResponse) {
            super.onLogout(commonResponse)
            hideProgressBar()
            if (commonResponse.code == ResponseCode.OK) {
                application.clearUserAuthInfo()
                LoginActivity.start(this@MainActivity)
            } else {
                showErrorDialog(commonResponse)
            }
        }
    }

    override fun getProgressBar(): View? = mainProgressBar

    private fun performLogout() {
        manuallyLogout = true
        userSystemService.logout(application.getUserPreference().getString(PREF_KEY_USERNAME, ""), userSystemCallback)
        showProgressBar()
    }

    companion object {
        fun start(launchFromActivity: Activity) {
            Intent(launchFromActivity, MainActivity::class.java).also {
                launchFromActivity.startActivity(it)
            }
        }
    }
}
