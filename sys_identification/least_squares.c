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


int32_t RLS_Compute(float *SysInputs, float SysOutput, RLS_t *Parameters)
{
  float auxf;
  /* computing */
  /* y = a0x0 + a1*x1 + a2*x2 + ... + an*xn */
  /* X = [x0, x1, x2, ..., xn] */
  /* erro = y - coeffs'*X */
  /* k = cov*X/(1 + X'*cov*X) */
  /* coeffs = coeffs + k*erro */
  /* p = p - k*X'*p */

  /* erro = y - coeffs'*X */
  DotProduct(Parameters->SysCoeffs, SysInputs, Parameters->NumCoeff,
      &Parameters->Error);
  Parameters->Error = SysOutput - Parameters->Error;
  /* k = cov*X/(1 + X'*cov*X) */
  MultiplyMatrix(Parameters->Cov, SysInputs, Parameters->NumCoeff,
      Parameters->NumCoeff, 1, Parameters->Gain);
  DotProduct(Parameters->Gain, SysInputs, Parameters->NumCoeff, &auxf);
  auxf = 1.0/(1.0 + auxf);
  ScaleMatrix(Parameters->Gain, Parameters->NumCoeff, 1, auxf,
      Parameters->Gain);
  /* p = p - k*X'*p */
  MultiplyMatrix(SysInputs, Parameters->Cov, 1, Parameters->NumCoeff,
      Parameters->NumCoeff, Parameters->Aux1);
  MultiplyMatrix(Parameters->Gain, Parameters->Aux1, Parameters->NumCoeff, 1,
      Parameters->NumCoeff, Parameters->Aux2);
  SubtractMatrix(Parameters->Cov, Parameters->Aux2, Parameters->NumCoeff,
      Parameters->NumCoeff, Parameters->Cov);

  /* coeffs = coeffs + k*erro */
  ScaleMatrix(Parameters->Gain, Parameters->NumCoeff, 1, Parameters->Error,
      Parameters->Gain);
  AddMatrix(Parameters->SysCoeffs, Parameters->Gain, Parameters->NumCoeff, 1,
      Parameters->SysCoeffs);

  return 0;
}
