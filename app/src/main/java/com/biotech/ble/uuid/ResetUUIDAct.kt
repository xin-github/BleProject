package com.biotech.ble.uuid

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.biotech.ble.R
import com.pupupula.blelib.util.BleConstant
import kotlinx.android.synthetic.main.reset_uuid_act.*

/**
 * @author TuXin
 * @date 2019-11-16 13:59.
 *
 * Email : tuxin@pupupula.com
 */
class ResetUUIDAct : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.reset_uuid_act)

        tvConfirm.setOnClickListener {
            val service = etService.text?.toString()
            val read = etRead.text?.toString()
            val write = etWrite.text?.toString()
            if (!service.isNullOrEmpty() && !read.isNullOrEmpty() && !write.isNullOrEmpty()) {
                BleConstant.setServiceUUID(service)
                BleConstant.setReadUUID(read)
                BleConstant.setWriteUUID(write)
            }
        }
        etService.setText(BleConstant.getServiceUUID().toString())
        etRead.setText(BleConstant.getReadUUID().toString())
        etWrite.setText(BleConstant.getWriteUUID().toString())
    }
}