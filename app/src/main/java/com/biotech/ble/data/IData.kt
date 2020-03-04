package com.biotech.ble.data

import java.util.*

/**
 * @author TuXin
 * @date 2020/2/29 5:07 PM.
 *
 * Email : tuxin@pupupula.com
 */
interface IData {
    companion object {
        const val TYPE_ORIGINAL = 0
        const val TYPE_FILTER_ALL = 1
        const val TYPE_ARV = 2
        const val TYPE_RMS = 3

        const val COLLECT_ORIGINAL_DATA_PER_SECOND = 1000
        const val COLLECT_ONE_DATA_TIME = 0.001
        const val MAX_WINDOW_NUM = 40
    }

    fun getDataType(): Int
    fun getCacheTotalSize(): Int
    fun addData(array: DoubleArray, startTime: Int, endTime: Int)

    fun getTimeList(): LinkedList<Int>
    fun getDataList(): LinkedList<Double>

    fun setDataChangeListener(changeListener: IChangeListener?)
    fun getDataChangeListener(): IChangeListener?

    fun getTitle(): String

    fun clearTimeAndData()

    fun getMinX(): Int
    fun getMaxX(): Int

    fun getMinY(): Double
    fun getMaxY(): Double

    fun getCoordinateConfig(): CoordinateConfig

//    val timeList: LinkedList<Int> = LinkedList()
//    val dataList: LinkedList<Double> = LinkedList()
}