#include "eos.h"
#include "Services/eosTimerService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany el servei.
///
TimerService::TimerService(
    Application *application):
    
    Service(application) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerService::~TimerService() {
    
    while (!counters.isEmpty()) {
        TimerCounter *counter = counters.getFirst();
        removeCounter(counter);
        delete counter;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un contador al servei.
/// \param    conter: El contador a afeigir.
///
void TimerService::addCounter(
    TimerCounter *counter) {

    // Prerequisits
    //
    eosAssert(counter != nullptr);
    eosAssert(counter->service == nullptr);

    counters.add(counter);
    counter->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un contador del servei.
/// \param    input: El contador a eliminar.
///
void TimerService::removeCounter(
    TimerCounter *counter) {

    // Precondicions
    //
    eosAssert(counter != nullptr);
    eosAssert(counter->service == this);

    counter->service = nullptr;
    counters.remove(counter);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots contadors del servei.
///
void TimerService::removeCounters() {
    
    while (!counters.isEmpty())
        removeCounter(counters.getFirst());
}


void TimerService::startCicle() {
    
    int time = MAX_INT;
    
    // Busca el minim periode de temps
    //
/*    for(auto counter: counters) {
        if (counter->time < time)
            time = counter->time;
    }*/
    
    // Activa el temnporizador
    
}


void TimerService::timeOut() {
    
}