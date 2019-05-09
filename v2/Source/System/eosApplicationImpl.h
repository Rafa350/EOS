#ifndef __eosApplicationImpl__
#define __eosApplicationImpl__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Collections/eosList.h"


namespace eos {
    
    class Service;

    class Application::Impl {

        private:
            typedef List<Service*> ServiceList;
            typedef ListIterator<Service*> ServiceListIterator;

        private:
            ServiceList services;

        public:
            Impl();

            void initializeServices();
            void runServices();

            void addService(Service *pService);       
            void removeService(Service *pService);
            void removeServices();    
    };   

}


#endif // __eosApplicationImpl__