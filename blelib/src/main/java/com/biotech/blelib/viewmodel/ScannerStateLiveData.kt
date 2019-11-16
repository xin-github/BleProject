package com.pupupula.blelib.viewmodel

import androidx.lifecycle.LiveData

/**
 * @author TuXin
 * @date 2019-07-19 17:33.
 *
 * Email : tuxin@pupupula.com
 */
class ScannerStateLiveData : LiveData<ScannerStateLiveData> {
    var mScanningStarted = false
        private set

    var mHasRecords = false
        private set

    var mBluetoothEnable = false
        private set

    var mLocationEnable = false
        private set

    constructor(bluetoothEnable: Boolean, locationEnable: Boolean) {
        mScanningStarted = false
        mBluetoothEnable = bluetoothEnable
        mLocationEnable = locationEnable
        postValue(this)
    }

    fun refresh() {
        postValue(this)
    }

    fun scanningStarted() {
        mScanningStarted = true
        postValue(this)
    }

    fun scanningStop() {
        mScanningStarted = false
        postValue(this)
    }

    fun bluetoothEnable() {
        mBluetoothEnable = true
        postValue(this)
    }

    @Synchronized
    fun bluetoothDisable() {
        mBluetoothEnable = false
        mHasRecords = false
        postValue(this)
    }

    fun setLocationEnable(enable: Boolean) {
        mLocationEnable = enable
        postValue(this)
    }

    fun recordFound() {
        mHasRecords = true
        postValue(this)
    }

    fun clearRecords() {
        mHasRecords = false
        postValue(this)
    }

    fun isScanning() : Boolean {
        return mScanningStarted
    }
}