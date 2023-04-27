#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"
#include "HTL/STM32/htlSPI_IRQ.h"


using namespace htl::spi;


#ifdef HTL_SPI1_EXIST
void SPIDevice1_InterruptHandler() {

	SPIDevice1::interruptHandler();
}
#endif


#ifdef HTL_SPI2_EXIST
void SPIDevice2_InterruptHandler() {

	SPIDevice2::interruptHandler();
}
#endif


#ifdef HTL_SPI3_EXIST
void SPIDevice3_InterruptHandler() {

	SPIDevice3::interruptHandler();
}
#endif


#ifdef HTL_SPI4_EXIST
void SPIDevice4_InterruptHandler() {

	SPIDevice4::interruptHandler();
}
#endif


#ifdef HTL_SPI5_EXIST
void SPIDevice5_InterruptHandler() {

	SPIDevice5::interruptHandler();
}
#endif


#ifdef HTL_SPI6_EXIST
void SPIDevice6_InterruptHandler() {

	SPIDevice6::interruptHandler();
}
#endif

