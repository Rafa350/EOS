#ifndef __EOS_APPLICATION_H
#define	__EOS_APPLICATION_H


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

        public:
            Application();
            virtual ~Application();

            void execute();

            void addService(Service *service);
            void removeService(Service *service);
            Service *getService(const char *name);

        protected:
            virtual void onInitialize();
            virtual void onTerminate();

        private:
            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;
    };

}

#endif


