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
import android.view.View
import android.widget.Toast
import com.wanghong.grpc.usersystem.UserSystemCallback
import com.wanghong.grpc.usersystem.proto.LoginResponse
import com.wanghong.grpc.usersystem.proto.Platform
import com.wanghong.grpc.usersystem.proto.ResponseCode
import kotlinx.android.synthetic.main.activity_login.*

class LoginActivity : BaseActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        loginGoToRegister.setOnClickListener {
            Intent(this@LoginActivity, RegisterActivity::class.java).also {
                startActivity(it)
                finish()
            }
        }

        loginButton.setOnClickListener {
            performLogin()
        }
    }

    private val userSystemCallback = object : UserSystemCallback {
        override fun onLogin(loginResponse: LoginResponse) {
            super.onLogin(loginResponse)
            hideProgressBar()

            if (loginResponse.response.code == ResponseCode.OK &&
                    loginResponse.token.isNotEmpty()) {
                application.saveUserAuthInfo(loginResponse.userModel.username,
                    loginResponse.userModel.id, loginResponse.token)
                MainActivity.start(this@LoginActivity)
                finish()
            } else {
                showErrorDialog(loginResponse.response)
            }
        }
    }

    override fun getProgressBar(): View? = loginProgressBar

    private fun performLogin() {
        val username = loginEditTextUsername.text.toString()
        val password = loginEditTextPassword.text.toString()
        if (username.isEmpty() || password.isEmpty()) {
            Toast.makeText(this, R.string.empty_username_password, Toast.LENGTH_LONG).show()
            return
        }

        userSystemService.login(username, password, application.getAndroidID(), Platform.Type_Android, userSystemCallback)
        showProgressBar()
    }

    companion object {
        fun start(activity: Activity) {
            Intent(activity, LoginActivity::class.java).also {
                activity.startActivity(it)
            }
        }
    }
}
