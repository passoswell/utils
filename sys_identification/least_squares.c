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
      Parameters->SumYiXji[j] = 0;
      for(uint32_t i = 0; i < numSamples; i++){

        /* Sum of products between SysOutputs and SysInputs */
        if(k == numCoeff - 1)
        {
          Parameters->SumYiXji[j] += SysOutputs[i] *
              SysInputs[j + i * numCoeff];
        }

        /* Sum of products between SysOutputs */
        Parameters->SumXkiXji[j + k * numCoeff] +=
            SysInputs[k + i * numCoeff] *
            SysInputs[j + i * numCoeff];
        if(j != k){
          Parameters->SumXkiXji[k + j * numCoeff] =
              Parameters->SumXkiXji[j + k * numCoeff];
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


int32_t RLS_Compute(float SysInputs, float SysOutputs, LMS_t *Parameters)
{
  //computing
  //%     fi = [-y(t-1);-y(t-2);u(t-1);u(t-2)];
  //%     erro(t) = y(t)-teta'*fi;
  //    K = p*fi/(1+fi'*p*fi);
  //    teta = [teta, teta(:,end)+K*erro(end)];
  //    p = (p-K*fi'*p);
  return 0;
}
