package com.biotech.ble.data

import android.content.Context
import android.graphics.Canvas
import android.util.AttributeSet
import android.view.View
import com.biotech.ble.utils.DataRepository

/**
 * @author TuXin
 * @date 2020/3/3 10:56 AM.
 *
 * Email : tuxin@pupupula.com
 */
class DrawView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : View(context, attrs, defStyleAttr) {
    var type: Int = IData.TYPE_RMS
        set(value) {
            field = value
            resetDrawHelper()
            invalidate()
        }

    private lateinit var mDrawHelper: DrawHelper

    init {
        resetDrawHelper()
    }

    private fun resetDrawHelper() {
        val iData = DataRepository.instance.getData(type)!!
        mDrawHelper = DrawHelper(
            iData,
            iData.getCoordinateConfig()
        )

        mDrawHelper.onSizeChanged(width, height, 0, 0)
        iData.setDataChangeListener(object : IChangeListener {
            override fun onDataChange(data: IData) {
                invalidate()
            }
        })
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        mDrawHelper.onSizeChanged(w, h, oldw, oldh)
    }

    override fun onDraw(canvas: Canvas) {
        mDrawHelper.drawCoordinate(canvas)
        mDrawHelper.drawTitle(canvas)
        mDrawHelper.drawPoints(canvas)
    }
}