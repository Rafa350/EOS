#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlINT.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::tick;


using TMRTick = HTL_TICK_TIMER;


TickGenerator TickGenerator::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
TickGenerator::TickGenerator():
	_tickCounter {0},
	_tmrNotifyEvent {*this, &TickGenerator::tmrNotifyEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    frequency: Frequencia.
///
void TickGenerator::initialize(
    uint32_t frequency) {

	uint32_t period = 1000;
	uint32_t prescaler = (clock::getClockFrequency(clock::ClockID::pclk) / frequency) - 1;
	tmr::ClockDivider clkDiv = tmr::ClockDivider::_1;

	TMRTick::pInst->initBase(clkDiv, prescaler, period);
	TMRTick::pInst->setNotifyEvent(_tmrNotifyEvent, true);

	irq::enableInterruptVector(irq::VectorID::tmr14);
	irq::setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::_7);

	start();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void TickGenerator::deinitialize() {

    stop();

	TMRTick::pInst->disableNotifyEvent();

	irq::disableInterruptVector(irq::VectorID::tmr14);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void TickGenerator::start() {

    TMRTick::pInst->start_IRQ();
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TickGenerator::stop() {

	TMRTick::pInst->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks
/// \return   El valor del contador
//
Ticks TickGenerator::getTick() {

	return _tickCounter;
}


/// ----------------------------------------------------------------------
/// \brief    Espera un nombre determinat de ticks
/// \param    ticks: El nombre de tics
///
void TickGenerator::wait(
	Ticks ticks) {

	auto lastTick = getTick() + ticks;
	while (static_cast<int>(lastTick - getTick()) > 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les notificacions del temporitzador.
/// \param    sender: El temporitzadort que envia la noptificacio.
/// \param    args: Parametres de la notificacio.
///
void TickGenerator::tmrNotifyEventHandler(
	htl::tmr::TMRDevice *sender,
	htl::tmr::NotifyEventArgs &args) {

	if (args.id == htl::tmr::NotifyID::update)
		_tickCounter++;

	#ifdef DBG_Pin
	DBG_Pin::pInst->toggle();
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler() {

    TMRTick::interruptHandler();
}
