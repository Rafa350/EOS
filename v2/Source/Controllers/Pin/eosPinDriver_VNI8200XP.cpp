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
	_hSPI {nullptr},
	_hPinSS {nullptr},
	_hPinOUTEN {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    hSPI: Handler del dispositiu SPI
/// \param    hPinSS: Handler del pin de seleccio.
/// \param    hPinOUTEN: Handler del pin de seleccio de les sortides.
///
VNI8200XP_Device::Result VNI8200XP_SerialDevice::initialize(
	htl::spi::SPIDeviceHandler hSPI,
	htl::gpio::PinHandler hPinSS,
	htl::gpio::PinHandler hPinOUTEN) {

	eosAssert(_state == State::reset);

	if (_state == State::reset) {

		_hSPI = hSPI;
		_hPinSS = hPinSS;
		_hPinOUTEN = hPinOUTEN;

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
		if (_hPinOUTEN != nullptr)
			_hPinOUTEN->set();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les sortides.
///
void VNI8200XP_SerialDevice::disable() const {

	eosAssert(_state == State::ready);

	if (_state == State::ready) {
		if (_hPinOUTEN != nullptr)
			_hPinOUTEN->clear();
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

			_hPinSS->clear();
			_hSPI->transmit(txData, rxData, sizeof(txData));
			_hPinSS->set();

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
	VNI8200XP_DeviceHandler hDevice,
	uint8_t pinNumber):

	_hDevice {hDevice},
	_pinMask {uint8_t(1 << pinNumber)} {

	eosAssert(hDevice != nullptr);
	eosAssert(pinNumber < 8);
}


void PinDriver_VNI8200XP::set() {

	_hDevice->set(_pinMask);
}


void PinDriver_VNI8200XP::clear() {

	_hDevice->clear(_pinMask);
}


void PinDriver_VNI8200XP::toggle() {

	_hDevice->toggle(_pinMask);
}


void PinDriver_VNI8200XP::write(
	bool pinState) {

	_hDevice->write(_pinMask, pinState);
}


bool PinDriver_VNI8200XP::read() {

	return (_hDevice->read() & _pinMask) != 0;
}

