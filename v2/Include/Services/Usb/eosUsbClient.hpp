#ifndef __EOS_SERVICES_USBCLIENT_HPP
#define __EOS_SERVICES_USBCLIENT_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"


namespace eos {
    
    class UsbClientService: private IRunable {
        
        private:
            Task task;
            
        public:
            UsbClientService();
            
        private:
            void run();
        
    };
        
}


#endif
