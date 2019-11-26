#include "eos.h"
#include "Services/eosTimerService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany el servei.
///
TimerService::TimerService(
    Application *application):
    
    Service(application),
    commandQueue(10) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerService::~TimerService() {
    
    while (!timers.isEmpty()) {
        TimerCounter *timer = timers.getFirst();
        removeTimer(timer);
        delete timer;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un contador al servei.
/// \param    timer: El temporitzador a afeigir.
///
void TimerService::addTimer(
    TimerCounter *timer) {

    // Prerequisits
    //
    eosAssert(timer != nullptr);
    eosAssert(timer->service == nullptr);

    timers.add(timer);
    timer->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un contador del servei.
/// \param    timer: El temporitzador a eliminar.
///
void TimerService::removeTimer(
    TimerCounter *timer) {

    // Precondicions
    //
    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    timer->service = nullptr;
    timers.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots temporitzadors del servei.
///
void TimerService::removeTimers() {
    
    while (!timers.isEmpty())
        removeTimer(timers.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief    Inicia un temporitzador.
/// \param    timer: El temporitzador.
/// \param    time: El periode.
///
void TimerService::start(
    TimerCounter *timer,
    int time) {
    
    timer->time = time;
    
    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::start;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El temporitzador.
///
void TimerService::stop(
    TimerCounter *timer) {
    
    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::stop;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Posa el temporitzador en pausa.
/// \param    timer: El temporitzador.
///
void TimerService::pause(
    TimerCounter *timer) {
    
    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::pause;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Torna a posar en marxa el temporitzador despres d'una pausa.
/// \param    timer: El temporitzador.
///
void TimerService::resume(
    TimerCounter *timer) {
    
    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::resume;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onTask() {
    
    while (true) {
        processActiveTimers();
        processCommands();
        waitTime();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els temporitzadors actius.
///
void TimerService::processActiveTimers() {
    
    if (!activeTimers.isEmpty()) {

    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la cua de comandes.
///
void TimerService::processCommands() {
    
    Command cmd;
    while (commandQueue.get(cmd, 0)) {
        switch (cmd.opCode) {
            case OpCode::start:
                break;

            case OpCode::stop:
                break;

            case OpCode::pause:
                break;

            case OpCode::resume:
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Espera el event de temps.
///
void TimerService::waitTime() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    callback: El callback dels events.
///
TimerCounter::TimerCounter(
    TimerService *service,
    IEventCallback *callback):

    service(nullptr),
    callback(callback) {    
    
    if (service != nullptr)
        service->addTimer(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerCounter::~TimerCounter() {
   
    if (service != nullptr)
        service->removeTimer(this);
}
