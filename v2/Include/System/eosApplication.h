#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"


namespace eos {

    class Service;

    class Application {
        private:
            class Impl;

        private:
            Impl *pImpl;

        private:
            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

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
            Service *getService(const char *name) const;
    };        
}


#endif // __eosApplication__


