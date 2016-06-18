#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/Usb/eosUsbDevice.hpp"
#include "HAL/halUSBDevice.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Contructor
///
UsbDeviceService::UsbDeviceService():
    task(taskStackSize, taskPriority, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
///
void UsbDeviceService::run() {
    
    UsbDeviceListIterator iterator(devices);

    halUSBDeviceSetup();

    for (iterator.first(); iterator.hasNext(); iterator.next())
        iterator.current()->initialize();
    
    while (true) {
        halUSBDeviceTask();
        
        for (iterator.first(); iterator.hasNext(); iterator.next())
            iterator.current()->process();
    }
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un dispositiu al servei.
/// \param device: El dispositiu a afeigir
///
void UsbDeviceService::add(
    UsbDeviceHandle device) {

    devices.add(device);
    device->service = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un dispositiu del servei.
/// \param device: El dispositiu a eliminar,
///
void UsbDeviceService::remove(
    UsbDeviceHandle device) {

    device->service = nullptr;
    devices.remove(devices.indexOf(device));
    
}


/// ----------------------------------------------------------------------
/// \brief Contructor
/// \param service: El servei al que pertany.
///
UsbDevice::UsbDevice(
    UsbDeviceServiceHandle _service):
    service(nullptr) {
    
    if (_service != nullptr)
        _service->add(this);    
}


/// ----------------------------------------------------------------------
/// \brief Desctuctor
///
UsbDevice::~UsbDevice() {
    
    if (service != nullptr)
        service->remove(this);
}