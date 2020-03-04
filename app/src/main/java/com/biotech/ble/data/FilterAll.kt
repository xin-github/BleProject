package com.biotech.ble.data

import com.biotech.ble.data.IData.Companion.COLLECT_ORIGINAL_DATA_PER_SECOND
import com.biotech.ble.data.IData.Companion.MAX_WINDOW_NUM
import com.biotech.ble.data.IData.Companion.TYPE_FILTER_ALL
import com.biotech.ble.utils.dp2px
import java.util.*

/**
 * @author TuXin
 * @date 2020/3/2 2:46 PM.
 *
 * Email : tuxin@pupupula.com
 */
class FilterAll : IData {

    companion object{
        const val DEFAULT_MAX_X = MAX_WINDOW_NUM * COLLECT_ORIGINAL_DATA_PER_SECOND
    }
    override fun getDataType(): Int {
        return TYPE_FILTER_ALL
    }

    override fun getCacheTotalSize(): Int {
        return MAX_WINDOW_NUM * COLLECT_ORIGINAL_DATA_PER_SECOND
    }

    override fun addData(array: DoubleArray, startTime: Int, endTime: Int) {
        getDataList().clear()
        getTimeList().clear()

        var time = startTime

        array.forEach {
            getDataList().add(it)
            getTimeList().add(time)
            time++
        }
        mChangeListener?.onDataChange(this)
    }

    private val mTimeList by lazy {
        LinkedList<Int>()
    }

    override fun getTimeList(): LinkedList<Int> {
        return mTimeList
    }

    private val mDataList by lazy {
        return@lazy LinkedList<Double>()
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
        return "FILTER ALL"
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
        return -0.1
    }

    override fun getMaxY(): Double {
        return 0.4
    }

    private val mConfig by lazy {
        CoordinateConfig(xPartition = 10, yPartition = 10, dataPointSize = 0.5F.dp2px().toFloat(), pickDataInterval = 20)
    }

    override fun getCoordinateConfig(): CoordinateConfig {
        return mConfig
    }
}