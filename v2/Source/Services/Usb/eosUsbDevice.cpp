#include "eos.h"
#include "System/Core/eosTask.h"
#include "Services/Usb/eosUsbDevice.h"
#include "HAL/halUSBDevice.h"


using namespace eos;


static const char *serviceName = "UsbDeviceService";
static const unsigned taskStackSize = 512;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Contructor
///
UsbDeviceService::UsbDeviceService(
    Application *application):
    Service(application, serviceName, taskStackSize, taskPriority) {
}



/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void UsbDeviceService::onSetup() {
    
    USBDeviceInitializeInfo info;
    
    info.id = HAL_USB_PORT_0;
    halUSBDeviceInitialize(&info);

    UsbDeviceListIterator iterator(devices);
    for (iterator.first(); iterator.hasNext(); iterator.next())
        iterator.current()->initialize();
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void UsbDeviceService::onLoop() {
       
    halUSBDeviceTask();
    
    UsbDeviceListIterator iterator(devices);
    for (iterator.first(); iterator.hasNext(); iterator.next())
        iterator.current()->process();
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un dispositiu al servei.
/// \param device: El dispositiu a afeigir
///
void UsbDeviceService::add(
    UsbDevice *device) {

    devices.add(device);
    device->service = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un dispositiu del servei.
/// \param device: El dispositiu a eliminar,
///
void UsbDeviceService::remove(
    UsbDevice *device) {

    device->service = nullptr;
    devices.remove(devices.indexOf(device));    
}


/// ----------------------------------------------------------------------
/// \brief Contructor
/// \param service: El servei al que pertany.
///
UsbDevice::UsbDevice(
    UsbDeviceService *service):
    service(nullptr) {
    
    if (service != nullptr)
        service->add(this);    
}


/// ----------------------------------------------------------------------
/// \brief Desctuctor
///
UsbDevice::~UsbDevice() {
    
    if (service != nullptr)
        service->remove(this);
}
