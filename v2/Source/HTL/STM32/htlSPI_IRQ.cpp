#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"
#include "HTL/STM32/htlSPI_IRQ.h"


using namespace htl::spi;


#ifdef HTL_SPI1_EXIST
void SPI_1_InterruptHandler() {

	SPIDevice1::getHandler()->interruptService();
}
#endif


#ifdef HTL_SPI2_EXIST
void SPI_2_InterruptHandler() {

	SPIDevice2::getHandler()->interruptService();
}
#endif


#ifdef HTL_SPI3_EXIST
void SPI_3_InterruptHandler() {

	SPIDevice3::getHandler()->interruptService();
}
#endif


#ifdef HTL_SPI4_EXIST
void SPI_4_InterruptHandler() {

	SPIDevice4::getHandler()->interruptService();
}
#endif


#ifdef HTL_SPI5_EXIST
void SPI_5_InterruptHandler() {

	SPIDevice5::getHandler()->interruptService();
}
#endif


#ifdef HTL_SPI6_EXIST
void SPI_6_InterruptHandler() {

	SPIDevice6::getHandler()->interruptService();
}
#endif

