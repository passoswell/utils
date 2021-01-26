#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "least_squares.h"


int32_t error[20];

/* Simple line */
/* y = 1 + 2 * x */
uint32_t numCoeff1 = 2;
uint32_t numSamples1 = 2;
float inputs1[2][2]  = {{1,1}, {1,10}}; /* {1, x} */
float outputs1[2] = {3, 21}; /* y */
float sumYiXji1[2];
float sumXkiXji1[2 * 2];
float coeffs1[2];

/* Multidimensional line */
/* y = 1 + 2 * x1 - 4 * x2 */
uint32_t numCoeff2 = 3;
uint32_t numSamples2 = 4;
float inputs2[4][3]  = {  /* {1, x1,x2} */
    {1, 1, 0},{1, 0,1},{1, 15,12},{1, -20, 20}
};
float outputs2[4] = {3, -3, -17, -119};                  /* y */
float sumYiXji2[3];
float sumXkiXji2[4 * 3];
float coeffs2[3];

/* Polynomial */
/* y = 5 + x + x^2 */
uint32_t numCoeff3 = 3;
uint32_t numSamples3 = 3;
float inputs3[3][3]  = {{1, 0, 0},{1, 1,1},{1, 2,4}}; /* {1, x, x^2} */
float outputs3[3] = {5, 7, 11};               /* y */
float sumYiXji3[3];
float sumXkiXji3[3 * 3];
float coeffs3[3];


/* Incomplete polynomial (fails) */
/* y = 0 + 0 + 5*x^2 */
/* This will not work because leads to a non-invertible matrix */
uint32_t numCoeff4 = 3;
uint32_t numSamples4 = 3;
float inputs4[3][3]  = {{0, 0, 0},{0, 0, 1},{0, 0, 4}}; /* {0, 0, x^2} */
float outputs4[3] = {0, 5, 20};               /* y */
float sumYiXji4[3];
float sumXkiXji4[3 * 3];
float coeffs4[3];


/* Incomplete polynomial (computes correctly) */
/* y = 5*x^2 */
uint32_t numCoeff5 = 1;
uint32_t numSamples5 = 3;
float inputs5[3][1]  = {{0},{1},{4}}; /* {x^2} */
float outputs5[3] = {0, 5, 20};               /* y */
float sumYiXji5[1];
float sumXkiXji5[3 * 1];
float coeffs5[1];


/* A difference equation of a dynamic system */
/* y(t) = b0u(t) + b1u(t-1) */
uint32_t numCoeff10 = 2;
uint32_t numSamples10 = 14;
float inputs10[14][2]  = {                /* {u(t), u(t-1)} */
    {0.8, 1.0}, {0.6, 0.8}, {0.4, 0.6},
    {0.2, 0.4}, {0.0, 0.2},
    {0.2, 0.0}, {0.4, 0.2}, {0.6, 0.4},
    {0.8, 0.6}, {1.0, 0.8}, {0.8, 1.0},
    {0.6, 0.8}, {0.4, 0.6}, {0.2, 0.4},
};
float outputs10[14] = {                   /* y(t) */
    2.5, 2.4, 1.3, 1.2, 0.8, 0.0,
    0.9, 1.4, 1.9, 2.3, 2.4, 2.3, 1.3, 1.2,
};
float sumYiXji10[2];
float sumXkiXji10[14 * 2];
float coeffs10[2];

int main(void) {
  LMS_t LMS1 = {
      .NumCoeff = numCoeff1,
      .NumSamples = numSamples1,
      .SumYiXji = sumYiXji1,
      .SumXkiXji = sumXkiXji1,
      .SysCoeffs = coeffs1,
  };
  LMS_t LMS2 = {
      .NumCoeff = numCoeff2,
      .NumSamples = numSamples2,
      .SumYiXji = sumYiXji2,
      .SumXkiXji = sumXkiXji2,
      .SysCoeffs = coeffs2,
  };
  LMS_t LMS3 = {
      .NumCoeff = numCoeff3,
      .NumSamples = numSamples3,
      .SumYiXji = sumYiXji3,
      .SumXkiXji = sumXkiXji3,
      .SysCoeffs = coeffs3,
  };
  LMS_t LMS4 = {
      .NumCoeff = numCoeff4,
      .NumSamples = numSamples4,
      .SumYiXji = sumYiXji4,
      .SumXkiXji = sumXkiXji4,
      .SysCoeffs = coeffs4,
  };
  LMS_t LMS5 = {
      .NumCoeff = numCoeff5,
      .NumSamples = numSamples5,
      .SumYiXji = sumYiXji5,
      .SumXkiXji = sumXkiXji5,
      .SysCoeffs = coeffs5,
  };
  LMS_t LMS10 = {
      .NumCoeff = numCoeff10,
      .NumSamples = numSamples10,
      .SumYiXji = sumYiXji10,
      .SumXkiXji = sumXkiXji10,
      .SysCoeffs = coeffs10,
  };

  printf("Finding coefficients of the line y = 1 + 2 * x \n");
  error[0] = LMS_Compute(&inputs1[0][0], outputs1, &LMS1);
  printf("Expected: [1.0, 2.0] Computed: [%f %f]\n",coeffs1[0], coeffs1[1]);

  printf("\nFinding coefficients of the line y = 1 + 2 * x1 - 4 * x2 \n");
  error[1] = LMS_Compute(&inputs2[0][0], outputs2, &LMS2);
  printf("Expected: [1.0, 2.0, -4.0] Computed: [%f %f %f]\n",coeffs2[0], coeffs2[1], coeffs2[2]);

  printf("\nFinding coefficients of the polynomial y = 5 + x + x^2 \n");
  error[2] = LMS_Compute(&inputs3[0][0], outputs3, &LMS3);
  printf("Expected: [5.0, 1.0, 1.0] Computed: [%f %f %f]\n",coeffs3[0], coeffs3[1], coeffs3[2]);

  printf("\nFinding coefficients of the polynomial y = 0 + 0 + 5*x^2 \n");
  error[3] = LMS_Compute(&inputs4[0][0], outputs4, &LMS4);
  printf("Expected: [0.0, 0.0, 5.0] Computed: [%f %f %f]\n",coeffs4[0], coeffs4[1], coeffs4[2]);

  printf("\nFinding coefficients of the polynomial y = 5*x^2 \n");
  error[4] = LMS_Compute(&inputs5[0][0], outputs5, &LMS5);
  printf("Expected: [5.0] Computed: [%f]\n",coeffs5[0]);

  printf("\nFinding coefficients for an unknown difference equation of the form  y(t) = b0u(t) + b1u(t-1) \n");
  for(int i = 7; i <= 14; i++){
    LMS10.NumSamples = i;
    error[i] = LMS_Compute(&inputs10[0][0], outputs10, &LMS10);
    printf("Using %d samples: b0 = %f, b1 = %f\n", i, coeffs10[0], coeffs10[1]);
  }
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  return EXIT_SUCCESS;
}
