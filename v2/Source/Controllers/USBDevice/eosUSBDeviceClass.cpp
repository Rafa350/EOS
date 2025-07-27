#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"


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
/// \brief    Procesa una solicitut dirigides al interficie
/// \param    request: La solicitut.
/// \return   True si tot es correcte.
///
bool USBDeviceClass::processInterfaceRequest(
	USBD_SetupReqTypedef *request) {

	ctlError();
	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Reserva un nombre determinat d'interficies
/// \param    ifaceQty: La quantitat a reservar.
/// \return   El primer iface disponible.
///
uint8_t USBDeviceClass::reserveIface(
	uint8_t ifaceQty) {

	auto iface = _ifaceCount;
	_ifaceCount += ifaceQty;

	return iface;
}


/// ----------------------------------------------------------------------
/// \brief    Respon com a error a una solicitut.
///
void USBDeviceClass::ctlError() {

	auto pdev = _drvUSBD->getHandle();
	USBD_LL_StallEP(pdev, 0x80);
	USBD_LL_StallEP(pdev, 0x00);
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut amb l'estat.
///
void USBDeviceClass::ctlSendStatus() {

	USBD_CtlSendStatus(_drvUSBD->getHandle());
}


/// ----------------------------------------------------------------------
/// \brief    Respon a una solicitut amb dades.
/// \param    data: Les dades.
/// \param    length: La longitut de les dades en bytes.
///
void USBDeviceClass::ctlSendData(
	uint8_t *data,
	unsigned length) {

	USBD_CtlSendData(_drvUSBD->getHandle(), data, length);
}

