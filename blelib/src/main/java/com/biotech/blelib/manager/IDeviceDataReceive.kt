package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import com.pupupula.blelib.datas.AbsDeviceData

/**
 * @author TuXin
 * @date 2019-07-22 16:27.
 *
 * Email : tuxin@pupupula.com
 */
interface IDeviceDataReceive{
    // todo: change data class
    fun onLightDataReceive(device : BluetoothDevice, data: AbsDeviceData)
}