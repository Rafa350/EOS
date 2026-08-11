#include "HTL/htlTick.h"
#include "HTL/STM32/htlClock.h"
#include "HTL/STM32/htlTMR.h"
#include "HTL/STM32/htlINT.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::tick;


using DevTMR = HTL_TICK_TIMER;


TickGenerator TickGenerator::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
TickGenerator::TickGenerator():
	_tickCounter {0},
	_devTMR {DevTMR::pInst},
	_devTMR_NotificationEvent {*this, &TickGenerator::devTMR_NotificationEventHandler} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    frequency: Frequencia.
///
void TickGenerator::initialize(
    uint32_t frequency,
	uint32_t divider) {

	auto clk = htl::clock::ClockDevice::pInst;
	uint32_t prescaler = (clk->getClockFrequency(htl::clock::ClockID::pclk) / frequency) - 1;

	_devTMR->initialize(tmr::ClockDivider::_1, prescaler, divider, 0);
	_devTMR->enableNotificationEvent(_devTMR_NotificationEvent);

	enableInterruptVector(irq::VectorID::tmr14);
	setInterruptVectorPriority(irq::VectorID::tmr14, irq::Priority::p3);

	start();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void TickGenerator::deinitialize() {

    stop();

	_devTMR->disableNotificationEvent();

	disableInterruptVector(irq::VectorID::tmr14);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador.
///
void TickGenerator::start() {

    _devTMR->start_IRQ();
}


/// ----------------------------------------------------------------------
/// \brief    Para el contador.
///
void TickGenerator::stop() {

    _devTMR->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks
/// \return   El valor del contador
//
uint32_t TickGenerator::getTick() {

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
	uint32_t ticks) {

	auto lastTick = getTick() + ticks;
	while (static_cast<int>(lastTick - getTick()) > 0)
		continue;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona les notificacions del temporitzador.
/// \param    sender: El temporitzadort que envia la notificacio.
/// \param    args: Parametres de la notificacio.
///
void TickGenerator::devTMR_NotificationEventHandler(
	htl::tmr::TMRDevice *sender,
	htl::tmr::TMRDevice::NotificationEventArgs *args) {

	if (args->id == htl::tmr::TMRDevice::NotificationID::update)
		_tickCounter += 1;
}


/// ----------------------------------------------------------------------
/// \brief    Vector d'interrupcio
///
extern "C" void TIM14_IRQHandler(void) {

    DevTMR::interruptHandler();
}
