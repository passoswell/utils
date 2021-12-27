/*
 * actvationfunc.c
 *
 *  Created on: Dec 25, 2021
 *      Author: user
 */

#include <math.h>

#include "activationfunc.h"


double FUNC_ReLU(double Input)
{
  if(Input < 0.0)
  {
    return 0.0;
  }
  else
  {
    return Input;
  }
}

double FUNC_IsNonNegative(double Input)
{
  if(Input < 0.0)
  {
    return 0.0;
  }
  else
  {
    return 1.0;
  }
}

double FUNC_Sigmoid(double Input)
{
  return (1.0/(1.0+exp(-Input)));
}

double FUNC_Tanh(double Input)
{
  return tanh(Input);
}
