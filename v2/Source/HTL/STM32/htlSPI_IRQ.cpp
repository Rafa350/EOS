#include "HTL/htl.h"
#include "HTL/STM32/htlSPI.h"
#include "HTL/STM32/htlSPI_IRQ.h"


using namespace htl;


#ifdef HTL_SPI1_EXIST
void SPI_1_InterruptHandler() {

	SPI_1::InterruptHandler();
}
#endif


#ifdef HTL_SPI2_EXIST
void SPI_2_InterruptHandler() {

	SPI_2::InterruptHandler();
}
#endif


#ifdef HTL_SPI3_EXIST
void SPI_3_InterruptHandler() {

	SPI_3::InterruptHandler();
}
#endif


#ifdef HTL_SPI4_EXIST
void SPI_4_InterruptHandler() {

	SPI_4::InterruptHandler();
}
#endif


#ifdef HTL_SPI5_EXIST
void SPI_5_InterruptHandler() {

	SPI_5::InterruptHandler();
}
#endif


#ifdef HTL_SPI6_EXIST
void SPI_6_InterruptHandler() {

	SPI_6::InterruptHandler();
}
#endif

