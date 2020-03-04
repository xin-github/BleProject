package com.biotech.ble

import android.app.Activity
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.biotech.ble.data.IData
import com.biotech.ble.scan.ScanListAct
import com.biotech.ble.utils.DataRepository
import com.biotech.ble.utils.FakeDataReader
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice
import com.pupupula.blelib.datas.AbsDeviceData
import com.pupupula.blelib.manager.BleManagerCallbacksAdapter
import com.pupupula.blelib.manager.DevicesManager
import com.pupupula.blelib.manager.EnableIndicationDoneCallback
import com.pupupula.blelib.manager.IDeviceDataReceive
import kotlinx.android.synthetic.main.layout_draw.*
import java.lang.Math.abs
import kotlin.math.abs


/**
 * @author TuXin
 * @date 2020/3/3 10:55 AM.
 *
 * Email : tuxin@pupupula.com
 */
class DrawActivity : AppCompatActivity() {
    var mDevice: DiscoveredBluetoothDevice? = null

    private val typeArray = IntArray(3)
    private var mCurrentType = 0

    init {
        typeArray[0] = IData.TYPE_RMS
        typeArray[1] = IData.TYPE_ARV
        typeArray[2] = IData.TYPE_FILTER_ALL
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout_draw)
        mFakeReader = FakeDataReader(this.applicationContext)
        initListener()
        updateConnectedDevices()
        registerBleCallbacks()
    }

    private fun updateConnectedDevices() {
        val list = DevicesManager.instance.getAllConnectedDevices()
        if (list.isNotEmpty()) {
            tvConnectedBle.text = "当前连接设备：${list[0].name}"
            mDevice = list[0]
        }
        list.forEachIndexed { index, discoveredBluetoothDevice ->
            if (index > 0) {
                DevicesManager.instance.disconnect(discoveredBluetoothDevice)
            }
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (resultCode == Activity.RESULT_OK) {
            when (requestCode) {
                ScanListAct.REQUEST_CODE -> {
                    updateConnectedDevices()
                    updateBleStatus(true)
                }
            }
        }
    }

    lateinit var mFakeReader: FakeDataReader

    private var mStartSimulate = false
    private var mStartListenBle = false

    private fun initListener() {
        tvStartSimulate.setOnClickListener {
            if (mStartListenBle) {
                Toast.makeText(this, "先暂停从蓝牙获取数据", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            if (mStartSimulate) {
                mStartSimulate = false
                mFakeReader.stopReadData()
                tvStartSimulate.text = "开始模拟"

            } else {
                tvStartSimulate.text = "停止模拟"
                mFakeReader.startReadData()
                mStartSimulate = true
            }

        }

        tvListenBle.setOnClickListener {
            if (mStartSimulate) {
                Toast.makeText(this, "先暂停模拟获取数据", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            if (mDevice == null) {
                val intent = Intent(this, ScanListAct::class.java)
                startActivityForResult(intent, ScanListAct.REQUEST_CODE)
                return@setOnClickListener
            }

            if (mStartListenBle) {
                updateBleStatus(false)
            } else {
                updateBleStatus(true)
            }
        }

        tvNextType.setOnClickListener {
            mCurrentType++
            val nextType = typeArray[mCurrentType % typeArray.size]
            drawView.type = nextType

        }
    }

    private fun updateBleStatus(started: Boolean) {
        mStartListenBle = started
        if (started) {
            tvListenBle.text = "停止接收蓝牙数据"
        } else {
            tvListenBle.text = "开始接收蓝牙数据"
        }
    }

    private fun unRegisterBleCallbacks() {
        DevicesManager.instance.unregisterEnableIndicationDone(mEnableIndicationCallback)
        DevicesManager.instance.unregisterBleManagerCallbacksAdapter(mBleManagerCallbacks)
        DevicesManager.instance.unregisterReceiveCallback(mReceiveCallback)
    }

    private fun registerBleCallbacks() {
        DevicesManager.instance.registerBleManagerCallbacksAdapter(mBleManagerCallbacks)
        DevicesManager.instance.registerEnableIndicationDone(mEnableIndicationCallback)
        DevicesManager.instance.registerReceiveCallback(mReceiveCallback)
    }

    private val mBleManagerCallbacks = object : BleManagerCallbacksAdapter() {
        override fun onError(device: BluetoothDevice, message: String, errorCode: Int) {
        }

        override fun onDeviceNotSupported(device: BluetoothDevice) {
        }

        override fun onConnectStateChange(device: BluetoothDevice, connectState: Int) {
        }
    }

    private val mEnableIndicationCallback = object : EnableIndicationDoneCallback {
        override fun onEnableIndicationDone(device: BluetoothDevice) {
        }
    }

    private val mReceiveCallback = object : IDeviceDataReceive {
        override fun onLightDataReceive(device: BluetoothDevice, data: AbsDeviceData) {
            if (!mStartListenBle) return
            val currentDevice = mDevice ?: return
            if (currentDevice.name == device.name) {
                val byteArray = data.value ?: return
                val sb = StringBuffer()
                for (i in byteArray.indices) {
                    var byte = byteArray[i]
                    if (byte < 0) {
                        byte = (-byte).toByte()
                    }
                    sb.append(byte)
                }
                val dataString = sb.toString()
                if (dataString.length < 10) return

//                val indexStr = dataString.substring(0 until 10)
//                val index = Integer.parseInt(indexStr, 2)
                val doubleArray = convertBleDataToDoubleArray(dataString)

                DataRepository.instance.addOriginalData(doubleArray)
            }
        }
    }

    private fun testDataConvert() {
        val stringBuffer = StringBuffer()
        for (i in 0..14) {
            val s = String.format("%10s", Integer.toBinaryString(i)).replace(" ", "0")
            stringBuffer.append(s)
        }

        val res = convertBleDataToDoubleArray(stringBuffer.toString())
        res.forEachIndexed { index, d ->
            println("index = $index d = $d")
        }

    }


    private fun convertBleDataToDoubleArray(dataString: String): DoubleArray {
        val arraySize = (dataString.length - 10) / 10
        val doubleArray = DoubleArray(arraySize)

        for (i in 1..arraySize) {
            val tempString = dataString.substring(i * 10, i * 10 + 10)
            val intValue = Integer.parseInt(tempString, 2)
            doubleArray[i - 1] = (intValue / 1024.0)
        }
        return doubleArray
    }

    override fun finish() {
        super.finish()
        unRegisterBleCallbacks()
    }
}