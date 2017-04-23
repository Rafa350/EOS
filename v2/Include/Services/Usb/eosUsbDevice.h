#ifndef __EOS_USBDEVICE_HPP
#define __EOS_USBDEVICE_HPP


#include "eos.hpp"
#include "Services/eosService.hpp"
#include "System/Collections//eosList.hpp"


namespace eos {
    
    
    class Task;
    class Application;
    class UsbDevice;
    
    class UsbDeviceService: public Service {
        private:
            typedef List<UsbDevice*> UsbDeviceList;
            typedef ListIterator<UsbDevice*> UsbDeviceListIterator;
       
        private:
            UsbDeviceList devices;
            
        public:
            UsbDeviceService(Application *application);
            void add(UsbDevice *device);
            void remove(UsbDevice *device);
            
        private:
            void run(Task *task);
        
    };
    
    class UsbDevice {
        private:
            UsbDeviceService *service;
            
        public:
            UsbDevice(UsbDeviceService *service);
            virtual ~UsbDevice();
            virtual void initialize() = 0;
            virtual void process() = 0;
            
        friend UsbDeviceService;
    };
    
    class UsbDeviceCDC: public UsbDevice {
        public:
            UsbDeviceCDC(UsbDeviceService *service);
            void initialize();
            void process();
    };
        
}


#endif
