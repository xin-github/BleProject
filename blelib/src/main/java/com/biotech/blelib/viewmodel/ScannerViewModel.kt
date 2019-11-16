package com.pupupula.blelib.viewmodel

import android.app.Application
import android.bluetooth.BluetoothAdapter
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.location.LocationManager
import android.util.Log
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.biotech.commonlib.BaseApplication
import com.biotech.commonlib.utils.addTo
import com.pupupula.blelib.util.isBleEnabled
import com.pupupula.blelib.util.isLocationEnabled
import com.pupupula.blelib.util.isLocationPermissionsGranted
import com.pupupula.blelib.util.isMarshmallowOrAbove
import io.reactivex.Observable
import io.reactivex.disposables.CompositeDisposable
import io.reactivex.schedulers.Schedulers
import no.nordicsemi.android.support.v18.scanner.BluetoothLeScannerCompat
import no.nordicsemi.android.support.v18.scanner.ScanCallback
import no.nordicsemi.android.support.v18.scanner.ScanResult
import no.nordicsemi.android.support.v18.scanner.ScanSettings

/**
 * @author TuXin
 * @date 2019-07-19 17:11.
 *
 * Email : tuxin@pupupula.com
 */
open class ScannerViewModel : ViewModel {
    private var _scannerStateLiveData: ScannerStateLiveData = ScannerStateLiveData(
        isBleEnabled(),
        isLocationPermissionsGranted(BaseApplication.instance!!)
    )
    val scannerStateLiveData get() = _scannerStateLiveData

    private var _bleEnableLive = MutableLiveData<Boolean>()
    val bleEnableLive get() = _bleEnableLive

    private var _locationEnableLive = MutableLiveData<Boolean>()
    val locationEnableLive get() = _locationEnableLive

    private var _scanningLive = MutableLiveData<Boolean>()
    val scanningLive get() = _scanningLive

    private var _devicesLiveData: DevicesLiveData? = null
    val devicesLiveData get() = _devicesLiveData

    private val mDisposables = CompositeDisposable()

    constructor() {
        registerBroadcastReceivers(BaseApplication.instance!!)
        _devicesLiveData = DevicesLiveData(
            mFilterUuidRequired = false,
            mFilterNameRequired = false,
            mFilterNearbyOnly = false
        )

        _bleEnableLive.value = isBleEnabled()
        _locationEnableLive.value = isLocationPermissionsGranted(BaseApplication.instance!!)
    }

    override fun onCleared() {
        super.onCleared()
        stopScan()
        BaseApplication.instance!!.unregisterReceiver(mBluetoothStateBroadcastReceiver)

        if (isMarshmallowOrAbove()) {
            BaseApplication.instance!!.unregisterReceiver(mLocationProviderChangedReceiver)
        }
        mDisposables.clear()
    }

    private fun registerBroadcastReceivers(application: Application) {
        application.registerReceiver(
            mBluetoothStateBroadcastReceiver,
            IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED)
        )
        if (isMarshmallowOrAbove()) {
            application.registerReceiver(
                mLocationProviderChangedReceiver,
                IntentFilter(LocationManager.MODE_CHANGED_ACTION)
            )
        }
    }

    private val mBluetoothStateBroadcastReceiver = object : BroadcastReceiver() {
        override fun onReceive(context: Context?, intent: Intent?) {
            val state =
                intent?.getIntExtra(BluetoothAdapter.EXTRA_STATE, BluetoothAdapter.STATE_OFF)
            val previousState = intent?.getIntExtra(
                BluetoothAdapter.EXTRA_PREVIOUS_STATE,
                BluetoothAdapter.STATE_OFF
            )

            when (state) {
                BluetoothAdapter.STATE_ON -> {
                    _scannerStateLiveData.bluetoothEnable()
                    _bleEnableLive.value = true
                }

                BluetoothAdapter.STATE_TURNING_OFF, BluetoothAdapter.STATE_OFF -> {
                    if (previousState != BluetoothAdapter.STATE_TURNING_OFF && previousState != BluetoothAdapter.STATE_OFF) {
                        stopScan()
                        _scannerStateLiveData.bluetoothDisable()
                        _bleEnableLive.value = false
                    }
                }
            }
        }
    }

    /**
     * Broadcast receiver to monitor the changes in the location provider.
     */
    private val mLocationProviderChangedReceiver = object : BroadcastReceiver() {
        override fun onReceive(context: Context, intent: Intent) {
            val enabled = isLocationEnabled(context)
            _scannerStateLiveData.setLocationEnable(enabled)
            _locationEnableLive.value = enabled
        }
    }

    private val scanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult) {
            Observable.just(true)
                .observeOn(Schedulers.computation())
                .subscribe({
                    if (_devicesLiveData != null && _devicesLiveData!!.deviceDiscovered(result)) {
                        _devicesLiveData!!.applyFilter()
                        _scannerStateLiveData.recordFound()
                    }
                }, {
                    it.printStackTrace()
                }).addTo(mDisposables)

        }

        override fun onBatchScanResults(results: MutableList<ScanResult>) {
            Observable.just(true)
                .observeOn(Schedulers.computation())
                .subscribe({
                    // This callback will be called only if the report delay set above is greater then 0.
                    var atLeastOneMatchedFilter = false
                    for (result in results) {
                        atLeastOneMatchedFilter =
                            (_devicesLiveData != null && _devicesLiveData!!.deviceDiscovered(result)) || atLeastOneMatchedFilter
                    }

                    if (atLeastOneMatchedFilter) {
                        _devicesLiveData?.applyFilter()
                        _scannerStateLiveData.recordFound()
                    }
                }, {
                    it.printStackTrace()
                }).addTo(mDisposables)
        }

        override fun onScanFailed(errorCode: Int) {
            super.onScanFailed(errorCode)
            _scannerStateLiveData.scanningStop()
            _scanningLive.value = false
        }
    }

    /**
     * Start scanning for Bluetooth devices.
     */
    open fun startScan() {
        if (_scannerStateLiveData.isScanning()) {
            return
        }
        if (_scanningLive.value == true) {
            return
        }

        Log.d(ScannerViewModel::javaClass.name, "scanner startScan !!!!!")
        // Scanning settings
        val settings = ScanSettings.Builder()
            .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
            .setUseHardwareBatchingIfSupported(true)
            .build()

        val scanner = BluetoothLeScannerCompat.getScanner()
        scanner.startScan(null, settings, scanCallback)
        _scannerStateLiveData.scanningStarted()
        _scanningLive.value = true
    }

    /**
     * Stop scanning for bluetooth devices.
     */
    open fun stopScan() {
        if (_scanningLive.value == true && isBleEnabled()) {
            val scanner = BluetoothLeScannerCompat.getScanner()
            scanner.stopScan(scanCallback)
            _scannerStateLiveData.scanningStop()
            _scanningLive.value = false
            Log.d(ScannerViewModel::javaClass.name, "scanner stopScan !!!!!")
        }
    }
}