#pragma once

#include "AC_CustomControl_Backend.h"
#include <AC_Simulink/arduAttCont.h>

#ifndef CUSTOMCONTROL_UMIC_ENABLED
    #define CUSTOMCONTROL_UMIC_ENABLED AP_CUSTOMCONTROL_ENABLED
#endif

#if CUSTOMCONTROL_UMIC_ENABLED

class AC_CustomControl_UMIC : public AC_CustomControl_Backend {
public:
    AC_CustomControl_UMIC(AC_CustomControl& frontend, AP_AHRS_View*& ahrs, AC_AttitudeControl_Multi*& att_control, AP_MotorsMulticopter*& motors, float dt);


    Vector3f update(void) override;
    void reset(void) override;

    arduAttCont simulink_controller;
    
    // user settable parameters
    static const struct AP_Param::GroupInfo var_info[];

protected:
    // declare parameters here
    AP_Float param0;
};

#endif
