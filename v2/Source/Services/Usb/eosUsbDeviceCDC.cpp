#include "Services/Usb/eosUsbClient.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param service: El servei al que pertany.
///
UsbDeviceCDC::UsbDeviceCDC(UsbClientServiceHandle* service):
    UsbDevice(service) {
    
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void UsbDeviceCDC::initialize() {
}


/// ---------------------------------------------------------------------
/// \brief Procesament de les tasques de control.
///
void UsbDeviceCDC::process() {
    
}
