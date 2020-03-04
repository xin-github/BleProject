package com.biotech.ble.data

import com.biotech.ble.data.IData.Companion.MAX_WINDOW_NUM
import com.biotech.ble.data.IData.Companion.TYPE_ARV
import java.util.*

/**
 * @author TuXin
 * @date 2020/3/2 11:56 AM.
 *
 * Email : tuxin@pupupula.com
 */
class ARV : IData {
    companion object {
        const val DEFAULT_MAX_X = IData.MAX_WINDOW_NUM
    }

    private val mTimeList by lazy {
        LinkedList<Int>()
    }

    private val mDataList by lazy {
        return@lazy LinkedList<Double>()
    }


    override fun getDataType(): Int {
        return TYPE_ARV
    }

    override fun getCacheTotalSize(): Int {
        return MAX_WINDOW_NUM
    }

    override fun addData(array: DoubleArray, startTime: Int, endTime: Int) {
        val oldData: LinkedList<Double> = LinkedList(getDataList())

        getDataList().clear()
        getTimeList().clear()

        var time = startTime / 1000
        array.forEachIndexed { index, it ->
            val realData = if ((it.isNaN() || it.isInfinite()) && index < oldData.size) {
                oldData[index]
            } else {
                it
            }

            getDataList().add(realData)
            getTimeList().add(time)
            time++
        }

        mChangeListener?.onDataChange(this)
    }


    override fun getTimeList(): LinkedList<Int> {
        return mTimeList
    }

    override fun getDataList(): LinkedList<Double> {
        return mDataList
    }

    private var mChangeListener: IChangeListener? = null
    override fun setDataChangeListener(changeListener: IChangeListener?) {
        mChangeListener = changeListener
    }

    override fun getDataChangeListener(): IChangeListener? {
        return mChangeListener
    }

    override fun getTitle(): String {
        return "ARV"
    }

    override fun clearTimeAndData() {
        mDataList.clear()
        mTimeList.clear()
        mChangeListener?.onDataChange(this)
    }

    private fun getLastTime(): Int {
        return if (mTimeList.isEmpty()) {
            0
        } else {
            mTimeList.last
        }
    }

    override fun getMinX(): Int {
        val lastTime = getLastTime()
        return if (lastTime > DEFAULT_MAX_X) {
            lastTime - DEFAULT_MAX_X
        } else {
            0
        }
    }

    override fun getMaxX(): Int {
        val lastTime = getLastTime()
        return if (lastTime > DEFAULT_MAX_X) {
            lastTime
        } else {
            DEFAULT_MAX_X
        }
    }

    override fun getMinY(): Double {
        return 0.0
    }

    override fun getMaxY(): Double {
        return 0.1
    }


    private val mConfig by lazy {
        CoordinateConfig(xPartition = 5, yPartition = 5)
    }
    override fun getCoordinateConfig(): CoordinateConfig {
        return mConfig
    }
}