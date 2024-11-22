#pragma once
#ifndef __STM32_htlINT__
#define __STM32_htlINT__


// HAL includes
//
#include "HTL/STM32/htl.h"


#if defined(EOS_PLATFORM_STM32F4)
	#include "F4/htlINT_Vectors.h"
#elif defined(EOS_PLATFORM_STM32F7)
	#include "F7/htlINT_Vectors.h"
#elif defined(EOS_PLATFORM_STM32G031)
	#include "G0/G031/htlINT_Vectors.h"
#elif defined(EOS_PLATFORM_STM32G051)
	#include "G0/G051/htlINT_Vectors.h"
#elif defined(EOS_PLATFORM_STM32G071)
	#include "G0/G071/htlINT_Vectors.h"
#elif defined(EOS_PLATFORM_STM32G0B1)
	#include "G0/G0B1/htlINT_Vectors.h"
#endif


namespace htl {
	namespace irq {

		enum class Priority {
			_0,
			_1,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,
			_9,
			_10,
			_11,
			_12,
			_13,
			_14,
			_15
		};

		enum class SubPriority {
			_0,
			_1,
			_2,
			_3,
		};

		void setInterruptVectorPriority(VectorID vector, Priority priority,
		        SubPriority subPriority = SubPriority::_0);

		inline void enableInterruptVector(
			VectorID vector) {

			NVIC_EnableIRQ(static_cast<IRQn_Type>(vector));
		}

		inline void disableInterruptVector(
			VectorID vector) {

			NVIC_DisableIRQ(static_cast<IRQn_Type>(vector));
		}

        inline bool getInterruptState() {
            return __get_PRIMASK() == 0;
        }

        inline void enableInterrupts() {
            __enable_irq();
        }

        inline void disableInterrupts() {
            __disable_irq();
        }

        inline void restoreInterrupts(bool state) {
            if (state)
                __enable_irq();
        }
	}
}


#endif // __STM32_htlINT__
