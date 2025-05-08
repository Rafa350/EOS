#include "eos.h"
#include "eosAssert.h"
#include "Services/eosTimerService.h"
#include "System/Core/eosTask.h"


using namespace eos;


constexpr static const unsigned _initTick = 1;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
TimerService::TimerService():
    _commandQueue {_commandQueueSize},
	_ticks {_initTick} {
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
        _timers.pushFront(timer);
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
        _timers.remove(timer);
        timer->_service = nullptr;
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

    while (!_timers.empty())
    	removeTimer(_timers.front());

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Inicia un temporitzador.
/// \param    timer: El temporitzador.
/// \param    period: El periode.
/// \param    autorestart: True si arranca ciclicament.
/// \param    blockTime: Temps maxim de bloqueig.
///
void TimerService::start(
    TimerCounter *timer,
    unsigned period,
	bool autorestart,
    unsigned blockTime) {

    eosAssert(timer != nullptr);
    eosAssert(timer->_service == this);

    if (period > 0) {

        Command command = {
        	.id = CommandID::timerStart,
        	.timerStart = {
        		.timer = timer,
        		.period = period,
				.autorestart = autorestart
        	}
        };
        _commandQueue.push(command, blockTime);
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

    Command command = {
    	.id = CommandID::timerStop,
    	.timerStop = {
    		.timer = timer
    	}
    };
    _commandQueue.push(command, blockTime);
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

    Command command = {
   		.id = CommandID::timerPause,
   		.timerPause = {
   			.timer = timer
   		}
    };
    _commandQueue.push(command, blockTime);
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

    Command command = {
    	.id = CommandID::timerResume,
    	.timerResume = {
    		.timer = timer
    	}
    };
    _commandQueue.push(command, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onExecute() {

    while (!stopSignal()) {
    	Command command;
        while (_commandQueue.pop(command, (unsigned) -1))
        	commandDispatcher(command);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una comanda.
/// \param    command: La comanda.
///
void TimerService::commandDispatcher(
	const Command &command) const {

	switch (command.id) {
		case CommandID::timerStart:
			command.timerStart.timer->processStart(
				command.timerStart.period,
				command.timerStart.autorestart);
			break;

		case CommandID::timerStop:
			command.timerStop.timer->processStop();
			break;

		case CommandID::timerPause:
			command.timerPause.timer->processPause();
			break;

		case CommandID::timerResume:
			command.timerResume.timer->processResume();
			break;

		case CommandID::tick:
			for (auto timer: _timers) {
				if (timer->processTick())
					timeout(timer);
			}
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza el contador de ticks
/// \return   True si s'ha arribat al final, false en cas contrari.
///
bool TimerService::updateTicks() {

	if (_ticks > 0)
		_ticks -= 1;

	if (_ticks == 0) {
		_ticks = _initTick;
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Senyal tick
///
void TimerService::tick(
	unsigned blockTime) {

	if (updateTicks()) {
		Command command = {
			.id = CommandID::tick
		};
		_commandQueue.push(command, blockTime);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Senyal tick per interrupcio
///
void TimerService::tickISR() {

	if (updateTicks()) {
		Command command = {
			.id = CommandID::tick
		};
		_commandQueue.pushISR(command);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Operacions a realitzar quant el temporitzador arriba al final.
/// \param    timer: El temporitzador.
///
void TimerService::timeout(
	TimerCounter *timer) const {

	notifyTimeout(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el 'timeout' d'un temporitzador.
/// \param    timer: El temporitzador.
///
void TimerService::notifyTimeout(
	TimerCounter *timer) const {

	if (_erNotify.isEnabled(NotifyID::timeout)) {
		NotifyEventArgs args = {
			.timeout = {
				.timer = timer
			}
		};
		_erNotify.raise(NotifyID::timeout, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
///
TimerCounter::TimerCounter(
    TimerService *service) :

    _service {nullptr},
	_state {State::stoped},
	_autorestart {false},
    _period {0},
	_counter {0} {

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


/// ----------------------------------------------------------------------
/// \brief    Procesa l'operacio 'Start'
///
void TimerCounter::processStart(
	unsigned period,
	bool autorestart) {

    Task::enterCriticalSection();

    if (_state == State::stoped) {
		_period = period;
		_counter = period;
		_autorestart = autorestart;
		_state = State::running;
	}

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'operacio 'Stop'.
///
void TimerCounter::processStop() {

    Task::enterCriticalSection();

    if (_state != State::stoped)
		_state = State::stoped;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'operacio 'Pause'.
///
void TimerCounter::processPause() {

    Task::enterCriticalSection();

    if (_state == State::running)
		_state = State::paused;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'operacio 'Resume'.
///
void TimerCounter::processResume() {

    Task::enterCriticalSection();

    if (_state == State::paused)
		_state = State::running;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'operacio 'Tick'.
/// \return   True si s'ha produit un timeout.
///
bool TimerCounter::processTick() {

	bool result = false;

    Task::enterCriticalSection();

    if (_state == State::running) {

		if (_counter > 0)
			_counter -= 1;

		if (_counter == 0) {

			if (_autorestart) {
				_counter = _period;
				_state = State::running;
			}
			else
			   _state = State::stoped;

			result = true;
		}
	}

    Task::exitCriticalSection();

    return result;
}
