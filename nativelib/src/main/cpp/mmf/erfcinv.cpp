/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * erfcinv.cpp
 *
 * Code generation for function 'erfcinv'
 *
 */

/* Include files */
#include <cmath>
#include <math.h>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "erfcinv.h"
#include "betaincinv.h"
#include "median_mean_frequency_rtwutil.h"

/* Function Declarations */
static double eml_erfcore(double x);

/* Function Definitions */
static double eml_erfcore(double x)
{
  double y;
  double absx;
  double S;
  double s;
  double R;
  int eint;

  /* ========================== COPYRIGHT NOTICE ============================ */
  /*  The algorithms for calculating ERF(X) and ERFC(X) are derived           */
  /*  from FDLIBM, which has the following notice:                            */
  /*                                                                          */
  /*  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.       */
  /*                                                                          */
  /*  Developed at SunSoft, a Sun Microsystems, Inc. business.                */
  /*  Permission to use, copy, modify, and distribute this                    */
  /*  software is freely granted, provided that this notice                   */
  /*  is preserved.                                                           */
  /* =============================    END    ================================ */
  absx = std::abs(x);
  if (rtIsNaN(x)) {
    y = x;
  } else if (rtIsInf(x)) {
    if (x < 0.0) {
      y = 2.0;
    } else {
      y = 0.0;
    }
  } else if (absx < 0.84375) {
    if (absx < 1.3877787807814457E-17) {
      y = 1.0 - x;
    } else {
      s = x * x;
      y = (0.12837916709551256 + s * (-0.3250421072470015 + s *
            (-0.02848174957559851 + s * (-0.0057702702964894416 + s *
              -2.3763016656650163E-5)))) / (1.0 + s * (0.39791722395915535 + s *
        (0.0650222499887673 + s * (0.0050813062818757656 + s *
        (0.00013249473800432164 + s * -3.9602282787753681E-6)))));
      if (x < 0.25) {
        y = 1.0 - (x + x * y);
      } else {
        y = 0.5 - (x * y + (x - 0.5));
      }
    }
  } else if (absx < 1.25) {
    S = -0.0023621185607526594 + (absx - 1.0) * (0.41485611868374833 + (absx -
      1.0) * (-0.37220787603570132 + (absx - 1.0) * (0.31834661990116175 + (absx
      - 1.0) * (-0.11089469428239668 + (absx - 1.0) * (0.035478304325618236 +
      (absx - 1.0) * -0.0021663755948687908)))));
    s = 1.0 + (absx - 1.0) * (0.10642088040084423 + (absx - 1.0) *
      (0.540397917702171 + (absx - 1.0) * (0.071828654414196266 + (absx - 1.0) *
      (0.12617121980876164 + (absx - 1.0) * (0.013637083912029051 + (absx - 1.0)
      * 0.011984499846799107)))));
    if (x >= 0.0) {
      y = 0.15493708848953247 - S / s;
    } else {
      y = 1.0 + (0.84506291151046753 + S / s);
    }
  } else if (x < -6.0) {
    y = 2.0;
  } else if (x >= 28.0) {
    y = 0.0;
  } else {
    s = 1.0 / (absx * absx);
    if (absx < 2.8571414947509766) {
      R = -0.0098649440348471482 + s * (-0.69385857270718176 + s *
        (-10.558626225323291 + s * (-62.375332450326006 + s *
        (-162.39666946257347 + s * (-184.60509290671104 + s * (-81.2874355063066
        + s * -9.8143293441691455))))));
      S = 1.0 + s * (19.651271667439257 + s * (137.65775414351904 + s *
        (434.56587747522923 + s * (645.38727173326788 + s * (429.00814002756783
        + s * (108.63500554177944 + s * (6.5702497703192817 + s *
        -0.0604244152148581)))))));
    } else {
      R = -0.0098649429247001 + s * (-0.799283237680523 + s *
        (-17.757954917754752 + s * (-160.63638485582192 + s *
        (-637.56644336838963 + s * (-1025.0951316110772 + s * -483.5191916086514)))));
      S = 1.0 + s * (30.338060743482458 + s * (325.79251299657392 + s *
        (1536.729586084437 + s * (3199.8582195085955 + s * (2553.0504064331644 +
        s * (474.52854120695537 + s * -22.440952446585818))))));
    }

    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      s = frexp(absx, &eint);
    } else {
      s = absx;
      eint = 0;
    }

    s = std::floor(s * 2.097152E+6) / 2.097152E+6 * rt_powd_snf(2.0, (double)
      eint);
    y = std::exp(-s * s - 0.5625) * std::exp((s - absx) * (s + absx) + R / S) /
      absx;
    if (x < 0.0) {
      y = 2.0 - y;
    }
  }

  return y;
}

double erfcinv(double y)
{
  double x;
  int nIterations;
  boolean_T guard1 = false;
  double z;
  int k;
  double absx;
  double P;
  double R;
  double S;
  int eint;
  int b;
  nIterations = 2;
  if (rtIsNaN(y)) {
    x = rtNaN;
  } else {
    guard1 = false;
    if (y > 1.7) {
      z = std::sqrt(-std::log((2.0 - y) / 2.0));
      x = -(((1.641345311 * z + 3.429567803) * z + -1.624906493) * z +
            -1.970840454) / ((1.6370678 * z + 3.5438892) * z + 1.0);
      guard1 = true;
    } else if (y < 0.3) {
      z = std::sqrt(0.69314718055994529 - std::log(y));
      if (y < 1.0947644252537633E-47) {
        if (y < 7.7532508072625747E-267) {
          nIterations = 4;
        } else {
          nIterations = 3;
        }
      }

      x = (((1.641345311 * z + 3.429567803) * z + -1.624906493) * z +
           -1.970840454) / ((1.6370678 * z + 3.5438892) * z + 1.0);
      for (k = 0; k < nIterations; k++) {
        z = -(eml_erfcore(x) - y) / (1.1283791670955126 * std::exp(-x * x));
        x -= z / (1.0 + x * z);
      }
    } else {
      z = (1.0 - y) * (1.0 - y);
      x = (1.0 - y) * (((-0.140543331 * z + 0.914624893) * z + -1.645349621) * z
                       + 0.886226899) / ((((0.012229801 * z + -0.329097515) * z
        + 1.442710462) * z + -2.118377725) * z + 1.0);
      guard1 = true;
    }

    if (guard1) {
      if (y > 1.7) {
        for (k = 0; k < 2; k++) {
          z = (eml_erfcore(-x) - (2.0 - y)) / (1.1283791670955126 * std::exp(-x *
            x));
          x -= z / (1.0 + x * z);
        }
      } else {
        for (k = 0; k < 2; k++) {
          /* ========================== COPYRIGHT NOTICE ============================ */
          /*  The algorithms for calculating ERF(X) and ERFC(X) are derived           */
          /*  from FDLIBM, which has the following notice:                            */
          /*                                                                          */
          /*  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.       */
          /*                                                                          */
          /*  Developed at SunSoft, a Sun Microsystems, Inc. business.                */
          /*  Permission to use, copy, modify, and distribute this                    */
          /*  software is freely granted, provided that this notice                   */
          /*  is preserved.                                                           */
          /* =============================    END    ================================ */
          absx = std::abs(x);
          if (rtIsNaN(x)) {
            z = x;
          } else if (rtIsInf(x)) {
            if (x < 0.0) {
              z = -1.0;
            } else {
              z = 1.0;
            }
          } else if (absx < 0.84375) {
            if (absx < 3.7252902984619141E-9) {
              if (absx < 2.8480945388892178E-306) {
                z = 0.125 * (8.0 * x + 1.0270333367641007 * x);
              } else {
                z = x + 0.12837916709551259 * x;
              }
            } else {
              z = x * x;
              z = x + x * ((0.12837916709551256 + z * (-0.3250421072470015 + z *
                (-0.02848174957559851 + z * (-0.0057702702964894416 + z *
                -2.3763016656650163E-5)))) / (1.0 + z * (0.39791722395915535 + z
                * (0.0650222499887673 + z * (0.0050813062818757656 + z *
                (0.00013249473800432164 + z * -3.9602282787753681E-6))))));
            }
          } else if (absx < 1.25) {
            P = -0.0023621185607526594 + (absx - 1.0) * (0.41485611868374833 +
              (absx - 1.0) * (-0.37220787603570132 + (absx - 1.0) *
                              (0.31834661990116175 + (absx - 1.0) *
                               (-0.11089469428239668 + (absx - 1.0) *
                                (0.035478304325618236 + (absx - 1.0) *
                                 -0.0021663755948687908)))));
            z = 1.0 + (absx - 1.0) * (0.10642088040084423 + (absx - 1.0) *
              (0.540397917702171 + (absx - 1.0) * (0.071828654414196266 + (absx
              - 1.0) * (0.12617121980876164 + (absx - 1.0) *
                        (0.013637083912029051 + (absx - 1.0) *
                         0.011984499846799107)))));
            if (x >= 0.0) {
              z = 0.84506291151046753 + P / z;
            } else {
              z = -0.84506291151046753 - P / z;
            }
          } else if (absx > 6.0) {
            if (x < 0.0) {
              z = -1.0;
            } else {
              z = 1.0;
            }
          } else {
            z = 1.0 / (absx * absx);
            if (absx < 2.8571434020996094) {
              R = -0.0098649440348471482 + z * (-0.69385857270718176 + z *
                (-10.558626225323291 + z * (-62.375332450326006 + z *
                (-162.39666946257347 + z * (-184.60509290671104 + z *
                (-81.2874355063066 + z * -9.8143293441691455))))));
              S = 1.0 + z * (19.651271667439257 + z * (137.65775414351904 + z *
                (434.56587747522923 + z * (645.38727173326788 + z *
                (429.00814002756783 + z * (108.63500554177944 + z *
                (6.5702497703192817 + z * -0.0604244152148581)))))));
            } else {
              R = -0.0098649429247001 + z * (-0.799283237680523 + z *
                (-17.757954917754752 + z * (-160.63638485582192 + z *
                (-637.56644336838963 + z * (-1025.0951316110772 + z *
                -483.5191916086514)))));
              S = 1.0 + z * (30.338060743482458 + z * (325.79251299657392 + z *
                (1536.729586084437 + z * (3199.8582195085955 + z *
                (2553.0504064331644 + z * (474.52854120695537 + z *
                -22.440952446585818))))));
            }

            if (!rtIsNaN(absx)) {
              P = frexp(absx, &eint);
              b = eint;
            } else {
              P = absx;
              b = 0;
            }

            z = std::floor(P * 2.097152E+6) / 2.097152E+6 * rt_powd_snf(2.0,
              (double)b);
            z = std::exp(-z * z - 0.5625) * std::exp((z - absx) * (z + absx) + R
              / S) / absx;
            if (x < 0.0) {
              z--;
            } else {
              z = 1.0 - z;
            }
          }

          z = (z - (1.0 - y)) / (1.1283791670955126 * std::exp(-x * x));
          x -= z / (1.0 + x * z);
        }
      }
    }
  }

  return x;
}

/* End of code generation (erfcinv.cpp) */
