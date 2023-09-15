#include "HTL/htlTick.h"
#include "htl/STM32/htlClock.h"
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

	auto tmr = tmr::TMRDevice14::getHandler();

	uint32_t period = 1000;
	uint32_t prescaler = (clock::getClockFrequency(clock::ClockID::pclk) / 1000000) - 1;
	tmr::ClockDivider clkDiv = tmr::ClockDivider::_1;

	tmr->initBase(clkDiv, prescaler, period);
	tmr->setNotifyEvent(_tmrNotifyEvent, true);
	tmr->startInterrupt();

	irq::enableInterruptVector(irq::VectorID::tmr14);
	irq::setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::_0, irq::SubPriority::_0);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void Tick::deinitialize() {

	auto tmr = htl::tmr::TMRDevice14::getHandler();
	tmr->stopInterrupt();
	tmr->disableNotifyEvent();

	irq::disableInterruptVector(irq::VectorID::tmr14);
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

	return;

	uint32_t startTime = _tickCounter;

	while (_tickCounter - startTime < time)
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

	auto tmr = htl::tmr::TMRDevice14::getHandler();
	tmr->interruptHandler();
}
