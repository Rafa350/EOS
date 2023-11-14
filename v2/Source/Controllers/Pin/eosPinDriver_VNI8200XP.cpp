#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Pin/eosPinDriver_VNI8200XP.h"
#include "System/Core/eosTask.h"


using namespace eos;
using namespace htl;


static uint8_t calcParity(uint8_t data);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hSPI: Handler del dispositiu SPI de comunicacions.
/// \param    hSS: Handler del pin SS
/// \param    hOUTEN: Handler del pin OUTEN
///
VNI8200XP_SerialDevice::VNI8200XP_SerialDevice() :

	_state {State::reset},
    _curPinState {0},
    _oldPinState {0},
	_spi {nullptr},
	_pinSS {nullptr},
	_pinOUTEN {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    spi: El dispositiu SPI
/// \param    pinSS: El pin de seleccio.
/// \param    pinOUTEN: El pin de seleccio de les sortides.
///
VNI8200XP_Device::Result VNI8200XP_SerialDevice::initialize(
	htl::spi::SPIDevice *spi,
	htl::gpio::Pin *pinSS,
	htl::gpio::Pin *pinOUTEN) {

	eosAssert(_state == State::reset);

	if (_state == State::reset) {

		_spi = spi;
		_pinSS = pinSS;
		_pinOUTEN = pinOUTEN;

		_state = State::ready;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les sortides.
///
void VNI8200XP_SerialDevice::enable() const {

	eosAssert(_state == State::ready);

	if (_state == State::ready) {
		if (_pinOUTEN != nullptr)
			_pinOUTEN->set();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les sortides.
///
void VNI8200XP_SerialDevice::disable() const {

	eosAssert(_state == State::ready);

	if (_state == State::ready) {
		if (_pinOUTEN != nullptr)
			_pinOUTEN->clear();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza les sortides en funcio del estat intern.
///
void VNI8200XP_SerialDevice::update() {

	eosAssert(_state == State::ready);
    
	if (_state == State::ready) {

		_state = State::updating;

		if (_curPinState != _oldPinState) {

			uint8_t txData[2], rxData[2];

			txData[0] = _curPinState;
			txData[1] = calcParity(_curPinState);

			_pinSS->clear();
			_spi->transmit(txData, rxData, sizeof(txData));
			_pinSS->set();

			_oldPinState = _curPinState;
		}

		_state = State::ready;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Activa els pins especificats.
/// \param    pinMask: Mascara dels pins a activar.
///
void VNI8200XP_SerialDevice::set(
	uint8_t pinMask) {

	_curPinState |= pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva els pins especificats.
/// \param    pinMask: Mascara dels pins a desactivar.
///
void VNI8200XP_SerialDevice::clear(
	uint8_t pinMask) {

	_curPinState &= ~pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix els pins especificats.
/// \param    pinMask: Mascara dels pins a invertir.
///
void VNI8200XP_SerialDevice::toggle(
	uint8_t pinMask) {

	_curPinState ^= pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu els pins.
/// \param    pinMask: Mascara dels pins a escriure.
/// \param    pinState: El estat a escriure.
///
void VNI8200XP_SerialDevice::write(
	uint8_t pinMask,
	bool pinState) {

	if (pinState)
		_curPinState |= pinMask;
	else
		_curPinState &= ~pinMask;

}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat dels pins.
/// \return   El estat.
///
uint8_t VNI8200XP_SerialDevice::read() const {

	return _curPinState;
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la paritat de les dades.
/// \param    data: Les dades sobre les que es calcula la paritat.
/// \return   La paritat calculada.
///
static uint8_t calcParity(
	uint8_t data) {

	uint8_t p0, p1, p2, np0;

	p0 = data ^ (data >> 1);
	p0 = p0 ^ (p0 >> 2);
	p0 = p0 ^ (p0 >> 4);
	p0 = p0 & 0x01;

	p1 = data ^ (data >> 2);
	p1 = p1 ^ (p1 >> 4);

	p2 = p1 & 0x01;

	p1 = p1 & 0x02;
	p1 = p1 >> 1;

	np0 = (~p0) & 0x01;

	return (p2 << 3) | (p1 << 2) | (p0 << 1) | np0;
}


PinDriver_VNI8200XP::PinDriver_VNI8200XP(
	VNI8200XP_Device *dev,
	uint8_t pinNumber):

	_dev {dev},
	_pinMask {uint8_t(1 << pinNumber)} {

	eosAssert(hDevice != nullptr);
	eosAssert(pinNumber < 8);
}


void PinDriver_VNI8200XP::set() {

	_dev->set(_pinMask);
}


void PinDriver_VNI8200XP::clear() {

	_dev->clear(_pinMask);
}


void PinDriver_VNI8200XP::toggle() {

	_dev->toggle(_pinMask);
}


void PinDriver_VNI8200XP::write(
	bool pinState) {

	_dev->write(_pinMask, pinState);
}


bool PinDriver_VNI8200XP::read() {

	return (_dev->read() & _pinMask) != 0;
}

