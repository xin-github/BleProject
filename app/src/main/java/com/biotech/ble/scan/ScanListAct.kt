package com.biotech.ble.scan

import android.Manifest
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProviders
import androidx.recyclerview.widget.LinearLayoutManager
import com.biotech.ble.R
import com.biotech.ble.showlog.ShowLogAct
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice
import com.pupupula.blelib.manager.BleManagerCallbacksAdapter
import com.pupupula.blelib.manager.DevicesManager
import com.pupupula.blelib.manager.EnableIndicationDoneCallback
import com.pupupula.blelib.util.isBleEnabled
import com.pupupula.blelib.util.isLocationPermissionsGranted
import com.pupupula.blelib.viewmodel.ScannerViewModel
import kotlinx.android.synthetic.main.wifi_scan_list_act.*

/**
 * @author TuXin
 * @date 2019-08-23 08:34.
 *
 * Email : tuxin@pupupula.com
 */
class ScanListAct : AppCompatActivity(), ItemClickListener<DiscoveredBluetoothDevice> {
    private var mDeviceMatched = false
    private var mFoundDevice: DiscoveredBluetoothDevice? = null
    private var mAdapter = ScanListAdapter(this)
    private val PERMISSION_REQUEST_CODE = 111

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.wifi_scan_list_act)
        initRecyclerView()
        subscribeUI()
        checkPermission()
    }

    private fun checkPermission() {
        if (!isBleEnabled()) {
            val enableIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivity(enableIntent)
        }

        if (ensurePermission()) {
            startScan()
        }
    }

    private fun ensurePermission(): Boolean {
        if (!isLocationPermissionsGranted(this)) {
            requestPermission()
            return false
        }
        return true
    }

    private fun requestPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            requestBlueScanPermission(this, PERMISSION_REQUEST_CODE)
        }
    }

    fun requestBlueScanPermission(activity: Activity, requestCode: Int) {
        ActivityCompat.requestPermissions(
            activity,
            arrayOf(
                Manifest.permission.ACCESS_COARSE_LOCATION,
                Manifest.permission.ACCESS_FINE_LOCATION
            ),
            requestCode
        )
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        val res = permissionResultOK(permissions, grantResults)
        if (res) {
            startScan()
        }
    }

    fun permissionResultOK(permissions: Array<String>, grantResults: IntArray): Boolean {
        if (permissions.isEmpty() || grantResults.isEmpty()) return false

        for (s in grantResults) {
            if (s != PackageManager.PERMISSION_GRANTED) {
                return false
            }
        }
        return true
    }


    private val mBleManagerCallbacks = object : BleManagerCallbacksAdapter() {
        override fun onError(device: BluetoothDevice, message: String, errorCode: Int) {
        }

        override fun onDeviceNotSupported(device: BluetoothDevice) {
        }

        override fun onConnectStateChange(device: BluetoothDevice, connectState: Int) {
//            _connectStateLive.value = connectState
        }

//        override fun onDeviceNotSupported(device: BluetoothDevice) {
////            _connectStateLive.value = BluetoothGatt.STATE_DISCONNECTED
//        }
//
//        override fun onError(device: BluetoothDevice, message: String, errorCode: Int) {
//        }
    }

    private val mEnableIndicationCallback = object : EnableIndicationDoneCallback {
        override fun onEnableIndicationDone(device: BluetoothDevice) {
            connected()
        }
    }

    val mScannerViewModel by lazy {
        ViewModelProviders.of(this).get(ScannerViewModel::class.java)
    }

    private fun unRegisterBleCallbacks() {
        DevicesManager.instance.unregisterEnableIndicationDone(mEnableIndicationCallback)
        DevicesManager.instance.unregisterBleManagerCallbacksAdapter(mBleManagerCallbacks)
    }

    private fun registerBleCallbacks() {
        DevicesManager.instance.registerBleManagerCallbacksAdapter(mBleManagerCallbacks)
        DevicesManager.instance.registerEnableIndicationDone(mEnableIndicationCallback)
    }

    private fun initRecyclerView() {
        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.itemAnimator = null
        recyclerView.setHasFixedSize(true)
        recyclerView.adapter = mAdapter
    }

    private fun connected() {
        progress.hide()
    }


    private fun subscribeUI() {
        mScannerViewModel.apply {
            devicesLiveData?.observe(this@ScanListAct, Observer { list ->
                list?.let {
                    mAdapter.setDatas(it)
                }
            })
        }
    }

    override fun finish() {
        super.finish()
        unRegisterBleCallbacks()
    }

    override fun onItemClick(data: DiscoveredBluetoothDevice) {
//        setTitleRes(R.string.connecting)
        stopScanAndStartConnect(data)
        showDialog()
        ShowLogAct.startAct(this, data)
    }

    private fun showDialog() {
        progress.show()
    }

    @Synchronized
    private fun stopScanAndStartConnect(device: DiscoveredBluetoothDevice) {
        mDeviceMatched = true
        mFoundDevice = device
        mScannerViewModel.stopScan()

        registerBleCallbacks()
        DevicesManager.instance.setDevice(device)
        DevicesManager.instance.connect(device)
    }

    private fun startScan() {
        mScannerViewModel.startScan()
    }

    private fun stopScan() {
        mScannerViewModel.stopScan()
    }
}