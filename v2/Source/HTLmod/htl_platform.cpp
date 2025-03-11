module;


#include "HTL/htl.h"


export module htl.platform;

if (defined(EOS_PLATFORM_STM32)
export include htl.platform.stm32g0;
#endif	
