/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filter_all.cpp
 *
 * Code generation for function 'filter_all'
 *
 */

/* Include files */
#include "filter_all.h"
#include "../emxutil.h"
#include "filter.h"

/* Function Definitions */
void filter_all(const emxArray_real_T *input, emxArray_real_T *EMG)
{
  emxArray_real_T *y;
  unsigned int input_idx_0;
  int i0;
  int nx;
  int loop_ub;
  emxArray_real_T *x;
  int a_tmp;
  emxArray_real_T *r0;
  int naxpy;
  int j;
  static const double dv0[7] = { 0.83346944981564608, -5.0008166988938765,
    12.502041747234692, -16.669388996312922, 12.502041747234692,
    -5.0008166988938765, 0.83346944981564608 };

  double as;
  static const double dv1[7] = { 1.0, -5.6358809154902492, 13.245104571761678,
    -16.614170156135557, 11.731246791933405, -4.4209710291044653,
    0.69467132377599572 };

  static const double dv2[32] = { 8.1045061070192381E-15, 2.5123968931759638E-13,
    3.7685953397639457E-12, 3.6429754951051475E-11, 2.5500828465736033E-10,
    1.3770447371497458E-9, 5.9671938609822317E-9, 2.1311406646365113E-8,
    6.3934219939095339E-8, 1.6338745095546587E-7, 3.5945239210202491E-7,
    6.8622729401295664E-7, 1.1437121566882611E-6, 1.6715793059289969E-6,
    2.1491733933372818E-6, 2.4357298457822527E-6, 2.4357298457822527E-6,
    2.1491733933372818E-6, 1.6715793059289969E-6, 1.1437121566882611E-6,
    6.8622729401295664E-7, 3.5945239210202491E-7, 1.6338745095546587E-7,
    6.3934219939095339E-8, 2.1311406646365113E-8, 5.9671938609822317E-9,
    1.3770447371497458E-9, 2.5500828465736033E-10, 3.6429754951051475E-11,
    3.7685953397639457E-12, 2.5123968931759638E-13, 8.1045061070192381E-15 };

  static const double dv3[32] = { 1.0, -13.635855403309318, 92.673295217923325,
    -416.63548581813751, 1388.5301093230964, -3646.6195542903051,
    7836.5291495465508, -14131.843171654305, 21768.136858689446,
    -29013.238385340723, 33781.333113732951, -34606.53160655003,
    31356.468359952516, -25224.703503198612, 18061.717538569494,
    -11528.190264843241, 6562.0396586078168, -3329.5694548264064,
    1503.8059241444494, -603.11127009832649, 214.02841295942164,
    -66.884397328640119, 18.289420412285235, -4.3401014874851667,
    0.88415668580390094, -0.152436345922389, 0.021817774412034033,
    -0.0025234907973638414, 0.00022669068236374966, -1.4843658897713815E-5,
    6.3037891635691617E-7, -1.3034013557226251E-8 };

  static const double dv4[3] = { 0.98409876658035933, -0.83801775132929435,
    0.98409876658035933 };

  static const double dv5[3] = { 1.0, -0.83801775132929435, 0.96819753316071866
  };

  emxInit_real_T(&y, 1);
  input_idx_0 = static_cast<unsigned int>(input->size[0]);
  i0 = y->size[0];
  y->size[0] = static_cast<int>(input_idx_0);
  emxEnsureCapacity_real_T(y, i0);
  nx = input->size[0] - 1;
  loop_ub = y->size[0];
  i0 = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    y->data[i0] = 0.0;
  }

  for (loop_ub = 0; loop_ub <= nx; loop_ub++) {
    a_tmp = nx - loop_ub;
    naxpy = a_tmp + 1;
    if (naxpy >= 7) {
      naxpy = 7;
    }

    for (j = 0; j < naxpy; j++) {
      i0 = loop_ub + j;
      y->data[i0] += input->data[loop_ub] * dv0[j];
    }

    if (a_tmp < 6) {
      naxpy = a_tmp;
    } else {
      naxpy = 6;
    }

    as = -y->data[loop_ub];
    for (j = 0; j < naxpy; j++) {
      i0 = (loop_ub + j) + 1;
      y->data[i0] += as * dv1[1 + j];
    }
  }

  emxInit_real_T(&x, 1);
  emxInit_real_T(&r0, 1);
  filter(y, r0);
  b_filter(r0, x);
  input_idx_0 = static_cast<unsigned int>(x->size[0]);
  i0 = y->size[0];
  y->size[0] = static_cast<int>(input_idx_0);
  emxEnsureCapacity_real_T(y, i0);
  nx = x->size[0] - 1;
  loop_ub = y->size[0];
  i0 = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    y->data[i0] = 0.0;
  }

  for (loop_ub = 0; loop_ub <= nx; loop_ub++) {
    a_tmp = nx - loop_ub;
    naxpy = a_tmp + 1;
    if (naxpy >= 32) {
      naxpy = 32;
    }

    for (j = 0; j < naxpy; j++) {
      i0 = loop_ub + j;
      y->data[i0] += x->data[loop_ub] * dv2[j];
    }

    if (a_tmp < 31) {
      naxpy = a_tmp;
    } else {
      naxpy = 31;
    }

    as = -y->data[loop_ub];
    for (j = 0; j < naxpy; j++) {
      i0 = (loop_ub + j) + 1;
      y->data[i0] += as * dv3[1 + j];
    }
  }

  emxFree_real_T(&x);
  input_idx_0 = static_cast<unsigned int>(y->size[0]);
  i0 = EMG->size[0];
  EMG->size[0] = static_cast<int>(input_idx_0);
  emxEnsureCapacity_real_T(EMG, i0);
  nx = y->size[0] - 1;
  loop_ub = EMG->size[0];
  i0 = EMG->size[0];
  EMG->size[0] = loop_ub;
  emxEnsureCapacity_real_T(EMG, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    EMG->data[i0] = 0.0;
  }

  for (loop_ub = 0; loop_ub <= nx; loop_ub++) {
    a_tmp = nx - loop_ub;
    naxpy = a_tmp + 1;
    if (naxpy >= 3) {
      naxpy = 3;
    }

    for (j = 0; j < naxpy; j++) {
      i0 = loop_ub + j;
      EMG->data[i0] += y->data[loop_ub] * dv4[j];
    }

    if (a_tmp < 2) {
      naxpy = a_tmp;
    } else {
      naxpy = 2;
    }

    as = -EMG->data[loop_ub];
    for (j = 0; j < naxpy; j++) {
      i0 = (loop_ub + j) + 1;
      EMG->data[i0] += as * dv5[1 + j];
    }
  }

  emxFree_real_T(&y);
  b_filter(EMG, r0);
  filter(r0, EMG);
  emxFree_real_T(&r0);
}

/* End of code generation (filter_all.cpp) */
