/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ARV_RMS.h
 *
 * Code generation for function 'ARV_RMS'
 *
 */

#ifndef ARV_RMS_H
#define ARV_RMS_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "../rtwtypes.h"
#include "../types.h"

/* Function Declarations */
extern void ARV_RMS(double window_num, const emxArray_real_T *EMG, double Fs,
                    emxArray_real_T *ARV, emxArray_real_T *RMS);

#endif

/* End of code generation (ARV_RMS.h) */
