package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice

/**
 * @author TuXin
 * @date 2019-08-01 09:37.
 *
 * Email : tuxin@pupupula.com
 */
interface IVersionRead {
    fun onVersionRead(device: BluetoothDevice, version: String?)
}