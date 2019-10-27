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

import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.content.ServiceConnection
import android.os.IBinder
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import com.wanghong.grpc.usersystem.UserSystemService
import com.wanghong.grpc.usersystem.proto.CommonResponse

/**
 * Created by wanghonglin on 2019-10-26 13:06.
 */
open class BaseActivity : AppCompatActivity() {

    protected lateinit var userSystemService: UserSystemService
    private var userSystemServiceBound = false

    private val connection = object : ServiceConnection {
        override fun onServiceDisconnected(name: ComponentName?) {
            userSystemServiceBound = false
        }

        override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
            val binder = service as UserSystemService.UserSystemBinder
            userSystemService = binder.getService()
            userSystemServiceBound = true
            onUserSystemServiceConnected()
        }
    }

    protected open fun onUserSystemServiceConnected() {

    }

    protected fun showErrorDialog(commonResponse: CommonResponse) {
        AlertDialog.Builder(this).setTitle(R.string.app_name)
            .setMessage(commonResponse.displayMessage())
            .setCancelable(true)
            .setPositiveButton(R.string.ok) { dialog, _ -> dialog?.dismiss() }
            .show()
    }

    override fun onStart() {
        super.onStart()
        Intent(this, UserSystemService::class.java).also {
            bindService(it, connection, Context.BIND_AUTO_CREATE)
        }
    }

    override fun onStop() {
        super.onStop()
        unbindService(connection)
        userSystemServiceBound = false
    }
}