package com.biotech.ble.data

import android.graphics.*
import com.biotech.ble.utils.dp2px
import com.biotech.ble.utils.sp2px
import kotlin.math.abs

/**
 * @author TuXin
 * @date 2020/3/2 11:51 PM.
 *
 * Email : tuxin@pupupula.com
 */
class DrawHelper(private val mData: IData, private val mCoordinateConfig: CoordinateConfig) {
    private val mXPath: Path = Path()
    private val mYPath: Path = Path()
    private var mXPathEffect: PathDashPathEffect? = null
    private var mYPathEffect: PathDashPathEffect? = null
    private var mXPathMeasure: PathMeasure? = null
    private var mYPathMeasure: PathMeasure? = null

    private var mCoordinatePaint = Paint()
    private var mTextPaint = Paint()
    private val mTitlePaint = Paint()
    private var mPointPaint = Paint()

    private var mCoordinateOriginalX: Float = 0F
    private var mCoordinateOriginalY: Float = 0F

    private var mWidth: Int = 0
    private var mHeight: Int = 0

    private val mTempTextBound = Rect()
    private val mFontMetrics = Paint.FontMetrics()

    companion object {
        val TEXT_PADDING_AXIS = 5.dp2px()
        val dp2 = 2.dp2px().toFloat()
    }

    init {
        mCoordinatePaint.color = mCoordinateConfig.color
        mCoordinatePaint.strokeWidth = mCoordinateConfig.coordinateWidth.toFloat()
        mCoordinatePaint.style = Paint.Style.STROKE

        mTextPaint.textSize = mCoordinateConfig.textSize.toFloat()
        mTextPaint.isAntiAlias = true
        mTextPaint.strokeWidth = 4F
        mTextPaint.style = Paint.Style.FILL
        mTextPaint.color = mCoordinateConfig.color
        mTextPaint.getFontMetrics(mFontMetrics)

        mTitlePaint.textSize = 16F.sp2px().toFloat()
        mTitlePaint.isAntiAlias = true
        mTitlePaint.style = Paint.Style.FILL
        mTitlePaint.color = mCoordinateConfig.color

        mPointPaint.isAntiAlias = true
        mPointPaint.style = Paint.Style.FILL
        mPointPaint.color = Color.BLUE
    }

    fun onSizeChanged(w: Int, h: Int, oldW: Int, oldH: Int) {
        mWidth = w
        mHeight = h

        mXPath.reset()
        mYPath.reset()

        mCoordinateOriginalX = mCoordinateConfig.padding.toFloat()
        mCoordinateOriginalY = mHeight - mCoordinateConfig.padding.toFloat()

        mXPath.moveTo(mCoordinateOriginalX, mCoordinateOriginalY)
        mXPath.lineTo((mWidth - mCoordinateConfig.padding).toFloat(), mCoordinateOriginalY)
        mXPathMeasure = PathMeasure(mXPath, false)

        mYPath.moveTo(mCoordinateOriginalX, mCoordinateOriginalY)
        mYPath.lineTo(mCoordinateOriginalX, mCoordinateConfig.padding.toFloat())
        mYPathMeasure = PathMeasure(mYPath, false)

        val xDash = Path()
        xDash.addRect(
            0F,
            0F,
            mCoordinateConfig.dashWidth.toFloat(),
            -mCoordinateConfig.dashWidth.toFloat() * 2,
            Path.Direction.CW
        )

        val yDash = Path()
        yDash.addRect(
            0F,
            0F,
            mCoordinateConfig.dashWidth.toFloat(),
            mCoordinateConfig.dashWidth.toFloat() * 2,
            Path.Direction.CW
        )
        mXPathEffect = PathDashPathEffect(
            xDash,
            (mXPathMeasure!!.length - mCoordinateConfig.dashWidth.toFloat()) / mCoordinateConfig.xPartition,
            0F,
            PathDashPathEffect.Style.ROTATE
        )

        mYPathEffect = PathDashPathEffect(
            yDash,
            (mYPathMeasure!!.length - mCoordinateConfig.dashWidth.toFloat()) / mCoordinateConfig.yPartition,
            0F,
            PathDashPathEffect.Style.ROTATE
        )

    }

    fun drawCoordinate(canvas: Canvas) {
        canvas.drawPath(mXPath, mCoordinatePaint)
        canvas.drawPath(mYPath, mCoordinatePaint)

        mCoordinatePaint.pathEffect = mXPathEffect
        canvas.drawPath(mXPath, mCoordinatePaint)

        mCoordinatePaint.pathEffect = mYPathEffect
        canvas.drawPath(mYPath, mCoordinatePaint)

        mCoordinatePaint.pathEffect = null

        drawAxisValues(canvas)
    }

    private fun drawAxisValues(canvas: Canvas) {
        val minX = mData.getMinX()
        val minY = mData.getMinY()
        val maxX = mData.getMaxX()
        val maxY = mData.getMaxY()

        val xPartitionValue = ((maxX - minX) / mCoordinateConfig.xPartition)
        val xPathStep = (mXPathMeasure?.length ?: 0F) / mCoordinateConfig.xPartition

        var diffX = 0F
        for (i in minX..maxX step xPartitionValue) {
            val text = "$i"
            mTextPaint.getTextBounds(text, 0, text.length, mTempTextBound)

            canvas.drawText(
                text,
                mCoordinateOriginalX + diffX - mTempTextBound.centerX(),
                mCoordinateOriginalY - mTempTextBound.top + TEXT_PADDING_AXIS,
                mTextPaint
            )
            diffX += xPathStep
        }

        val yPartitionValue = ((maxY - minY)) / mCoordinateConfig.yPartition
        val yPathStep = (mYPathMeasure?.length ?: 0F) / mCoordinateConfig.yPartition

        var diffY = 0F
        for (i in 0..mCoordinateConfig.yPartition) {
            val text = String.format("%.2f", minY + yPartitionValue * i)
            mTextPaint.getTextBounds(text, 0, text.length, mTempTextBound)

            canvas.drawText(
                text,
                mCoordinateOriginalX - mTempTextBound.width() - TEXT_PADDING_AXIS,
                mCoordinateOriginalY - diffY + mTempTextBound.height() / 2,
                mTextPaint
            )
            diffY += yPathStep
        }
    }

    fun drawTitle(canvas: Canvas) {
        val title = mData.getTitle()
        mTextPaint.getTextBounds(title, 0, title.length, mTempTextBound)
        canvas.drawText(
            title,
            (mWidth / 2 - mTempTextBound.centerX()).toFloat(),
            mCoordinateConfig.padding.toFloat(),
            mTitlePaint
        )
    }

    fun drawPoints(canvas: Canvas) {
        val data = mData.getDataList()
        val time = mData.getTimeList()

        val size = data.size
        val xPathLength = mXPathMeasure?.length ?: 0F
        val yPathLength = mYPathMeasure?.length ?: 0F
        val yPathLengthStep = yPathLength / mCoordinateConfig.yPartition

        val yMax = mData.getMaxY()
        val yMin = mData.getMinY()
        val yStep = (yMax - yMin) / mCoordinateConfig.yPartition
        var zeroPosition = 0

        for (i in 0..mCoordinateConfig.yPartition) {
            val y = yMin + i * yStep
            if (doubleEquals(y, 0.0)) {
                zeroPosition = i
                break
            }
        }


        val originalY = mCoordinateOriginalY - zeroPosition * yPathLengthStep
        for (i in 0 until size step mCoordinateConfig.pickDataInterval) {
            val xValue = time[i]
            val xAxisValue =
                ((xValue - mData.getMinX()).toFloat() / (mData.getMaxX() - mData.getMinX())) * xPathLength + mCoordinateOriginalX

            val yValue = data[i]
            val yAxisValue =
                originalY - (yValue / (mData.getMaxY() - mData.getMinY()) * yPathLength)

            canvas.drawCircle(
                xAxisValue,
                yAxisValue.toFloat(),
                mCoordinateConfig.dataPointSize,
                mPointPaint
            )
        }
    }

    private fun doubleEquals(double1: Double, double2: Double): Boolean {
        return abs(double1 - double2) < 0.00000001
    }
}