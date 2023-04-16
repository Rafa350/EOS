#include "HTL/htl.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlLTDC_IRQ.h"


using namespace htl::ltdc;


void LTDC_InterruptHandler() {

	LTDCDevice::getHandler()->interruptService();
}


void LTDC_ER_InterruptHandler() {

	LTDCDevice::getHandler()->interruptERService();
}
