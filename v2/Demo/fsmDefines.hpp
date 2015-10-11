#ifndef __FSM_DEFINES_HPP
#define __FSM_DEFINES_HPP


#define EV_T1                          10
#define EV_T2                          11
#define EV_T3                          12
#define EV_ST                          13
#define EV_PT                          14
#define EV_LR                          16

#define TIM_T1                         10
#define TIM_T2                         11
#define TIM_T3                         12

#define OUT_PU                         10
#define OUT_PD                         11
#define OUT_ER                         12
#define OUT_AJ                         12
#define OUT_AA                         13
#define OUT_PL                         14
#define OUT_VC                         15

#define INP_PT                         19
#define INP_ST                         20
#define INP_LR                         12

#define VAR_ArmUpPreDelay              30
#define VAR_ArmUpPostDelay             31
#define VAR_ArmUpTimeout               32

#define VAR_ArmDownPreDelay            33
#define VAR_ArmDownPostDelay           34

#define VAR_PrintLabelPreDelay         30
#define VAR_PrintLabelPostDelay        31
#define VAR_PrintLabelTimeout          32

#define VAR_AirAssistDelay             34
#define VAR_VacuumDelay                33


#define PistonTopCondition             ctl->inpGet(INP_PT)
#define PrintVacuumModeOnCondition     true

#define ArmUpPreDelay                  ctl->varGet(VAR_ArmUpPreDelay)
#define ArmUpPostDelay                 ctl->varGet(VAR_ArmUpPostDelay)
#define ArmUpTimeout                   ctl->varGet(VAR_ArmUpTimeout)

#define ArmDownPreDelay                ctl->varGet(VAR_ArmDownPreDelay)
#define ArmDownPostDelay               ctl->varGet(VAR_ArmDownPostDelay)

#define PrintLabelPreDelay             ctl->varGet(VAR_PrintLabelPreDelay)
#define PrintLabelPostDelay            ctl->varGet(VAR_PrintLabelPostDelay)
#define PrintLabelTimeout              ctl->varGet(VAR_PrintLabelTimeout)

#define AirAssistDelay                 ctl->varGet(VAR_AirAssistDelay)
#define VacuumDelay                    ctl->varGet(VAR_VacuumDelay)

#endif
