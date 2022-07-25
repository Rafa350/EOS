#include "eos.h"
#include "htl/STM32/htlEXTI.h"




void htl::EXTI_init(
	EXTILine line,
	EXTIPort port,
	EXTIMode mode,
	EXTITrigger trigger) {

	// Configura el port a explorar
	//
	uint32_t temp = SYSCFG->EXTICR[uint32_t(line) >> 2];
	temp &= ~(0xF << (4 * (uint32_t(line) & 0x03)));
	temp |= (uint32_t(port) & 0xF) << (4 * (uint32_t(line) & 0x03));
	SYSCFG->EXTICR[uint32_t(line) >> 2] = temp;

	// Configura el registre IMR (Interrupt Mask Register);
	//
    if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
    	EXTI->IMR |= 1 << uint32_t(line);
    else
    	EXTI->IMR &= ~(1 << uint32_t(line));

	// Configura el registre EMR (Event Mask Register);
	//
    if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
    	EXTI->EMR |= 1 << uint32_t(line);
    else
    	EXTI->EMR &= ~(1 << uint32_t(line));

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
		EXTI->RTSR |= 1 << uint32_t(line);
	else
		EXTI->RTSR &= ~(1 << uint32_t(line));

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
		EXTI->FTSR |= 1 << uint32_t(line);
	else
		EXTI->FTSR &= ~(1 << uint32_t(line));
}
