module;

#include "eos.h"
#include "HTL/htlGPIO.h"


export module Eos.Controllers.EEPROM_25AA010A;


export import Eos.Controllers.EEPROM;


import Eos.Types;
import Eos.Hardware.SPI;
import Eos.System.Core.Ticks;


export namespace eos {

	class EEPROMDriver_25AA010A final: public EEPROMDriver {
		public:
			using PinDevice = htl::gpio::PinDevice;
			using SPIDevice = eos::hardware::spi::SPIDevice;

		private:
            SPIDevice * const _devSPI;
            PinDevice * const _pinCS;

		private:
            UInt8 readState();

		public:
            EEPROMDriver_25AA010A(SPIDevice *spi, PinDevice *pinCS);

            void read(UInt32 addr, UInt8 *data, UInt32 dataLength) override;
			void write(UInt32 addr, const UInt8 *data, UInt32 dataLength) override;

			void enableWrite();
            void disableWrite();
	};
}



using namespace eos;

constexpr Ticks __timeout = Ticks::fromMiliseconds(100);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    delSPI: El dispositiu SPI per comunicacio.
/// \param    pinCD: El pin CS.
///
EEPROMDriver_25AA010A::EEPROMDriver_25AA010A(
	SPIDevice *devSPI,
	PinDevice *pinCS):

	_devSPI {devSPI},
	_pinCS {pinCS} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'escriptura.
///
void EEPROMDriver_25AA010A::enableWrite() {

	_pinCS->clear();

	uint8_t data = 0b00000110; // WREN
	_devSPI->transmit(&data, sizeof(data), __timeout);

	_pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'escriptura.
///
void EEPROMDriver_25AA010A::disableWrite() {

	_pinCS->clear();

	uint8_t data = 0b00000100; // WRDI
	_devSPI->transmit(&data, sizeof(data), __timeout);

	_pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat de la EEPROM.
/// \return   L'estat.
///
UInt8 EEPROMDriver_25AA010A::readState() {

	_pinCS->clear();

	UInt8 data = 0b00000101; // RDSR
	_devSPI->transmit(&data, sizeof(data), __timeout);
	_devSPI->receive(&data, sizeof(data), __timeout);

	_pinCS->set();

	return data;
}


void EEPROMDriver_25AA010A::read(
	UInt32 addr,
	UInt8 *data,
	UInt32 dataLength) {

	_pinCS->clear();

	UInt8 cmd[2];
	cmd[0] = 0b00000011; // READ
	cmd[1] = (uint8_t)addr;
	_devSPI->transmit(cmd, sizeof(cmd), __timeout);
	_devSPI->receive(data, dataLength, __timeout);

	_pinCS->set();
}


void EEPROMDriver_25AA010A::write(
	UInt32 addr,
	const UInt8 *data,
	UInt32 dataLength) {

	_pinCS->clear();

	UInt8 cmd[2];
	cmd[0] = 0b00000010; // WRITE
	cmd[1] = (uint8_t)addr;
	_devSPI->transmit(cmd, sizeof(cmd), __timeout);
	_devSPI->transmit(data, dataLength, __timeout);

	_pinCS->set();
}
