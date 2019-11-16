package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import no.nordicsemi.android.ble.callback.SuccessCallback

/**
 * @author TuXin
 * @date 2019-08-06 10:13.
 *
 * Email : tuxin@pupupula.com
 */
interface EnableIndicationDoneCallback : SuccessCallback {
    fun onEnableIndicationDone(device : BluetoothDevice)
    override fun onRequestCompleted(device: BluetoothDevice) {}
}