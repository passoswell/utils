#include <math.h>
#include "pid.h"


void PID_Init(float Kp, float Ki, float Kd, float SamplingTime,
    PID_t *Parameters)
{
  Parameters->Kp = Kp;
  Parameters->Ki = Ki;
  Parameters->Kd = Kd;
  Parameters->SamplingTime = SamplingTime;

  Parameters->InternalUse.Error[0] = 0.0;
  Parameters->InternalUse.Error[1] = 0.0;
  Parameters->InternalUse.Error[2] = 0.0;
  Parameters->InternalUse.Uk[0] = 0.0;
  Parameters->InternalUse.Uk[1] = 0.0;
  Parameters->PidMax = 0.0;
  Parameters->PidMin = 0.0;
  Parameters->MaxError = 0.0;

  Parameters->InternalUse.Coeff[0] = Kp + (Ki*SamplingTime) + (Kd/SamplingTime);
  Parameters->InternalUse.Coeff[1] = 0.0 - Kp - 2*(Kd/SamplingTime);
  Parameters->InternalUse.Coeff[2] = Kd/SamplingTime;
}


float PID_Compute(float Input, float Setpoint, PID_t *Parameters)
{
  /* Computing error */
  Parameters->InternalUse.Error[0] = Setpoint - Input;

  /* Testing if error is big or small */
  if(Setpoint == 0.0 && Parameters->InternalUse.Error[0] == 0.0){
    /* Error is small, Good thing to do for motor drivers is turn output zero */
    Parameters->InternalUse.Uk[0] = 0.0;
  }else if(fabsf(Parameters->InternalUse.Error[0]) < Parameters->MaxError){
    /* Error is small, Good thing to do is to keep previous control output */
    Parameters->InternalUse.Uk[0] = Parameters->InternalUse.Uk[1];
  }else
  {
    /* Error is big, running PID to compute control output */
    Parameters->InternalUse.Uk[0] = Parameters->InternalUse.Uk[1];
    Parameters->InternalUse.Uk[0] +=
        Parameters->InternalUse.Coeff[0]*Parameters->InternalUse.Error[0];
    Parameters->InternalUse.Uk[0] +=
        Parameters->InternalUse.Coeff[1]*Parameters->InternalUse.Error[1];
    Parameters->InternalUse.Uk[0] +=
        Parameters->InternalUse.Coeff[2]*Parameters->InternalUse.Error[2];
    /* Taking care of control output saturation */
    if( Parameters->InternalUse.Uk[0] <  Parameters->PidMin ){
      Parameters->InternalUse.Uk[0] =  Parameters->PidMin;
    }
    if( Parameters->InternalUse.Uk[0] > Parameters->PidMax ){
      Parameters->InternalUse.Uk[0] = Parameters->PidMax;
    }
  }
  /* Updating past states of PID variables */
  Parameters->InternalUse.Uk[1] = Parameters->InternalUse.Uk[0];
  Parameters->InternalUse.Error[2] = Parameters->InternalUse.Error[1];
  Parameters->InternalUse.Error[1] = Parameters->InternalUse.Error[0];

  return Parameters->InternalUse.Uk[0];
}


void PID_SetLimits(float PIDmax, float PIDmin, PID_t *Parameters)
{
  if( PIDmax > PIDmin){
    Parameters->PidMax = PIDmax;
    Parameters->PidMin = PIDmin;
  }else{
    Parameters->PidMax = PIDmin;
    Parameters->PidMin = PIDmax;
  }
}

void PID_SetMaxError(float MaxError, PID_t *Parameters)
{
  Parameters->MaxError = MaxError;
}
