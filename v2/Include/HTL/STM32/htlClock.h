#pragma once
#ifndef __STM32_htlClock__
#define __STM32_htlClock__


#include "htl.h"


#if defined(EOS_PLATFORM_STM32F0)
    #include "htl/STM32/F0/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F1)
    #include "htl/STM32/F1/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlClock.h"
#elif defined(EOS_PLATFORM_STM32G0)
    #include "htl/STM32/G0/htlClock.h"
#else
    #error Plataforma no soportada
#endif



#endif // __STM32_htlClock__
