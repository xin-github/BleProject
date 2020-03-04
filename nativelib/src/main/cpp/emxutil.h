/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filter_all_emxutil.h
 *
 * Code generation for function 'filter_all_emxutil'
 *
 */

#ifndef FILTER_ALL_EMXUTIL_H
#define FILTER_ALL_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "types.h"

/* Function Declarations */
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int oldNumel);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
#endif

/* End of code generation (filter_all_emxutil.h) */
