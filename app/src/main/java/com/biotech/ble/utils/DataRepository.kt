package com.biotech.ble.utils

import android.os.Handler
import android.os.Looper
import android.os.Message
import com.biotech.ble.data.*
import com.biotech.nativelib.NativeBridge
import java.util.concurrent.Executors

/**
 * @author TuXin
 * @date 2020/3/1 12:58 AM.
 *
 * Email : tuxin@pupupula.com
 */
class DataRepository {
    companion object {
        val instance = InnerClass.HOLDER
    }

    private data class FftCompareRes(
        val array: Array<DoubleArray>,
        val startTime: Int,
        val endTime: Int
    )

    private val mOriginData = OriginalData()
    val mFilterAll = FilterAll()
    val mRMS = RMS()
    val mARV = ARV()

    fun getData(type: Int): IData? {
        return when (type) {
            IData.TYPE_FILTER_ALL -> {
                mFilterAll
            }
            IData.TYPE_RMS -> {
                mRMS
            }
            IData.TYPE_ARV -> {
                mARV
            }
            else -> null
        }
    }

    fun clearAllData() {
        mComputedTimeMs = 0
        mOriginData.clearTimeAndData()
        mFilterAll.clearTimeAndData()
        mRMS.clearTimeAndData()
        mARV.clearTimeAndData()
    }

    private val mFilterAllExecutor = Executors.newSingleThreadExecutor()
    private val mFftCompareExecutor = Executors.newSingleThreadExecutor()
    private val mARV_RMSExecutor = Executors.newSingleThreadExecutor()

    private val mainHandler = object : Handler(Looper.getMainLooper()) {
        override fun handleMessage(msg: Message) {
            when (msg.obj) {
                is FilterAllRes -> {
                    val data = msg.obj as? FilterAllRes ?: return
                    val filterAll = data.array
                    mFilterAll.addData(filterAll, data.startTime, data.endTime)

                    // todo: fft and AVR_RMS
                    val fftRunnable =
                        FftCompareRunnable(filterAll, data.startTime, data.endTime, this)
                    mFftCompareExecutor.execute(fftRunnable)

                    val arv_rmsRunnable =
                        ARV_RMSRunnable(filterAll, data.startTime, data.endTime, this)
                    mARV_RMSExecutor.execute(arv_rmsRunnable)
                }

                is FftCompareRes -> {
                    val data = msg.obj as? FftCompareRes ?: return
                    // [0] -> P1
                    val P1 = data.array[0]
                    // [1] -> f
                    val f = data.array[0]
                }

                is ARV_RMSRes -> {
                    val data = msg.obj as? ARV_RMSRes ?: return
                    // [0] arv
                    mARV.addData(data.array[0], data.startTime, data.endTime)

                    // [1] rms
                    mRMS.addData(data.array[1], data.startTime, data.endTime)
                }
            }
        }
    }

    class FilterAllRunnable(
        private val doubleArray: DoubleArray,
        private val startTime: Int,
        private val endTime: Int,
        private val handler: Handler
    ) :
        Runnable {
        override fun run() {
            val res = NativeBridge.filterAll(doubleArray, doubleArray.size)
            val msg = Message.obtain()

            msg.obj = FilterAllRes(res, startTime, endTime)

            handler.sendMessage(msg)
        }
    }

    class FftCompareRunnable(
        private val doubleArray: DoubleArray,
        private val startTime: Int,
        private val endTime: Int,
        private val handler: Handler
    ) : Runnable {
        override fun run() {
            val res = NativeBridge.fftCompare(doubleArray, doubleArray.size)
            val msg = Message.obtain()

            msg.obj = FftCompareRes(res, startTime, endTime)

            handler.sendMessage(msg)
        }
    }

    class ARV_RMSRunnable(
        private val doubleArray: DoubleArray,
        private val startTime: Int,
        private val endTime: Int,
        private val handler: Handler
    ) : Runnable {
        override fun run() {
            val res = NativeBridge.arv_rmsCompare(doubleArray, doubleArray.size)
            val msg = Message.obtain()

            msg.obj = ARV_RMSRes(res, startTime, endTime)

            handler.sendMessage(msg)
        }
    }

    private var mComputedTimeMs: Int = 0

    fun addOriginalData(doubleArray: DoubleArray) {
        val timeBefore = mOriginData.getEndTime()
        mOriginData.addData(
            doubleArray,
            timeBefore + 1,
            timeBefore + doubleArray.size
        )
        val timeAfter = mOriginData.getEndTime()

        if (timeAfter - mComputedTimeMs > IData.COLLECT_ORIGINAL_DATA_PER_SECOND) {
            val runnable = FilterAllRunnable(
                mOriginData.getDataList().toDoubleArray(),
                mOriginData.getStartTime(),
                mOriginData.getEndTime(),
                mainHandler
            )

            mFilterAllExecutor.execute(runnable)
            mComputedTimeMs = timeAfter
        }
    }

    private object InnerClass {
        val HOLDER = DataRepository()
    }
}