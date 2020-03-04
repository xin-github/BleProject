/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filter.cpp
 *
 * Code generation for function 'filter'
 *
 */

/* Include files */
#include "filter_all.h"
#include "filter.h"
#include "../emxutil.h"

/* Function Definitions */
void b_filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int i2;
  int nx;
  int loop_ub;
  int a_tmp;
  int naxpy;
  int j;
  static const double dv8[3] = { 0.9893431993199342, -1.4424003081139209,
    0.9893431993199342 };

  double as;
  static const double dv9[3] = { 1.0, -1.4424003081139209, 0.97868639863986839 };

  x_idx_0 = static_cast<unsigned int>(x->size[0]);
  i2 = y->size[0];
  y->size[0] = static_cast<int>(x_idx_0);
  emxEnsureCapacity_real_T(y, i2);
  nx = x->size[0] - 1;
  loop_ub = y->size[0];
  i2 = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    y->data[i2] = 0.0;
  }

  for (loop_ub = 0; loop_ub <= nx; loop_ub++) {
    a_tmp = nx - loop_ub;
    naxpy = a_tmp + 1;
    if (naxpy >= 3) {
      naxpy = 3;
    }

    for (j = 0; j < naxpy; j++) {
      i2 = loop_ub + j;
      y->data[i2] += x->data[loop_ub] * dv8[j];
    }

    if (a_tmp < 2) {
      naxpy = a_tmp;
    } else {
      naxpy = 2;
    }

    as = -y->data[loop_ub];
    for (j = 0; j < naxpy; j++) {
      i2 = (loop_ub + j) + 1;
      y->data[i2] += as * dv9[1 + j];
    }
  }
}

void filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int i1;
  int nx;
  int loop_ub;
  int a_tmp;
  int naxpy;
  int j;
  static const double dv6[3] = { 0.99464321026266433, -1.8495917375012585,
    0.99464321026266433 };

  double as;
  static const double dv7[3] = { 1.0, -1.8495917375012585, 0.98928642052532867 };

  x_idx_0 = static_cast<unsigned int>(x->size[0]);
  i1 = y->size[0];
  y->size[0] = static_cast<int>(x_idx_0);
  emxEnsureCapacity_real_T(y, i1);
  nx = x->size[0] - 1;
  loop_ub = y->size[0];
  i1 = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    y->data[i1] = 0.0;
  }

  for (loop_ub = 0; loop_ub <= nx; loop_ub++) {
    a_tmp = nx - loop_ub;
    naxpy = a_tmp + 1;
    if (naxpy >= 3) {
      naxpy = 3;
    }

    for (j = 0; j < naxpy; j++) {
      i1 = loop_ub + j;
      y->data[i1] += x->data[loop_ub] * dv6[j];
    }

    if (a_tmp < 2) {
      naxpy = a_tmp;
    } else {
      naxpy = 2;
    }

    as = -y->data[loop_ub];
    for (j = 0; j < naxpy; j++) {
      i1 = (loop_ub + j) + 1;
      y->data[i1] += as * dv7[1 + j];
    }
  }
}

/* End of code generation (filter.cpp) */
