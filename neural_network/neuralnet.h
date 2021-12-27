/*
 * neuralnet.h
 *
 *  Created on: Dec 25, 2021
 *      Author: user
 */

#ifndef NEURALNET_H
#define NEURALNET_H


#include <stdint.h>


#include "activationfunc.h"


typedef enum
{
  FUNC_NONE = 0,
  FUNC_RELU,
  FUNC_IS_NON_NEGATIVE,
  FUNC_SIGMOID,
  FUNC_TANH,
}NN_ActivationFunction_t;


typedef struct
{
  double* Weight;
  double  Bias;
  double  Output;

  NN_ActivationFunction_t ActivationFunction;

  uint32_t NumberInputs;

}NN_Neuron_t;


typedef struct
{
  NN_Neuron_t *Neuron;

  uint32_t NumberNeurons;

}NN_Layer_t;


typedef struct
{
  double *Weight;
  double *Bias;
  double *Output;

  NN_ActivationFunction_t ActivationFunction;

  uint32_t NumberInputs;
  uint32_t NumberNeurons;

}NN_LayerV2_t;



/**
 * @brief Uses dinamic allocation to reserve memory for the neuron
 * @param Neuron : Variable of type NN_Neuron_t to represent the neuron
 * @param NumberInputs : Number of inputs to the neuron, between 0.0 and 1.0
 * @param Func : Activation function
 */
void NN_InitNeuron(NN_Neuron_t *Neuron, uint32_t NumberInputs,
    NN_ActivationFunction_t Func);

/**
 * @brief Free the memory that was allocated dynamically
 * @param Neuron : Variable of type NN_Neuron_t to represent the neuron
 */
void NN_DeleteNeuron(NN_Neuron_t *Neuron);

/**
 * @brief Compute the output of a neuron given an input
 * @param Neuron : Variable of type NN_Neuron_t to represent the neuron
 * @param Inputs : Array of values to feed the neuron inputs,
 *                 between 0.0 and 1.0
 * @return
 */
double NN_ComputeNeuronOutput(NN_Neuron_t *Neuron, double *Inputs);

/**
 * @brief Routine updates the weights of the neuron
 * @param Neuron : Variable of type NN_Neuron_t to represent the neuron
 * @param Input : Array of values that fed the neuron inputs
 * @param TargetOutput : The desired output, between 0.0 and 1.0
 * @param LearningRate : The learning rate, between 0.0 and 1.0
 */
void NN_UpdateNeuronWeights(NN_Neuron_t *Neuron, double *Inputs,
    double TargetOutput, double LearningRate);

/**
 * @brief
 * @param Layer
 * @param NumberNeurons
 * @param NumberInputs
 * @param Func
 */
void NN_InitLayer(NN_Layer_t *Layer, uint32_t NumberNeurons,
    uint32_t NumberInputs, NN_ActivationFunction_t Func);

/**
 * @brief
 * @param Layer
 */
void NN_DeleteLayer(NN_Layer_t *Layer);

/**
 * @brief
 * @param Layer
 * @param Inputs
 * @param Outputs
 */
void NN_ComputeLayerOutput(NN_Layer_t *Layer, double *Inputs, double *Outputs);

/**
 * @brief
 * @param Layer
 * @param Inputs
 * @param TargetOutputs
 * @param LearningRate
 */
void NN_UpdateLayerWeights(NN_Layer_t *Layer, double *Inputs,
    double *TargetOutputs, double LearningRate);

/**
 * @brief
 * @param Layer
 * @param NumberNeurons
 * @param NumberInputs
 * @param Func
 */
void NN_InitLayerV2(NN_LayerV2_t *Layer, uint32_t NumberNeurons,
    uint32_t NumberInputs, NN_ActivationFunction_t Func);

/**
 * @brief
 * @param Layer
 */
void NN_DeleteLayerV2(NN_LayerV2_t *Layer);

#endif /* NEURALNET_H */
