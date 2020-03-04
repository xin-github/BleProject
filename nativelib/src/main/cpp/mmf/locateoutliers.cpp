/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * locateoutliers.cpp
 *
 * Code generation for function 'locateoutliers'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "locateoutliers.h"
#include "median_mean_frequency_emxutil.h"
#include "betaincinv.h"
#include "gammaln.h"
#include "erfcinv.h"
#include "vvarstd.h"
#include "median_mean_frequency_rtwutil.h"
#include "../emxutil.h"

/* Function Definitions */
void vIsOutlier(const emxArray_real_T *a, int mxo, emxArray_boolean_T *tf,
                double *lb, double *ub, double *center)
{
  emxArray_real_T *b_a;
  int i0;
  int yk;
  int na;
  double amean;
  unsigned int unnamed_idx_1;
  int n;
  emxArray_int32_T *y;
  emxArray_int32_T *indvec;
  int k;
  emxArray_int32_T *Rloc;
  double astd;
  double lambda;
  int j;
  int b_j;
  double xn;
  double astdj;
  double ameanj;
  double amaxj;
  int loc;
  int b_xn;
  double p;
  double absq;
  double xn3;
  double xn5;
  double xn7;
  emxInit_real_T(&b_a, 2);
  i0 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = 1;
  b_a->size[1] = a->size[1];
  emxEnsureCapacity_real_T(b_a, i0);
  yk = a->size[0] * a->size[1];
  for (i0 = 0; i0 < yk; i0++) {
    b_a->data[i0] = a->data[i0];
  }

  na = a->size[1];
  *lb = rtNaN;
  *ub = rtNaN;
  amean = rtNaN;
  unnamed_idx_1 = static_cast<unsigned int>(a->size[1]);
  i0 = tf->size[0] * tf->size[1];
  tf->size[0] = 1;
  tf->size[1] = static_cast<int>(unnamed_idx_1);
  emxEnsureCapacity_boolean_T(tf, i0);
  yk = static_cast<int>(unnamed_idx_1);
  for (i0 = 0; i0 < yk; i0++) {
    tf->data[i0] = false;
  }

  if (a->size[1] < 1) {
    n = 0;
  } else {
    n = a->size[1];
  }

  emxInit_int32_T(&y, 2);
  i0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_int32_T(y, i0);
  if (n > 0) {
    y->data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y->data[k - 1] = yk;
    }
  }

  emxInit_int32_T(&indvec, 1);
  i0 = indvec->size[0];
  indvec->size[0] = y->size[1];
  emxEnsureCapacity_int32_T(indvec, i0);
  yk = y->size[1];
  for (i0 = 0; i0 < yk; i0++) {
    indvec->data[i0] = y->data[i0];
  }

  emxFree_int32_T(&y);
  n = -1;
  for (k = 0; k < na; k++) {
    if (!rtIsNaN(b_a->data[k])) {
      n++;
      b_a->data[n] = b_a->data[k];
      indvec->data[n] = indvec->data[k];
    }
  }

  yk = n + 1;
  if (n + 1 > 0) {
    emxInit_int32_T(&Rloc, 1);
    i0 = Rloc->size[0];
    Rloc->size[0] = mxo;
    emxEnsureCapacity_int32_T(Rloc, i0);
    for (i0 = 0; i0 < mxo; i0++) {
      Rloc->data[i0] = 0;
    }

    na = 0;
    amean = 0.0;
    astd = 0.0;
    lambda = 0.0;
    for (j = 0; j < mxo; j++) {
      b_j = 1 + j;
      vvarstd(b_a, yk, &astdj, &ameanj, &amaxj, &loc);
      xn = b_a->data[loc - 1];
      i0 = yk - 1;
      for (k = loc; k <= i0; k++) {
        b_a->data[k - 1] = b_a->data[k];
      }

      b_a->data[yk - 1] = xn;
      Rloc->data[b_j - 1] = indvec->data[loc - 1];
      b_xn = indvec->data[loc - 1];
      i0 = yk - 1;
      for (k = loc; k <= i0; k++) {
        indvec->data[k - 1] = indvec->data[k];
      }

      indvec->data[yk - 1] = b_xn;
      yk--;
      p = 1.0 - 0.05 / (2.0 * (static_cast<double>(yk) + 1.0));
      if ((static_cast<double>(yk) - 1.0 > 0.0) && (0.0 <= p) && (p <= 1.0)) {
        if (p == 0.0) {
          xn = rtMinusInf;
        } else if (p == 1.0) {
          xn = rtInf;
        } else if (static_cast<double>(yk) - 1.0 == 1.0) {
          xn = std::tan(3.1415926535897931 * (p - 0.5));
        } else if (static_cast<double>(yk) - 1.0 < 1000.0) {
          absq = std::abs(p - 0.5);
          if (absq < 0.25) {
            xn5 = (betaincinv(2.0 * absq, (static_cast<double>(yk) - 1.0) / 2.0))
              .re;
            xn = 1.0 - (betaincinv(2.0 * absq, (static_cast<double>(yk) - 1.0) /
              2.0)).re;
          } else {
            xn = (static_cast<double>(yk) - 1.0) / 2.0;
            xn3 = xn;
            gammaln(&xn3);
            xn5 = 0.5;
            gammaln(&xn5);
            xn7 = xn + 0.5;
            gammaln(&xn7);
            xn = eml_betaincinv(2.0 * absq, xn, (xn3 + xn5) - xn7);
            xn5 = 1.0 - xn;
          }

          xn3 = p - 0.5;
          if (p - 0.5 < 0.0) {
            xn3 = -1.0;
          } else if (p - 0.5 > 0.0) {
            xn3 = 1.0;
          } else {
            if (p - 0.5 == 0.0) {
              xn3 = 0.0;
            }
          }

          xn = xn3 * std::sqrt((static_cast<double>(yk) - 1.0) * (xn5 / xn));
        } else {
          xn = -1.4142135623730951 * erfcinv(2.0 * p);
          xn3 = rt_powd_snf(xn, 3.0);
          xn5 = rt_powd_snf(xn, 5.0);
          xn7 = rt_powd_snf(xn, 7.0);
          xn = (((xn + (xn3 + xn) / (4.0 * (static_cast<double>(yk) - 1.0))) +
                 ((5.0 * xn5 + 16.0 * xn3) + 3.0 * xn) / (96.0 * ((static_cast<
                    double>(yk) - 1.0) * (static_cast<double>(yk) - 1.0)))) +
                (((3.0 * xn7 + 19.0 * xn5) + 17.0 * xn3) - 15.0 * xn) / (384.0 *
                 rt_powd_snf(static_cast<double>(yk) - 1.0, 3.0))) + ((((79.0 *
            rt_powd_snf(xn, 9.0) + 776.0 * xn7) + 1482.0 * xn5) - 1920.0 * xn3)
            - 945.0 * xn) / (92160.0 * rt_powd_snf(static_cast<double>(yk) - 1.0,
            4.0));
        }
      } else {
        xn = rtNaN;
      }

      xn = static_cast<double>(yk) * xn / std::sqrt(((static_cast<double>(yk) -
        1.0) + xn * xn) * (static_cast<double>(yk) + 1.0));
      if (amaxj / astdj > xn) {
        i0 = na + 1;
        for (k = i0; k <= b_j; k++) {
          tf->data[Rloc->data[k - 1] - 1] = true;
        }

        na = b_j;
        amean = ameanj;
        astd = astdj;
        lambda = xn;
      } else {
        if (b_j == na + 1) {
          amean = ameanj;
          astd = astdj;
          lambda = xn;
        }
      }
    }

    emxFree_int32_T(&Rloc);
    xn = astd * lambda;
    *lb = amean - xn;
    *ub = amean + xn;
    for (j = 0; j <= n; j++) {
      if ((b_a->data[j] < *lb) || (b_a->data[j] > *ub)) {
        tf->data[indvec->data[j] - 1] = true;
      }
    }
  }

  emxFree_int32_T(&indvec);
  emxFree_real_T(&b_a);
  *center = amean;
}

/* End of code generation (locateoutliers.cpp) */
