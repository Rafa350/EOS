#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlINT.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::tick;
using namespace htl::irq;


using DevTMR = HTL_TICK_TIMER;
constexpr DevTMR *__devTMR = DevTMR::pInst;

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

	__devTMR->initBase(clkDiv, prescaler, period);
	__devTMR->setNotifyEvent(_tmrNotifyEvent, true);

	enableInterruptVector(irq::VectorID::tmr14);
	setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::_7);

	start();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void TickGenerator::deinitialize() {

    stop();

	__devTMR->disableNotifyEvent();

	disableInterruptVector(irq::VectorID::tmr14);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void TickGenerator::start() {

    __devTMR->start_IRQ();
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TickGenerator::stop() {

    __devTMR->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks
/// \return   El valor del contador
//
Tick TickGenerator::getTick() {

    disableInterrupts();
	auto tick = _tickCounter;
	enableInterrupts();

	return tick;
}


/// ----------------------------------------------------------------------
/// \brief    Espera un nombre determinat de ticks
/// \param    ticks: El nombre de tics
///
void TickGenerator::wait(
	Tick ticks) {

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

    __devTMR->interruptHandler();
}
