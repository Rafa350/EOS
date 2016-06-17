#ifndef __EOS_SERVICES_USBCLIENT_HPP
#define __EOS_SERVICES_USBCLIENT_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"


namespace eos {
    
    class UsbDevice;
    typedef UsbDevice *UsbDeviceHandle;
    
    class UsbClientService;
    typedef UsbClientService *UsbClientServiceHandle;
    
    class UsbClientService: private IRunable {
       
        private:
            Task task;
            
        public:
            UsbClientService();
            void addDevice(UsbDeviceHandle *device);
            
        private:
            void run();
        
    };
    
    class UsbDevice {
        public:
            UsbDevice(UsbClientServiceHandle *service);
            virtual ~UsbDevice();
            virtual void initialize() = 0;
            virtual void process() = 0;
    };
    
    class UsbDeviceCDC: public UsbDevice {
        public:
            UsbDeviceCDC(UsbClientServiceHandle *service);
            void initialize();
            void process();
    };
        
}


#endif
