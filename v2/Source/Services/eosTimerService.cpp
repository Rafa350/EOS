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
    _commandQueue(10),
    _activeQueue(),
    _osTimerEventCallback(this, &TimerService::osTimerEventHandler) {
    //_osTimer(false, &osTimerEventCallback, nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerService::~TimerService() {

    while (!_timers.isEmpty())
        delete _timers.peekBack();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un contador al servei.
/// \param    timer: El temporitzador a afeigir.
///
void TimerService::addTimer(
    TimerCounter* timer) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (timer->_service == nullptr) {
        _timers.pushBack(timer);
        timer->_service = this;
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
    eosAssert(timer->_service == this);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (timer->_service == this) {

        // Si esta actiu l'elimina de la cua d'actius
        //
        if (_activeQueue.contains(timer))
            _activeQueue.remove(timer);

        timer->_service = nullptr;
        _timers.removeAt(_timers.indexOf(timer));
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

    while (!_timers.isEmpty()) {

        TimerCounter* timer = _timers.peekBack();

        // Si esta actiu l'elimina de la cua d'actius
        //
        if (_activeQueue.contains(timer))
            _activeQueue.remove(timer);

        _timers.popBack();
        timer->_service = nullptr;
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
    TimerCounter *timer,
    unsigned period,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == this);

    if (period > 0) {

        timer->_period = period;

        Command cmd;
        cmd.opCode = OpCode::start;
        cmd.timer = timer;
        _commandQueue.push(cmd, blockTime);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::stop(
    TimerCounter *timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == this);

    Command cmd;
    cmd.opCode = OpCode::stop;
    cmd.timer = timer;
    _commandQueue.push(cmd, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Posa el temporitzador en pausa.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::pause(
    TimerCounter *timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == this);

    Command cmd;
    cmd.opCode = OpCode::pause;
    cmd.timer = timer;
    _commandQueue.push(cmd, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Torna a posar en marxa el temporitzador despres d'una pausa.
/// \param    timer: El temporitzador.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::resume(
    TimerCounter *timer,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == this);

    Command cmd;
    cmd.opCode = OpCode::resume;
    cmd.timer = timer;
    _commandQueue.push(cmd, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events del timer.
/// \param    args: Parametres del event.
///
void TimerService::osTimerEventHandler(
    const Timer::EventArgs &args) {

    Command cmd;
    cmd.opCode = OpCode::timeOut;
    cmd.period = _osPeriod;
    _commandQueue.push(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Initialiyza el servei.
///
void TimerService::onInitialize() {

    _osTimer.setEventCallback(&_osTimerEventCallback);

    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onTask(
    Task *task) {

    // Espera indefinidament que arribin comandes per procesar
    //
    Command cmd;
    while (_commandQueue.pop(cmd, unsigned(-1))) {

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
    TimerCounter *timer) {

    // Calcula el temps d'expiracio.
    //
    timer->_currentPeriod = timer->_period;
    timer->_expireTime = osalGetTickTime() + timer->_currentPeriod;

    // Afegeig el contador a la llista de contadors actius.
    //
    if (_activeQueue.contains(timer))
        _activeQueue.remove(timer);

    _activeQueue.push(timer);

    // Si es el primer, inicia el temporitzador.
    //
    if (_activeQueue.getSize() == 1)
        _osTimer.start(timer->_currentPeriod, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Stop'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdStop(
    TimerCounter *timer) {

    // Elimina el contador de la llista de contadors actius.
    //
    _activeQueue.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Pause'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdPause(
    TimerCounter *timer) {

    // Elimina el contador de la llista de contadors actius.
    //
    _activeQueue.remove(timer);

    // Recalcula el periode que resta.
    //
    timer->_currentPeriod = timer->_expireTime - osalGetTickTime();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'Resume'.
/// \param    timer: El temporitzador.
///
void TimerService::cmdResume(
    TimerCounter *timer) {

    // Recalcula el temps d'expiracio amb el periode ue resta.
    //
    timer->_expireTime = osalGetTickTime() + timer->_currentPeriod;

    // Afegeix el contador a la cua de contadors actius.
    //
    _activeQueue.push(timer);

    // Si es el primer, inicia el temporitzador.
    //
    if (_activeQueue.getSize() == 1)
        _osTimer.start(timer->_currentPeriod, 0);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'TimeOut'.
/// \param    period: Periode de temps procesat.
///
void TimerService::cmdTimeOut() {

    // Comprova si hi han contadors actius.
    //
    if (!_activeQueue.isEmpty()) {

        // Obte el temps actual.
        //
        unsigned currentTime = osalGetTickTime();

        // Elimina els contadors que hagin arribat al final.
        //
        while (true) {

            if (_activeQueue.isEmpty())
                break;

            TimerCounter *timer = _activeQueue.peek();
            if (currentTime < timer->_expireTime)
                break;

            // Elimina el contador de la cua d'actius.
            //
            _activeQueue.pop();

            // Crida a la funcio callback del contador.
            //
            if (timer->_eventCallback != nullptr) {
                TimerCounter::EventArgs args;
                args.type = TimerCounter::EventType::timeout;
                args.timer = timer;
                timer->_eventCallback->execute(args);
            }
        }

        // Obte el primer contador actiu.
        //
        if (!_activeQueue.isEmpty()) {

            // Recalcula el temps d'expiracio.
            //
            TimerCounter *timer = _activeQueue.peek();
            _osPeriod = timer->_expireTime - currentTime;

            // Activa el temporitzador, per un nou cicle.
            //
            _osTimer.start(_osPeriod, 0);
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

    _service(nullptr),
    _eventCallback(callback),
    _period(0) {

    if (service != nullptr)
        service->addTimer(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerCounter::~TimerCounter() {

    if (_service != nullptr)
        _service->removeTimer(this);
}


bool QueueComparator::operator () (
    const TimerCounter *left,
    const TimerCounter *right) {

    return left->_expireTime < right->_expireTime;
}
