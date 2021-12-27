/*
 * activationfunc.h
 *
 *  Created on: Dec 25, 2021
 *      Author: user
 */

#ifndef ACTIVATIONFUNC_H
#define ACTIVATIONFUNC_H

/**
 * @brief Implements rectified linear unit function
 * @param Input : Value to use on computation
 * @return double
 */
double FUNC_ReLU(double Input);

/**
 * @brief Returns one if Input is positive or zero, returns zero otherwise
 * @param Input : Value to use on computation
 * @return double
 */
double FUNC_IsNonNegative(double Input);

/**
 * @brief Implements the sigmoid function
 * @param Input
 * @return double
 */
double FUNC_Sigmoid(double Input);

/**
 * @brief Implements hyperbolic tangent function
 * @param Input
 * @return double
 */
double FUNC_Tanh(double Input);



#endif /* ACTIVATIONFUNC_H */
