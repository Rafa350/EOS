#ifndef __EOS_SERVICES_USBDEVICE_HPP
#define __EOS_SERVICES_USBDEVICE_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections//eosList.hpp"


namespace eos {
    
    class UsbDevice;
    typedef UsbDevice *UsbDeviceHandle;
    
    class UsbDeviceService;
    typedef UsbDeviceService *UsbDeviceServiceHandle;
    
    class UsbDeviceService: private IRunable {
        private:
            typedef List<UsbDeviceHandle> UsbDeviceList;
            typedef ListIterator<UsbDeviceHandle> UsbDeviceListIterator;
       
        private:
            Task task;
            UsbDeviceList devices;
            
        public:
            UsbDeviceService();
            void add(UsbDeviceHandle device);
            void remove(UsbDeviceHandle device);
            
        private:
            void run();
        
    };
    
    class UsbDevice {
        private:
            UsbDeviceServiceHandle service;
            
        public:
            UsbDevice(UsbDeviceServiceHandle service);
            virtual ~UsbDevice();
            virtual void initialize() = 0;
            virtual void process() = 0;
            
        friend UsbDeviceService;
    };
    
    class UsbDeviceCDC: public UsbDevice {
        public:
            UsbDeviceCDC(UsbDeviceServiceHandle service);
            void initialize();
            void process();
    };
        
}


#endif
