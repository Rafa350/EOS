#include "eos.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlLTDC_InterruptHandler.h"


using namespace htl;


void LTDC_InterruptHandler() {

	uint32_t pending = LTDC->ISR;

	if (pending != 0) {

		if (pending & LTDC_ISR_LIF)
			LTDC_1::interruptHandler(LTDCEvent::line);

		if (pending & LTDC_ISR_FUIF)
			LTDC_1::interruptHandler(LTDCEvent::fifoError);

		if (pending & LTDC_ISR_TERRIF)
			LTDC_1::interruptHandler(LTDCEvent::transferError);

		if (pending & LTDC_ISR_RRIF)
			LTDC_1::interruptHandler(LTDCEvent::reload);

		LTDC->ICR = pending;
	}
}
