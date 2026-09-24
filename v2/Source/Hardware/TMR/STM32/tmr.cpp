module;


#include "HTL/htl.h"


export module Eos.Hardware.TMR;


export import Eos.Hardware.TMR.Identifiers;
export import Eos.Hardware.TMR.Classes;
export import Eos.Hardware.TMR.Templates;


export namespace eos::hardware::tmr {

#ifdef HTL_TMR1_EXIST
    using TMRDevice1 = TMRDeviceX<TMRDeviceID::tmr1>;
#endif
#ifdef HTL_TMR2_EXIST
    using TMRDevice2 = TMRDeviceX<TMRDeviceID::tmr2>;
#endif
#ifdef HTL_TMR3_EXIST
    using TMRDevice3 = TMRDeviceX<TMRDeviceID::tmr3>;
#endif
#ifdef HTL_TMR4_EXIST
    using TMRDevice4 = TMRDeviceX<TMRDeviceID::tmr4>;
#endif
#ifdef HTL_TMR5_EXIST
    using TMRDevice5 = TMRDeviceX<TMRDeviceID::tmr5>;
#endif
#ifdef HTL_TMR6_EXIST
    using TMRDevice6 = TMRDeviceX<TMRDeviceID::tmr6>;
#endif
#ifdef HTL_TMR7_EXIST
    using TMRDevice7 = TMRDeviceX<TMRDeviceID::tmr7>;
#endif
#ifdef HTL_TMR8_EXIST
    using TMRDevice8 = TMRDeviceX<TMRDeviceID::tmr8>;
#endif
#ifdef HTL_TMR9_EXIST
    using TMRDevice9 = TMRDeviceX<TMRDeviceID::tmr9>;
#endif
#ifdef HTL_TMR10_EXIST
    using TMRDevice10 = TMRDeviceX<TMRDeviceID::tmr10>;
#endif
#ifdef HTL_TMR11_EXIST
    using TMRDevice11 = TMRDeviceX<TMRDeviceID::tmr11>;
#endif
#ifdef HTL_TMR12_EXIST
    using TMRDevice12 = TMRDeviceX<TMRDeviceID::tmr12>;
#endif
#ifdef HTL_TMR13_EXIST
    using TMRDevice13 = TMRDeviceX<TMRDeviceID::tmr13>;
#endif
#ifdef HTL_TMR14_EXIST
    using TMRDevice14 = TMRDeviceX<TMRDeviceID::tmr14>;
#endif
#ifdef HTL_TMR15_EXIST
    using TMRDevice15 = TMRDeviceX<TMRDeviceID::tmr15>;
#endif
#ifdef HTL_TMR16_EXIST
    using TMRDevice16 = TMRDeviceX<TMRDeviceID::tmr16>;
#endif
#ifdef HTL_TMR17_EXIST
    using TMRDevice17 = TMRDeviceX<TMRDeviceID::tmr17>;
#endif

}
