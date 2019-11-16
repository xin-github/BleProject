package com.pupupula.blelib.util

import android.content.Context
import com.biotech.commonlib.BaseApplication
import java.util.*

/**
 * @author TuXin
 * @date 2019-08-19 12:02.
 *
 * Email : tuxin@pupupula.com
 */
object BleConstant {
    const val SP_FILE_NAME = "ble_uuid"
    const val KEY_SERVICE = "key_service"
    const val KEY_READ = "key_read"
    const val KEY_WRITE = "key_write"

    private val SERVICE_UUID = UUID.fromString("0a10cb10-0000-0000-00cb-075582842602")

    private val READ_UUID = UUID.fromString("0A10CB11-0000-0000-00CB-075582842602")

    private val WRITE_UUID = UUID.fromString("0A10CB12-0000-0000-00CB-075582842602")

    fun getServiceUUID(): UUID {
        val service = BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .getString(KEY_SERVICE, "")
        return if (service.isNullOrEmpty()) {
            SERVICE_UUID
        } else {
            UUID.fromString(service)
        }
    }

    fun getReadUUID(): UUID {
        val service = BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .getString(KEY_READ, "")
        return if (service.isNullOrEmpty()) {
            READ_UUID
        } else {
            UUID.fromString(service)
        }
    }

    fun getWriteUUID(): UUID {
        val service = BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .getString(KEY_WRITE, "")
        return if (service.isNullOrEmpty()) {
            WRITE_UUID
        } else {
            UUID.fromString(service)
        }
    }

    fun setServiceUUID(ids: String) {
        BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .edit()
            .putString(KEY_SERVICE, ids)
            .apply()
    }

    fun setReadUUID(ids: String) {
        BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .edit()
            .putString(KEY_READ, ids)
            .apply()
    }

    fun setWriteUUID(ids: String) {
        BaseApplication.instance!!
            .getSharedPreferences(SP_FILE_NAME, Context.MODE_PRIVATE)
            .edit()
            .putString(KEY_WRITE, ids)
            .apply()
    }
}