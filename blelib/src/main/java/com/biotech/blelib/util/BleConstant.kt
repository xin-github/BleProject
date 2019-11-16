package com.pupupula.blelib.util

import java.util.*

/**
 * @author TuXin
 * @date 2019-08-19 12:02.
 *
 * Email : tuxin@pupupula.com
 */
object BleConstant {
    val SERVICE_UUID = UUID.fromString("0a10cb10-0000-0000-00cb-075582842602")

    val READ_UUID = UUID.fromString("0A10CB11-0000-0000-00CB-075582842602")

    val WRITE_UUID = UUID.fromString("0A10CB12-0000-0000-00CB-075582842602")

    val VERSION_SERVICE_UUID = UUID.fromString("0000180a-0000-1000-8000-00805f9b34fb")
    val VERSION_UUID = UUID.fromString("00002a26-0000-1000-8000-00805f9b34fb")
}