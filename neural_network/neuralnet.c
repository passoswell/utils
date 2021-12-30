/*
 * neuralnet.c
 *
 *  Created on: Dec 25, 2021
 *      Author: user
 */



#include <stdlib.h>

#include "neuralnet.h"

/**
 * @brief Sets the maximum starting value for weights.
 */
#define NN_INITIAL_WEIGHT_MAX                                                0.5


double ComputeActivationFunction(NN_ActivationFunction_t Func, double Value);


void NN_InitNeuron(NN_Neuron_t *Neuron, uint32_t NumberInputs,
    NN_ActivationFunction_t Func)
{
  //Allocating memory for the weights of the neuron
  Neuron->NumberInputs = NumberInputs;
  Neuron->Weight = (double*)malloc(NumberInputs*sizeof(double));

  //Giving initial value for each weight and bias
  for(uint32_t i=0; i<NumberInputs; i++)
  {
    Neuron->Weight[i] = (double)rand()/RAND_MAX;
    Neuron->Weight[i] = 2.0 * ( Neuron->Weight[i] - 0.5 )
                  * NN_INITIAL_WEIGHT_MAX;
  }
  Neuron->Bias = 0.0;

  Neuron->ActivationFunction = Func;
  Neuron->Output = 1.0;
}

void NN_DeleteNeuron(NN_Neuron_t *Neuron)
{
  //Freeing the memory allocated for the weights
  if(Neuron->Weight != NULL)
  {
    free(Neuron->Weight);
  }
}

double NN_ComputeNeuronOutput(NN_Neuron_t *Neuron, double *Inputs)
{
  double sum = 0.0;

  //Computing the linear combination of inputs
  for(uint32_t i=0; i<Neuron->NumberInputs; i++)
  {
    sum += Inputs[i] * Neuron->Weight[i];
  }
  sum += Neuron->Bias;

  //Evaluating the activation function
  Neuron->Output = ComputeActivationFunction(Neuron->ActivationFunction, sum);
  return Neuron->Output;
}

void NN_UpdateNeuronWeights(NN_Neuron_t *Neuron, double *Inputs,
    double TargetOutput, double LearningRate)
{
  double learningRate;
  //Computing the new weights and bias based on desired output, neuron output
  //and the inputs applied to generate the given output
  learningRate = LearningRate;
  if(learningRate > 1.0) learningRate = 1.0;
  if(learningRate < 0.0) learningRate = 0.0;
  for(uint32_t i=0; i<Neuron->NumberInputs; i++)
  {
    //wi = wi + eta * (target - out) * X
    Neuron->Weight[i] += learningRate * (TargetOutput - Neuron->Output)
                * Inputs[i];
  }
  Neuron->Bias += learningRate * (TargetOutput - Neuron->Output) * 1.0;
}


void NN_InitLayer(NN_Layer_t *Layer, uint32_t NumberNeurons,
    uint32_t NumberInputs, NN_ActivationFunction_t Func)
{
  //Allocating memory for the neurons
  Layer->NumberNeurons = NumberNeurons;
  Layer->Neuron = (NN_Neuron_t*)malloc(NumberNeurons*sizeof(NN_Neuron_t));

  //Allocating memory for the weights of the neurons
  for(uint32_t i=0; i<NumberNeurons; i++)
  {
    NN_InitNeuron(&Layer->Neuron[i], NumberInputs, Func);
  }
}

void NN_DeleteLayer(NN_Layer_t *Layer)
{

  if(Layer->Neuron != NULL)
  {
    //Freeing memory from neurons
    for(uint32_t i=0; i<Layer->NumberNeurons; i++)
    {
      NN_DeleteNeuron(&Layer->Neuron[i]);
    }
    //Freeing memory allocated to the layer
    free(Layer->Neuron);
  }

}

void NN_ComputeLayerOutput(NN_Layer_t *Layer, double *Inputs, double *Outputs)
{
  if(Outputs == NULL)
  {
    for(uint32_t i=0; i<Layer->NumberNeurons; i++)
    {
      NN_ComputeNeuronOutput(&Layer->Neuron[i], Inputs + i);
    }
  }
  else
  {
    for(uint32_t i=0; i<Layer->NumberNeurons; i++)
    {
      Outputs[i] = NN_ComputeNeuronOutput(&Layer->Neuron[i], Inputs);
    }
  }
}

void NN_UpdateLayerWeights(NN_Layer_t *Layer, double *Inputs,
    double *TargetOutputs, double LearningRate)
{
  //Computing the new weights and biases based on desired outputs,
  //neurons outputs and the inputs applied to generate the given outputs
  for(uint32_t i=0; i<Layer->NumberNeurons; i++)
  {
    NN_UpdateNeuronWeights(&Layer->Neuron[i], Inputs, TargetOutputs[i],
        LearningRate);
  }
}



void NN_InitLayerV2(NN_LayerV2_t *Layer, uint32_t NumberNeurons,
    uint32_t NumberInputs, NN_ActivationFunction_t Func)
{
  //Allocating memory for the neurons
  Layer->NumberNeurons = NumberNeurons;
  Layer->NumberInputs = NumberInputs;
  Layer->Weight = (double*) malloc(NumberInputs*NumberNeurons*sizeof(double));
  Layer->Bias = (double*) malloc(NumberNeurons*sizeof(double));
  Layer->Output = (double*) malloc(NumberNeurons*sizeof(double));
  Layer->ActivationFunction = Func;


  //Giving initial value for each weight and bias
  for(uint32_t i=0; i<NumberNeurons; i++)
  {
    for(uint32_t j=0; j<NumberInputs; j++)
    {
      Layer->Weight[NumberInputs*i + j] = (double)rand()/RAND_MAX;
      Layer->Weight[NumberInputs*i + j] = 2.0 *
          ( Layer->Weight[Layer->NumberInputs*i + j] - 0.5 )
                      * NN_INITIAL_WEIGHT_MAX;
    }
    Layer->Bias[i] = 0.0;
  }
}


void NN_DeleteLayerV2(NN_LayerV2_t *Layer)
{
  free(Layer->Output);
  free(Layer->Bias);
  free(Layer->Weight);
}


void NN_ComputeLayerOutputV2(NN_LayerV2_t *Layer, double *Inputs,
    double *Outputs)
{
  for(uint32_t i=0; i<Layer->NumberNeurons; i++)
  {
    Layer->Output[i] = Layer->Bias[i];
    for(uint32_t j=0; j<Layer->NumberInputs; j++)
    {
      Layer->Output[i] += Layer->Weight[Layer->NumberInputs*i + j] * Inputs[j];
    }
    Layer->Output[i] = ComputeActivationFunction(Layer->ActivationFunction,
        Layer->Output[i]);
  }

  Outputs = &Layer->Output[0];
}


void NN_UpdateLayerWeightsV2(NN_LayerV2_t *Layer, double *Inputs,
    double *TargetOutputs, double LearningRate)
{
  double learningRate;
  //Computing the new weights and bias based on desired output, neuron output
  //and the inputs applied to generate the given output
  learningRate = LearningRate;
  if(learningRate > 1.0) learningRate = 1.0;
  if(learningRate < 0.0) learningRate = 0.0;
  for(uint32_t i=0; i<Layer->NumberNeurons; i++)
  {
    for(uint32_t j=0; j<Layer->NumberInputs; j++)
    {
      //wi = wi + eta * (target - out) * X
      Layer->Weight[Layer->NumberInputs*i + j] += learningRate *
          (TargetOutputs[i] - Layer->Output[i]) * Inputs[j];
    }
    Layer->Bias[i] += learningRate * (TargetOutputs[i] - Layer->Output[i]);
  }
}




double ComputeActivationFunction(NN_ActivationFunction_t Func, double Value)
{
  double output;
  switch(Func)
  {
  case FUNC_NONE:
    output = Value;
    break;
  case FUNC_RELU:
    output = FUNC_ReLU(Value);
    break;
  case FUNC_IS_NON_NEGATIVE:
    output = FUNC_IsNonNegative(Value);
    break;
  case FUNC_SIGMOID:
    output = FUNC_Sigmoid(Value);
    break;
  case FUNC_TANH:
    output = FUNC_Tanh(Value);
    break;
  default:
    output = FUNC_ReLU(Value);
    break;
  }
  return output;
}
