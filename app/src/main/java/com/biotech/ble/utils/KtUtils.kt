package com.biotech.ble.utils

import android.content.res.Resources

/**
 * @author TuXin
 * @date 2020/3/3 9:51 AM.
 *
 * Email : tuxin@pupupula.com
 */
fun Int.dp2px(): Int {
    val scale = Resources.getSystem().displayMetrics.density
    return (this * scale + 0.5f).toInt()
}

fun Float.dp2px(): Int {
    val scale = Resources.getSystem().displayMetrics.density
    return (this * scale + 0.5f).toInt()
}

fun Float.sp2px(): Int {
    val scale = Resources.getSystem().displayMetrics.scaledDensity
    return (this * scale + 0.5f).toInt()
}