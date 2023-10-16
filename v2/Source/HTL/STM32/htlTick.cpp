#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/HtlINT.h"
#include "HTL/STM32/HtlGPIO.h"


using namespace htl::tick;


Tick Tick::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
Tick::Tick():
	_tickCounter {0},
	_tmrNotifyEvent {*this, &Tick::tmrNotifyEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void Tick::initialize() {

	uint32_t period = 1000;
	uint32_t prescaler = (clock::getClockFrequency(clock::ClockID::pclk) / 1000000) - 1;
	tmr::ClockDivider clkDiv = tmr::ClockDivider::_1;

	auto tmr = tmr::TMRDevice14::getHandler();
	tmr->initBase(clkDiv, prescaler, period);
	tmr->setNotifyEvent(_tmrNotifyEvent, true);
	tmr->start_IRQ();

	irq::enableInterruptVector(irq::VectorID::tmr14);
	irq::setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::_7);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void Tick::deinitialize() {

	stop();

	auto hTMR = htl::tmr::TMRDevice14::getHandler();
	hTMR->stop();
	hTMR->disableNotifyEvent();

	irq::disableInterruptVector(irq::VectorID::tmr14);
}


void Tick::start() {

	auto hTMR = htl::tmr::TMRDevice14::getHandler();
	hTMR->setNotifyEvent(_tmrNotifyEvent, true);
	hTMR->start_IRQ();
}


void Tick::stop() {

	auto hTMR = htl::tmr::TMRDevice14::getHandler();
	hTMR->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks
/// \return   El valor del contador
//
uint32_t Tick::getTickCount() {

	return _tickCounter;
}


/// ----------------------------------------------------------------------
/// \brief    Espera un nombre determinat de ticks
/// \param    time: El nombre de tics
///
void Tick::wait(
	uint32_t time) {

	uint32_t startTime = getTickCount();
	while (getTickCount() - startTime < time)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les notificacions del temporitzador.
/// \param    sender: El temporitzadort que envia la noptificacio.
/// \param    args: Parametres de la notificacio.
///
void Tick::tmrNotifyEventHandler(
	htl::tmr::TMRDevice *sender,
	htl::tmr::NotifyEventArgs &args) {

	if (args.id == htl::tmr::NotifyID::update)
		_tickCounter++;

	#ifdef DBG_Pin
	auto dbgPin = DBG_Pin::getHandler();
	dbgPin->toggle();
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler() {

	auto hTMR = htl::tmr::TMRDevice14::getHandler();
	hTMR->interruptHandler();
}
