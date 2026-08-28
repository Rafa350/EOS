module;

#include "eos.h"
#include "eosResults.h"
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

			Result sendBoot();
			Result sendBeat();

			Result start();
			Result start(Time interval);
			Result stop();

			bool isActive() const;
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
/// \return   El resultat de l'operacio.
///
eos::Result eos::CanOpenHeartbeatProducer::start() {

	if (!_active) {
		uint16_t interval;
		if (_service->readU16(0x1017, 0, interval) && interval > 0)
			if (_timer.start(Time::fromMiliseconds(interval), Times::infinite))
				_active = true;
	}

	return _active ? Result::ErrorCodes::ok : Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la produccio.
/// \param    interval: Interval entre beats.
/// \return   True si tot es correcte i la produccio s'ha iniciat.
///
eos::Result eos::CanOpenHeartbeatProducer::start(
	Time interval) {

	if (!_active) {
		if (_timer.start(interval, Time::fromMiliseconds(100)))
			_active = true;
	}

	return _active ? Result::ErrorCodes::ok : Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la produccio.
/// \return   True si tot es correcte i la produccio s'ha parat.
///
eos::Result eos::CanOpenHeartbeatProducer::stop() {

	if (_active)
		if (_timer.stop(Time::fromMiliseconds(100)))
			_active = false;

	return _active ? Result::ErrorCodes::error : Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// \brief    Indica si esta actiu i generant beats.
/// \return   True si esta actiu.
///
inline bool eos::CanOpenHeartbeatProducer::isActive() const {

	return _active;
}


/// ----------------------------------------------------------------------
/// \brief    Respon al event del temporitzador.
/// \param    timer: El temporitzador.
/// \param    args: Els parametres del event.
///
void eos::CanOpenHeartbeatProducer::timerEventHandler(
	rtos::Timer *timer,
	rtos::Timer::EventArgs *args) {

	sendBeat();
}


/// ----------------------------------------------------------------------
/// \brief    Emet el boot
/// \return   El resultat de l'operacio.
/// \remarks  Nomes es permet si el node esta en estat 'initializing'
///
eos::Result eos::CanOpenHeartbeatProducer::sendBoot() {

	if (_service->getNodeState() != eos::CanOpenService::NodeState::initializing)
		return eos::Result::ErrorCodes::errorState;
	else
		return sendBeat();
}


/// ----------------------------------------------------------------------
/// \brief    Emet el beat
/// \return   El resultat de l'operacio.
///
eos::Result eos::CanOpenHeartbeatProducer::sendBeat() {

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

	return _service->emitFrame(
		cobId,
		data,
		sizeof(data),
		eos::Time::fromMiliseconds(100));
}
