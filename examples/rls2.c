#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "least_squares.h"


/* A difference equation of a dynamic system */
/* y[0] = 0.75*y[1] - 0.126*y[2] + u[0] + 2.45*u[1] + 0.9*u[2]; */
/* Equivalent transfer function (TF) */
/**
 *     Y(z⁻1)     1.0 + 2.45 * z^-1 + 0.9 * z^-2
 *    -------- = ----------------------------------
 *     U(z⁻1)     1.0 - 0.75 * z^-1 + 0.126 * z^-2
 */
uint32_t numCoeff = 5;
uint32_t sizeNumerator = 3; /* 3 unknown coeffs on numerator of TF */
uint32_t sizeDenominator = 2; /* 2 unknown coeffs on denominator of TF */
uint32_t numSamples = 100;
float inputs[5];
float outputs = 0.0;
float coeffs[5];
float cov[5 * 5];
float aux_1[5], aux_2[5 * 5];
float gain[5];


void make_diag(float *A, uint32_t n, float Value){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i != j){
        *(A + j + n*i) = 0;
      }else{
        *(A + j + n*i) = Value;
      }
    }
  }
}


int main(void) {
  int auxint;

  RLS_t RLS = {
      .NumCoeff = numCoeff,
      .SysCoeffs = coeffs,
      .Cov = cov,
      .Gain = gain,
      .Aux1 = aux_1,
      .Aux2 = aux_2,
  };

  memset(inputs, 0, sizeof(inputs));
  memset(&outputs, 0, sizeof(outputs));
  memset(coeffs, 0, sizeof(coeffs));
  memset(cov, 0, sizeof(cov));
  memset(gain, 0, sizeof(gain));


  /* Initializes random number generator */
  srand(0);
  /* Initializes covariance matrix */
  make_diag(cov, numCoeff, 1000.0);


  for(int i = 0; i < 100; i++){

    /* Iterating the difference equation */
    inputs[1] = inputs[0];
    inputs[0] = outputs;
    inputs[4] = inputs[3];
    inputs[3] = inputs[2];
    auxint = rand() % 255;
    inputs[2] = auxint;
    /* y[0] = 0.75*y[1] - 0.126*y[2] + u[0] + 2.45*u[1] + 0.9*u[2]; */
    outputs = 0.75*inputs[0] - 0.126*inputs[1] + inputs[2] + 2.45*inputs[3] + 0.9*inputs[4];

//    printf("Iteration: %d Measurements: [", i);
//    for(int j = 0; j < numCoeff; j++){
//      printf("%f ",inputs[j]);
//    }
//    printf("], Output: %f\n", outputs);

    RLS_Compute(inputs, outputs, &RLS);
    printf("Iteration: %d Coeffs: [", i);
    for(int j = 0; j < numCoeff; j++){
      printf("%f ",coeffs[j]);
    }
    printf("], Error: %f\n",RLS.Error);
  }
  printf("\n\n\n");

  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  return EXIT_SUCCESS;
}
