package com.biotech.ble.data

/**
 * @author TuXin
 * @date 2020/3/2 11:04 PM.
 *
 * Email : tuxin@pupupula.com
 */
interface IDraw {
    fun getMinDrawYAxis(): Float
    fun getMaxDrawYAxis(): Float

    fun getMinDrawXAxis(): Float
    fun getMaxDrawXAxis(): Float
}