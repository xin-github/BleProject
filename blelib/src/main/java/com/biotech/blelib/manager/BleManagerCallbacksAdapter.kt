package com.pupupula.blelib.manager

import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import no.nordicsemi.android.ble.BleManagerCallbacks

/**
 * @author TuXin
 * @date 2019-08-09 16:58.
 *
 * Email : tuxin@pupupula.com
 */
abstract class BleManagerCallbacksAdapter : BleManagerCallbacks {
    private var mConnectionState = BluetoothGatt.STATE_DISCONNECTED

    abstract fun onConnectStateChange(device: BluetoothDevice, connectState: Int)

    override fun onDeviceDisconnecting(device: BluetoothDevice) {
        mConnectionState = BluetoothGatt.STATE_DISCONNECTING
        onConnectStateChange(device, mConnectionState)
    }

    override fun onDeviceDisconnected(device: BluetoothDevice) {
        mConnectionState = BluetoothGatt.STATE_DISCONNECTED
        onConnectStateChange(device, mConnectionState)
    }

    override fun onDeviceConnecting(device: BluetoothDevice) {
        mConnectionState = BluetoothGatt.STATE_CONNECTING
        onConnectStateChange(device, mConnectionState)
    }

    override fun onDeviceConnected(device: BluetoothDevice) {
        mConnectionState = BluetoothGatt.STATE_CONNECTED
        onConnectStateChange(device, mConnectionState)
    }

    override fun onBondingFailed(device: BluetoothDevice) {
        // do nothing
    }

    override fun onServicesDiscovered(device: BluetoothDevice, optionalServicesFound: Boolean) {
        // do nothing
    }

    override fun onBondingRequired(device: BluetoothDevice) {
        // do nothing
    }

    override fun onLinkLossOccurred(device: BluetoothDevice) {
        mConnectionState = BluetoothGatt.STATE_DISCONNECTED
        onConnectStateChange(device, mConnectionState)
    }

    override fun onBonded(device: BluetoothDevice) {
    }

    override fun onDeviceReady(device: BluetoothDevice) {
    }
}