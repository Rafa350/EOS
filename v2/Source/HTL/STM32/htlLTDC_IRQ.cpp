#include "HTL/htl.h"
#include "HTL/STM32/htlLTDC.h"
#include "HTL/STM32/htlLTDC_IRQ.h"


using namespace htl::ltdc;


void LTDCDevice_InterruptHandler() {

	LTDCDevice::interruptHandler();
}
