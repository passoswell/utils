#include <math.h>
#include <stdlib.h>
#include "matrix_math.h"


/**
 * @brief  Computes aproximation for square root of a floating point number.
 * @param  x : Number to compute the square root.
 * @retval float
 * @note   Assumes that float is in the IEEE 754 single precision floating
 *         point format and that int is 32 bits.
 *         Source:
 *         https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
 */
float Sqrt_approx(float x)
{
  typedef union{int32_t asint32; float asfloat;}FLOAT_INT32;
  FLOAT_INT32 val;
  val.asfloat = x;

  val.asint32 = (val.asint32 >> 1) + 532676608L - 0x4B0D2L;

  return val.asfloat;
}


/**
 * @brief  Computes aproximation for inverse square root of a float number.
 * @param  x : Number to compute the inverse square root.
 * @retval float
 * @note   Assumes that float is in the IEEE 754 single precision floating
 *         point format and that int is 32 bits.
 *         Source:
 *         https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
 */
float InvSqrt_approx(float x)
{
  //float xhalf = 0.5f*x;
  typedef union{int32_t asint32; float asfloat;}FLOAT_INT32;
  FLOAT_INT32 val;
  val.asfloat = x;
  val.asint32 = 0x5f375a86 - (val.asint32 >> 1);
  /* The next line can be repeated any number of times to increase accuracy */
  //val.asint32 = val.asint32 * (1.5f - xhalf * u.x * u.x);
  return val.asfloat;
}


float NormVectorL1(float* V, int Size)
{
  int32_t i;
  float norm = 0.0;
  for(i = 0; i < Size; i++){
    norm += fabsf(*(V+i));
  }
  return norm;
}


float NormVectorL2Squared(float* V, uint32_t Size)
{
  int32_t i;
  float norm = 0.0;
  for(i = 0; i < Size; i++){
    norm += (*(V+i)) * (*(V+i));
  }
  return norm;
}


float NormVectorL2(float* V, uint32_t Size)
{
  //return sqrtf(NormVectorL2Squared(V, Size));
  return 0;
}


void ConcatenateVector(float *V1, int32_t SizeV1, float *V2, int32_t SizeV2,
    float* Vresult)
{
  CopyMatrix(V1,SizeV1,1,Vresult);
  CopyMatrix(V2,SizeV2,1,Vresult+SizeV1);
}


void CopyMatrix(float *A, int m, int n, float *B)
{
  int i,j;
  j = m*n;
  for (i = 0; i < j ; i++){
    *B = *A;
    A++;B++;
  }
}


void MultiplyMatrix(float* A, float* B, int m, int p, int n, float* C)
{
  int i, j, k;
  for (i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      *(C + n*i + j) = 0;
      for (k = 0; k < p; k++){
        *(C + n*i + j) = *(C + n*i + j) + *(A + p*i + k) * (*(B + n*k + j));
      }
    }
  }
}


void AddMatrix(float *A, float *B, int m, int n, float *C)
{
  int i,j;
  j = m*n;
  for (i = 0; i < j ; i++)
  {
    *C = *A + *B;
    A++;B++;C++;
  }
}


void SubtractMatrix(float *A, float *B, int m, int n, float *C)
{
  int i,j;
  j = m*n;
  for (i = 0; i < j ; i++)
  {
    *C = *A - *B;
    A++;B++;C++;
  }
}


void TransposeMatrix(float *A, int m, int n, float *C)
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++){
      *(C+m*j+i) = *(A+n*i+j);
    }
  }
}


void ScaleMatrix(float *A, int m, int n, float k, float *C)
{
  int i,j;
  j = m*n;
  for (i = 0; i < j ; i++)
  {
    *C = (*A)*k;
    A++; C++;
  }
}


int32_t InvertMatrix(float* A, int n)
{
  // A = input matrix AND result matrix
  // n = number of rows = number of columns in A (n x n)
  int pivrow = 0;   // keeps track of current pivot row
  int k, i, j;    // k: overall index along diagonal; i: row index; j: col index
  int pivrows[n]; // keeps track of rows swaps to undo at end
  float tmp;    // used for finding max value and making column swaps

  for (k = 0; k < n; k++){
    // find pivot row, the row with biggest entry in current column
    tmp = 0;
    for (i = k; i < n; i++){
      // 'Avoid using other functions inside abs()?'
      if (fabs(*(A + i*n + k)) >= tmp){
        tmp = fabs(*(A + i*n + k));
        pivrow = i;
      }
    }

    // check for singular matrix
    if (*(A + pivrow*n + k) == 0.0f){
      //Serial.println("Inversion failed due to singular matrix");
      return 0;
    }

    // Execute pivot (row swap) if needed
    if (pivrow != k){
      // swap row k with pivrow
      for (j = 0; j < n; j++){
        tmp = *(A + k*n + j);
        *(A + k*n + j) = *(A + pivrow*n + j);
        *(A + pivrow*n + j) = tmp;
      }
    }
    pivrows[k] = pivrow;  // record row swap (even if no swap happened)

    tmp = 1.0f / *(A + k*n + k);  // invert pivot element
    // This element of input matrix becomes result matrix
    *(A + k*n + k) = 1.0f;

    // Perform row reduction (divide every element by pivot)
    for (j = 0; j < n; j++){
      *(A + k*n + j) = (*(A + k*n + j)) * tmp;
    }

    // Now eliminate all other entries in this column
    for (i = 0; i < n; i++){
      if (i != k){
        tmp = *(A + i*n + k);
        // The other place where in matrix becomes result mat
        *(A + i*n + k) = 0.0f;
        for (j = 0; j < n; j++){
          *(A + i*n + j) = *(A + i*n + j) - *(A + k*n + j) * tmp;
        }
      }
    }
  }

  // Done, now need to undo pivot row swaps
  //by doing column swaps in reverse order
  for (k = n - 1; k >= 0; k--){
    if (pivrows[k] != k){
      for (i = 0; i < n; i++){
        tmp = *(A + i*n + k);
        *(A + i*n + k) = *(A + i*n + pivrows[k]);
        *(A + i*n + pivrows[k]) = tmp;
      }
    }
  }
  return 1;
}
