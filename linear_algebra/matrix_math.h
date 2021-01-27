/**
 * @file  matrixmath.h
 * @date  22-January-2021
 * @brief Basic math using vectors and matrces.
 *
 *   Adapted from MatrixMath for Arduino
 *   [https://github.com/eecharlie/MatrixMath]
 *
 * @author
 * @author
 */


#ifdef __cplusplus
"C" {
#endif

#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H


#define MATRIX_MATH_VER_MAJOR                                               2021
#define MATRIX_MATH_VER_MINOR                                                  1
#define MATRIX_MATH_VER_PATCH                                                  2
#define MATRIX_MATH_BRANCH_MASTER


#include <stdint.h>


/**
 * @brief  Computes absolute-value norm of a row or column vector.
 * @param  v : Vector.
 * @param  Size : Number of elements on vector.
 * @param  v : Vector.
 * @retval float
 * @note
 *             Size
 *             ===
 *     norm =  \    |v |
 *             /    | i|
 *             ===
 *             i = 0
 */
float NormVectorL1(float *V, int Size);


/**
 * @brief  Computes squared euclidian norm of a row or column vector.
 * @param  v : Vector.
 * @param  Size : Number of elements on vector.
 * @retval float
 * @note
 *            size
 *            ====
 *            \
 *             \        2
 *     norm =  /    /v \
 *            /     \ i/
 *            ====
 *           i = 0
 */
float NormVectorL2Squared(float *V, uint32_t Size);


/**
 * @brief  Computes euclidian norm of a row or column vector.
 * @param  v : Vector.
 * @param  Size : Number of elements on vector.
 * @retval float
 * @note
 *                     ___________
 *                    /size
 *                   / ====
 *                  /  \
 *                 /    \        2
 *     norm =     /     /    /v \
 *               /     /     \ i/
 *              /      ====
 *            \/       i = 0

 */
float NormVectorL2(float *V, uint32_t Size);


/**
 * @brief  Appends V2 to the end of V1 and store the result in Vresult.
 * @param  V1 : First input vector.
 * @param  SizeV1 : Size of V1.
 * @param  V2 : Second input vector.
 * @param  SizeV2 : Size of V2.
 * @param  Vresult : Vector where the concatenated vector will be stored.
 * @param  Size : Number of elements on vector.
 * @retval void
 */
void ConcatenateVector(float *V1, int32_t SizeV1, float *V2, int32_t SizeV2,
    float *Vresult);


/**
 * @brief  Compute the dot product between two sequences of equal size.
 * @param  V1 : First input vector.
 * @param  V2 : Second input vector.
 * @param  Size : Size of the vectors.
 * @param  Result : Scalar where dot product result will be stored.
 * @retval void
 */
void DotProduct(float *V1, float *V2, int32_t Size, float  *Result);


/**
 * @brief  Copy A to B.
 * @param  A : Pointer to input matrix (m x p).
 * @param  m : Number of rows in A.
 * @param  n : Number of columns in B.
 * @param  B : Pointer to output matrix (p x n).
 * @retval void
 * @note   A and B may not be of the same dimensions, but they must have
 *         the same number of elements (m * p = p * n).
 */
void CopyMatrix(float *A, int m, int n, float *B);


/**
 * @brief  Multiply A by B, store result in C.
 * @param  A : Pointer to input matrix (m x p).
 * @param  B : Pointer to input matrix (p x n).
 * @param  m : Number of rows in A.
 * @param  p : Number of columns in A = number of rows in B.
 * @param  n : Number of columns in B.
 * @param  C : Pointer to output matrix (m x n).
 * @retval void
 */
void MultiplyMatrix(float *A, float *B, int m, int p, int n, float *C);


/**
 * @brief  Add A and B, store result in C.
 * @param  A : Pointer to input matrix (m x n).
 * @param  B : Pointer to input matrix (m x n).
 * @param  m : Number of rows in A and in B.
 * @param  n : Number of columns A and in B.
 * @param  C : Pointer to output matrix  = A + B (m x n).
 * @retval void
 */
void AddMatrix(float *A, float *B, int m, int n, float *C);


/**
 * @brief  Subtract A and B, store result in C.
 * @param  A : Pointer to input matrix (m x n).
 * @param  B : Pointer to input matrix (m x n).
 * @param  m : Number of rows in A and in B.
 * @param  n : Number of columns A and in B.
 * @param  C : Pointer to output matrix = A - B (m x n).
 * @retval void
 */
void SubtractMatrix(float *A, float *B, int m, int n, float *C);


/**
 * @brief  Transpose A, store result in C.
 * @param  A : Pointer to input matrix (m x n).
 * @param  B : Pointer to input matrix (m x n).
 * @param  m : Number of rows in A.
 * @param  n : Number of columns A.
 * @param  C : Pointer to output matrix = transpose of A (n x m).
 * @retval void
 */
void TransposeMatrix(float *A, int m, int n, float *C);


/**
 * @brief  Multiply A by constant K, store result in C.
 * @param  A : Pointer to input matrix (m x n).
 * @param  m : Number of rows in A.
 * @param  n : Number of columns A.
 * @param  k : Real constant.
 * @param  C : Pointer to output matrix = k * A (m x n).
 * @retval void
 */
void ScaleMatrix(float *A, int m, int n, float k, float *C);


/**
 * @brief  Invert matrix A, store result in A.
 * @param  A : Pointer to input matrix (n x n).
 * @param  n : Number of rows and columns in A.
 * @retval int32_t
 * @note
 * This function inverts a matrix based on the Gauss Jordan method.
 * Specifically, it uses partial pivoting to improve numeric stability.
 * The algorithm is drawn from those presented in
 * NUMERICAL RECIPES: The Art of Scientific Computing.
 * The function returns 1 on success, 0 on failure.
 *
 * Returns 0 if no success
 *
 * NOTE: The argument is ALSO the result matrix, meaning
 * the input matrix is
 * REPLACED
 */
int32_t InvertMatrix(float *A, int n);

#endif /* MATRIX_MATH_H */



#ifdef __cplusplus
}
#endif
