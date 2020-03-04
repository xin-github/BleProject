/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft1.cpp
 *
 * Code generation for function 'fft1'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "fft_compare.h"
#include "fft1.h"
#include "../emxutil.h"

/* Function Declarations */
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);

/* Function Definitions */
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int temp_re_tmp;
  double twid_re;
  double twid_im;
  j = x->size[0];
  if (j >= unsigned_nRows) {
    j = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y->data[iy] = x->data[ix];
    iDelta = unsigned_nRows;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re_tmp = i + iDelta;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iDelta;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
                    emxArray_real_T *costab, const emxArray_real_T *sintab,
                    const emxArray_real_T *sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int ju;
  int idx;
  int rt;
  int nInt2;
  int ihi;
  double nt_im;
  double nt_re;
  int nt_re_tmp;
  emxArray_creal_T *fy;
  int nRowsD2;
  int nRowsD4;
  int i;
  boolean_T tst;
  emxArray_creal_T *fv;
  double twid_re;
  double twid_im;
  double fv_re;
  double fv_im;
  double wwc_im;
  double b_fv_re;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  ju = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, ju);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (ihi = 0; ihi <= n1 - 2; ihi++) {
    ju = ((1 + ihi) << 1) - 1;
    if (nInt2 - rt <= ju) {
      rt += ju - nInt2;
    } else {
      rt += ju;
    }

    nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
      (n1);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  ju = nInt2m1 - 1;
  for (ihi = ju; ihi >= n1; ihi--) {
    wwc->data[ihi] = wwc->data[idx];
    idx++;
  }

  nInt2 = x->size[0];
  if (n1 < nInt2) {
    nInt2 = n1;
  }

  ju = y->size[0];
  y->size[0] = n1;
  emxEnsureCapacity_creal_T(y, ju);
  if (n1 > x->size[0]) {
    rt = y->size[0];
    ju = y->size[0];
    y->size[0] = rt;
    emxEnsureCapacity_creal_T(y, ju);
    for (ju = 0; ju < rt; ju++) {
      y->data[ju].re = 0.0;
      y->data[ju].im = 0.0;
    }
  }

  rt = 0;
  for (ihi = 0; ihi < nInt2; ihi++) {
    nt_re_tmp = (n1 + ihi) - 1;
    nt_re = wwc->data[nt_re_tmp].re;
    nt_im = wwc->data[nt_re_tmp].im;
    y->data[ihi].re = nt_re * x->data[rt];
    y->data[ihi].im = nt_im * -x->data[rt];
    rt++;
  }

  ju = nInt2 + 1;
  for (ihi = ju; ihi <= n1; ihi++) {
    y->data[ihi - 1].re = 0.0;
    y->data[ihi - 1].im = 0.0;
  }

  nInt2m1 = y->size[0];
  if (nInt2m1 >= N2) {
    nInt2m1 = N2;
  }

  emxInit_creal_T(&fy, 1);
  idx = N2 - 2;
  nRowsD2 = N2 / 2;
  nRowsD4 = nRowsD2 / 2;
  ju = fy->size[0];
  fy->size[0] = N2;
  emxEnsureCapacity_creal_T(fy, ju);
  if (N2 > y->size[0]) {
    rt = fy->size[0];
    ju = fy->size[0];
    fy->size[0] = rt;
    emxEnsureCapacity_creal_T(fy, ju);
    for (ju = 0; ju < rt; ju++) {
      fy->data[ju].re = 0.0;
      fy->data[ju].im = 0.0;
    }
  }

  nInt2 = 0;
  ju = 0;
  rt = 0;
  for (i = 0; i <= nInt2m1 - 2; i++) {
    fy->data[rt] = y->data[nInt2];
    rt = N2;
    tst = true;
    while (tst) {
      rt >>= 1;
      ju ^= rt;
      tst = ((ju & rt) == 0);
    }

    rt = ju;
    nInt2++;
  }

  fy->data[rt] = y->data[nInt2];
  if (N2 > 1) {
    for (i = 0; i <= idx; i += 2) {
      nt_re = fy->data[i + 1].re;
      nt_im = fy->data[i + 1].im;
      fy->data[i + 1].re = fy->data[i].re - fy->data[i + 1].re;
      fy->data[i + 1].im = fy->data[i].im - fy->data[i + 1].im;
      fy->data[i].re += nt_re;
      fy->data[i].im += nt_im;
    }
  }

  rt = 2;
  nInt2 = 4;
  nInt2m1 = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < nInt2m1; i += nInt2) {
      nt_re_tmp = i + rt;
      nt_re = fy->data[nt_re_tmp].re;
      nt_im = fy->data[nt_re_tmp].im;
      fy->data[nt_re_tmp].re = fy->data[i].re - nt_re;
      fy->data[nt_re_tmp].im = fy->data[i].im - nt_im;
      fy->data[i].re += nt_re;
      fy->data[i].im += nt_im;
    }

    idx = 1;
    for (ju = nRowsD4; ju < nRowsD2; ju += nRowsD4) {
      twid_re = costab->data[ju];
      twid_im = sintab->data[ju];
      i = idx;
      ihi = idx + nInt2m1;
      while (i < ihi) {
        nt_re_tmp = i + rt;
        nt_re = twid_re * fy->data[nt_re_tmp].re - twid_im * fy->data[nt_re_tmp]
          .im;
        nt_im = twid_re * fy->data[nt_re_tmp].im + twid_im * fy->data[nt_re_tmp]
          .re;
        fy->data[nt_re_tmp].re = fy->data[i].re - nt_re;
        fy->data[nt_re_tmp].im = fy->data[i].im - nt_im;
        fy->data[i].re += nt_re;
        fy->data[i].im += nt_im;
        i += nInt2;
      }

      idx++;
    }

    nRowsD4 /= 2;
    rt = nInt2;
    nInt2 += nInt2;
    nInt2m1 -= rt;
  }

  emxInit_creal_T(&fv, 1);
  r2br_r2dit_trig_impl(wwc, N2, costab, sintab, fv);
  ju = fy->size[0];
  emxEnsureCapacity_creal_T(fy, ju);
  rt = fy->size[0];
  for (ju = 0; ju < rt; ju++) {
    nt_re = fy->data[ju].re;
    nt_im = fy->data[ju].im;
    fv_re = fv->data[ju].re;
    fv_im = fv->data[ju].im;
    fy->data[ju].re = nt_re * fv_re - nt_im * fv_im;
    fy->data[ju].im = nt_re * fv_im + nt_im * fv_re;
  }

  r2br_r2dit_trig_impl(fy, N2, costab, sintabinv, fv);
  emxFree_creal_T(&fy);
  if (fv->size[0] > 1) {
    nt_re = 1.0 / static_cast<double>(fv->size[0]);
    ju = fv->size[0];
    emxEnsureCapacity_creal_T(fv, ju);
    rt = fv->size[0];
    for (ju = 0; ju < rt; ju++) {
      fv->data[ju].re *= nt_re;
      fv->data[ju].im *= nt_re;
    }
  }

  idx = 0;
  ju = wwc->size[0];
  for (ihi = n1; ihi <= ju; ihi++) {
    nt_re = wwc->data[ihi - 1].re;
    fv_re = fv->data[ihi - 1].re;
    nt_im = wwc->data[ihi - 1].im;
    fv_im = fv->data[ihi - 1].im;
    twid_re = wwc->data[ihi - 1].re;
    twid_im = fv->data[ihi - 1].im;
    wwc_im = wwc->data[ihi - 1].im;
    b_fv_re = fv->data[ihi - 1].re;
    y->data[idx].re = nt_re * fv_re + nt_im * fv_im;
    y->data[idx].im = twid_re * twid_im - wwc_im * b_fv_re;
    idx++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

/* End of code generation (fft1.cpp) */
