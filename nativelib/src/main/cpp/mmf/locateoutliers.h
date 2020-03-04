/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * locateoutliers.h
 *
 * Code generation for function 'locateoutliers'
 *
 */

#ifndef LOCATEOUTLIERS_H
#define LOCATEOUTLIERS_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "../rtwtypes.h"
#include "../types.h"

/* Function Declarations */
extern void vIsOutlier(const emxArray_real_T *a, int mxo, emxArray_boolean_T *tf,
  double *lb, double *ub, double *center);

#endif

/* End of code generation (locateoutliers.h) */
