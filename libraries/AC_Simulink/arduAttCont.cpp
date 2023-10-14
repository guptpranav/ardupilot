//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: arduAttCont.cpp
//
// Code generated for Simulink model 'arduAttCont'.
//
// Model version                  : 4.8
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Fri Sep  8 02:40:38 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "arduAttCont.h"
#include "rtwtypes.h"

// Model step function
void arduAttCont::step(real32_T arg_attiude_error[3], real32_T arg_rate_ff[3],
  real32_T arg_rate_meas[3], real32_T (&arg_Out1)[3])
{
  real32_T rtb_FilterCoefficient;
  real32_T rtb_FilterCoefficient_g;
  real32_T rtb_FilterCoefficient_p;
  real32_T rtb_pitchsum;
  real32_T rtb_rollsum;
  real32_T rtb_yawsum;

  // Sum: '<Root>/rollsum' incorporates:
  //   Gain: '<Root>/Kp_roll'
  //   Inport: '<Root>/attitude_error'
  //   Inport: '<Root>/rate_feedforward'
  //   Inport: '<Root>/rate_measured'

  rtb_rollsum = (arduAttCont_P.ANG_RLL_P * arg_attiude_error[0] + arg_rate_ff[0])
    - arg_rate_meas[0];

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S77>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  rtb_FilterCoefficient = (arduAttCont_P.RAT_RLL_D * rtb_rollsum -
    arduAttCont_DW.Filter_DSTATE) * arduAttCont_P.rollratePIDController_N;

  // Sum: '<Root>/pitchsum' incorporates:
  //   Gain: '<Root>/Kp_pitch'
  //   Inport: '<Root>/attitude_error'
  //   Inport: '<Root>/rate_feedforward'
  //   Inport: '<Root>/rate_measured'

  rtb_pitchsum = (arduAttCont_P.ANG_PIT_P * arg_attiude_error[1] + arg_rate_ff[1])
    - arg_rate_meas[1];

  // Gain: '<S38>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S30>/Filter'
  //   Gain: '<S29>/Derivative Gain'
  //   Sum: '<S30>/SumD'

  rtb_FilterCoefficient_g = (arduAttCont_P.RAT_PIT_D * rtb_pitchsum -
    arduAttCont_DW.Filter_DSTATE_j) * arduAttCont_P.pitchratePIDController_N;

  // Sum: '<Root>/yawsum' incorporates:
  //   Gain: '<Root>/Kp_yaw'
  //   Inport: '<Root>/attitude_error'
  //   Inport: '<Root>/rate_feedforward'
  //   Inport: '<Root>/rate_measured'

  rtb_yawsum = (arduAttCont_P.ANG_YAW_P * arg_attiude_error[2] + arg_rate_ff[2])
    - arg_rate_meas[2];

  // Gain: '<S134>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S126>/Filter'
  //   Gain: '<S125>/Derivative Gain'
  //   Sum: '<S126>/SumD'

  rtb_FilterCoefficient_p = (arduAttCont_P.RAT_YAW_D * rtb_yawsum -
    arduAttCont_DW.Filter_DSTATE_b) * arduAttCont_P.yawratePIDController_N;

  // Outport: '<Root>/RPY_out' incorporates:
  //   DiscreteIntegrator: '<S131>/Integrator'
  //   DiscreteIntegrator: '<S35>/Integrator'
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S136>/Proportional Gain'
  //   Gain: '<S40>/Proportional Gain'
  //   Gain: '<S88>/Proportional Gain'
  //   Sum: '<S140>/Sum'
  //   Sum: '<S44>/Sum'
  //   Sum: '<S92>/Sum'

  arg_Out1[0] = (arduAttCont_P.RAT_RLL_P * rtb_rollsum +
                 arduAttCont_DW.Integrator_DSTATE) + rtb_FilterCoefficient;
  arg_Out1[1] = (arduAttCont_P.RAT_PIT_P * rtb_pitchsum +
                 arduAttCont_DW.Integrator_DSTATE_k) + rtb_FilterCoefficient_g;
  arg_Out1[2] = (arduAttCont_P.RAT_YAW_P * rtb_yawsum +
                 arduAttCont_DW.Integrator_DSTATE_a) + rtb_FilterCoefficient_p;

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Gain: '<S80>/Integral Gain'

  arduAttCont_DW.Integrator_DSTATE += arduAttCont_P.RAT_RLL_I * rtb_rollsum *
    arduAttCont_P.Integrator_gainval;

  // Update for DiscreteIntegrator: '<S78>/Filter'
  arduAttCont_DW.Filter_DSTATE += arduAttCont_P.Filter_gainval *
    rtb_FilterCoefficient;

  // Update for DiscreteIntegrator: '<S35>/Integrator' incorporates:
  //   Gain: '<S32>/Integral Gain'

  arduAttCont_DW.Integrator_DSTATE_k += arduAttCont_P.RAT_PIT_I * rtb_pitchsum *
    arduAttCont_P.Integrator_gainval_d;

  // Update for DiscreteIntegrator: '<S30>/Filter'
  arduAttCont_DW.Filter_DSTATE_j += arduAttCont_P.Filter_gainval_c *
    rtb_FilterCoefficient_g;

  // Update for DiscreteIntegrator: '<S131>/Integrator' incorporates:
  //   Gain: '<S128>/Integral Gain'

  arduAttCont_DW.Integrator_DSTATE_a += arduAttCont_P.RAT_YAW_I * rtb_yawsum *
    arduAttCont_P.Integrator_gainval_o;

  // Update for DiscreteIntegrator: '<S126>/Filter'
  arduAttCont_DW.Filter_DSTATE_b += arduAttCont_P.Filter_gainval_n *
    rtb_FilterCoefficient_p;
}

// Model initialize function
void arduAttCont::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S83>/Integrator'
  arduAttCont_DW.Integrator_DSTATE =
    arduAttCont_P.rollratePIDController_Initial_o;

  // InitializeConditions for DiscreteIntegrator: '<S78>/Filter'
  arduAttCont_DW.Filter_DSTATE = arduAttCont_P.rollratePIDController_InitialCo;

  // InitializeConditions for DiscreteIntegrator: '<S35>/Integrator'
  arduAttCont_DW.Integrator_DSTATE_k =
    arduAttCont_P.pitchratePIDController_Initia_d;

  // InitializeConditions for DiscreteIntegrator: '<S30>/Filter'
  arduAttCont_DW.Filter_DSTATE_j = arduAttCont_P.pitchratePIDController_InitialC;

  // InitializeConditions for DiscreteIntegrator: '<S131>/Integrator'
  arduAttCont_DW.Integrator_DSTATE_a =
    arduAttCont_P.yawratePIDController_InitialC_n;

  // InitializeConditions for DiscreteIntegrator: '<S126>/Filter'
  arduAttCont_DW.Filter_DSTATE_b = arduAttCont_P.yawratePIDController_InitialCon;
}

// Model terminate function
void arduAttCont::terminate()
{
  // (no terminate code required)
}

// Constructor
arduAttCont::arduAttCont() :
  arduAttCont_DW(),
  arduAttCont_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
arduAttCont::~arduAttCont() = default;

// Real-Time Model get method
arduAttCont::RT_MODEL_arduAttCont_T * arduAttCont::getRTM()
{
  return (&arduAttCont_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
