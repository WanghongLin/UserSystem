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

import android.content.DialogInterface
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import com.wanghong.grpc.usersystem.UserSystemCallback
import com.wanghong.grpc.usersystem.proto.Platform
import com.wanghong.grpc.usersystem.proto.RegisterResponse
import com.wanghong.grpc.usersystem.proto.ResponseCode
import kotlinx.android.synthetic.main.activity_register.*

class RegisterActivity : BaseActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)

        registerGoToLogin.setOnClickListener {
            LoginActivity.start(this)
        }

        registerButtonSingUp.setOnClickListener {
            performRegister()
        }
    }

    private val userSystemCallback = object : UserSystemCallback {
        override fun onRegistered(registerResponse: RegisterResponse) {
            super.onRegistered(registerResponse)
            if (registerResponse.response.code == ResponseCode.OK && registerResponse.token.isNotEmpty()) {
                application.saveUserAuthInfo(registerResponse.userModel.username, registerResponse.userModel.id, registerResponse.token)
                MainActivity.start(this@RegisterActivity)
                finish()
            } else {
                showErrorDialog(registerResponse.response)
            }

            registerProgressBar.visibility = View.GONE
        }
    }

    private fun performRegister() {
        val username = registerEditTextUsername.text.toString()
        val password = registerEditTextPassword.text.toString()
        val confirmPassword = registerEditTextConfirmPassword.text.toString()

        if (username.isEmpty() || password.isEmpty()) {
            Toast.makeText(this, R.string.empty_username_password, Toast.LENGTH_LONG).show()
            return
        }
        if (confirmPassword != password) {
            Toast.makeText(this, R.string.password_did_not_match, Toast.LENGTH_LONG).show()
            return
        }

        registerProgressBar.visibility = View.VISIBLE
        userSystemService.register(username, password, application.getAndroidID(), Platform.Type_Android, userSystemCallback)
    }
}
