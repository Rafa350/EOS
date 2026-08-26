module;

#include "eos.h"
#include "eosTime.h"
#include "RTOS/rtosTimer.h"
#include "Services/CanOPen/eosCanOpenService.h"


export module Eos.Services.CanOpen.HeartbeatProducer;


export namespace eos {

	class CanOpenHeartbeatProducer {
		private:
			CanOpenService * const _service;
			rtos::Timer::Event<CanOpenHeartbeatProducer> _timerEvent;
			rtos::Timer _timer;
			bool _active;

		private:
			void timerEventHandler(rtos::Timer *timer, rtos::Timer::EventArgs *args);

		public:
			CanOpenHeartbeatProducer(CanOpenService *service);

			bool start();
			bool start(Time interval);
			bool stop();
	};
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei CanOpen.
///
eos::CanOpenHeartbeatProducer::CanOpenHeartbeatProducer(
	eos::CanOpenService *service):

	_service {service},
	_timerEvent {*this, &CanOpenHeartbeatProducer::timerEventHandler},
	_timer {rtos::Timer::Mode::autoRestart, nullptr, _timerEvent},
	_active {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la produccio amb l'interval per defecte.
/// \return   True si tot es correcte i la produccio s'ha iniciat.
///
bool eos::CanOpenHeartbeatProducer::start() {

	if (!_active) {
		uint16_t interval;
		if (_service->readU16(0x1017, 0, interval) && interval > 0)
			if (_timer.start(Time::fromMiliseconds(interval), Times::infinite))
				_active = true;
	}

	return _active;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la produccio.
/// \param    interval: Interval entre beats.
/// \return   True si tot es correcte i la produccio s'ha iniciat.
///
bool eos::CanOpenHeartbeatProducer::start(
	Time interval) {

	if (!_active) {
		if (_timer.start(interval, Time::fromMiliseconds(100)))
			_active = true;
	}

	return _active;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la produccio.
/// \return   True si tot es correcte i la produccio s'ha parat.
///
bool eos::CanOpenHeartbeatProducer::stop() {

	if (_active)
		if (_timer.stop(Time::fromMiliseconds(100)))
			_active = false;

	return !_active;
}


/// ----------------------------------------------------------------------
/// \brief    Respon al event del temporitzador.
/// \param    timer: El temporitzador.
/// \param    args: Els parametres del event.
///
void eos::CanOpenHeartbeatProducer::timerEventHandler(
	rtos::Timer *timer,
	rtos::Timer::EventArgs *args) {

	uint8_t data[1];
	switch (_service->getNodeState()) {
		case CanOpenService::NodeState::initializing:
			data[0] = 0;
			break;

		case CanOpenService::NodeState::stoped:
			data[0] = 4;
			break;

		case CanOpenService::NodeState::preOperational:
			data[0] = 0x7F;
			break;

		case CanOpenService::NodeState::operational:
			data[0] = 5;
			break;

		case CanOpenService::NodeState::error:
			data[0] = 0x80;
			break;
	}

	CobID cobId = CobID::makeHeartbeat(_service->getNodeId());

	_service->emitFrame(
		cobId,
		data,
		sizeof(data),
		eos::Time::fromMiliseconds(100));
}
