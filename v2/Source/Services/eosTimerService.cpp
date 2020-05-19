#include "eos.h"
#include "OSAL/osalKernel.h"
#include "Services/eosTimerService.h"
#include "System/Core/eosTask.h"

using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany el servei.
///
TimerService::TimerService(
    Application* application):

    Service(application),
    commandQueue(10),
    osTimerEventCallback(this, &TimerService::osTimerEventHandler) {
    //osTimer(false, &osTimerEventCallback, nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerService::~TimerService() {

    while (!timers.isEmpty())
        delete timers.getBack();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un contador al servei.
/// \param    timer: El temporitzador a afeigir.
///
void TimerService::addTimer(
    TimerCounter* timer) {

    eosAssert(timer != nullptr);
    eosAssert(timer->service == nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();
    
    if (timer->service == nullptr) {
        timers.pushBack(timer);
        timer->service = this;
    }
    
    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un contador del servei.
/// \param    timer: El temporitzador a eliminar.
///
void TimerService::removeTimer(
    TimerCounter* timer) {

    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();
    
    if (timer->service == this) {    
        
        // Si esta actiu l'elimina de la cua d'actius
        //
        if (activeQueue.contains(timer))
            activeQueue.remove(timer);
        
        timer->service = nullptr;
        timers.removeAt(timers.indexOf(timer));
    }

    // Fi de la seccio critica
    //    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots temporitzadors del servei.
///
void TimerService::removeTimers() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();
    
    while (!timers.isEmpty()) {
        
        TimerCounter* timer = timers.getBack();

        // Si esta actiu l'elimina de la cua d'actius
        //
        if (activeQueue.contains(timer))
            activeQueue.remove(timer);

        timers.popBack();
        timer->service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Inicia un temporitzador.
/// \param    timer: El temporitzador.
/// \param    period: El periode.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::start(
    TimerCounter* timer,
    unsigned period,
    unsigned blockTime) {
    
    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    if (period > 0) {

        timer->period = period;

        Command cmd;
        cmd.opCode = OpCode::start;
        cmd.timer = timer;
        commandQueue.push(cmd, blockTime);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::stop(
    TimerCounter* timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    Command cmd;
    cmd.opCode = OpCode::stop;
    cmd.timer = timer;
    commandQueue.push(cmd, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Posa el temporitzador en pausa.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::pause(
    TimerCounter* timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    Command cmd;
    cmd.opCode = OpCode::pause;
    cmd.timer = timer;
    commandQueue.push(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Torna a posar en marxa el temporitzador despres d'una pausa.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::resume(
    TimerCounter* timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    Command cmd;
    cmd.opCode = OpCode::resume;
    cmd.timer = timer;
    commandQueue.push(cmd, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events del timer.
/// \param    args: Parametres del event.
///
void TimerService::osTimerEventHandler(
    const Timer::EventArgs& args) {
    
    Command cmd;
    cmd.opCode = OpCode::timeOut;
    cmd.period = osPeriod;
    commandQueue.push(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Initialiyza el servei.
///
void TimerService::onInitialize() {
    
    osTimer.setEventCallback(&osTimerEventCallback);
    
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onTask() {

    // Espera indefinidament que arribin comandes per procesar
    //
    Command cmd;
    while (commandQueue.pop(cmd, unsigned(-1))) {

        switch (cmd.opCode) {
            case OpCode::start:
                cmdStart(cmd.timer);
                break;

            case OpCode::stop:
                cmdStop(cmd.timer);
                break;

            case OpCode::pause:
                cmdPause(cmd.timer);
                break;

            case OpCode::resume:
                cmdResume(cmd.timer);
                break;

            case OpCode::timeOut:
                cmdTimeOut();
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Start'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdStart(
    TimerCounter* timer) {
    
    // Calcula el temps d'expiracio.
    //
    timer->currentPeriod = timer->period;
    timer->expireTime = osalGetTickTime() + timer->currentPeriod;

    // Afegeig el contador a la llista de contadors actius.
    //
    if (activeQueue.contains(timer))
        activeQueue.remove(timer);
    activeQueue.push(timer->expireTime, timer);
    
    // Si es el primer, inicia el temporitzador.
    //
    if (activeQueue.getSize() == 1)
        osTimer.start(timer->currentPeriod, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Stop'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdStop(
    TimerCounter* timer) {
    
    // Elimina el contador de la llista de contadors actius.
    //
    activeQueue.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Pause'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdPause(
    TimerCounter* timer) {
    
    // Elimina el contador de la llista de contadors actius.
    //
    activeQueue.remove(timer);
    
    // Recalcula el periode que resta. 
    //
    timer->currentPeriod = timer->expireTime - osalGetTickTime();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Resume'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdResume(
    TimerCounter* timer) {

    // Recalcula el temps d'expiracio amb el periode ue resta.
    //
    timer->expireTime = osalGetTickTime() + timer->currentPeriod;
    
    // Afegeix el contador a la cua de contadors actius.
    //
    activeQueue.push(timer->expireTime, timer);

    // Si es el primer, inicia el temporitzador.
    //
    if (activeQueue.getSize() == 1)
        osTimer.start(timer->currentPeriod, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'TimeOut'.
/// \param    period: Periode de temps procesat.
///
void TimerService::cmdTimeOut() {
    
    TimerCounter* timer;

    // Comprova si hi han contadors actius.
    //
    if (!activeQueue.isEmpty()) {

        // Obte el temps actual.
        //
        unsigned currentTime = osalGetTickTime();
    
        // Elimina els contadors que hagin arribat al final.
        //
        while (activeQueue.peek(timer) && (currentTime >= timer->expireTime)) {
            
            // Elimina el contador de la cua d'actius.
            //
            activeQueue.pop();
            
            // Crida a la funcio callback del contador.
            //
            if (timer->eventCallback != nullptr) {
                TimerCounter::EventArgs args;
                args.type = TimerCounter::EventType::timeout;
                args.timer = timer;
                timer->eventCallback->execute(args);
            }
        }
        
        // Obte el primer contador actiu.
        //
        if (activeQueue.peek(timer)) {
            
            // Recalcula el temps d'expiracio.
            //
            osPeriod = timer->expireTime - currentTime;
            
            // Activa el temporitzador, per un nou cicle.
            //
            osTimer.start(osPeriod, 0);
        }
    }
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
    eventCallback(callback),
    period(0) {

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
