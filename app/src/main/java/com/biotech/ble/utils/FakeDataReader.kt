package com.biotech.ble.utils

import android.content.Context
import android.os.Handler
import android.os.Looper
import android.os.Message
import android.os.SystemClock
import java.io.BufferedReader
import java.io.InputStream
import java.io.InputStreamReader
import java.util.concurrent.Executor
import java.util.concurrent.Executors

/**
 * @author TuXin
 * @date 2020/2/29 2:08 AM.
 *
 * Email : tuxin@pupupula.com
 */
class FakeDataReader(context: Context) {
    private val mainHandler: Handler

    private val am = context.assets
    var inputStream: InputStream? = null
    private var reader: InputStreamReader? = null
    private var bufferedReader: BufferedReader? = null
    @Volatile
    private var mStop = true

    private val executor: Executor

    @Volatile
    private var started: Boolean = false

    private val lock = Any()

    init {
        executor = Executors.newSingleThreadExecutor()

        mainHandler = object : Handler(Looper.getMainLooper()) {
            override fun handleMessage(msg: Message) {
                if (msg.obj is DoubleArray) {
                    val doubleArray = msg.obj as DoubleArray
                    DataRepository.instance.addOriginalData(doubleArray)
                }
            }
        }
    }

    fun startReadData() {
        if (started) {
            return
        }
        inputStream = am.open("sample.txt")
        reader = InputStreamReader(inputStream!!)
        bufferedReader = BufferedReader(reader)
        
        started = true
        mStop = false
        executor.execute {
            try {
                while (!mStop) {
                    val doubleList = randomReadDoubles()
                    val msg = Message.obtain()

                    msg.obj = doubleList.toDoubleArray()

                    mainHandler.sendMessage(msg)
                    SystemClock.sleep(200)

                }
            } catch (e: Exception) {
                e.printStackTrace()
            } finally {
                if (inputStream != null) {
                    try {
                        inputStream?.close()
                    } catch (e: Exception) {

                    }
                }
            }
        }
    }

    fun stopReadData() {
        if (mStop) {
            return
        }

        mStop = true
        started = false

        try {
            inputStream?.close()

        } catch (e: Exception) {
            e.printStackTrace()
        } finally {
            if (inputStream != null) {
                try {
                    inputStream?.close()
                } catch (e: Exception) {

                }
            }
        }

        inputStream = am.open("sample.txt")
        reader = InputStreamReader(inputStream!!)
        bufferedReader = BufferedReader(reader)

        DataRepository.instance.clearAllData()

    }

    private fun randomReadDoubles(): MutableList<Double> {
        val arrayList = mutableListOf<Double>()
        val times = (100..500).random()

        for (i in 0..times) {
            val text: String? = bufferedReader?.readLine()
            if (text == null) {
                inputStream = am.open("sample.txt")
                reader = InputStreamReader(inputStream!!)
                bufferedReader = BufferedReader(reader)
            } else {
                val tables = text.split('\t')
                if (tables.size >= 3) {
                    arrayList.add(tables[2].toDouble())
                }
            }
        }

        return arrayList
    }
}