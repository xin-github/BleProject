package com.pupupula.blelib.datas

import no.nordicsemi.android.ble.data.Data

/**
 * @author TuXin
 * @date 2019-07-24 18:52.
 *
 * Email : tuxin@pupupula.com
 */
abstract class AbsDeviceData : Data {
    abstract fun convertDataValueToParam()
    var isSendData = true
    var id = 0
    var dataValue: String? = null

    constructor()
    constructor(data: Data) {
        mValue = data.value
    }

    constructor(isSendData: Boolean, id: Int, dataValue: String?) {
        this.id = id
        this.isSendData = isSendData
        this.dataValue = dataValue

        val stringBuffer = StringBuffer()

        stringBuffer.append(integerToHexString(id))
            .append(if (dataValue.isNullOrEmpty()) "" else dataValue)
        mValue = hexStringToByteArray(stringBuffer.toString())
    }

    companion object {
        fun hexStringToByteArray(s: String): ByteArray {
            val len = s.length
            val data = ByteArray(len / 2)
            var i = 0
            while (i < len) {
                data[i / 2] =
                    ((Character.digit(s[i], 16) shl 4) + Character.digit(s[i + 1], 16)).toByte()
                i += 2
            }
            return data
        }

        fun integerToHexString(s: Int): String {
            var ss = Integer.toHexString(s)
            if (ss.length % 2 != 0) {
                ss = "0$ss"//0F格式
            }
            return ss.toUpperCase()
        }

    }
}