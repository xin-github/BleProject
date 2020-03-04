/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgeqp3.cpp
 *
 * Code generation for function 'xgeqp3'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "xscal.h"

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

void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int jpvt[2])
{
  int m;
  int mn;
  double work[2];
  double temp;
  double vn1[2];
  double vn2[2];
  int i;
  int ip1;
  int iy;
  int i_i;
  int mmi;
  int itemp;
  int pvt;
  int ix;
  int k;
  double atmp;
  double beta1;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int exitg1;
  int i4;
  int ijA;
  m = A->size[0];
  mn = A->size[0];
  if (mn >= 2) {
    mn = 2;
  }

  tau_size[0] = mn;
  jpvt[0] = 1;
  jpvt[1] = 2;
  if (A->size[0] != 0) {
    work[0] = 0.0;
    temp = xnrm2(m, A, 1);
    vn1[0] = temp;
    vn2[0] = temp;
    work[1] = 0.0;
    temp = xnrm2(m, A, 1 + m);
    vn1[1] = temp;
    vn2[1] = temp;
    for (i = 0; i < mn; i++) {
      ip1 = i + 2;
      iy = i * m;
      i_i = i + iy;
      mmi = (m - i) - 1;
      itemp = 0;
      if ((2 - i > 1) && (std::abs(vn1[1]) > std::abs(vn1[i]))) {
        itemp = 1;
      }

      pvt = i + itemp;
      if (pvt + 1 != i + 1) {
        ix = m * pvt;
        for (k = 0; k < m; k++) {
          temp = A->data[ix];
          A->data[ix] = A->data[iy];
          A->data[iy] = temp;
          ix++;
          iy++;
        }

        itemp = jpvt[pvt];
        jpvt[pvt] = jpvt[i];
        jpvt[i] = itemp;
        vn1[pvt] = vn1[i];
        vn2[pvt] = vn2[i];
      }

      if (i + 1 < m) {
        atmp = A->data[i_i];
        tau_data[i] = 0.0;
        if (1 + mmi > 0) {
          temp = xnrm2(mmi, A, i_i + 2);
          if (temp != 0.0) {
            beta1 = rt_hypotd_snf(A->data[i_i], temp);
            if (A->data[i_i] >= 0.0) {
              beta1 = -beta1;
            }

            if (std::abs(beta1) < 1.0020841800044864E-292) {
              itemp = -1;
              do {
                itemp++;
                xscal(mmi, 9.9792015476736E+291, A, i_i + 2);
                beta1 *= 9.9792015476736E+291;
                atmp *= 9.9792015476736E+291;
              } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

              beta1 = rt_hypotd_snf(atmp, xnrm2(mmi, A, i_i + 2));
              if (atmp >= 0.0) {
                beta1 = -beta1;
              }

              tau_data[i] = (beta1 - atmp) / beta1;
              xscal(mmi, 1.0 / (atmp - beta1), A, i_i + 2);
              for (k = 0; k <= itemp; k++) {
                beta1 *= 1.0020841800044864E-292;
              }

              atmp = beta1;
            } else {
              tau_data[i] = (beta1 - A->data[i_i]) / beta1;
              temp = 1.0 / (A->data[i_i] - beta1);
              xscal(mmi, temp, A, i_i + 2);
              atmp = beta1;
            }
          }
        }

        A->data[i_i] = atmp;
      } else {
        tau_data[i] = 0.0;
      }

      if (i + 1 < 2) {
        atmp = A->data[i_i];
        A->data[i_i] = 1.0;
        k = 1 + m;
        if (tau_data[0] != 0.0) {
          lastv = 1 + mmi;
          itemp = i_i + mmi;
          while ((lastv > 0) && (A->data[itemp] == 0.0)) {
            lastv--;
            itemp--;
          }

          lastc = 1 - i;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            itemp = m;
            do {
              exitg1 = 0;
              if (itemp + 1 <= m + lastv) {
                if (A->data[itemp] != 0.0) {
                  exitg1 = 1;
                } else {
                  itemp++;
                }
              } else {
                lastc = 0;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc != 0) {
            work[0] = 0.0;
            iy = 0;
            for (pvt = k; m < 0 ? pvt >= k : pvt <= k; pvt += m) {
              ix = i_i;
              temp = 0.0;
              i4 = (pvt + lastv) - 1;
              for (itemp = pvt; itemp <= i4; itemp++) {
                temp += A->data[itemp - 1] * A->data[ix];
                ix++;
              }

              work[iy] += temp;
              iy++;
            }
          }

          if (!(-tau_data[0] == 0.0)) {
            itemp = m;
            pvt = 0;
            for (k = 0; k < lastc; k++) {
              if (work[pvt] != 0.0) {
                temp = work[pvt] * -tau_data[0];
                ix = i_i;
                i4 = itemp + 1;
                iy = lastv + itemp;
                for (ijA = i4; ijA <= iy; ijA++) {
                  A->data[ijA - 1] += A->data[ix] * temp;
                  ix++;
                }
              }

              pvt++;
              itemp += m;
            }
          }
        }

        A->data[i_i] = atmp;
      }

      for (k = ip1; k < 3; k++) {
        if (vn1[1] != 0.0) {
          temp = std::abs(A->data[i + A->size[0]]) / vn1[1];
          temp = 1.0 - temp * temp;
          if (temp < 0.0) {
            temp = 0.0;
          }

          beta1 = vn1[1] / vn2[1];
          beta1 = temp * (beta1 * beta1);
          if (beta1 <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              temp = xnrm2(mmi, A, (i + m) + 2);
              vn1[1] = temp;
              vn2[1] = temp;
            } else {
              vn1[1] = 0.0;
              vn2[1] = 0.0;
            }
          } else {
            vn1[1] *= std::sqrt(temp);
          }
        }
      }
    }
  }
}

/* End of code generation (xgeqp3.cpp) */
