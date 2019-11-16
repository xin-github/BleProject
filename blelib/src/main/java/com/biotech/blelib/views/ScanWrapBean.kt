package com.pupupula.blelib.views

import com.biotech.blelib.adapter.DiscoveredBluetoothDevice

/**
 * Created by lsy
 * on 2019/6/5
 */
data class ScanWrapBean(
        var discoveredDevice: DiscoveredBluetoothDevice,
        var rssi: Int,
        var scanRecord: ByteArray,
        var allName: String
)