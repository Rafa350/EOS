#pragma once


// EOS includes
//
#include "eos.h"


namespace eos {

    /// \brief Clase que representa l'aplicacio.
    ///
    class ApplicationBase {
        private:
            ApplicationBase(const ApplicationBase&) = delete;
            ApplicationBase& operator=(const ApplicationBase&) = delete;

        protected:
            ApplicationBase();
            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onStart();
            virtual void onStop();
            virtual void onRun();

        public:
            virtual ~ApplicationBase() = default;
            void run();
    };
}


