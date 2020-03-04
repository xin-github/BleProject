//
// Created by 涂鑫 on 2020-02-25.
//
#include <jni.h>
#include <string>
#include <vector>

#include "types.h"
#include "emxAPI.h"
#include "filter_all/filter_all.h"
#include "fft/fft_compare.h"
#include "fft/fft_compare_initialize.h"
#include "mmf/median_mean_frequency.h"
#include "arv_rms/ARV_RMS.h"

emxArray_real_T *main_filter_all(double data[], int size);

emxArray_real_T *argInit_Unboundedx1_real_T();

emxArray_real_T *argInit_Unboundedx1_real_T(const double *data, int size);

static void main_fft_compare(emxArray_real_T *EMG);

static double argInit_real_T();

extern "C" JNIEXPORT jstring JNICALL
Java_com_biotech_nativelib_NativeBridge_stringFromJNI(
        JNIEnv *env, jclass) {
    std::string hello = "Hello From C++";

    return env->NewStringUTF(hello.c_str());
}

int checkExc(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe(); // writes to logcat
        env->ExceptionClear();
        return 1;
    }
    return -1;
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_biotech_nativelib_NativeBridge_filterAll(
        JNIEnv *env, jclass, jdoubleArray originalData, jint size) {
    double *doubleArray;

    doubleArray = env->GetDoubleArrayElements(originalData, NULL);
    if (doubleArray == NULL) return NULL;
    // ============== filter all =================
    emxArray_real_T *EMG = main_filter_all(doubleArray, size);

    jdoubleArray jEMG = env->NewDoubleArray(EMG->size[0]);
    env->SetDoubleArrayRegion(jEMG, 0, EMG->size[0], EMG->data);
    return jEMG;
}

emxArray_real_T *main_filter_all(double data[], int size) {
    emxArray_real_T *EMG;
    emxArray_real_T *input;

    emxInitArray_real_T(&EMG, 1);

    input = argInit_Unboundedx1_real_T(data, size);

    filter_all(input, EMG);

    emxDestroyArray_real_T(input);
    return EMG;
}


extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_biotech_nativelib_NativeBridge_fftCompare(JNIEnv *env, jclass, jdoubleArray originalData,
                                                   jint size) {
    double *doubleArray = env->GetDoubleArrayElements(originalData, NULL);
    if (doubleArray == NULL) return NULL;

    double Fs = 1000;
    fft_compare_initialize();

    emxArray_real_T *EMG = argInit_Unboundedx1_real_T(doubleArray, size);
    emxArray_real_T *P1;
    emxArray_real_T *f;
    emxInitArray_real_T(&P1, 1);
    emxInitArray_real_T(&f, 2);

    /* Initialize function 'fft_compare' input arguments. */
    int L = size;
    if (L % 2 == 1) {
        L = L - 1;
    }

    /* Call the entry-point 'fft_compare'. */
    fft_compare(Fs, EMG, L, P1, f);

    // change P1 to jP1
    jdoubleArray jP1 = env->NewDoubleArray(P1->size[0]);
    env->SetDoubleArrayRegion(jP1, 0, P1->size[0], P1->data);

    // change f to jf
    jdoubleArray jf = env->NewDoubleArray(f->size[1]);
    env->SetDoubleArrayRegion(jf, 0, f->size[1], f->data);

    // create jRes
    jclass doubleArrCls = env->FindClass("[D");
    jobjectArray jRes = env->NewObjectArray(2, doubleArrCls, NULL);

    env->SetObjectArrayElement(jRes, 0, jP1);
    env->SetObjectArrayElement(jRes, 1, jf);

    emxDestroyArray_real_T(EMG);
    emxDestroyArray_real_T(f);
    emxDestroyArray_real_T(P1);
    return jRes;
}


extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_biotech_nativelib_NativeBridge_arv_1rmsCompare(JNIEnv *env, jclass, jdoubleArray originalData,
                                                        jint size) {
    double *doubleArray = env->GetDoubleArrayElements(originalData, NULL);
    if (doubleArray == NULL) return NULL;

    double Fs = 1000;
    fft_compare_initialize();

    emxArray_real_T *EMG = argInit_Unboundedx1_real_T(doubleArray, size);
    // ============= ARV_RMS ==============
    emxArray_real_T *ARV;
    emxArray_real_T *RMS;

    int window_num = static_cast<int>(size / Fs);
    emxInitArray_real_T(&ARV, 2);
    emxInitArray_real_T(&RMS, 2);

    /* Call the entry-point 'ARV_RMS'. */
    ARV_RMS(window_num, EMG, Fs, ARV, RMS);

    int size1 = ARV->size[0];
    int size2 = ARV->size[1];
    // change ARV to jARV
    jdoubleArray jARV = env->NewDoubleArray(ARV->size[1]);
    env->SetDoubleArrayRegion(jARV, 0, ARV->size[1], ARV->data);

    // change RMS to jRMS
    jdoubleArray jRMS = env->NewDoubleArray(RMS->size[1]);
    env->SetDoubleArrayRegion(jRMS, 0, RMS->size[1], RMS->data);

    // create jRes
    jclass doubleArrCls = env->FindClass("[D");
    jobjectArray jRes = env->NewObjectArray(2, doubleArrCls, NULL);

    env->SetObjectArrayElement(jRes, 0, jARV);
    env->SetObjectArrayElement(jRes, 1, jRMS);

    emxDestroyArray_real_T(EMG);
    emxDestroyArray_real_T(RMS);
    emxDestroyArray_real_T(ARV);
    return jRes;

}

static double argInit_real_T() {
    return 0.0;
}

emxArray_real_T *argInit_Unboundedx1_real_T() {
    emxArray_real_T *result;
    static int iv0[1] = {2};

    int idx0;

    /* Set the size of the array.
       Change this size to the value that the application requires. */
    result = emxCreateND_real_T(1, iv0);

    /* Loop over the array to initialize each element. */
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        /* Set the value of the array element.
           Change this value to the value that the application requires. */
        result->data[idx0] = argInit_real_T();
    }

    return result;
}

emxArray_real_T *argInit_Unboundedx1_real_T(const double *data, int size) {
    emxArray_real_T *result;
    int iv0[1]{size};

    int idx0;

    /* Set the size of the array.
       Change this size to the value that the application requires. */
    result = emxCreateND_real_T(1, iv0);

    /* Loop over the array to initialize each element. */
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        /* Set the value of the array element.
           Change this value to the value that the application requires. */
        result->data[idx0] = data[idx0];
    }

    return result;
}

//static void main_fft_compare(emxArray_real_T *EMG)
//{
//
//    fft_compare_initialize();
//
//    emxArray_real_T *P1;
//    emxArray_real_T *f;
//    emxInitArray_real_T(&P1, 1);
//    emxInitArray_real_T(&f, 2);
//
//    /* Initialize function 'fft_compare' input arguments. */
//    double Fs;
//    Fs = argInit_real_T();
//    Fs = 1000;
//
//    /* Initialize function input argument 'EMG'. */
////    EMG = argInit_Unboundedx1_real_T();
//
//    /* Call the entry-point 'fft_compare'. */
//    fft_compare(Fs, EMG, argInit_real_T(), P1, f);
//
//    emxDestroyArray_real_T(f);
//    emxDestroyArray_real_T(P1);
//    emxDestroyArray_real_T(EMG);
//}


static emxArray_real_T *argInit_1xUnbounded_real_T() {
    emxArray_real_T *result;
    int idx1;

    /* Set the size of the array.
       Change this size to the value that the application requires. */
    result = emxCreate_real_T(1, 2);

    /* Loop over the array to initialize each element. */
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
        /* Set the value of the array element.
           Change this value to the value that the application requires. */
        result->data[idx1] = argInit_real_T();
    }

    return result;
}

static void main_median_mean_frequency() {
    emxArray_real_T *temp_mdf;
    emxArray_real_T *temp_mef;
    emxArray_real_T *mdf;
    emxArray_real_T *mef;
    emxArray_real_T *t;
    emxInitArray_real_T(&temp_mdf, 2);
    emxInitArray_real_T(&temp_mef, 2);

    /* Initialize function 'median_mean_frequency' input arguments. */
    /* Initialize function input argument 'mdf'. */
    mdf = argInit_1xUnbounded_real_T();

    /* Initialize function input argument 'mef'. */
    mef = argInit_1xUnbounded_real_T();

    /* Initialize function input argument 't'. */
    t = argInit_1xUnbounded_real_T();

    /* Call the entry-point 'median_mean_frequency'. */
    median_mean_frequency(mdf, mef, t, temp_mdf, temp_mef);
    emxDestroyArray_real_T(temp_mef);
    emxDestroyArray_real_T(temp_mdf);
    emxDestroyArray_real_T(t);
    emxDestroyArray_real_T(mef);
    emxDestroyArray_real_T(mdf);
}

// [[Rcpp::export]]
double median_freq(double *values, int *freqs, int length) {
    const int len = length;
    std::vector<std::pair<double, int>> allDat;
    int freqSum = 0;
    for (int i = 0; i < len; ++i) {
        allDat.push_back(std::pair<double, int>(values[i], freqs[i]));
        freqSum += freqs[i];
    }
    std::sort(allDat.begin(), allDat.end());
    int accum = 0;
    for (int i = 0; i < len; ++i) {
        accum += allDat[i].second;
        if (freqSum % 2 == 0) {
            if (accum > freqSum / 2) {
                return allDat[i].first;
            } else if (accum == freqSum / 2) {
                return (allDat[i].first + allDat[i + 1].first) / 2;
            }
        } else {
            if (accum >= (freqSum + 1) / 2) {
                return allDat[i].first;
            }
        }
    }
    return 0;  // Should not be reached
}

//
//int main(int, const char * const [])
//{
//    /* Initialize the application.
//       You do not need to do this more than one time. */
//    median_mean_frequency_initialize();
//
//    /* Invoke the entry-point functions.
//       You can call entry-point functions multiple times. */
//    main_median_mean_frequency();
//
//    /* Terminate the application.
//       You do not need to do this more than one time. */
//    median_mean_frequency_terminate();
//    return 0;
//}

//static void main_ARV_RMS()
//{
//    emxArray_real_T *ARV;
//    emxArray_real_T *RMS;
//    double window_num;
//    emxArray_real_T *EMG;
//    emxInitArray_real_T(&ARV, 2);
//    emxInitArray_real_T(&RMS, 2);
//
//    /* Initialize function 'ARV_RMS' input arguments. */
//    double Fs = 1000;
//    window_num = argInit_real_T();
//
//    /* Initialize function input argument 'EMG'. */
//    EMG = argInit_Unboundedx1_real_T();
//
//    /* Call the entry-point 'ARV_RMS'. */
//    ARV_RMS(window_num, EMG, Fs, ARV, RMS);
//    emxDestroyArray_real_T(RMS);
//    emxDestroyArray_real_T(ARV);
//    emxDestroyArray_real_T(EMG);
//}

//int main(int, const char * const [])
//{
//    /* Initialize the application.
//       You do not need to do this more than one time. */
//    ARV_RMS_initialize();
//
//    /* Invoke the entry-point functions.
//       You can call entry-point functions multiple times. */
//    main_ARV_RMS();
//
//    /* Terminate the application.
//       You do not need to do this more than one time. */
//    ARV_RMS_terminate();
//    return 0;
//}