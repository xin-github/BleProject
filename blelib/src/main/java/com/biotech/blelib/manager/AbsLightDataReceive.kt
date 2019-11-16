package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import android.util.Log
import com.pupupula.blelib.factory.LightDataFactory
import no.nordicsemi.android.ble.callback.DataSentCallback
import no.nordicsemi.android.ble.callback.profile.ProfileReadResponse
import no.nordicsemi.android.ble.data.Data

/**
 * @author TuXin
 * @date 2019-07-22 16:35.
 *
 * Email : tuxin@pupupula.com
 */
abstract class AbsLightDataReceive : ProfileReadResponse(), DataSentCallback, IDeviceDataReceive {
    override fun onDataReceived(device: BluetoothDevice, data: Data) {
        val convertData = LightDataFactory.createDeviceReceiveData(data)
        if (convertData != null) {
            onLightDataReceive(device, convertData)
        }
        Log.d("DataReceive","onDataReceived device = $device data = $convertData original data = $data")

    }

    override fun onDataSent(device: BluetoothDevice, data: Data) {
        val convertData = LightDataFactory.createDeviceReceiveData(data)
        Log.d("DataReceive","onDataSent device = $device data = $convertData original data = $data")

    }

    private fun parse(device: BluetoothDevice, data: Data) {

    }
}