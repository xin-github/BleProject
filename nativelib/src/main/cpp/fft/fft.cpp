/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft.cpp
 *
 * Code generation for function 'fft'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "fft_compare.h"
#include "fft.h"
#include "../emxutil.h"
#include "fft1.h"

/* Function Definitions */
void fft(const emxArray_real_T *x, emxArray_creal_T *y)
{
  boolean_T useRadix2;
  int nRowsM1;
  int ihi;
  int pmax;
  emxArray_real_T *costab1q;
  int pmin;
  double temp_re;
  boolean_T exitg1;
  int pow2p;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int i;
  double temp_im;
  int temp_re_tmp;
  double twid_re;
  double twid_im;
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    nRowsM1 = 1;
    if (useRadix2) {
      pmax = x->size[0];
    } else {
      ihi = (x->size[0] + x->size[0]) - 1;
      pmax = 31;
      if (ihi <= 1) {
        pmax = 0;
      } else {
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          nRowsM1 = (pmin + pmax) >> 1;
          pow2p = 1 << nRowsM1;
          if (pow2p == ihi) {
            pmax = nRowsM1;
            exitg1 = true;
          } else if (pow2p > ihi) {
            pmax = nRowsM1;
          } else {
            pmin = nRowsM1;
          }
        }
      }

      nRowsM1 = 1 << pmax;
      pmax = nRowsM1;
    }

    emxInit_real_T(&costab1q, 2);
    temp_re = 6.2831853071795862 / static_cast<double>(pmax);
    ihi = pmax / 2 / 2;
    pow2p = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = ihi + 1;
    emxEnsureCapacity_real_T(costab1q, pow2p);
    costab1q->data[0] = 1.0;
    pmax = ihi / 2 - 1;
    for (pmin = 0; pmin <= pmax; pmin++) {
      costab1q->data[1 + pmin] = std::cos(temp_re * (1.0 + static_cast<double>
        (pmin)));
    }

    pow2p = pmax + 2;
    pmax = ihi - 1;
    for (pmin = pow2p; pmin <= pmax; pmin++) {
      costab1q->data[pmin] = std::sin(temp_re * static_cast<double>((ihi - pmin)));
    }

    costab1q->data[ihi] = 0.0;
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    if (!useRadix2) {
      ihi = costab1q->size[1] - 1;
      pmax = (costab1q->size[1] - 1) << 1;
      pow2p = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = pmax + 1;
      emxEnsureCapacity_real_T(costab, pow2p);
      pow2p = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = pmax + 1;
      emxEnsureCapacity_real_T(sintab, pow2p);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      pow2p = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = pmax + 1;
      emxEnsureCapacity_real_T(sintabinv, pow2p);
      for (pmin = 0; pmin < ihi; pmin++) {
        sintabinv->data[1 + pmin] = costab1q->data[(ihi - pmin) - 1];
      }

      pow2p = costab1q->size[1];
      for (pmin = pow2p; pmin <= pmax; pmin++) {
        sintabinv->data[pmin] = costab1q->data[pmin - ihi];
      }

      for (pmin = 0; pmin < ihi; pmin++) {
        costab->data[1 + pmin] = costab1q->data[1 + pmin];
        sintab->data[1 + pmin] = -costab1q->data[(ihi - pmin) - 1];
      }

      pow2p = costab1q->size[1];
      for (pmin = pow2p; pmin <= pmax; pmin++) {
        costab->data[pmin] = -costab1q->data[pmax - pmin];
        sintab->data[pmin] = -costab1q->data[pmin - ihi];
      }
    } else {
      ihi = costab1q->size[1] - 1;
      pmax = (costab1q->size[1] - 1) << 1;
      pow2p = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = pmax + 1;
      emxEnsureCapacity_real_T(costab, pow2p);
      pow2p = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = pmax + 1;
      emxEnsureCapacity_real_T(sintab, pow2p);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      for (pmin = 0; pmin < ihi; pmin++) {
        costab->data[1 + pmin] = costab1q->data[1 + pmin];
        sintab->data[1 + pmin] = -costab1q->data[(ihi - pmin) - 1];
      }

      pow2p = costab1q->size[1];
      for (pmin = pow2p; pmin <= pmax; pmin++) {
        costab->data[pmin] = -costab1q->data[pmax - pmin];
        sintab->data[pmin] = -costab1q->data[pmin - ihi];
      }

      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }

    emxFree_real_T(&costab1q);
    if (useRadix2) {
      pmax = x->size[0];
      nRowsM1 = pmax - 2;
      nRowsM2 = x->size[0] - 2;
      nRowsD2 = x->size[0] / 2;
      nRowsD4 = nRowsD2 / 2;
      pmax = x->size[0];
      pow2p = y->size[0];
      y->size[0] = pmax;
      emxEnsureCapacity_creal_T(y, pow2p);
      pmin = 0;
      pow2p = 0;
      pmax = 0;
      for (i = 0; i <= nRowsM1; i++) {
        y->data[pmax].re = x->data[pmin];
        y->data[pmax].im = 0.0;
        ihi = x->size[0];
        useRadix2 = true;
        while (useRadix2) {
          ihi >>= 1;
          pow2p ^= ihi;
          useRadix2 = ((pow2p & ihi) == 0);
        }

        pmax = pow2p;
        pmin++;
      }

      y->data[pmax].re = x->data[pmin];
      y->data[pmax].im = 0.0;
      if (x->size[0] > 1) {
        for (i = 0; i <= nRowsM2; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }
      }

      pmax = 2;
      pmin = 4;
      pow2p = 1 + ((nRowsD4 - 1) << 2);
      while (nRowsD4 > 0) {
        for (i = 0; i < pow2p; i += pmin) {
          temp_re_tmp = i + pmax;
          temp_re = y->data[temp_re_tmp].re;
          temp_im = y->data[temp_re_tmp].im;
          y->data[temp_re_tmp].re = y->data[i].re - temp_re;
          y->data[temp_re_tmp].im = y->data[i].im - temp_im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }

        nRowsM1 = 1;
        for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
          twid_re = costab->data[nRowsM2];
          twid_im = sintab->data[nRowsM2];
          i = nRowsM1;
          ihi = nRowsM1 + pow2p;
          while (i < ihi) {
            temp_re_tmp = i + pmax;
            temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
              data[temp_re_tmp].im;
            temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
              data[temp_re_tmp].re;
            y->data[temp_re_tmp].re = y->data[i].re - temp_re;
            y->data[temp_re_tmp].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += pmin;
          }

          nRowsM1++;
        }

        nRowsD4 /= 2;
        pmax = pmin;
        pmin += pmin;
        pow2p -= pmax;
      }
    } else {
      dobluesteinfft(x, nRowsM1, x->size[0], costab, sintab, sintabinv, y);
    }

    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
}

/* End of code generation (fft.cpp) */
