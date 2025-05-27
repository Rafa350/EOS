#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosApplicationBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
ApplicationBase::ApplicationBase() {
}



/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void ApplicationBase::run() {

    onInitialize();
    onStart();
    onRun();
    onStop();
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void ApplicationBase::onInitialize() {
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void ApplicationBase::onTerminate() {
}


/// ----------------------------------------------------------------------
/// \brief    Notifica l'inici de l'execucio de l'aplicacio
///
void ApplicationBase::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de l'execucio de l'aplicacio.
///
void ApplicationBase::onStop() {

}


void ApplicationBase::onRun() {

}

