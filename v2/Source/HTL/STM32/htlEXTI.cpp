#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlGPIO.h"


using namespace eos;
using namespace htl;
using namespace htl::exti;


EXTIDevice EXTIDevice::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
EXTIDevice::EXTIDevice() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza una linia d'interrupcio asignada al GPIO
/// \param    portID: Identificador del port GPIO.
/// \param    pinID: Identificador del pin GPIO.
/// \param    mode: El modus.
/// \param    edge: El flanc.
///
void EXTIDevice::initGPIO(
	gpio::PortID portID,
	gpio::PinID pinID,
	Mode mode,
	Edge edge) {

	LineID lineID = (LineID) pinID;

	setPort(lineID, portID);
	setMode(lineID, mode);
	setEdge(lineID, edge);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void EXTIDevice::deinitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna un port a una linia d'interrupcio externa
///
void EXTIDevice::setPort(
	LineID lineID,
	gpio::PortID portID) {

#if defined(EOS_PLATFORM_STM32G0)

	uint32_t lineNum = (uint32_t) lineID;

	/// Asigna el port GPIO a la linia EXTI
	//
	uint32_t tmp = EXTI->EXTICR[lineNum >> 2];
	tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03)));
	tmp |= ((uint32_t)portID << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03)));
	EXTI->EXTICR[lineNum >> 2] = tmp;

#else
	#error "Unknown platform"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna modus a una linia d'interrupcio externa
/// \param    lineID: Idenfificador de la linia.
/// \param    mode: El modus.
///
void EXTIDevice::setMode(
	LineID lineID,
	Mode mode) {

	uint32_t mask = 1 << ((uint32_t) lineID);

#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == Mode::interrupt) || (mode == Mode::all))
		bits::set(EXTI->IMR1, mask);
	else
		bits::clear(EXTI->IMR1, mask);

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == Mode::event) || (mode == Mode::all))
		bits::set(EXTI->EMR1, mask);
	else
		bits::clear(EXTI->EMR1, mask);

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
		EXTI->IMR |= 1 << uint32_t(line_);
	else
		EXTI->IMR &= ~(1 << uint32_t(line_));

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
		EXTI->EMR |= 1 << uint32_t(line_);
	else
		EXTI->EMR &= ~(1 << uint32_t(line_));

#else
	#error "Unknown platform"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el flanc a una linia d'interrupcio externa
/// \param    lineID: Idenfificador de la linia.
/// \param    edge: El flanc.
///
void EXTIDevice::setEdge(
	LineID lineID,
	Edge edge) {

	uint32_t mask = 1 << ((uint32_t) lineID);

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rissing) || (edge == Edge::all))
		bits::set(EXTI->RTSR1, mask);
	else
		bits::clear(EXTI->RTSR1, mask);

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		bits::set(EXTI->FTSR1, mask);
	else
		bits::clear(EXTI->FTSR1, mask);

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
		EXTI->RTSR |= 1 << uint32_t(line_);
	else
		EXTI->RTSR &= ~(1 << uint32_t(line_));

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
		EXTI->FTSR |= 1 << uint32_t(line_);
	else
		EXTI->FTSR &= ~(1 << uint32_t(line_));

#else
	#error "Unknown platform"
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el event de notificacio.
/// \param    event: L'event.
/// \param    enabled: True per habilitar l'event.
/// \return   El resultat de l'operacio.
///
eos::Result EXTIDevice::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

   	_erNotify.set(event, enabled);
   	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void EXTIDevice::interruptService() {

	// Gestiona els events dels pins GPIO
	//
	auto fmask = EXTI->FPR1 & 0x0000FFFF;
	auto rmask = EXTI->RPR1 & 0x0000FFFF;
	if ((fmask | rmask) != 0) {

		if (_erNotify.isEnabled()) {

			NotifyEventArgs args = {
				.id {NotifyID::pinEdge},
				.irq {true},
				.pinEdge {
					.falling {(uint16_t)fmask},
					.rissing {(uint16_t)rmask}
				}
			};

			_erNotify(this, &args);
		}

		EXTI->FPR1 = fmask; // Borra els flags
		EXTI->RPR1 = rmask; // Borra els flags
	}
}
