#include "eos.h"
#include "Controllers/Motor/Drivers/STSPIN840/eosDevice_STSPIN840.h"
#include "HTL/STM32/htlClock.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    tmr: El temporitzador per generar el senyal PWM.
/// \param    channel: El canal de sortida del senyal PWM.
/// \param    pinSTBY: El pin del senyal STBY
/// \param    pinPH: El pin del senyal PH
/// \param    pinEF: El pin del senyal EF
///
STSPIN840_Device::STSPIN840_Device(
	TmrDev *tmr,
	TmrChannel channel,
	Pin *pinSTBY,
	Pin *pinPH,
	Pin *pinEF):

	_tmr {tmr},
	_channel {channel},
	_pinSTBY {pinSTBY},
	_pinPH {pinPH},
	_pinEF {pinEF} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    frequency: Frequencia del senyal PWM.
///
void STSPIN840_Device::initialize(
	unsigned frequency) {

	// Inicialitza el pin EF
	//
	_pinEF->initOutput(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::medium, false);

	// Inicialitza el pin PH
	//
	_pinPH->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none,  gpio::Speed::medium, false);

	// Inicialitza el pin STANDBY/RESET
	//
	_pinSTBY->initOutput(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::medium, false);

	// Inicialitza el timer per la generacio del senyal PWM
	//
	auto clk = clock::ClockDevice::pInst;
	_reload = (clk->getClockFrequency(clock::ClockID::pclk) / (_prescaler * frequency)) - 1;
	_tmr->initialize(htl::tmr::ClockDivider::_1, _prescaler - 1, _reload, 0);
}


void STSPIN840_Device::deinitialize() {

}


void STSPIN840_Device::enable() {

	// Reconfigura el pin EF com entrada
	//
	_pinEF->set();
	_pinEF->initInput(gpio::PullUpDown::up);

	_pinSTBY->set();
}


void STSPIN840_Device::disable() {

	_pinSTBY->clear();

	// Reconfigura el pin EF com sortida
	//
	__disable_irq();
	_pinEF->initOutput(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::medium, false);
	__enable_irq();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el sentiti de rotacio del motor.
/// \param    direction: La direccio de rotacio.
///
void STSPIN840_Device::setDirection(
	Direction dir) {

	_pinPH->write(dir == Direction::backward);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la generacio del senyal PWM.
/// \param    duty: El duty cycle del senay PWM. de 0 a 100
///
void STSPIN840_Device::pwmStart(
	unsigned duty) {

	if (duty > 100)
		duty = 100;
	unsigned compare = (_reload * duty) / 100;

	_tmr->configurePwmChannel(_channel, htl::tmr::ChannelPolarity::activeHigh, compare);
	_tmr->enableChannel(_channel);
	_tmr->start();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la generacio del senyal PWM.
///
void STSPIN840_Device::pwmStop() {

	_tmr->disableChannel(_channel);
	_tmr->stop();
}


