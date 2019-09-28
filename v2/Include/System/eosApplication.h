#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"


namespace eos {

    class Service;
    class String;

    typedef List<Service*> ServiceList;
    typedef ListIterator<Service*> ServiceListIterator;

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
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

            static Application *getApplication();

            void run();
            void tick();

            void addService(Service *pService);
            void removeService(Service *pService);
            void removeServices();
            Service *getService(int id) const;
            Service *getService(const String &serviceName) const;
            inline const ServiceList& getServices() const { return services; }

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;
    };
}


#endif // __eosApplication__


