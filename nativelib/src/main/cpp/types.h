/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft_compare_types.h
 *
 * Code generation for function 'fft_compare'
 *
 */

#ifndef FFT_COMPARE_TYPES_H
#define FFT_COMPARE_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} emxArray_creal_T;

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_boolean_T
{
    boolean_T *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};

struct emxArray_int32_T
{
    int *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};

#endif

/* End of code generation (fft_compare_types.h) */
