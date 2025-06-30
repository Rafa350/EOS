#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    devUSBD: El dispositiu USB
///
USBDeviceClass::USBDeviceClass(
	USBDeviceDriver *drvUSBD) :

	_drvUSBD {drvUSBD} {
}
