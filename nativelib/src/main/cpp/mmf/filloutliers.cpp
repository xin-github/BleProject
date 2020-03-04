/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filloutliers.cpp
 *
 * Code generation for function 'filloutliers'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "filloutliers.h"
#include "median_mean_frequency_emxutil.h"
#include "locateoutliers.h"
#include "../emxutil.h"

/* Function Definitions */
void filloutliers(emxArray_real_T *a)
{
  emxArray_boolean_T *tf;
  double tmp;
  double ub;
  double center;
  int na;
  int nOutliers;
  int nNaNs;
  int k;
  int iLeft;
  int iRight;
  int iLeftLast;
  boolean_T dosearch;
  int b_k;
  double y[2];
  emxInit_boolean_T(&tf, 2);
  vIsOutlier(a, (int)std::ceil(static_cast<double>(a->size[1]) * 0.1), tf, &tmp,
             &ub, &center);
  na = a->size[1] - 1;
  nOutliers = 0;
  nNaNs = 0;
  for (k = 0; k <= na; k++) {
    if (tf->data[k]) {
      nOutliers++;
    } else {
      if (rtIsNaN(a->data[k])) {
        nNaNs++;
      }
    }
  }

  nOutliers = (a->size[1] - nOutliers) - nNaNs;
  if (nOutliers != 0) {
    if (nOutliers == 1) {
      nOutliers = 0;
      while ((nOutliers + 1 <= tf->size[1]) && (tf->data[nOutliers] || rtIsNaN
              (a->data[nOutliers]))) {
        nOutliers++;
      }

      if (nOutliers + 1 > tf->size[1]) {
        nOutliers = -1;
      }

      for (k = 0; k <= na; k++) {
        if (tf->data[k]) {
          a->data[k] = a->data[nOutliers];
        }
      }
    } else {
      na = a->size[1];
      iLeft = 1;
      while ((iLeft <= tf->size[1]) && (tf->data[iLeft - 1] || rtIsNaN(a->
               data[iLeft - 1]))) {
        iLeft++;
      }

      if (iLeft > tf->size[1]) {
        iLeft = 0;
      }

      iRight = iLeft + 1;
      while ((iRight <= tf->size[1]) && (tf->data[iRight - 1] || rtIsNaN(a->
               data[iRight - 1]))) {
        iRight++;
      }

      if (iRight > tf->size[1]) {
        iRight = 0;
      }

      iLeftLast = 0;
      dosearch = true;
      for (k = 0; k < na; k++) {
        b_k = 1 + k;
        if (tf->data[b_k - 1]) {
          if (dosearch && (b_k > iRight)) {
            iRight = b_k + 1;
            while ((iRight <= tf->size[1]) && (tf->data[iRight - 1] || rtIsNaN
                    (a->data[iRight - 1]))) {
              iRight++;
            }

            if (iRight > tf->size[1]) {
              iRight = 0;
            }

            if (iRight == 0) {
              iRight = iLeft;
              iLeft = iLeftLast;
              dosearch = false;
            }
          }

          y[0] = a->data[iLeft - 1];
          y[1] = a->data[iRight - 1];
          nOutliers = iLeft;
          nNaNs = iRight;
          if (iRight < iLeft) {
            nOutliers = iRight;
            nNaNs = iLeft;
            tmp = y[0];
            y[0] = y[1];
            y[1] = tmp;
          }

          if (b_k > nNaNs) {
            tmp = y[1];
          } else if (b_k < nOutliers) {
            tmp = y[0];
          } else {
            tmp = y[static_cast<int>((b_k >= (static_cast<double>(nNaNs) +
              static_cast<double>(nOutliers)) / 2.0))];
          }

          a->data[b_k - 1] = tmp;
        } else {
          if (dosearch && (b_k > iLeft) && (!rtIsNaN(a->data[b_k - 1]))) {
            iLeftLast = iLeft;
            iLeft = b_k;
          }
        }
      }
    }
  }

  emxFree_boolean_T(&tf);
}

/* End of code generation (filloutliers.cpp) */
