module;


#include "HTL/htl.h"


export module htl.interrupts.stm32f0;


export namespace htl::interrupts {

	enum class VectorID {
#ifdef HTL_UART1_EXIST
		usart1 = USART1_IRQn,
#endif
#ifdef HTL_UART1_EXIST
		usart2 = USART2_IRQn,
#endif

		spi1 = SPI1_IRQn,
		spi2 = SPI2_IRQn,

		tmr3 = TIM3_IRQn,
		tmr6 = TIM6_IRQn,
		tmr14 = TIM14_IRQn,
		tmr15 = TIM15_IRQn,
		tmr16 = TIM16_IRQn,
		tmr17 = TIM17_IRQn
	};

}
