/**
 * @file  pid.h
 * @date  22-January-2021
 * @brief Implementations of PID controller.
 *
 * @author
 * @author
 */


#ifndef PID_H
#define PID_H


#include <stdint.h>


/**
 * @brief List of PID variables that must not be changed.
 */
typedef struct
{
  float Error[3];       /*!< Present and past errors */
  float Uk[2];          /*!< Present and past controller outputs */
  float Coeff[3];       /*!< PID coefficients */
}PID_Internal_t;

/**
 * @brief List of PID variables.
 */
typedef struct
{
  float          Kp;           /*!< Proportional gain */
  float          Ki;           /*!< Integral gain */
  float          Kd;           /*!< Derivative gain */
  float          SamplingTime; /*!< Time between sample acquisitions */
  float          PidMax;       /*!< Maximum controller output value */
  float          PidMin;       /*!< Minimum controller output value */
  float          MaxError;     /*!< Error at which PID can stop updating */
  PID_Internal_t InternalUse;
}PID_t;


/**
 * @brief  Configures PID internal variables.
 * @param  Kp : Proportional gain.
 * @param  Ki : Integral gain.
 * @param  Kd : Derivative gain.
 * @param  SamplingTime : Time between sample acquisitions.
 * @param  Parameter : List of PID parameters to be initialized.
 * @retval void
 */
void PID_Init(float Kp, float Ki, float Kd, float SamplingTime,
    PID_t *Parameters);


/**
 * @brief  Computes PID output.
 * @param  Input : New measurement.
 * @param  Setpoint : Desired value for the Input.
 * @param  Parameter : List of PID parameters.
 * @retval float
 * @note   This function uses bilinear transformation to approximate a
 *         continuous-time controller into a discrete-time equivalent.
 */
float PID_Compute(float Input, float Setpoint, PID_t *Parameters);


/**
 * @brief  Set limits to PID output value.
 * @param  PIDmax : Maximum PID output value.
 * @param  PIDmin : Minimum PID output value.
 * @param  Parameter : List of PID parameters.
 * @retval void
 */
void PID_SetLimits(float PIDmax, float PIDmin, PID_t *Parameters);


/**
 * @brief  Set an target error for the controller.
 * @param  MaxError : Target error.
 * @param  Parameter : List of PID parameters.
 * @retval void
 */
void PID_SetMaxError(float MaxError, PID_t *Parameters);

#endif /* PID_H */
