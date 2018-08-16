#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"


namespace eos {

    class Service;

    class Application {
        private:
            typedef List<Service*> ServiceList;
            typedef ListIterator<Service*> ServiceListIterator;

        private:
            ServiceList services;

        private:
            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

        protected:
            virtual void onInitialize();
            virtual void onTerminate();

        public:
            Application();
            virtual ~Application();

            void run();

            void addService(Service *pService);
            void removeService(Service *pService);
            Service *getService(const char *name) const;
    };

}


#endif // __eosApplication__


