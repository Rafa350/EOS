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
    commandQueue(10),
    osTimerEventCallback(this, &TimerService::osTimerEventHandler) {
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
        removeTimer(timers.getLast());
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
/// \brief    Procesa els events del timer.
/// \param    args: Parametres del event.
///
void TimerService::osTimerEventHandler(
    const Timer::EventArgs &args) {
    
    Command cmd;
    cmd.period = osPeriod;
    cmd.opCode = OpCode::timeOut;
    commandQueue.put(cmd, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Initialiyza el servei.
///
void TimerService::onInitialize() {
    
    osTimer.setEventCallback(&osTimerEventCallback);
}

/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onTask() {

    while (true) {
        Command cmd;
        while (commandQueue.get(cmd, 0)) {
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
                    cmdTimeOut(cmd.period);
                    break;
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Start'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdStart(
    TimerCounter *timer) {
    
    timer->counter = timer->time;
    activeQueue.push(timer->counter, timer);
    cmdTimeOut(0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Stop'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdStop(
    TimerCounter *timer) {

    timer->counter = 0;    
    activeQueue.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Pause'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdPause(
    TimerCounter *timer) {
    
    activeQueue.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Resume'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdResume(
    TimerCounter *timer) {

    activeQueue.push(timer->counter, timer);
    cmdTimeOut(0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'TimeOut'.
/// \param    period: Periode de temps procesat.
///
void TimerService::cmdTimeOut(
    int period) {

    if (!activeQueue.isEmpty()) {

        TimerCounter* timer;

        // Decrementa els contadors del temporitzadors actius
        //
        if (period > 0)
            for (TimerQueueIterator it(activeQueue); it.hasNext(); it.next()) {
                timer = it.getCurrent();

                if (timer->counter > period)
                    timer->counter -= period;
                else
                    timer->counter = 0;
            }

        // Elimina els contadors que hagin arribat a zero
        //
        while (activeQueue.peek(timer) && (timer->counter == 0)) {
            activeQueue.pop();
            if (timer->callback != nullptr) {
                TimerCounter::EventArgs args;
                args.timer = timer;
                timer->callback->execute(args);
            }
        }
        
        // Obte el nou periode
        //
        if (activeQueue.peek(timer)) {
            osPeriod = timer->counter;
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
    callback(callback),
    counter(0),
    time(0) {

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
