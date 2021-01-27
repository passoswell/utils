#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "least_squares.h"


/* A difference equation of a dynamic system */
/* y(t) = b0u(t) + b1u(t-1) */
uint32_t numCoeff = 2;
uint32_t numSamples = 14;
float inputs[14][2]  = {                /* {u(t), u(t-1)} */
    {0.8, 1.0}, {0.6, 0.8}, {0.4, 0.6},
    {0.2, 0.4}, {0.0, 0.2},
    {0.2, 0.0}, {0.4, 0.2}, {0.6, 0.4},
    {0.8, 0.6}, {1.0, 0.8}, {0.8, 1.0},
    {0.6, 0.8}, {0.4, 0.6}, {0.2, 0.4},
};
float outputs[14] = {                   /* y(t) */
    2.5, 2.4, 1.3, 1.2, 0.8, 0.0,
    0.9, 1.4, 1.9, 2.3, 2.4, 2.3, 1.3, 1.2,
};
float sumYiXji[2];
float sumXkiXji[14 * 2];
float coeffs[2];
float coeffs_2[2] = {0.0, 0.0};
float cov[2 * 2] = {1000.0, 0.0, 0.0, 1000.0};
float aux_1[2], aux_2[2*2];
float gain[2];

int main(void) {
  LMS_t LMS = {
      .NumCoeff = numCoeff,
      .NumSamples = numSamples,
      .SumYiXji = sumYiXji,
      .SumXkiXji = sumXkiXji,
      .SysCoeffs = coeffs,
  };
  RLS_t RLS = {
      .NumCoeff = numCoeff,
      .SysCoeffs = coeffs_2,
      .Cov = cov,
      .Gain = gain,
      .Aux1 = aux_1,
      .Aux2 = aux_2,
  };


  printf("\nFinding coefficients for an unknown difference equation of the form  y(t) = b0u(t) + b1u(t-1)  using LMS\n");
  for(int i = 7; i <= 14; i++){
    LMS.NumSamples = i;
    LMS_Compute(&inputs[0][0], outputs, &LMS);
    printf("Using %d samples: b0 = %f, b1 = %f\n", i, coeffs[0], coeffs[1]);
  }
  //printf("\n\n\n");

  printf("\nFinding coefficients for an unknown difference equation of the form  y(t) = b0u(t) + b1u(t-1) using RLS\n");
  for(int i = 0; i < 14; i++){
    RLS_Compute(&inputs[i][0], outputs[i], &RLS);
    printf("Iteration %d: b0 = %f, b1 = %f, cov matrix: [%f %f; %f %f]\n", i, coeffs_2[0], coeffs_2[1], cov[0], cov[1], cov[2], cov[3]);
  }
  printf("\n\n\n");

  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  return EXIT_SUCCESS;
}
