module;


#include "eos.h"


export module Eos.System.Application;


export namespace eos {

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
        protected:
            Application();

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onStart();
            virtual void onStop();
            virtual void onRun();

        public:
            Application(const Application&) = delete;
            Application(const Application&&) = delete;
            virtual ~Application() = default;

            void run();

            Application& operator=(const Application&) = delete;
            Application& operator=(const Application&&) = delete;
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
