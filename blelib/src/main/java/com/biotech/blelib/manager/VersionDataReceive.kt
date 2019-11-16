package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import com.pupupula.blelib.datas.AbsDeviceData
import no.nordicsemi.android.ble.callback.DataSentCallback
import no.nordicsemi.android.ble.callback.profile.ProfileReadResponse
import no.nordicsemi.android.ble.data.Data

/**
 * @author TuXin
 * @date 2019-07-31 22:34.
 *
 * Email : tuxin@pupupula.com
 */
abstract class VersionDataReceive : ProfileReadResponse(), DataSentCallback, IDeviceDataReceive, IVersionRead{
    override fun onDataSent(device: BluetoothDevice, data: Data) {
        // do nothing here
    }

    override fun onDataReceived(device: BluetoothDevice, data: Data) {
        onVersionRead(device, data.getStringValue(0))
    }

    override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
        // do nothing here
    }

}