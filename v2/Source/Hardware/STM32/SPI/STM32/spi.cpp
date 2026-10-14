module;


#include "hardware.h"


export module Eos.Hardware.SPI;


export import Eos.Hardware.SPI.PlatformTraits;
export import Eos.Hardware.SPI.Classes;
export import Eos.Hardware.SPI.Templates;
export import Eos.Hardware.SPI.Types;
export import Eos.Hardware.SPI.DeviceTraits;

import Eos.Hardware.SPI.PlatformTraits;


export namespace eos::hardware::spi {

#ifdef SPI1_BASE
	using SPIDevice1 = SPIDeviceX<SPIDeviceID::spi1>;
#endif
#ifdef SPI2_BASE
	using SPIDevice2 = SPIDeviceX<SPIDeviceID::spi2>;
#endif
#ifdef SPI3_BASE
	using SPIDevice3 = SPIDeviceX<SPIDeviceID::spi3>;
#endif
#ifdef SPI4_BASE
	using SPIDevice4 = SPIDeviceX<SPIDeviceID::spi4>;
#endif
#ifdef SPI5_BASE
	using SPIDevice5 = SPIDeviceX<SPIDeviceID::spi5>;
#endif
#ifdef SPI6_BASE
	using SPIDevice6 = SPIDeviceX<SPIDeviceID::spi6>;
#endif

}
