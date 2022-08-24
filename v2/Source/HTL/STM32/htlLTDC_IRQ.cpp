#include "HTL/htl.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlLTDC_IRQ.h"


using namespace htl;


void LTDC_InterruptHandler() {

	uint32_t isr = LTDC->ISR;

	if (isr != 0) {

		if (isr & LTDC_ISR_LIF)
			LTDC_1::interruptHandler(LTDCEvent::line);

		if (isr & LTDC_ISR_RRIF)
			LTDC_1::interruptHandler(LTDCEvent::reload);

		LTDC->ICR = isr;
	}
}


void LTDC_ER_InterruptHandler() {

	uint32_t isr = LTDC->ISR;

	if (isr != 0) {

		if (isr & LTDC_ISR_FUIF)
			LTDC_1::interruptHandler(LTDCEvent::fifoError);

		if (isr & LTDC_ISR_TERRIF)
			LTDC_1::interruptHandler(LTDCEvent::transferError);

		LTDC->ICR = isr;
	}
}
