module;


#include "HTL/htl.h"


export module htl.clocks;

#if defined(EOS_PLATFORM_STM32G0)
export import htl.clocks.stm32g0;
#elif defined(EOS_PLATFORM_STM32F0)
export import htl.clocks.stm32f0;
#elif defined(EOS_PLATFORM_STM32F4)
export import htl.clocks.stm32f4;
#elif defined(EOS_PLATFORM_STM32F7)
export import htl.clocks.stm32f7;
#else
	#error "Unsuported platform."
#endif

