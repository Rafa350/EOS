module;


#include "HTL/htl.h"
#include "HTL/htlTMR.h"


export module htl.tick;

import htl.clocks;
import htl.interrupts;


export namespace htl::tick {

	class TickGenerator {
		private:
			using DevTMR = HTL_TICK_TIMER;

		private:
			static TickGenerator _instance;
			DevTMR * const _devTMR;
			volatile unsigned _tickCounter;
			htl::tmr::NotifyEvent<TickGenerator> _tmrNotifyEvent;

		public:
			static constexpr TickGenerator* pInst = &_instance;
            static constexpr TickGenerator& rInst = _instance;

		private:
			TickGenerator();
			TickGenerator(const TickGenerator&) = delete;

			void tmrNotifyEventHandler(htl::tmr::NotifyID id, htl::tmr::NotifyEventArgs * const args);

		public:
			void initialize(unsigned frequency);
			void deinitialize();
			void start();
			void stop();
			unsigned getTick();
			void wait(unsigned ticks);

			void tmrInterruptHandler();
	};

}


using namespace htl::tick;


TickGenerator TickGenerator::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
htl::tick::TickGenerator::TickGenerator():
	_devTMR {DevTMR::pInst},
	_tickCounter {0},
	_tmrNotifyEvent {*this, &TickGenerator::tmrNotifyEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    frequency: Frequencia.
///
void htl::tick::TickGenerator::initialize(
    unsigned frequency) {

	unsigned limit = 1000;
	auto prescaler = (htl::clock::getClockFrequency(htl::clock::ClockID::pclk) / frequency) - 1;
	auto clkDiv = htl::tmr::ClockDivider::_1;

	_devTMR->initialize(clkDiv, prescaler, limit, 0);
	_devTMR->setNotifyEvent(_tmrNotifyEvent, true);

	htl::interrupts::enableInterruptVector(htl::interrupts::VectorID::tmr14);
	htl::interrupts::setInterruptVectorPriority(htl::interrupts::VectorID::tmr14, htl::interrupts::Priority::p7);

	start();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void htl::tick::TickGenerator::deinitialize() {

    stop();

	_devTMR->disableNotifyEvent();

	interrupts::disableInterruptVector(interrupts::VectorID::tmr14);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void htl::tick::TickGenerator::start() {

    _devTMR->start_IRQ();
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void htl::tick::TickGenerator::stop() {

    _devTMR->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks
/// \return   El valor del contador
//
unsigned htl::tick::TickGenerator::getTick() {

    //disableInterrupts();
	auto tick = _tickCounter;
	//enableInterrupts();

	return tick;
}


/// ----------------------------------------------------------------------
/// \brief    Espera un nombre determinat de ticks
/// \param    ticks: El nombre de tics
///
void htl::tick::TickGenerator::wait(
	unsigned ticks) {

	auto lastTick = getTick() + ticks;
	while (static_cast<int>(lastTick - getTick()) > 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les notificacions del temporitzador.
/// \param    sender: El temporitzadort que envia la notificacio.
/// \param    args: Parametres de la notificacio.
///
void htl::tick::TickGenerator::tmrNotifyEventHandler(
	htl::tmr::NotifyID id,
	htl::tmr::NotifyEventArgs * const args) {

	if (id == htl::tmr::NotifyID::update)
		_tickCounter += 1;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del TMR
///
void htl::tick::TickGenerator::tmrInterruptHandler() {

    _devTMR->interruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler(void) {

	TickGenerator::pInst->tmrInterruptHandler();
}
