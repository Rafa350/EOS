#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"


namespace eos {

	class Service;
    class String;

    void link(Application *application, Service *service);
    void unlink(Application *application, Service *service);

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
    	private:
        	typedef List<Service*, 5> ServiceList;

        private:
            ServiceList services;

        private:
            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

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

            void addService(Service *service);
            void removeService(Service *service);
            void removeServices();

            Service *findService(const String &serviceName) const;

            friend void link(Application *application, Service *service);
            friend void unlink(Application *application, Service *service);
    };
}


#endif // __eosApplication__


