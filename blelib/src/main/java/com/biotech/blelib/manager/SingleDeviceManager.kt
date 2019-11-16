package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothGattService
import android.content.Context
import android.util.Log
import com.pupupula.blelib.datas.AbsDeviceData
import com.pupupula.blelib.util.BleConstant
import io.reactivex.Observable
import io.reactivex.disposables.Disposable
import no.nordicsemi.android.ble.BleManager
import java.util.*
import java.util.concurrent.TimeUnit

/**
 * @author TuXin
 * @date 2019-07-19 16:29.
 *
 * Email : tuxin@pupupula.com
 */
class SingleDeviceManager(context: Context,
                          var receiveCallback: IDeviceDataReceive?,
                          var enableIndicationDoneCallback: EnableIndicationDoneCallback?)
    : BleManager<IDevicesManager>(context) {

    private var mDeviceReadCharacteristic: BluetoothGattCharacteristic? = null
    private var mDeviceWriteCharacteristic: BluetoothGattCharacteristic? = null
    private val mQueue = Collections.synchronizedList(LinkedList<Pair<Long, ByteArray>?>())
    private var mTimer: Disposable? = null

    @Volatile
    private var mTiming = false

    var mSupport = false
    private val mGattCallback = object : BleManagerGattCallback() {
        override fun initialize() {
            if (isConnected) {
                setIndicationCallback(mDeviceReadCharacteristic)
                        .with(mReadDataCallback)

                enableIndications(mDeviceReadCharacteristic)
                        .done {
                            enableIndicationDoneCallback?.onEnableIndicationDone(it)
                            Log.d(SingleDeviceManager::javaClass.name,"enableNotifications notifications enable")
                        }
                        .fail { _, code ->
                            Log.d(SingleDeviceManager::javaClass.name,"enableNotifications fail, fail code = $code")
                        }
                        .enqueue()
            }
        }

        override fun onDeviceDisconnected() {
            mDeviceReadCharacteristic = null
            mDeviceWriteCharacteristic = null
        }

        override fun isRequiredServiceSupported(gatt: BluetoothGatt): Boolean {
            val service = gatt.getService(BleConstant.getServiceUUID())
            if (service != null) {
                mDeviceWriteCharacteristic = service.getCharacteristic(BleConstant.getWriteUUID())
                mDeviceReadCharacteristic = service.getCharacteristic(BleConstant.getReadUUID())

                mSupport = true
                return mSupport
            }
            return false
        }
    }

    override fun getGattCallback(): BleManagerGattCallback {
        return mGattCallback
    }

    override fun shouldClearCacheWhenDisconnected(): Boolean {
        return !mSupport
    }

    private val mWriteDataCallback = object : AbsLightDataReceive() {
        override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
            Log.d(SingleDeviceManager::javaClass.name,"device = $device data = $data")
        }
    }

    private val mReadDataCallback = object : AbsLightDataReceive() {
        override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
            receiveCallback?.onLightDataReceive(device, data)
        }
    }

    fun sendLightData(lightData: AbsDeviceData, delayToDequeNext: Long) {
        enqueue(lightData, delayToDequeNext)
        timingToDequeue()
    }

    @Synchronized
    private fun enqueue(lightData: AbsDeviceData, delayToDequeNext: Long) {
        mQueue.add(Pair(delayToDequeNext, lightData.value!!))
    }

    @Synchronized
    private fun dequeue(): Pair<Long, ByteArray>? {
        return if (mQueue.isEmpty()) null else mQueue.removeAt(0)
    }

    private fun timingToDequeue() {
        if (mTiming) return
        mTiming = true

        val dequeData = dequeue()
        if (dequeData == null) {
            mTiming = false
            return
        }

        mTimer = Observable.timer(dequeData.first, TimeUnit.MILLISECONDS)
                .subscribe({
                    writeCharacteristic(mDeviceWriteCharacteristic, dequeData.second)
                            .with(mWriteDataCallback)
                            .enqueue()
                    mTiming = false

                    timingToDequeue()
                }, {

                })
    }
}