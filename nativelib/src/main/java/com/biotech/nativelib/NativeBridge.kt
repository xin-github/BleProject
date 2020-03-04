package com.biotech.nativelib

/**
 * @author TuXin
 * @date 2020-02-25 22:21.
 *
 *
 * Email : tuxin@pupupula.com
 */
class NativeBridge {
    companion object {
        @JvmStatic
        external fun stringFromJNI(): String

        @JvmStatic
        external fun filterAll(doubleArray: DoubleArray, size: Int): DoubleArray

        @JvmStatic
        external fun fftCompare(doubleArray: DoubleArray, size: Int): Array<DoubleArray>

        @JvmStatic
        external fun arv_rmsCompare(doubleArray: DoubleArray, size: Int): Array<DoubleArray>


        init {
            System.loadLibrary("native-lib")
        }
    }
}
