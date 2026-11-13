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


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Application::Application() {
}



/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void Application::run() {

    onInitialize();
    onStart();
    onRun();
    onStop();
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void Application::onInitialize() {
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void Application::onTerminate() {
}


/// ----------------------------------------------------------------------
/// \brief    Notifica l'inici de l'execucio de l'aplicacio
///
void Application::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de l'execucio de l'aplicacio.
///
void Application::onStop() {

}


void Application::onRun() {

}
