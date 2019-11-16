package com.pupupula.blelib.util

import android.Manifest
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.content.Context
import android.content.pm.PackageManager
import android.os.Build
import android.preference.PreferenceManager
import android.provider.Settings
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat

/**
 * On some devices running Android Marshmallow or newer location services must be enabled in
 * order to scan for Bluetooth LE devices. This method returns whether the Location has been
 * enabled or not.
 *
 * @return True on Android 6.0+ if location mode is different than LOCATION_MODE_OFF.
 * It always returns true on Android versions prior to Marshmallow.
 */
fun isLocationEnabled(context: Context): Boolean {
    if (isMarshmallowOrAbove()) {
        var locationMode = Settings.Secure.LOCATION_MODE_OFF
        try {
            locationMode = Settings.Secure.getInt(context.contentResolver,
                    Settings.Secure.LOCATION_MODE)
        } catch (e: Settings.SettingNotFoundException) {
            // do nothing
        }

        return locationMode != Settings.Secure.LOCATION_MODE_OFF
    }
    return true
}

fun isMarshmallowOrAbove(): Boolean {
    return Build.VERSION.SDK_INT >= Build.VERSION_CODES.M
}

/**
 * Checks whether Bluetooth is enabled.
 *
 * @return true if Bluetooth is enabled, false otherwise.
 */
fun isBleEnabled(): Boolean {
    val adapter = BluetoothAdapter.getDefaultAdapter()
    return adapter != null && adapter.isEnabled
}

/**
 * Checks for required permissions.
 *
 * @return True if permissions are already granted, false otherwise.
 */
fun isLocationPermissionsGranted(context: Context): Boolean {
    return ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED
}
