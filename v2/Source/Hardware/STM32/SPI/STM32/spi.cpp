module;


#include "HTL/htl.h"


export module Eos.Hardware.SPI;


export import Eos.Hardware.SPI.Identifiers;
export import Eos.Hardware.SPI.Classes;
export import Eos.Hardware.SPI.Templates;
export import Eos.Hardware.SPI.__DEVICE_TRAITS;


export namespace eos::hardware::spi {

#ifdef HTL_SPI1_EXIST
	using SPIDevice1 = SPIDeviceX<SPIDeviceID::spi1>;
#endif
#ifdef HTL_SPI2_EXIST
	using SPIDevice2 = SPIDeviceX<SPIDeviceID::spi2>;
#endif
#ifdef HTL_SPI3_EXIST
	using SPIDevice3 = SPIDeviceX<SPIDeviceID::spi3>;
#endif
#ifdef HTL_SPI4_EXIST
	using SPIDevice4 = SPIDeviceX<SPIDeviceID::spi4>;
#endif
#ifdef HTL_SPI5_EXIST
	using SPIDevice5 = SPIDeviceX<SPIDeviceID::spi5>;
#endif
#ifdef HTL_SPI6_EXIST
	using SPIDevice6 = SPIDeviceX<SPIDeviceID::spi6>;
#endif

}
