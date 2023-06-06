#include "HTL/htl.h"
#include "HTL/STM32/htlDMA2D.h"
#include "HTL/STM32/htlDMA2D_IRQ.h"


using namespace htl::dma2d;


void DMA2DDevice_InterruptHandler() {

    DMA2DDevice::interruptHandler();
}
