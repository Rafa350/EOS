#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlINT.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::clock;
using namespace htl::tick;


using DevTMR = HTL_TICK_TIMER;
constexpr DevTMR *__devTMR = DevTMR::pInst;

TickGenerator TickGenerator::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
TickGenerator::TickGenerator():
	_tickCounter {0},
	_tmrNotificationEvent {*this, &TickGenerator::tmrNotificationEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    frequency: Frequencia.
///
void TickGenerator::initialize(
    unsigned frequency) {

	auto clk = ClockDevice::pInst;

	unsigned limit = 1000;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	unsigned prescaler = (clk->getClockFrequency(clock::ClockID::pclk1) / frequency) - 1;
#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32G0)
	unsigned prescaler = (clk->getClockFrequency(clock::ClockID::pclk) / frequency) - 1;
#endif
	tmr::ClockDivider clkDiv = tmr::ClockDivider::_1;

	__devTMR->initialize(clkDiv, prescaler, limit, 0);
	__devTMR->setNotificationEvent(_tmrNotificationEvent, true);

	enableInterruptVector(irq::VectorID::tmr14);
	setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::p3);

	start();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void TickGenerator::deinitialize() {

    stop();

	__devTMR->disableNotificationEvent();

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
void TickGenerator::tmrNotificationEventHandler(
	htl::tmr::TMRDevice * const sender,
	htl::tmr::NotificationEventArgs * const args) {

	if (args->id == htl::tmr::NotificationID::update)
		_tickCounter += 1;
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler(void) {

    __devTMR->interruptHandler();
}
