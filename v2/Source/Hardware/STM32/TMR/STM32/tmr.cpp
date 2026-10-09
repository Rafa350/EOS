module;


#include "hardware.h"


export module Eos.Hardware.TMR;


export import Eos.Hardware.TMR.Identifiers;
export import Eos.Hardware.TMR.Classes;
export import Eos.Hardware.TMR.Templates;


export namespace eos::hardware::tmr {

#ifdef TIM1_BASE
    using TMRDevice1 = TMRDeviceX<TMRDeviceID::tmr1>;
#endif
#ifdef TIM2_BASE
    using TMRDevice2 = TMRDeviceX<TMRDeviceID::tmr2>;
#endif
#ifdef TIM3_BASE
    using TMRDevice3 = TMRDeviceX<TMRDeviceID::tmr3>;
#endif
#ifdef TIM4_BASE
    using TMRDevice4 = TMRDeviceX<TMRDeviceID::tmr4>;
#endif
#ifdef TIM5_BASE
    using TMRDevice5 = TMRDeviceX<TMRDeviceID::tmr5>;
#endif
#ifdef TIM6_BASE
    using TMRDevice6 = TMRDeviceX<TMRDeviceID::tmr6>;
#endif
#ifdef TIM7_BASE
    using TMRDevice7 = TMRDeviceX<TMRDeviceID::tmr7>;
#endif
#ifdef TIM8_BASE
    using TMRDevice8 = TMRDeviceX<TMRDeviceID::tmr8>;
#endif
#ifdef TIM9_BASE
    using TMRDevice9 = TMRDeviceX<TMRDeviceID::tmr9>;
#endif
#ifdef TIM10_BASE
    using TMRDevice10 = TMRDeviceX<TMRDeviceID::tmr10>;
#endif
#ifdef TIM11_BASE
    using TMRDevice11 = TMRDeviceX<TMRDeviceID::tmr11>;
#endif
#ifdef TIM12_BASE
    using TMRDevice12 = TMRDeviceX<TMRDeviceID::tmr12>;
#endif
#ifdef TIM13_BASE
    using TMRDevice13 = TMRDeviceX<TMRDeviceID::tmr13>;
#endif
#ifdef TIM14_BASE
    using TMRDevice14 = TMRDeviceX<TMRDeviceID::tmr14>;
#endif
#ifdef TIM15_BASE
    using TMRDevice15 = TMRDeviceX<TMRDeviceID::tmr15>;
#endif
#ifdef TIM16_BASE
    using TMRDevice16 = TMRDeviceX<TMRDeviceID::tmr16>;
#endif
#ifdef TIM17_BASE
    using TMRDevice17 = TMRDeviceX<TMRDeviceID::tmr17>;
#endif

}
