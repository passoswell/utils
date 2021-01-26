#include <string.h>
#include "least_squares.h"
#include "matrix_math.h"


int32_t LMS_Compute(float* SysInputs, float *SysOutputs, LMS_t *Parameters)
{
  int32_t returnvalue;
  uint32_t numCoeff = Parameters->NumCoeff;
  uint32_t numSamples = Parameters->NumSamples;

  /**
   * Matrix of sum of product of inputs and outputs (Y)
   * Syx0 Syx1 Syx2 Syx3
   */

  /**
   * Matrix of sum of products of inputs (X)
   * Sx0x0  Sx0x1  Sx0x2  Sx0x3
   * Sx1x0  Sx1x1  Sx1x2  Sx1x3
   * Sx2x0  Sx2x1  Sx2x2  Sx2x3
   * Sx3x0  Sx3x1  Sx3x2  Sx3x3
   */

  for(uint32_t k = 0; k < numCoeff; k++){
    for(uint32_t j = 0; j <= k; j++){
      Parameters->SumXkiXji[j + k * numCoeff] = 0;
      for(uint32_t i = 0; i < numSamples; i++){

        /* Sum of products between SysOutputs and SysInputs */
        if(k == numCoeff - 1)
        {
          if(j != 0){
            Parameters->SumYiXji[j] += SysOutputs[i] *
                SysInputs[(j-1) + i * (numCoeff - 1)];
          }else{
            Parameters->SumYiXji[j] += SysOutputs[i]; /* x0 is always 1 */
          }
        }

        /* Sum of products between SysOutputs */
        if( k == 0 ){
          if(j == 0){
            Parameters->SumXkiXji[0] = numSamples; /* x0 is always 1 */
            break;
          }else{
            /* x0 is always 1 */
            Parameters->SumXkiXji[j + k * numCoeff] +=
                SysInputs[(j-1) + i * (numCoeff - 1)];
          }
        }else{
          if(j == 0){
            /* x0 is always 1 */
            Parameters->SumXkiXji[j + k * numCoeff] +=
                SysInputs[(k-1) + i * (numCoeff - 1)];
          }else{
            Parameters->SumXkiXji[j + k * numCoeff] +=
                SysInputs[(k-1) + i * (numCoeff - 1)] *
                SysInputs[(j-1) + i * (numCoeff - 1)];
          }
          if(j != k){
            Parameters->SumXkiXji[k + j * numCoeff] =
                Parameters->SumXkiXji[j + k * numCoeff];
          }
        }

      }
    }
  }



  /**
   * Coefficients: A = inv(X) * Y
   */
  returnvalue = InvertMatrix(Parameters->SumXkiXji, numCoeff);
  if(returnvalue == 1){
    MultiplyMatrix(Parameters->SumXkiXji, Parameters->SumYiXji,
        numCoeff, numCoeff, 1, Parameters->SysCoeffs);
  }

  return returnvalue;

}
