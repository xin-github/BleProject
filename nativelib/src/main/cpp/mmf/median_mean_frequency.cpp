/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * median_mean_frequency.cpp
 *
 * Code generation for function 'median_mean_frequency'
 *
 */

/* Include files */
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "median_mean_frequency_emxutil.h"
#include "polyfit.h"
#include "filloutliers.h"
#include "../emxutil.h"

/* Function Definitions */
void median_mean_frequency(emxArray_real_T *mdf, emxArray_real_T *mef, const
  emxArray_real_T *t, emxArray_real_T *temp_mdf, emxArray_real_T *temp_mef)
{
  double p[2];
  int i3;
  boolean_T b0;
  int loop_ub;
  filloutliers(mdf);
  filloutliers(mef);
  polyfit(t, mdf, p);
  i3 = temp_mdf->size[0] * temp_mdf->size[1];
  temp_mdf->size[0] = 1;
  temp_mdf->size[1] = t->size[1];
  emxEnsureCapacity_real_T(temp_mdf, i3);
  b0 = (temp_mdf->size[1] == 0);
  if (!b0) {
    i3 = temp_mdf->size[0] * temp_mdf->size[1];
    temp_mdf->size[0] = 1;
    emxEnsureCapacity_real_T(temp_mdf, i3);
    loop_ub = temp_mdf->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      temp_mdf->data[i3] = p[0];
    }

    i3 = t->size[0] * t->size[1];
    loop_ub = temp_mdf->size[0] * temp_mdf->size[1];
    temp_mdf->size[0] = 1;
    temp_mdf->size[1] = t->size[1];
    emxEnsureCapacity_real_T(temp_mdf, loop_ub);
    loop_ub = i3 - 1;
    for (i3 = 0; i3 <= loop_ub; i3++) {
      temp_mdf->data[i3] = t->data[i3] * temp_mdf->data[i3] + p[1];
    }
  }

  polyfit(t, mef, p);
  i3 = temp_mef->size[0] * temp_mef->size[1];
  temp_mef->size[0] = 1;
  temp_mef->size[1] = t->size[1];
  emxEnsureCapacity_real_T(temp_mef, i3);
  b0 = (temp_mef->size[1] == 0);
  if (!b0) {
    i3 = temp_mef->size[0] * temp_mef->size[1];
    temp_mef->size[0] = 1;
    emxEnsureCapacity_real_T(temp_mef, i3);
    loop_ub = temp_mef->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      temp_mef->data[i3] = p[0];
    }

    i3 = t->size[0] * t->size[1];
    loop_ub = temp_mef->size[0] * temp_mef->size[1];
    temp_mef->size[0] = 1;
    temp_mef->size[1] = t->size[1];
    emxEnsureCapacity_real_T(temp_mef, loop_ub);
    loop_ub = i3 - 1;
    for (i3 = 0; i3 <= loop_ub; i3++) {
      temp_mef->data[i3] = t->data[i3] * temp_mef->data[i3] + p[1];
    }
  }
}

/* End of code generation (median_mean_frequency.cpp) */
