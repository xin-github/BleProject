package com.biotech.commonlib.utils

import android.content.res.Resources
import android.util.TypedValue
import io.reactivex.disposables.CompositeDisposable
import io.reactivex.disposables.Disposable

fun Int.toTextSizeValue(): Float {
    val resources = Resources.getSystem()
    return TypedValue.applyDimension(
        TypedValue.COMPLEX_UNIT_SP,
        this.toFloat(),
        resources.displayMetrics
    )
}

fun String.splitU(s: String): List<String>? {
    if (this.contains(s)) {
        return this.split(s)
    }
    return null
}

fun Disposable?.addTo(disposable: CompositeDisposable?) {
    if (disposable != null && this != null) {
        disposable.add(this)
    }
}