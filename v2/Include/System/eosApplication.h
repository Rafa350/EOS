#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"


namespace eos {

    class Service;

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
        private:
            typedef List<Service*> ServiceList;
            typedef ListIterator<Service*> ServiceListIterator;

        private:
            ServiceList services;

        private:
            void initializeServices();
            void runServices();

        protected:
            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTick();

        public:
            Application();
            virtual ~Application();

            void run();
            void tick();

            void addService(Service *pService);
            void removeService(Service *pService);
            void removeServices();
            Service *getService(int id);
            Service *getService(const char *serviceName);

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;
    };
}


#endif // __eosApplication__


