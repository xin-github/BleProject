package com.pupupula.blelib.datas

import no.nordicsemi.android.ble.data.Data

/**
 * @author TuXin
 * @date 2019-07-28 23:06.
 *
 * Email : tuxin@pupupula.com
 */
open class SimpleLightData : AbsDeviceData {
    constructor():super()
    constructor(data: Data) : super(data)
    constructor(isSendData: Boolean, id: Int, dataValue: String?) : super(isSendData, id, dataValue)

    override fun convertDataValueToParam() {

    }
}