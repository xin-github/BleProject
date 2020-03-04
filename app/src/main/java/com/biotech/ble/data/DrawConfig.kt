package com.biotech.ble.data

import android.graphics.Color
import com.biotech.ble.utils.dp2px
import com.biotech.ble.utils.sp2px

/**
 * @author TuXin
 * @date 2020/3/3 9:40 AM.
 *
 * Email : tuxin@pupupula.com
 */
data class DrawConfig(
    val coordinateColor: Int = Color.BLACK
)

data class CoordinateConfig(
    val color: Int = Color.BLACK,
    val textSize: Int = 10F.sp2px(),
    val padding: Int = 30.dp2px(),
    val dashWidth: Int = 2.dp2px(),
    val coordinateWidth: Int = 2.dp2px(),
    var xPartition: Int,
    var yPartition: Int,
    var drawStyle: Int = DRAW_STYLE_POINT,
    var dataPointSize: Float = 2.dp2px().toFloat(),
    var pickDataInterval: Int = 1
) {
    companion object {
        const val DRAW_STYLE_POINT = 0
        const val DRAW_STYLE_LINE = 1
    }
}