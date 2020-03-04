package com.biotech.ble.data

import com.biotech.ble.data.IData.Companion.COLLECT_ORIGINAL_DATA_PER_SECOND
import com.biotech.ble.data.IData.Companion.MAX_WINDOW_NUM
import com.biotech.ble.data.IData.Companion.TYPE_ORIGINAL
import java.util.*

/**
 * @author TuXin
 * @date 2020/2/29 5:36 PM.
 *
 *
 * Email : tuxin@pupupula.com
 */
class OriginalData : IData {
    override fun getDataType(): Int {
        return TYPE_ORIGINAL
    }

    override fun getCacheTotalSize(): Int {
        return MAX_WINDOW_NUM * COLLECT_ORIGINAL_DATA_PER_SECOND
    }

    override fun addData(array: DoubleArray, startTime: Int, endTime: Int) {
        var currentTime = startTime

        array.forEachIndexed { index, d ->
            if (getTimeList().size >= getCacheTotalSize()) {
                getTimeList().removeFirst()
            }
            getTimeList().add(currentTime)

            if (getDataList().size >= getCacheTotalSize()) {
                getDataList().removeFirst()
            }
            getDataList().add(d)

            currentTime++
        }
        mChangeListener?.onDataChange(this)
    }

    fun getStartTime(): Int {
        return if (getTimeList().size == 0) {
            0
        } else {
            getTimeList().first
        }
    }

    fun getEndTime(): Int {
        return if (getTimeList().size == 0) {
            0
        } else {
            getTimeList().last
        }
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
        return "ORIGINAL"
    }

    override fun clearTimeAndData() {
        mDataList.clear()
        mTimeList.clear()
        mChangeListener?.onDataChange(this)
    }

    override fun getMinX(): Int {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getMaxX(): Int {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getMinY(): Double {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getMaxY(): Double {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getCoordinateConfig(): CoordinateConfig {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}