module;


#include "eos.h"


export module Eos.System.Application;


import Eos.Types;


export namespace eos {

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application: private NonCopyableClass {
        protected:
            Application();

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onStart();
            virtual void onStop();
            virtual void onRun();

        public:
            virtual ~Application() = default;

            void run();
    };
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Application::Application() {
}



/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void eos::Application::run() {

    onInitialize();
    onStart();
    onRun();
    onStop();
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void eos::Application::onInitialize() {
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void eos::Application::onTerminate() {
}


/// ----------------------------------------------------------------------
/// \brief    Notifica l'inici de l'execucio de l'aplicacio
///
void eos::Application::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de l'execucio de l'aplicacio.
///
void eos::Application::onStop() {

}


void eos::Application::onRun() {

}
