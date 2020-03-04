package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice
import com.biotech.commonlib.BaseApplication
import com.pupupula.blelib.datas.AbsDeviceData

/**
 * @author TuXin
 * @date 2019-07-22 17:17.
 *
 * Email : tuxin@pupupula.com
 */
class DevicesManager private constructor() : BleManagerCallbacksAdapter(), IDevicesManager,
    EnableIndicationDoneCallback {
    val mReceiveCallbacks = ArrayList<IDeviceDataReceive>()
    val mEnableIndicationDoneCallback = ArrayList<EnableIndicationDoneCallback>()
    val mBleManagerCallbacksAdapters = ArrayList<BleManagerCallbacksAdapter>()
    private val mLightDeviceManagerMap = HashMap<DiscoveredBluetoothDevice, SingleDeviceManager>()

    override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
        mReceiveCallbacks.forEach {
            // todo: convert to light data
            it.onLightDataReceive(device, data)
        }
    }

    fun registerReceiveCallback(callback: IDeviceDataReceive) {
        if (!mReceiveCallbacks.contains(callback)) {
            mReceiveCallbacks.add(callback)
        }
    }

    fun unregisterReceiveCallback(callback: IDeviceDataReceive) {
        mReceiveCallbacks.remove(callback)
    }

    fun registerEnableIndicationDone(callback: EnableIndicationDoneCallback) {
        if (!mEnableIndicationDoneCallback.contains(callback)) {
            mEnableIndicationDoneCallback.add(callback)
        }
    }

    fun unregisterEnableIndicationDone(callback: EnableIndicationDoneCallback) {
        mEnableIndicationDoneCallback.remove(callback)
    }

    fun registerBleManagerCallbacksAdapter(adapter: BleManagerCallbacksAdapter) {
        if (!mBleManagerCallbacksAdapters.contains(adapter)) {
            mBleManagerCallbacksAdapters.add(adapter)
        }
    }

    fun unregisterBleManagerCallbacksAdapter(adapter: BleManagerCallbacksAdapter) {
        mBleManagerCallbacksAdapters.remove(adapter)
    }

    override fun onEnableIndicationDone(device: BluetoothDevice) {
        mEnableIndicationDoneCallback.forEach {
            it.onEnableIndicationDone(device)
        }
    }

    override fun onConnectStateChange(device: BluetoothDevice, connectState: Int) {
        mBleManagerCallbacksAdapters.forEach {
            it.onConnectStateChange(device, connectState)
        }
    }

    override fun onDeviceNotSupported(device: BluetoothDevice) {
        mBleManagerCallbacksAdapters.forEach {
            it.onDeviceNotSupported(device)
        }
    }

    override fun onError(device: BluetoothDevice, message: String, errorCode: Int) {
        mBleManagerCallbacksAdapters.forEach {
            it.onError(device, message, errorCode)
        }
    }

    private fun findDiscoveredBluetoothDevice(device: BluetoothDevice): DiscoveredBluetoothDevice? {
        val keys = mLightDeviceManagerMap.keys
        return keys.find {
            device == it.device
        }
    }

    fun getAllDevices(): List<DiscoveredBluetoothDevice> {
        return mLightDeviceManagerMap.keys.toList()
    }

    fun getAllConnectedDevices(): List<DiscoveredBluetoothDevice> {
        return mLightDeviceManagerMap.keys.filter {
            isDeviceConnected(it)
        }
    }

    fun findDiscoveredBluetoothDevice(address: String): DiscoveredBluetoothDevice? {
        val keys = mLightDeviceManagerMap.keys
        return keys.find {
            address.toLowerCase() == it.device?.address?.toLowerCase()
        }
    }

    fun isDeviceConnected(device: DiscoveredBluetoothDevice?): Boolean {
        val manager = mLightDeviceManagerMap[device]
        if (device == null || manager == null) {
            return false
        }
        return manager.isConnected
    }

    fun setDevice(device: DiscoveredBluetoothDevice?) {
        if (device == null) return
        if (!mLightDeviceManagerMap.containsKey(device)) {
            val manager = SingleDeviceManager(
                BaseApplication.instance!!,
                this,
                this
            )

            mLightDeviceManagerMap[device] = manager
            manager.setGattCallbacks(this)
        }
    }

    fun setDevice(
        device: DiscoveredBluetoothDevice, receiveCallback: IDeviceDataReceive,
        enableIndicationDone: EnableIndicationDoneCallback
    ) {

        if (!mLightDeviceManagerMap.containsKey(device)) {

            registerReceiveCallback(receiveCallback)
            registerEnableIndicationDone(enableIndicationDone)

            val manager = SingleDeviceManager(
                BaseApplication.instance!!,
                this,
                this
            )

            mLightDeviceManagerMap[device] = manager
            manager.setGattCallbacks(this)
        }
    }

    fun isDeviceExists(device: DiscoveredBluetoothDevice): Boolean {
        return mLightDeviceManagerMap.containsKey(device)
    }

    fun connect(device: DiscoveredBluetoothDevice) {
        connect(device, 3, 100)
    }

    fun connect(device: DiscoveredBluetoothDevice, retryTime: Int, delay: Int) {
        if (device.device != null && mLightDeviceManagerMap.containsKey(device)) {
            internalConnect(device.device!!, mLightDeviceManagerMap[device]!!, retryTime, delay)
        }
    }

    fun isConnected(device: DiscoveredBluetoothDevice): Boolean {
        return mLightDeviceManagerMap[device]?.isConnected == true
    }

    fun sendLightData(
        lightData: AbsDeviceData, device: DiscoveredBluetoothDevice?,
        delayToDequeNext: Long = 0
    ) {
        if (device?.device != null && mLightDeviceManagerMap.containsKey(device)) {
            mLightDeviceManagerMap[device]!!.sendLightData(lightData, delayToDequeNext)
        }
    }

    fun clearAllDevices() {
        val keys = mLightDeviceManagerMap.keys
        keys.forEach {
            mLightDeviceManagerMap[it]?.disconnect()?.enqueue()
        }

        mReceiveCallbacks.clear()
        mBleManagerCallbacksAdapters.clear()
        mEnableIndicationDoneCallback.clear()
        mLightDeviceManagerMap.clear()
    }

    fun disconnect(device: DiscoveredBluetoothDevice?) {
        if (device?.device != null && mLightDeviceManagerMap.containsKey(device)) {

            mLightDeviceManagerMap[device]?.disconnect()?.enqueue()
            mLightDeviceManagerMap.remove(device)
        }
    }

    private fun internalConnect(
        device: BluetoothDevice,
        deviceManager: SingleDeviceManager,
        retryTime: Int,
        delay: Int
    ) {
        deviceManager.connect(device)
            .retry(retryTime, delay)
            .useAutoConnect(false)
            .enqueue()
    }

    companion object {
        val instance = InnerClass.HOLDER
    }

    private object InnerClass {
        val HOLDER = DevicesManager()
    }
}