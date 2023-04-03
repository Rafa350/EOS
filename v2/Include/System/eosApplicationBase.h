#pragma once
#ifndef __eosApplicationBase__
#define	__eosApplicationBase__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"


namespace eos {

    class Service;

    /// \brief Clase que representa l'aplicacio.
    ///
    class ApplicationBase {
        private:
            ApplicationBase(const ApplicationBase&) = delete;
            ApplicationBase& operator=(const ApplicationBase&) = delete;
            virtual void initializeServices() = 0;
            virtual void terminateServices() = 0;
            virtual void runServices() = 0;

        protected:
            ApplicationBase();
            virtual void onInitialize();
            virtual void onStart();
            virtual void onStop();
            virtual void onTerminate();

        public:
            virtual ~ApplicationBase();
            void run();
    };
}


#endif // __eosApplicationBase__


