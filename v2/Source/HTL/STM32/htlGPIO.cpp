#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/htlAtomic.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::gpio;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres hardware del modul GPIO.
///
PortDevice::PortDevice(
	GPIO_TypeDef *gpio):

	_gpio {gpio} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrades.
/// \param    mask: Mascara de pins a configurar.
/// \param    pupd: Resistencies pull up/down.
///
void PortDevice::initInput(
	PinMask mask,
	PullUpDown pupd) const {

	activate(mask);
	htl::gpio::initInput(_gpio, mask, pupd);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    type: El tipus de sortida.
/// \param    pupd: Resistencies pull up/down.
/// \param    speed: Opcions de velocitat.
///
void PortDevice::initOutput(
	PinMask mask,
	OutputType type,
	PullUpDown pupd,
	Speed speed) const {

	activate(mask);
	htl::gpio::initOutput(_gpio, mask, type, pupd, speed, false);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
#if HTL_GPIO_OPTION_DEACTIVATE == 1
void PortDevice::deinitialize() const {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    params: Parametres d'inicialitzacio.
///
void PinDevice::initialize(
    const InitParams &params) const {

    switch(params.mode) {
        case InitMode::input:
            initInput(params.input.pupd);
            break;

        case InitMode::output:
        	initOutput(params.output.type, params.output.pupd,
        		params.output.speed, params.output.state);
            break;

        case InitMode::alternate:
        	initAlternate(params.alternate.type, params.alternate.pupd,
        		params.alternate.speed, params.alternate.function);
            break;

        case InitMode::analogic:
        	initAnalogic();
            break;
    }
}
