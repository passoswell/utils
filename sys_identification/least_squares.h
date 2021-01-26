/**
 * @file  least_squares.h
 * @date  24-January-2021
 * @brief Implementations of least squares algorithms.
 *
 * @author
 * @author
 */


#ifdef __cplusplus
"C" {
#endif



#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H


#define LEAST_SQUARES_VER_MAJOR                                             2021
#define LEAST_SQUARES_VER_MINOR                                                1
#define LEAST_SQUARES_VER_PATCH                                                1
#define LEAST_SQUARES_BRANCH_MASTER


#include "matrix_math.h"


typedef struct
{
  float *SysCoeffs;    /*!<  */
  float *SumYiXji;     /*!< 1-D array of size NumCoeff */
  float *SumXkiXji;    /*!< 2-D array of size NumSamples * NumCoeff
                            float A[NumSamples * NumCoeff]
                            float A[NumSamples][NumCoeff]*/
  uint32_t NumCoeff;   /*!< Number coefficients to discover */
  uint32_t NumSamples; /*!< Number of points */
}LMS_t;


/**
 * @brief  Uses the least mean squares algorithm to find the coefficients of
 *         a multidimensional line.
 * @param  SysInput : Values aplied on the input of the line equation.
 * @param  SysOutput : Line equation response to aplied SysInput.
 * @param  Parameters : Handle with all needed variables.
 * @retval void
 * @note   SysInputs is a 2-D array of size NumSamples * (NumCoeff - 1)
 *                   can be defined as float x[NumSamples * (NumCoeff - 1)]
 *                   can be defined as float x[NumSamples][NumCoeff - 1]
 *                   NumCoeff is the number of coefficients to find
 *                   NumSamples is the number of points used, >= NumCoeff
 *         SysOutputs is a 1-D array of size NumSamples
 *                   can be defined as float y[NumSamples]
 *         The function returns 1 on success, 0 on failure.
 *
 *         If there is a line of the form:
 *         y = a0 + a1*x1 + a2*x2 + ... + an*xn
 *         This function finds the value for the coefficients:
 *         Parameters.SysCoeffs = {a0, a1, a2, ..., an},
 *         n = Parameters.NumCoeff
 *         Using values input to the equation / system
 *         SysInputs = {{x11, x21, x31, ..., xn1},
 *                      {x12, x22, x32, ..., xn2},
 *                                ...
 *                      {x1k, x2k, x3k, ..., xnk},}
 *         And values output by the equation / system
 *         SysOutputs = {y1, y2, ..., yk},
 *         k = Parameters.NumSamples
 *         NumSamples must be equal to or bigger than NumCoeff.
 */
int32_t LMS_Compute(float* SysInputs, float *SysOutputs, LMS_t *Parameters);

#endif /* LEAST_SQUARES_H */



#ifdef __cplusplus
}
#endif
