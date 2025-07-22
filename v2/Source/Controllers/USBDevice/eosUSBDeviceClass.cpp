#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"


using namespace eos;


uint8_t USBDeviceClass::_ifaceCount = 0;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUSBD: El dispositiu USB
/// \param    iface: El numero del primer interface que gestiona
///
USBDeviceClass::USBDeviceClass(
	USBDeviceDriver *drvUSBD,
	uint8_t iface) :

	_state {State::reset},
	_drvUSBD {drvUSBD},
	_iface {iface} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \return   El resultat de l'operacio.
///
Result USBDeviceClass::initialize() {

	if (_state != State::reset)
		return Results::errorState;

	if (initializeImpl() != Results::success)
		return Results::error;

	_state = State::ready;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Reserva un nombre de interfaces
/// \param    ifaceQty: La quantitat a reservar.
/// \return   El primer iface disponible.
///
uint8_t USBDeviceClass::reserveIface(
	unsigned ifaceQty) {

	uint8_t iface = _ifaceCount;
	_ifaceCount += ifaceQty;
	return iface;
}
