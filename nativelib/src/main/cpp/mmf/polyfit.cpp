/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * polyfit.cpp
 *
 * Code generation for function 'polyfit'
 *
 */

/* Include files */
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "polyfit.h"
#include "median_mean_frequency_emxutil.h"
#include "xgeqp3.h"
#include "../emxutil.h"

/* Function Definitions */
void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double p[2])
{
  emxArray_real_T *V;
  int i2;
  emxArray_real_T *B;
  int m;
  int u0;
  double tau_data[2];
  int tau_size[1];
  int jpvt[2];
  int mn;
  int j;
  int i;
  double wj;
  emxInit_real_T(&V, 2);
  i2 = V->size[0] * V->size[1];
  V->size[0] = x->size[1];
  V->size[1] = 2;
  emxEnsureCapacity_real_T(V, i2);
  if (V->size[0] != 0) {
    i2 = x->size[1];
    for (m = 0; m < i2; m++) {
      V->data[m + V->size[0]] = 1.0;
    }

    i2 = x->size[1];
    for (m = 0; m < i2; m++) {
      V->data[m] = x->data[m];
    }
  }

  emxInit_real_T(&B, 1);
  i2 = B->size[0];
  B->size[0] = y->size[1];
  emxEnsureCapacity_real_T(B, i2);
  m = y->size[1];
  for (i2 = 0; i2 < m; i2++) {
    B->data[i2] = y->data[i2];
  }

  u0 = V->size[0];
  if (u0 >= 2) {
    u0 = 2;
  }

  xgeqp3(V, tau_data, tau_size, jpvt);
  p[0] = 0.0;
  p[1] = 0.0;
  m = V->size[0];
  mn = V->size[0];
  if (mn >= 2) {
    mn = 2;
  }

  for (j = 0; j < mn; j++) {
    if (tau_data[j] != 0.0) {
      wj = B->data[j];
      i2 = j + 2;
      for (i = i2; i <= m; i++) {
        wj += V->data[(i + V->size[0] * j) - 1] * B->data[i - 1];
      }

      wj *= tau_data[j];
      if (wj != 0.0) {
        B->data[j] -= wj;
        i2 = j + 2;
        for (i = i2; i <= m; i++) {
          B->data[i - 1] -= V->data[(i + V->size[0] * j) - 1] * wj;
        }
      }
    }
  }

  for (i = 0; i < u0; i++) {
    p[jpvt[i] - 1] = B->data[i];
  }

  emxFree_real_T(&B);
  for (j = u0; j >= 1; j--) {
    m = jpvt[j - 1] - 1;
    p[m] /= V->data[(j + V->size[0] * (j - 1)) - 1];
    for (i = 0; i <= j - 2; i++) {
      p[jpvt[0] - 1] -= p[m] * V->data[V->size[0] * (j - 1)];
    }
  }

  emxFree_real_T(&V);
}

/* End of code generation (polyfit.cpp) */
