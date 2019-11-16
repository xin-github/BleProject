package com.biotech.ble

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.biotech.ble.scan.ScanListAct
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tvGotoScanAct.setOnClickListener {
            val intent = Intent(this, ScanListAct::class.java)
            startActivity(intent)
        }
    }
}
