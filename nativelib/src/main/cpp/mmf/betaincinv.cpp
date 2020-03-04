/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * betaincinv.cpp
 *
 * Code generation for function 'betaincinv'
 *
 */

/* Include files */
#include <cmath>
#include "../rt/rt_nonfinite.h"
#include "median_mean_frequency.h"
#include "betaincinv.h"
#include "log.h"
#include "sqrt.h"
#include "gammaln.h"
#include "median_mean_frequency_rtwutil.h"

/* Function Declarations */
static double betainc_cf(double x, double a, double b);
static double eml_PHIc(double z);
static double eml_betainc(double x, double a, double b, double lbeta, boolean_T
  upper);
static double eml_gammainc(double x, double a, double la, double lgap1,
  boolean_T upper);

/* Function Definitions */
static double betainc_cf(double x, double a, double b)
{
  double y;
  double aplusb;
  double C;
  double Dinv;
  int m;
  int exitg1;
  double yold;
  int twom;
  double d_tmp;
  double d;
  aplusb = a + b;
  C = 1.0;
  Dinv = 1.0 - aplusb * x / (a + 1.0);
  y = 1.0 / Dinv;
  m = 0;
  do {
    exitg1 = 0;
    if (m < 1000) {
      yold = y;
      twom = (1 + m) << 1;
      d_tmp = a + static_cast<double>(twom);
      d = (1.0 + static_cast<double>(m)) * (b - (1.0 + static_cast<double>(m))) *
        x / (((a - 1.0) + static_cast<double>(twom)) * d_tmp);
      C = 1.0 + d / C;
      Dinv = 1.0 + d / Dinv;
      y *= C / Dinv;
      d = -(a + (1.0 + static_cast<double>(m))) * (aplusb + (1.0 + static_cast<
        double>(m))) * x / (d_tmp * ((a + 1.0) + static_cast<double>(twom)));
      C = 1.0 + d / C;
      Dinv = 1.0 + d / Dinv;
      y *= C / Dinv;
      if (std::abs(y - yold) < 2.2204460492503131E-15) {
        exitg1 = 1;
      } else {
        m++;
      }
    } else {
      y = rtNaN;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return y;
}

static double eml_PHIc(double z)
{
  double y;
  double x;
  double t;
  x = 0.70710678118654746 * z;
  t = 3.97886080735226 / (std::abs(x) + 3.97886080735226);
  y = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (t - 0.5) +
    0.00011931402283834095) * (t - 0.5) + -0.0039638509736051354) * (t - 0.5) +
    -0.00087077963531729586) * (t - 0.5) + 0.0077367252831352668) * (t - 0.5) +
    0.0038333512626488732) * (t - 0.5) + -0.012722381378212275) * (t - 0.5) +
    -0.013382364453346007) * (t - 0.5) + 0.016131532973325226) * (t - 0.5) +
    0.039097684558848406) * (t - 0.5) + 0.0024936720005350331) * (t - 0.5) +
                        -0.0838864557023002) * (t - 0.5) + -0.11946395996432542)
                      * (t - 0.5) + 0.016620792496936737) * (t - 0.5) +
                     0.35752427444953105) * (t - 0.5) + 0.80527640875291062) *
                   (t - 0.5) + 1.1890298290927332) * (t - 0.5) +
                  1.3704021768233816) * (t - 0.5) + 1.313146538310231) * (t -
    0.5) + 1.0792551515585667) * (t - 0.5) + 0.77436819911953858) * (t - 0.5) +
              0.49016508058531844) * (t - 0.5) + 0.27537474159737679) * t * std::
    exp(-x * x);
  if (x < 0.0) {
    y = 1.0 - y;
  }

  return y;
}

static double eml_betainc(double x, double a, double b, double lbeta, boolean_T
  upper)
{
  double rval;
  double d0;
  boolean_T guard1 = false;
  double logx;
  double log1mx;
  if ((0.0 < x) && (x < 1.0)) {
    if (rtIsInf(a)) {
      if (!rtIsInf(b)) {
        if (x < 1.0) {
          rval = upper;
        } else {
          rval = 1.0 - static_cast<double>(upper);
        }
      } else if (x == 0.0) {
        rval = upper;
      } else if (x == 1.0) {
        rval = 1.0 - static_cast<double>(upper);
      } else {
        rval = rtNaN;
      }
    } else if (rtIsInf(b)) {
      if (x == 0.0) {
        rval = upper;
      } else {
        rval = 1.0 - static_cast<double>(upper);
      }
    } else {
      d0 = a + b;
      guard1 = false;
      if (d0 < 1.0E+7) {
        logx = std::log(x);
        if (1.0 - x != 1.0) {
          log1mx = std::log(1.0 - x) * (-x / ((1.0 - x) - 1.0));
        } else {
          log1mx = -x;
        }

        if (x < (a + 1.0) / (d0 + 2.0)) {
          rval = std::exp(((a * logx + b * log1mx) - std::log(a)) - lbeta) *
            betainc_cf(x, a, b);
          if (upper) {
            rval = 1.0 - rval;
          }
        } else {
          rval = std::exp(((a * logx + b * log1mx) - std::log(b)) - lbeta) *
            betainc_cf(1.0 - x, b, a);
          if (!upper) {
            rval = 1.0 - rval;
          }
        }

        if (rval == rval) {
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        logx = rt_powd_snf(b * x, 0.33333333333333331);
        log1mx = rt_powd_snf(a * (1.0 - x), 0.33333333333333331);
        if ((d0 - 1.0) * (1.0 - x) > 0.8) {
          logx = 3.0 * ((1.0 - 1.0 / (9.0 * b)) * logx - (1.0 - 1.0 / (9.0 * a))
                        * log1mx) / std::sqrt(logx * logx / b + log1mx * log1mx /
            a);
          if (upper) {
            log1mx = 0.70710678118654746 * logx;
            logx = 3.97886080735226 / (std::abs(log1mx) + 3.97886080735226);
            rval = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (logx -
              0.5) + 0.00011931402283834095) * (logx - 0.5) +
              -0.0039638509736051354) * (logx - 0.5) + -0.00087077963531729586) *
              (logx - 0.5) + 0.0077367252831352668) * (logx - 0.5) +
              0.0038333512626488732) * (logx - 0.5) + -0.012722381378212275) *
              (logx - 0.5) + -0.013382364453346007) * (logx - 0.5) +
              0.016131532973325226) * (logx - 0.5) + 0.039097684558848406) *
              (logx - 0.5) + 0.0024936720005350331) * (logx - 0.5) +
              -0.0838864557023002) * (logx - 0.5) + -0.11946395996432542) *
              (logx - 0.5) + 0.016620792496936737) * (logx - 0.5) +
                                  0.35752427444953105) * (logx - 0.5) +
                                 0.80527640875291062) * (logx - 0.5) +
                                1.1890298290927332) * (logx - 0.5) +
                               1.3704021768233816) * (logx - 0.5) +
                              1.313146538310231) * (logx - 0.5) +
                             1.0792551515585667) * (logx - 0.5) +
                            0.77436819911953858) * (logx - 0.5) +
                           0.49016508058531844) * (logx - 0.5) +
                          0.27537474159737679) * logx * std::exp(-log1mx *
              log1mx);
            if (log1mx < 0.0) {
              rval = 1.0 - rval;
            }
          } else {
            log1mx = 0.70710678118654746 * -logx;
            logx = 3.97886080735226 / (std::abs(log1mx) + 3.97886080735226);
            rval = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (logx -
              0.5) + 0.00011931402283834095) * (logx - 0.5) +
              -0.0039638509736051354) * (logx - 0.5) + -0.00087077963531729586) *
              (logx - 0.5) + 0.0077367252831352668) * (logx - 0.5) +
              0.0038333512626488732) * (logx - 0.5) + -0.012722381378212275) *
              (logx - 0.5) + -0.013382364453346007) * (logx - 0.5) +
              0.016131532973325226) * (logx - 0.5) + 0.039097684558848406) *
              (logx - 0.5) + 0.0024936720005350331) * (logx - 0.5) +
              -0.0838864557023002) * (logx - 0.5) + -0.11946395996432542) *
              (logx - 0.5) + 0.016620792496936737) * (logx - 0.5) +
                                  0.35752427444953105) * (logx - 0.5) +
                                 0.80527640875291062) * (logx - 0.5) +
                                1.1890298290927332) * (logx - 0.5) +
                               1.3704021768233816) * (logx - 0.5) +
                              1.313146538310231) * (logx - 0.5) +
                             1.0792551515585667) * (logx - 0.5) +
                            0.77436819911953858) * (logx - 0.5) +
                           0.49016508058531844) * (logx - 0.5) +
                          0.27537474159737679) * logx * std::exp(-log1mx *
              log1mx);
            if (log1mx < 0.0) {
              rval = 1.0 - rval;
            }
          }
        } else {
          d0 = b;
          gammaln(&d0);
          rval = eml_gammainc(0.5 * (((a + b) - 1.0) * (3.0 - x) - (b - 1.0)) *
                              (1.0 - x), b, std::log(b), d0, !upper);
        }
      }
    }
  } else if (x == 0.0) {
    rval = upper;
  } else if (x == 1.0) {
    rval = 1.0 - static_cast<double>(upper);
  } else {
    rval = rtNaN;
  }

  return rval;
}

static double eml_gammainc(double x, double a, double la, double lgap1,
  boolean_T upper)
{
  double rval;
  double asq;
  double stirlerr;
  static const double dv0[31] = { 0.0, 0.15342640972002736, 0.081061466795327261,
    0.054814121051917651, 0.0413406959554093, 0.033162873519936291,
    0.027677925684998338, 0.023746163656297496, 0.020790672103765093,
    0.018488450532673187, 0.016644691189821193, 0.015134973221917378,
    0.013876128823070748, 0.012810465242920227, 0.01189670994589177,
    0.011104559758206917, 0.010411265261972096, 0.0097994161261588039,
    0.0092554621827127329, 0.0087687001341393862, 0.00833056343336287,
    0.00793411456431402, 0.0075736754879518406, 0.007244554301320383,
    0.00694284010720953, 0.0066652470327076821, 0.0064089941880042071,
    0.0061717122630394576, 0.0059513701127588475, 0.0057462165130101155,
    0.0055547335519628011 };

  double d1;
  double a1;
  double xD0;
  double vsq;
  double old;
  double logpax;
  double term;
  double fac;
  int exitg1;
  double n;
  int i1;
  int i;
  if (!(x > 0.0)) {
    if (x == 0.0) {
      rval = upper;
    } else {
      rval = rtNaN;
    }
  } else if (rtIsInf(a)) {
    if (rtIsInf(x)) {
      rval = rtNaN;
    } else {
      rval = upper;
    }
  } else if (rtIsInf(x)) {
    rval = 1.0 - static_cast<double>(upper);
  } else {
    if (a <= 15.0) {
      asq = 2.0 * a;
      if (asq == std::floor(asq)) {
        stirlerr = dv0[static_cast<int>((asq + 1.0)) - 1];
      } else {
        stirlerr = ((lgap1 - (a + 0.5) * la) + a) - 0.91893853320467267;
      }
    } else {
      asq = a * a;
      stirlerr = (0.083333333333333329 + (-0.0027777777777777779 +
        (0.00079365079365079365 + (-0.00059523809523809529 +
        0.00084175084175084171 / asq) / asq) / asq) / asq) / a;
    }

    d1 = a - x;
    a1 = a + x;
    if (std::abs(d1) > 0.1 * a1) {
      if (a < 2.2250738585072014E-308 * x) {
        xD0 = x;
      } else if ((x < 1.0) && (a > 1.7976931348623157E+308 * x)) {
        xD0 = (a * la - a * std::log(x)) - a;
      } else {
        xD0 = (a * std::log(a / x) + x) - a;
      }
    } else {
      asq = x / a;
      asq = (1.0 - asq) / (1.0 + asq);
      vsq = asq * asq;
      xD0 = d1 * asq;
      old = xD0;
      term = 2.0 * (a * asq);
      asq = 3.0;
      do {
        exitg1 = 0;
        term *= vsq;
        xD0 += term / asq;
        if (xD0 == old) {
          exitg1 = 1;
        } else {
          old = xD0;
          asq += 2.0;
        }
      } while (exitg1 == 0);
    }

    logpax = (-0.5 * (1.8378770664093453 + la) - stirlerr) - xD0;
    if (x > 1.0E+6) {
      term = std::sqrt(x);
      old = std::abs(d1 - 1.0) / term;
      stirlerr = old * old;
      if (old < 15.0) {
        asq = 0.70710678118654746 * old;
        vsq = 3.97886080735226 / (asq + 3.97886080735226);
        a1 = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (vsq - 0.5) +
          0.00011931402283834095) * (vsq - 0.5) + -0.0039638509736051354) * (vsq
          - 0.5) + -0.00087077963531729586) * (vsq - 0.5) +
          0.0077367252831352668) * (vsq - 0.5) + 0.0038333512626488732) * (vsq -
          0.5) + -0.012722381378212275) * (vsq - 0.5) + -0.013382364453346007) *
          (vsq - 0.5) + 0.016131532973325226) * (vsq - 0.5) +
          0.039097684558848406) * (vsq - 0.5) + 0.0024936720005350331) * (vsq -
          0.5) + -0.0838864557023002) * (vsq - 0.5) + -0.11946395996432542) *
                             (vsq - 0.5) + 0.016620792496936737) * (vsq - 0.5) +
                            0.35752427444953105) * (vsq - 0.5) +
                           0.80527640875291062) * (vsq - 0.5) +
                          1.1890298290927332) * (vsq - 0.5) + 1.3704021768233816)
                        * (vsq - 0.5) + 1.313146538310231) * (vsq - 0.5) +
                       1.0792551515585667) * (vsq - 0.5) + 0.77436819911953858) *
                     (vsq - 0.5) + 0.49016508058531844) * (vsq - 0.5) +
                    0.27537474159737679) * vsq * std::exp(-asq * asq) *
          2.5066282746310002 * std::exp(0.5 * stirlerr);
        vsq = (a1 * ((stirlerr - 3.0) * old) - (stirlerr - 4.0)) / 6.0;
        xD0 = (a1 * ((stirlerr * stirlerr - 9.0) * stirlerr + 6.0) - ((stirlerr
                 - 1.0) * stirlerr - 6.0) * old) / 72.0;
        asq = (a1 * (((((5.0 * stirlerr + 45.0) * stirlerr - 81.0) * stirlerr -
                       315.0) * stirlerr + 270.0) * old) - ((((5.0 * stirlerr +
                   40.0) * stirlerr - 111.0) * stirlerr - 174.0) * stirlerr +
                192.0)) / 6480.0;
      } else {
        a1 = (1.0 + (-1.0 + (3.0 - 15.0 / stirlerr) / stirlerr) / stirlerr) /
          old;
        vsq = (1.0 + (-4.0 + (25.0 - 210.0 / stirlerr) / stirlerr) / stirlerr) /
          stirlerr;
        xD0 = (1.0 + (-11.0 + (130.0 - 1750.0 / stirlerr) / stirlerr) / stirlerr)
          / (stirlerr * old);
        asq = (1.0 + (-26.0 + (546.0 - 11368.0 / stirlerr) / stirlerr) /
               stirlerr) / (stirlerr * stirlerr);
      }

      if (x < a - 1.0) {
        asq = a * (((a1 / term - vsq / x) + xD0 / (x * term)) - asq / (x * x));
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }

        if (upper) {
          rval = 1.0 - rval;
        }
      } else {
        asq = a * (((a1 / term + vsq / x) + xD0 / (x * term)) + asq / (x * x));
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }

        if (!upper) {
          rval = 1.0 - rval;
        }
      }
    } else if (upper && (x < 1.0) && (a < 1.0)) {
      fac = a * -x;
      xD0 = fac / (a + 1.0);
      n = 2.0;
      do {
        exitg1 = 0;
        fac = -x * fac / n;
        term = fac / (a + n);
        xD0 += term;
        if (std::abs(term) <= std::abs(xD0) * 2.2204460492503131E-16) {
          exitg1 = 1;
        } else {
          n++;
        }
      } while (exitg1 == 0);

      asq = a * std::log(x) - lgap1;
      vsq = std::exp(asq);
      if (!(vsq == 1.0)) {
        if (vsq - 1.0 == -1.0) {
          asq = -1.0;
        } else {
          asq = (vsq - 1.0) * asq / std::log(vsq);
        }
      }

      rval = -((xD0 + asq) + xD0 * asq);
      if (rval < 0.0) {
        rval = 0.0;
      }
    } else if ((x < a) || (x < 1.0)) {
      n = 1.0;
      if (x > 2.2204460492503131E-16 * a) {
        fac = x / a;
        n = 2.0;
        do {
          exitg1 = 0;
          fac = x * fac / (a + (n - 1.0));
          if (fac < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            n++;
          }
        } while (exitg1 == 0);
      }

      asq = 0.0;
      i1 = static_cast<int>(((1.0 + (-1.0 - (n - 1.0))) / -1.0));
      for (i = 0; i < i1; i++) {
        asq = x * (1.0 + asq) / (a + ((n - 1.0) + -static_cast<double>(i)));
      }

      asq++;
      if (logpax < 709.782712893384) {
        rval = std::exp(logpax) * asq;
      } else {
        b_log(&asq);
        rval = std::exp(logpax + asq);
      }

      if (rval > 1.0) {
        rval = 1.0;
      }

      if (upper) {
        rval = 1.0 - rval;
      }
    } else {
      fac = 1.0;
      n = 1.0;
      do {
        exitg1 = 0;
        d1 = std::floor(a1);
        if (n <= d1) {
          fac = (a - n) * fac / x;
          if (std::abs(fac) < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            n++;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (n <= d1) {
        asq = 1.0;
      } else {
        n = std::floor(a);
        vsq = a - n;
        if (vsq == 0.0) {
          asq = 1.0;
        } else if (vsq == 0.5) {
          d1 = 3.1415926535897931 * x;
          b_sqrt(&d1);
          a1 = 2.0 * x;
          b_sqrt(&a1);
          asq = d1 * std::exp(x) * (2.0 * eml_PHIc(a1));
          n++;
        } else {
          xD0 = 1.0;
          a1 = x;
          old = 0.0;
          stirlerr = 1.0;
          fac = 1.0 / x;
          n = 1.0;
          asq = fac;
          term = 0.0;
          while (std::abs(asq - term) > 2.2204460492503131E-16 * asq) {
            term = asq;
            asq = n - vsq;
            xD0 = (a1 + xD0 * asq) * fac;
            old = (stirlerr + old * asq) * fac;
            asq = n * fac;
            a1 = x * xD0 + asq * a1;
            stirlerr = x * old + asq * stirlerr;
            fac = 1.0 / a1;
            asq = stirlerr * fac;
            n++;
          }

          asq *= x;
          n = std::floor(a) + 1.0;
        }
      }

      i1 = static_cast<int>(((1.0 + (-1.0 - (n - 1.0))) / -1.0));
      for (i = 0; i < i1; i++) {
        asq = 1.0 + (a - ((n - 1.0) + -static_cast<double>(i))) * asq / x;
      }

      asq = asq * a / x;
      if (logpax < 709.782712893384) {
        rval = std::exp(logpax) * asq;
      } else {
        b_log(&asq);
        rval = std::exp(logpax + asq);
      }

      if (rval > 1.0) {
        rval = 1.0;
      }

      if (!upper) {
        rval = 1.0 - rval;
      }
    }
  }

  return rval;
}

creal_T betaincinv(double x, double b)
{
  creal_T y;
  double r;
  double b_y;
  double t;
  double lbeta;
  double ftol1;
  double zlo;
  double zhi;
  int i;
  boolean_T exitg1;
  double f;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  double log1mz;
  r = 0.5;
  gammaln(&r);
  b_y = b;
  gammaln(&b_y);
  t = 0.5 + b;
  gammaln(&t);
  lbeta = (r + b_y) - t;
  if (!(0.0 < x)) {
    if (x == 0.0) {
      r = 0.0;
    } else {
      r = rtNaN;
    }
  } else {
    r = std::sqrt(-2.0 * std::log(x));
    b_y = r - (2.30753 + 0.27061 * r) / (1.0 + (0.99229 + 0.04481 * r) * r);
    r = 2.0 * b;
    t = 1.0 / (9.0 * b);
    t = (1.0 - t) + b_y * std::sqrt(t);
    t *= r * t * t;
    if (t > 0.0) {
      t = ((2.0 + r) - 2.0) / t;
      if (t > 1.0) {
        r = 1.0 - 2.0 / (t + 1.0);
      } else {
        r = std::exp((std::log(x * 0.5) + lbeta) / 0.5);
      }
    } else {
      r = 1.0 - std::exp((std::log((1.0 - x) * b) + lbeta) / b);
    }

    if (!(r > 0.0001)) {
      r = 0.0001;
    }

    if (!(r < 0.9999)) {
      r = 0.9999;
    }

    b_y = rtInf;
    t = rtInf;
    if (x > 1.0021E-294) {
      ftol1 = 2.2204460492503131E-14 * x;
    } else {
      ftol1 = 2.2251089859537388E-308;
    }

    zlo = 0.0;
    zhi = 1.0;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 1000)) {
      f = eml_betainc(r, 0.5, b, lbeta, false) - x;
      if ((f * b_y < 0.0) && (std::abs(b_y) <= std::abs(f))) {
        r = 0.5 * (r + t);
        f = eml_betainc(r, 0.5, b, lbeta, false) - x;
      }

      if (f > 0.0) {
        zhi = r;
      } else {
        zlo = r;
      }

      if ((std::abs(f) < ftol1) || (std::abs(r - t) < 2.2204460492503131E-16 * r
           + 2.2250738585072014E-308)) {
        exitg1 = true;
      } else {
        guard1 = false;
        guard2 = false;
        if (i < 200) {
          t = r;
          b_y = f;
          if (1.0 - r != 1.0) {
            log1mz = std::log(1.0 - r) * (-r / ((1.0 - r) - 1.0));
          } else {
            log1mz = -r;
          }

          r -= f / std::exp((-0.5 * std::log(r) + (b - 1.0) * log1mz) - lbeta);
          if (r <= zlo) {
            if (zlo == 0.0) {
              if (std::abs(0.0 - x) < std::abs(eml_betainc
                   (2.2250738585072014E-308, 0.5, b, lbeta, false) - x)) {
                r = 0.0;
                exitg1 = true;
              } else {
                zlo = 2.2250738585072014E-308;
                guard2 = true;
              }
            } else {
              guard2 = true;
            }
          } else if (r >= zhi) {
            if (zhi == 1.0) {
              if (std::abs(1.0 - x) < std::abs(eml_betainc(0.99999999999999989,
                    0.5, b, lbeta, false) - x)) {
                r = 1.0;
                exitg1 = true;
              } else {
                zhi = 0.99999999999999989;
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            i++;
          }
        } else {
          r = 0.5 * (zlo + zhi);
          i++;
        }

        if (guard2) {
          r = 0.99 * zlo + 0.01 * zhi;
          i++;
        }

        if (guard1) {
          r = 0.01 * zlo + 0.99 * zhi;
          i++;
        }
      }
    }
  }

  y.re = r;
  y.im = 0.0;
  return y;
}

double eml_betaincinv(double p, double a, double lbeta)
{
  double rval;
  boolean_T upper;
  double pLower;
  double r;
  double ftol1;
  int sgn;
  double zlo;
  double zhi;
  int i;
  boolean_T exitg1;
  double f;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  double log1mz;
  upper = true;
  if (!(p < 1.0)) {
    if (p == 1.0) {
      rval = 0.0;
    } else {
      rval = rtNaN;
    }
  } else {
    if (p > 0.5) {
      p = 1.0 - p;
      upper = false;
    }

    if (upper) {
      pLower = 1.0 - p;
      if (1.0 - p == 1.0) {
        pLower = 0.9999999999999778;
      }
    } else {
      pLower = p;
    }

    r = std::sqrt(-2.0 * std::log(pLower));
    r = 0.77777777777777779 + (r - (2.30753 + 0.27061 * r) / (1.0 + (0.99229 +
      0.04481 * r) * r)) * 0.47140452079103168;
    r *= r * r;
    if (r > 0.0) {
      r = ((4.0 * a + 1.0) - 2.0) / r;
      if (r > 1.0) {
        rval = 1.0 - 2.0 / (r + 1.0);
      } else {
        rval = std::exp((std::log(pLower * a) + lbeta) / a);
      }
    } else {
      rval = 1.0 - std::exp((std::log((1.0 - pLower) * 0.5) + lbeta) / 0.5);
    }

    if (!(rval > 0.0001)) {
      rval = 0.0001;
    }

    if (!(rval < 0.9999)) {
      rval = 0.9999;
    }

    r = rtInf;
    pLower = rtInf;
    if (p > 1.0021E-294) {
      ftol1 = 2.2204460492503131E-14 * p;
    } else {
      ftol1 = 2.2251089859537388E-308;
    }

    if (upper) {
      sgn = -1;
    } else {
      sgn = 1;
    }

    zlo = 0.0;
    zhi = 1.0;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 1000)) {
      f = static_cast<double>(sgn) * (eml_betainc(rval, a, 0.5, lbeta, upper) -
        p);
      if ((f * r < 0.0) && (std::abs(r) <= std::abs(f))) {
        rval = 0.5 * (rval + pLower);
        f = static_cast<double>(sgn) * (eml_betainc(rval, a, 0.5, lbeta, upper)
          - p);
      }

      if (f > 0.0) {
        zhi = rval;
      } else {
        zlo = rval;
      }

      if ((std::abs(f) < ftol1) || (std::abs(rval - pLower) <
           2.2204460492503131E-16 * rval + 2.2250738585072014E-308)) {
        exitg1 = true;
      } else {
        guard1 = false;
        guard2 = false;
        if (i < 200) {
          pLower = rval;
          r = f;
          if (1.0 - rval != 1.0) {
            log1mz = std::log(1.0 - rval) * (-rval / ((1.0 - rval) - 1.0));
          } else {
            log1mz = -rval;
          }

          rval -= f / std::exp(((a - 1.0) * std::log(rval) + -0.5 * log1mz) -
                               lbeta);
          if (rval <= zlo) {
            if (zlo == 0.0) {
              if (std::abs(static_cast<double>(upper) - p) < std::abs
                  (eml_betainc(2.2250738585072014E-308, a, 0.5, lbeta, upper) -
                   p)) {
                rval = 0.0;
                exitg1 = true;
              } else {
                zlo = 2.2250738585072014E-308;
                guard2 = true;
              }
            } else {
              guard2 = true;
            }
          } else if (rval >= zhi) {
            if (zhi == 1.0) {
              if (std::abs((1.0 - static_cast<double>(upper)) - p) < std::abs
                  (eml_betainc(0.99999999999999989, a, 0.5, lbeta, upper) - p))
              {
                rval = 1.0;
                exitg1 = true;
              } else {
                zhi = 0.99999999999999989;
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            i++;
          }
        } else {
          rval = 0.5 * (zlo + zhi);
          i++;
        }

        if (guard2) {
          rval = 0.99 * zlo + 0.01 * zhi;
          i++;
        }

        if (guard1) {
          rval = 0.01 * zlo + 0.99 * zhi;
          i++;
        }
      }
    }
  }

  return rval;
}

/* End of code generation (betaincinv.cpp) */
