package com.biotech.ble.showlog

import android.app.Activity
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import com.biotech.ble.R
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice
import com.pupupula.blelib.datas.AbsDeviceData
import com.pupupula.blelib.manager.DevicesManager
import com.pupupula.blelib.manager.IDeviceDataReceive
import kotlinx.android.synthetic.main.show_log_act.*

/**
 * @author TuXin
 * @date 2019-11-16 13:10.
 *
 * Email : tuxin@pupupula.com
 */
class ShowLogAct : AppCompatActivity() {
    companion object {
        private const val KEY_DEVICE = "key_device"

        fun startAct(context: Activity, device: DiscoveredBluetoothDevice) {
            val intent = Intent(context, ShowLogAct::class.java)
            val bundle = Bundle()
            bundle.putParcelable(KEY_DEVICE, device)
            intent.putExtras(bundle)
            context.startActivity(intent)
        }
    }

    val mDevice by lazy { intent.getParcelableExtra(KEY_DEVICE) as? DiscoveredBluetoothDevice }
    private val mAdapter = LogAdapter()

    private val mReceiveCallback = object : IDeviceDataReceive {
        override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
            val currentDevice = mDevice ?: return
            val strings = data.toString() ?: return
            if (currentDevice.name == device.name) {
                mAdapter.addItem(strings)
            }
        }
    }

    private fun registerBleCallbacks() {
        DevicesManager.instance.registerReceiveCallback(mReceiveCallback)
    }

    private fun unregisterBleCallbacks() {
        DevicesManager.instance.unregisterReceiveCallback(mReceiveCallback)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.show_log_act)
        initRecyclerView()
        registerBleCallbacks()
    }

    private fun initRecyclerView() {
        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.itemAnimator = null
        recyclerView.adapter = mAdapter
    }

    override fun finish() {
        super.finish()
        unregisterBleCallbacks()
        DevicesManager.instance.clearAllDevices()
    }
}