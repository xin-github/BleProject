package com.biotech.commonlib

import android.app.Activity
import android.app.Application
import android.os.Bundle
import android.text.TextUtils

import java.io.BufferedReader
import java.io.FileReader
import java.io.IOException
import java.util.ArrayList

/**
 * @author TuXin
 * @date 2018/12/19 下午5:54.
 *
 *
 * Email : tuxin@pupupula.com
 */
class BaseApplication : Application(), Application.ActivityLifecycleCallbacks {
    var activityCount: Int = 0
        private set
    var curActivity: Activity? = null
        private set
    private var currentProcessName: String? = null

    override fun onCreate() {
        super.onCreate()
        instance = this
        currentProcessName = getProcessName(android.os.Process.myPid())

        if (currentProcessName == null || packageName == currentProcessName) {
            registerActivityLifecycleCallbacks(this)
        }
    }

    override fun onActivityCreated(activity: Activity, savedInstanceState: Bundle?) {

    }

    override fun onActivityStarted(activity: Activity) {

    }

    override fun onActivityResumed(activity: Activity) {
        // from 0=>1 means from background=>foreground
        if (activityCount == 0) {
            for (listener in mRunStateListeners) {
                listener.onChange(false)
            }
        }
        activityCount++
        curActivity = activity
    }

    override fun onActivityPaused(activity: Activity) {

    }

    override fun onActivityStopped(activity: Activity) {
        activityCount--
        // from 1=>0 means from foreground=>background
        if (activityCount == 0) {
            for (listener in mRunStateListeners) {
                listener.onChange(true)
            }
        }
        if (activity === curActivity) {
            curActivity = null
        }
    }

    override fun onActivitySaveInstanceState(activity: Activity, outState: Bundle) {

    }

    override fun onActivityDestroyed(activity: Activity) {
        if (activity === curActivity) {
            curActivity = null
        }
    }


    interface OnAppRunStateChangeListener {
        fun onChange(isBackgroundNow: Boolean)
    }

    companion object {
        var instance: BaseApplication? = null
            private set

        private val mRunStateListeners = ArrayList<OnAppRunStateChangeListener>()

        fun registerRunStateListener(listener: OnAppRunStateChangeListener) {
            if (!mRunStateListeners.contains(listener)) {
                mRunStateListeners.add(listener)
            }
        }

        fun unregisterRunStateListener(listener: OnAppRunStateChangeListener) {
            mRunStateListeners.remove(listener)
        }

        /**
         * 获取进程号对应的进程名
         *
         * @param pid 进程号
         * @return 进程名
         */
        private fun getProcessName(pid: Int): String? {
            var reader: BufferedReader? = null
            try {
                reader = BufferedReader(FileReader("/proc/$pid/cmdline"))
                var processName = reader.readLine()
                if (!TextUtils.isEmpty(processName)) {
                    processName = processName.trim { it <= ' ' }
                }
                return processName
            } catch (throwable: Throwable) {
                throwable.printStackTrace()
            } finally {
                try {
                    reader?.close()
                } catch (exception: IOException) {
                    exception.printStackTrace()
                }

            }
            return null
        }
    }
}
