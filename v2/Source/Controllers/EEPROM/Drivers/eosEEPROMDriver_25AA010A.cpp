#include "eos.h"
#include "eosTime.h"
#include "Controllers/EEPROM/Drivers/eosEEPROMDriver_25AA010A.h"


static constexpr eos::Time __timeout = eos::Time::fromMiliseconds(100);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    delSPI: El dispositiu SPI per comunicacio.
/// \param    pinCD: El pin CS.
///
eos::EEPROMDriver_25AA010A::EEPROMDriver_25AA010A(
	DevSPI *devSPI,
	Pin *pinCS):

	_devSPI {devSPI},
	_pinCS {pinCS} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'escriptura.
///
void eos::EEPROMDriver_25AA010A::enableWrite() {

	_pinCS->clear();

	uint8_t data = 0b00000110; // WREN
	_devSPI->transmit(&data, sizeof(data), __timeout);

	_pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'escriptura.
///
void eos::EEPROMDriver_25AA010A::disableWrite() {

	_pinCS->clear();

	uint8_t data = 0b00000100; // WRDI
	_devSPI->transmit(&data, sizeof(data), __timeout);

	_pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat de la EEPROM.
/// \return   L'estat.
///
uint8_t eos::EEPROMDriver_25AA010A::readState() {

	_pinCS->clear();

	uint8_t data = 0b00000101; // RDSR
	_devSPI->transmit(&data, sizeof(data), __timeout);
	_devSPI->receive(&data, sizeof(data), __timeout);

	_pinCS->set();

	return data;
}


void eos::EEPROMDriver_25AA010A::read(
	uint32_t addr,
	uint8_t *data,
	uint32_t dataLength) {

	_pinCS->clear();

	uint8_t cmd[2];
	cmd[0] = 0b00000011; // READ
	cmd[1] = (uint8_t)addr;
	_devSPI->transmit(cmd, sizeof(cmd), __timeout);
	_devSPI->receive(data, dataLength, __timeout);

	_pinCS->set();
}


void eos::EEPROMDriver_25AA010A::write(
	uint32_t addr,
	const uint8_t *data,
	uint32_t dataLength) {

	_pinCS->clear();

	uint8_t cmd[2];
	cmd[0] = 0b00000010; // WRITE
	cmd[1] = (uint8_t)addr;
	_devSPI->transmit(cmd, sizeof(cmd), __timeout);
	_devSPI->transmit(data, dataLength, __timeout);

	_pinCS->set();
}
