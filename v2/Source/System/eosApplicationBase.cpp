#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosApplicationBase.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
ApplicationBase::ApplicationBase() {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
ApplicationBase::~ApplicationBase() {
}


/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void ApplicationBase::run() {

    // Inicialitza els serveis
    //
    onInitialize();
    initializeServices();

    // Executa els serveis fins que finalitzi l'aplicacio.
    //
    onStart();
    runServices();
    onStop();

    // Finalitza els serveis
    //
    terminateServices();
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void ApplicationBase::onInitialize() {

#if Eos_UseApplicationInitializeCallback
    if (initializeEventCallback != nullptr)
	    initializeEventCallback->execute(this);
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void ApplicationBase::onTerminate() {

#if Eos_UseApplicationTerminateCallback
	if (terminateEventCallback != nullptr)
	    terminateEventCallback->execute(this);
#endif
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


/// ----------------------------------------------------------------------
/// \brief    Notificacio del senyal tick
///
#if Eos_ApplicationTickEnabled
void ApplicationBase::onTick() {

}
#endif
