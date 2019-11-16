package com.pupupula.blelib.factory

import com.pupupula.blelib.datas.*
import no.nordicsemi.android.ble.data.Data

/**
 * @author TuXin
 * @date 2019-07-28 18:36.
 *
 * Email : tuxin@pupupula.com
 */
class LightDataFactory {
    companion object {

        fun createDeviceReceiveData(data: Data): AbsDeviceData? {
            return if (data.value != null) {
                // todo:根据协议解析具体的值
//                // first byte == DA
//                val idStr = String.format("%02x", data.value!![1])
//                val id = Integer.parseInt(idStr, 16)
//
//                val stringBuffer = StringBuffer()
//                for (i in 2..5) {
//                    stringBuffer.append(String.format("%02x", data.value!![i]))
//                }
//
//                val kid = java.lang.Long.parseLong(stringBuffer.toString(), 16)
//
//                stringBuffer.delete(0, stringBuffer.length)
//
//                if (data.value!!.size > 6) {
//                    for (i in 6 until data.value!!.size) {
//                        stringBuffer.append(String.format("%02x", data.value!![i]))
//                    }
//                }
//                var dataValue = ""
//                if (stringBuffer.isNotEmpty()) {
//                    dataValue = stringBuffer.toString()
//                }

                return when {
                    //                    AbsDeviceData.ID_SET_KID -> {
                    //                        createSetKidData(kid, false)
                    //                    }
                    else -> {
                        SimpleLightData(data)
                    }
                }
            } else {
                null
            }
        }
    }
}