/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ARV_RMS.cpp
 *
 * Code generation for function 'ARV_RMS'
 *
 */

/* Include files */
#include <cmath>
#include "ARV_RMS.h"
#include "../emxutil.h"

/* Function Definitions */
void ARV_RMS(double window_num, const emxArray_real_T *EMG, double Fs,
             emxArray_real_T *ARV, emxArray_real_T *RMS)
{
  int i0;
  int k;
  emxArray_real_T *y;
  int N;
  double d0;
  int i1;
  int vlen;
  double b_y;
  boolean_T guard1 = false;
  int i2;
  i0 = static_cast<int>(window_num);
  k = ARV->size[0] * ARV->size[1];
  ARV->size[0] = 1;
  ARV->size[1] = i0;
  emxEnsureCapacity_real_T(ARV, k);
  k = RMS->size[0] * RMS->size[1];
  RMS->size[0] = 1;
  RMS->size[1] = i0;
  emxEnsureCapacity_real_T(RMS, k);
  emxInit_real_T(&y, 1);
  for (N = 0; N < i0; N++) {
    d0 = Fs * (1.0 + static_cast<double>(N));
    if (1.0 > d0) {
      k = 0;
    } else {
      k = static_cast<int>(d0);
    }

    i1 = k - 1;
    vlen = y->size[0];
    y->size[0] = k;
    emxEnsureCapacity_real_T(y, vlen);
    for (k = 0; k <= i1; k++) {
      y->data[k] = std::abs(EMG->data[k]);
    }

    vlen = y->size[0];
    if (y->size[0] == 0) {
      b_y = 0.0;
    } else {
      b_y = y->data[0];
      for (k = 2; k <= vlen; k++) {
        b_y += y->data[k - 1];
      }
    }

    ARV->data[N] = b_y / d0;
    if (1.0 > d0) {
      vlen = 0;
    } else {
      vlen = static_cast<int>(d0);
    }

    guard1 = false;
    if (vlen == 1) {
      guard1 = true;
    } else {
      if (1.0 > d0) {
        i2 = 0;
      } else {
        i2 = static_cast<int>(d0);
      }

      if (i2 == 1) {
        guard1 = true;
      } else {
        b_y = 0.0;
        for (k = 0; k < vlen; k++) {
          b_y += EMG->data[k] * EMG->data[k];
        }
      }
    }

    if (guard1) {
      b_y = 0.0;
      for (k = 0; k < vlen; k++) {
        b_y += EMG->data[k] * EMG->data[k];
      }
    }

    RMS->data[N] = std::sqrt(b_y / d0);
  }

  emxFree_real_T(&y);
}

/* End of code generation (ARV_RMS.cpp) */
