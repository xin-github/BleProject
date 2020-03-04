/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft_compare.cpp
 *
 * Code generation for function 'fft_compare'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "fft_compare.h"
#include "../emxutil.h"
#include "fft.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

void fft_compare(double Fs, const emxArray_real_T *EMG, double L,
                 emxArray_real_T *P1, emxArray_real_T *f)
{
  emxArray_creal_T *z;
  int i0;
  int loop_ub;
  emxArray_real_T *P2;
  double z_re;
  int nx;
  double z_im;
  unsigned int z_idx_0;
  int i1;
  emxInit_creal_T(&z, 1);
  fft(EMG, z);
  i0 = z->size[0];
  emxEnsureCapacity_creal_T(z, i0);
  loop_ub = z->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z_re = z->data[i0].re;
    z_im = z->data[i0].im;
    if (z_im == 0.0) {
      z->data[i0].re = z_re / L;
      z->data[i0].im = 0.0;
    } else if (z_re == 0.0) {
      z->data[i0].re = 0.0;
      z->data[i0].im = z_im / L;
    } else {
      z->data[i0].re = z_re / L;
      z->data[i0].im = z_im / L;
    }
  }

  emxInit_real_T(&P2, 1);
  nx = z->size[0];
  z_idx_0 = static_cast<unsigned int>(z->size[0]);
  i0 = P2->size[0];
  P2->size[0] = static_cast<int>(z_idx_0);
  emxEnsureCapacity_real_T(P2, i0);
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    P2->data[loop_ub] = rt_hypotd_snf(z->data[loop_ub].re, z->data[loop_ub].im);
  }

  emxFree_creal_T(&z);
  z_re = L / 2.0 + 1.0;
  if (1.0 > z_re) {
    loop_ub = -1;
  } else {
    loop_ub = static_cast<int>(z_re) - 1;
  }

  i0 = P1->size[0];
  P1->size[0] = loop_ub + 1;
  emxEnsureCapacity_real_T(P1, i0);
  for (i0 = 0; i0 <= loop_ub; i0++) {
    P1->data[i0] = P2->data[i0];
  }

  i0 = (2 <= loop_ub);
  if (2 > loop_ub) {
    nx = -1;
    loop_ub = 0;
  } else {
    nx = 0;
  }

  loop_ub = (loop_ub - nx) - 1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    P1->data[(nx + i1) + 1] = 2.0 * P2->data[i0 + i1];
  }

  emxFree_real_T(&P2);
  z_re = L / 2.0;
  if (rtIsNaN(z_re)) {
    i0 = f->size[0] * f->size[1];
    f->size[0] = 1;
    f->size[1] = 1;
    emxEnsureCapacity_real_T(f, i0);
    f->data[0] = rtNaN;
  } else if (z_re < 0.0) {
    f->size[0] = 1;
    f->size[1] = 0;
  } else if (rtIsInf(z_re) && (0.0 == z_re)) {
    i0 = f->size[0] * f->size[1];
    f->size[0] = 1;
    f->size[1] = 1;
    emxEnsureCapacity_real_T(f, i0);
    f->data[0] = rtNaN;
  } else {
    i0 = f->size[0] * f->size[1];
    f->size[0] = 1;
    loop_ub = static_cast<int>(std::floor(z_re));
    f->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(f, i0);
    for (i0 = 0; i0 <= loop_ub; i0++) {
      f->data[i0] = i0;
    }
  }

  i0 = f->size[0] * f->size[1];
  nx = f->size[0] * f->size[1];
  f->size[0] = 1;
  emxEnsureCapacity_real_T(f, nx);
  loop_ub = i0 - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    f->data[i0] = Fs * f->data[i0] / L;
  }
}

/* End of code generation (fft_compare.cpp) */
