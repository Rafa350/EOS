#include "HTL/htl.h"
#include "HTL/htlTMR.h"


using namespace htl::tmr;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    tim: Registres de hardware del dispositiu.
///
TMRDevice::TMRDevice(
	TIM_TypeDef *tim) :

	_tim {tim},
	_state {State::reset},
	_notifyEvent {nullptr},
	_notifyEventEnabled {false}{

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el temporitzador en modus base de temps
/// \param    clkDiv: Divisor del rellotge.
/// \param    prescaler: Valor del prescaler.
/// \param    period: Periode.
/// \param    repeat: Contador de repeticions del event 'update'.
///
TMRDevice::Result TMRDevice::initBase(
	ClockDivider clkDiv,
	uint32_t prescaler,
	uint32_t period,
	uint32_t repeat) {

	if (!IS_TIM_CLOCK_DIVISION_INSTANCE(_tim) && clkDiv != ClockDivider::_1)
		return Result::error;

	if (!IS_TIM_REPETITION_COUNTER_INSTANCE(_tim) && repeat != 0)
		return Result::error;

	if (_state != State::reset)
		return Result::error;

	// Activa el dispositiu
	//
	activate();

	// Inicialitza el timer.
	// -Para el contador (CEN = 0).
	// -Inicialitza ARR de forma in mediata (ARPE = 0).
	// -Inicilitza el divisor del rellotge.
	//
	uint32_t cr1 = _tim->CR1;
	cr1 &= ~(TIM_CR1_CEN | TIM_CR1_ARPE);
	if (IS_TIM_CLOCK_DIVISION_INSTANCE(_tim)) {
		cr1 &= ~TIM_CR1_CKD;
		switch (clkDiv) {
			case ClockDivider::_1:
				break;

			case ClockDivider::_2:
				cr1 |= TIM_CR1_CKD_0;
				break;

			case ClockDivider::_4:
				cr1 |= TIM_CR1_CKD_1;
				break;
		}
	}
	_tim->CR1 = cr1;

	// Configura la base de temps
	//
	_tim->ARR = period;
	_tim->PSC = prescaler;

	// Configura cada quant es genere un event 'update'
	//
	if (IS_TIM_REPETITION_COUNTER_INSTANCE(_tim))
		_tim->RCR = repeat;

	_state = State::ready;

	return Result::ok;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el temporitzador en modus generador PWM
/// \param    prescaler: Valor del prescaler.
/// \param    period: Periode.
/// \param    duty: Duty
///
TMRDevice::Result TMRDevice::initPWM(
	ClockDivider clkDiv,
	uint32_t prescaler,
	uint32_t period,
	uint32_t duty) {

	if (initBase(clkDiv, prescaler, period) != Result::ok)
		return Result::error;

	return Result::ok;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el timer.
///
TMRDevice::Result TMRDevice::deinitialize() {

	if (_state == State::ready) {

		_tim->CR1 &= ~TIM_CR1_CEN;
		_tim->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

		deactivate();

		_state = State::reset;

		return Result::ok;
	}

	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Canvia el periode del temporitzador.
/// \param    period: El nou valor del periode.
/// \param    immediate: True si el canvi es inmediat.
///
void TMRDevice::setPeriod(
	uint32_t period,
	bool immediate) {

	if (immediate)
		_tim->CR1 &= ~TIM_CR1_ARPE;
	else
		_tim->CR1 |= TIM_CR1_ARPE;
	_tim->ARR = period;
}


void TMRDevice::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

	_notifyEvent = &event;
	_notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador en modus polling
///
TMRDevice::Result TMRDevice::start() {

	if (_state == State::ready) {

		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.
		_tim->CR1 |= TIM_CR1_CEN;   // Comença a contar.

		_state = State::busy;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el contador en modus interrupcio
///
TMRDevice::Result TMRDevice::startInterrupt() {

	if (_state == State::ready) {

		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.
		_tim->DIER |= TIM_DIER_UIE; // Habilita la interrupcio
		_tim->CR1 |= TIM_CR1_CEN;   // Comença a contar

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el contador en modus polling.
///
TMRDevice::Result TMRDevice::stop() {

	if (_state == State::busy) {

		_tim->CR1 &= ~TIM_CR1_CEN;  // Deixa de contar.
		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.

		_state = State::ready;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el contador en modus interrupcio.
///
TMRDevice::Result TMRDevice::stopInterrupt() {

	if (_state == State::busy) {

		_tim->CR1 &= ~TIM_CR1_CEN;    // Deixa de contar
		_tim->DIER &= ~TIM_DIER_UIE;  // Deshabilita la interrupcio.
		_tim->SR &= ~TIM_SR_UIF;      // Borra el flag.

		_state = State::ready;

		return Result::ok;
	}
	else
		return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void TMRDevice::interruptService() {

	// Event TRIGGER
	//
	if ((_tim->SR & TIM_SR_TIF) && (_tim->DIER & TIM_DIER_TIE)) {
		_tim->SR &= ~TIM_SR_TIF;
		notifyTrigger();
	}

	// Event UPDATE
	//
	if ((_tim->SR & TIM_SR_UIF) && (_tim->DIER & TIM_DIER_UIE)) {
		_tim->SR &= ~TIM_SR_UIF;
		notifyUpdate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Llasça un event de notificacio Trigger
///
void TMRDevice::notifyTrigger() {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::trigger,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Llasça un event de notificacio Update
///
void TMRDevice::notifyUpdate() {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::update,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}
