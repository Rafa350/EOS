#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlINT.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::tick;


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
    unsigned frequency) {

	unsigned limit = 1000;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	unsigned prescaler = (clock::getClockFrequency(clock::ClockID::pclk1) / frequency) - 1;
#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32G0)
	unsigned prescaler = (clock::getClockFrequency(clock::ClockID::pclk) / frequency) - 1;
#endif
	tmr::ClockDivider clkDiv = tmr::ClockDivider::_1;

	__devTMR->initialize(clkDiv, prescaler, limit, 0);
	__devTMR->setNotifyEvent(_tmrNotifyEvent, true);

	enableInterruptVector(irq::VectorID::tmr14);
	setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::p7);

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
unsigned TickGenerator::getTick() {

    //disableInterrupts();
	auto tick = _tickCounter;
	//enableInterrupts();

	return tick;
}


/// ----------------------------------------------------------------------
/// \brief    Espera un nombre determinat de ticks
/// \param    ticks: El nombre de tics
///
void TickGenerator::wait(
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
void TickGenerator::tmrNotifyEventHandler(
	htl::tmr::NotifyID id,
	htl::tmr::NotifyEventArgs * const args) {

	if (id == htl::tmr::NotifyID::update)
		_tickCounter += 1;

	#ifdef DBG_Pin
	DBG_Pin::pInst->toggle();
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler(void) {

    __devTMR->interruptHandler();
}
