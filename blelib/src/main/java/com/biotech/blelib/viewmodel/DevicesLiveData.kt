package com.pupupula.blelib.viewmodel

import android.os.ParcelUuid
import androidx.lifecycle.LiveData
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice
import com.pupupula.blelib.util.BleConstant
import no.nordicsemi.android.support.v18.scanner.ScanResult
import java.util.*

/**
 * @author TuXin
 * @date 2019-07-22 09:20.
 *
 * Email : tuxin@pupupula.com
 */
class DevicesLiveData constructor(
    private var mFilterUuidRequired: Boolean,
    private var mFilterNameRequired: Boolean,
    private var mFilterNearbyOnly: Boolean
) : LiveData<List<DiscoveredBluetoothDevice>?>() {

    private val mDevices = ArrayList<DiscoveredBluetoothDevice>()
    private var mFilteredDevices: List<DiscoveredBluetoothDevice>? = null

    @Synchronized
    fun bluetoothDisabled() {
        mDevices.clear()
        mFilteredDevices = null
        postValue(null)
    }

    /* package */  fun filterByUuid(uuidRequired: Boolean): Boolean {
        mFilterUuidRequired = uuidRequired
        return applyFilter()
    }

    /* package */  fun filterByDistance(nearbyOnly: Boolean): Boolean {
        mFilterNearbyOnly = nearbyOnly
        return applyFilter()
    }

    /* package */ @Synchronized
    fun deviceDiscovered(result: ScanResult): Boolean {
        val device: DiscoveredBluetoothDevice

        // Check if it's a new device.
        val index = indexOf(result)
        if (index == -1) {
            device = DiscoveredBluetoothDevice(result)
            mDevices.add(device)
        } else {
            device = mDevices[index]
        }

        // Update RSSI and name.
        device.update(result)

        // Return true if the device was on the filtered list or is to be added.
        return (mFilteredDevices != null && mFilteredDevices!!.contains(device))
                || (matchesUuidFilter(result)
                && matchesNearbyFilter(device.highestRssi) && matchesNameFilter(device.name))
    }

    /**
     * Clears the list of devices.
     */
    @Synchronized
    fun clear() {
        mDevices.clear()
        mFilteredDevices = null
        postValue(null)
    }

    /**
     * Refreshes the filtered device list based on the filter flags.
     */
    /* package */ @Synchronized
    fun applyFilter(): Boolean {
        val devices = ArrayList<DiscoveredBluetoothDevice>()
        for (device in mDevices) {
            val result = device.scanResult
            if (result != null && matchesUuidFilter(result)
                && matchesNearbyFilter(device.highestRssi)
                && matchesNameFilter(result.device.name)
            ) {
                devices.add(device)
            }
        }
        mFilteredDevices = devices
        postValue(mFilteredDevices)
        return mFilteredDevices!!.isNotEmpty()
    }

    /**
     * Finds the index of existing devices on the device list.
     *
     * @param result scan result.
     * @return Index of -1 if not found.
     */
    private fun indexOf(result: ScanResult): Int {
        var i = 0
        for (device in mDevices) {
            if (device.matches(result))
                return i
            i++
        }
        return -1
    }

    private fun matchesUuidFilter(result: ScanResult): Boolean {
        if (!mFilterUuidRequired)
            return true

        val record = result.scanRecord ?: return false

        val uuids = record.serviceUuids ?: return false

        return uuids.contains(FILTER_UUID)
    }

    private fun matchesNearbyFilter(rssi: Int): Boolean {
        return if (!mFilterNearbyOnly) true else rssi >= FILTER_RSSI
    }

    private fun matchesNameFilter(name: String?): Boolean {
        return if (!mFilterNameRequired) {
            true
        } else {
            name?.startsWith(FILTER_NAME) ?: false
        }
    }

    companion object {
        private val FILTER_UUID = ParcelUuid(BleConstant.SERVICE_UUID)
        private val FILTER_RSSI = -50 // [dBm]
        private val FILTER_NAME = "LL"
    }
}
