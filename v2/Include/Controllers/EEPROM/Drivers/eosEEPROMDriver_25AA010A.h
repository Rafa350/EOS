#pragma once
#ifndef __eosEEPROMDriver_25AA010A__
#define __eosEEPROMDriver_25AA010A__


#include "eos.h"
#include "Controllers/EEPROM/eosEEPROMDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

	class EEPROMDriver_25AA010A final: public EEPROMDriver {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;

		private:
            DevSPI * const _devSPI;
            Pin * const _pinCS;

		private:
            uint8_t readState();

		public:
            EEPROMDriver_25AA010A(DevSPI *spi, Pin *pinCS);

            void read(uint32_t addr, uint8_t *data, uint32_t dataLength) override;
			void write(uint32_t addr, const uint8_t *data, uint32_t dataLength) override;

			void enableWrite();
            void disableWrite();
	};
}


#endif // __eosEEPROMDriver_25AA010A__
