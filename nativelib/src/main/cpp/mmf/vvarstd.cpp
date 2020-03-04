/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * vvarstd.cpp
 *
 * Code generation for function 'vvarstd'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "vvarstd.h"
#include "median_mean_frequency_emxutil.h"
#include "../emxutil.h"

/* Function Definitions */
void vvarstd(const emxArray_real_T *v, int n, double *s, double *xbar, double
             *maxabs, int *imax)
{
  int k;
  emxArray_real_T *absdiff;
  double scale;
  double absxk;
  double t;
  if (n == 0) {
    *s = rtNaN;
    *xbar = rtNaN;
    *maxabs = 0.0;
    *imax = 0;
  } else if (n == 1) {
    *xbar = v->data[0];
    if ((!rtIsInf(v->data[0])) && (!rtIsNaN(v->data[0]))) {
      *s = 0.0;
    } else {
      *s = rtNaN;
    }

    *maxabs = 0.0;
    *imax = 1;
  } else {
    if ((v->size[1] == 0) || (n == 0)) {
      *xbar = 0.0;
    } else {
      *xbar = v->data[0];
      for (k = 2; k <= n; k++) {
        *xbar += v->data[k - 1];
      }
    }

    emxInit_real_T(&absdiff, 1);
    *xbar /= static_cast<double>(n);
    *imax = 0;
    *maxabs = 0.0;
    k = absdiff->size[0];
    absdiff->size[0] = v->size[1];
    emxEnsureCapacity_real_T(absdiff, k);
    for (k = 0; k < n; k++) {
      absdiff->data[k] = std::abs(v->data[k] - *xbar);
      if (absdiff->data[k] > *maxabs) {
        *maxabs = absdiff->data[k];
        *imax = k + 1;
      }
    }

    *s = 0.0;
    if (n >= 1) {
      if (n == 1) {
        *s = absdiff->data[0];
      } else {
        scale = 3.3121686421112381E-170;
        for (k = 0; k < n; k++) {
          absxk = absdiff->data[k];
          if (absxk > scale) {
            t = scale / absxk;
            *s = 1.0 + *s * t * t;
            scale = absxk;
          } else {
            t = absxk / scale;
            *s += t * t;
          }
        }

        *s = scale * std::sqrt(*s);
      }
    }

    emxFree_real_T(&absdiff);
    *s /= std::sqrt((double)(n - 1));
  }
}

/* End of code generation (vvarstd.cpp) */
