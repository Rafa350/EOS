#include "HTL/htl.h"
#include "HTL/STM32/htlDMA2D.h"
#include "HTL/STM32/htlDMA2D_IRQ.h"


using namespace htl;


void DMA2D_InterruptHandler() {

	uint32_t isr = DMA2D->ISR;

	if (isr != 0) {

		if (isr & DMA2D_ISR_CEIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::configurationError);

		if (isr & DMA2D_ISR_CTCIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::transferComplete);

		if (isr & DMA2D_ISR_CAEIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::clutAccessError);

		if (isr & DMA2D_ISR_TWIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::transferWatermark);

		if (isr & DMA2D_ISR_TCIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::transferComplete);

		if (isr & DMA2D_ISR_TEIF)
			DMA2D_1::InterruptHandler(DMA2DEvent::transferError);

		DMA2D->IFCR = isr;
	}
}
