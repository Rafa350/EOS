#include "eos.h"
#include "Controllers/Pin/eosPinDriver_VNI8200XP.h"


using namespace eos;
using namespace htl;


static uint8_t calcParity(uint8_t data);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    hSPI: Handler del dispositiu SPI de comunicacions.
/// \param    hSS: Handler del pin SS
/// \param    hOUTEN: Handler del pin OUTEN
///
VNI8200XP_SerialDevice::VNI8200XP_SerialDevice(
	spi::SPIDeviceHandler hSPI,
	gpio::PinHandler hPinSS,
	gpio::PinHandler hPinOUTEN) :

    _newState {0},
    _oldState {0},
	_hSPI {hSPI},
	_hPinSS {hPinSS},
	_hPinOUTEN {hPinOUTEN} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void VNI8200XP_SerialDevice::initialize() {

}


void VNI8200XP_SerialDevice::enable() const {

	_hPinOUTEN->set();
}


void VNI8200XP_SerialDevice::disable() const {

	_hPinOUTEN->clear();
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza les sortides en funcio del estat intern.
///
void VNI8200XP_SerialDevice::update() {
    
    if (_newState != _oldState) {
    
    	uint8_t txData[2], rxData[2];

    	txData[0] = _newState;
    	txData[1] = calcParity(_newState);

    	_hPinSS->clear();
    	_hSPI->transmit(txData, rxData, sizeof(txData));
    	_hPinSS->set();
        
        _oldState = _newState;
    }
}


void VNI8200XP_SerialDevice::set(
	uint8_t pinMask) {

	_newState |= pinMask;
}


void VNI8200XP_SerialDevice::clear(
	uint8_t pinMask) {

	_newState &= ~pinMask;
}


void VNI8200XP_SerialDevice::toggle(
	uint8_t pinMask) {

	_newState ^= pinMask;
}


void VNI8200XP_SerialDevice::write(
	uint8_t pinMask,
	bool pinState) {

	if (pinState)
		_newState |= pinMask;
	else
		_newState &= ~pinMask;

}


uint8_t VNI8200XP_SerialDevice::read() const {

	return _newState;
}


bool VNI8200XP_SerialDevice::isOK() const {

	return true;
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

