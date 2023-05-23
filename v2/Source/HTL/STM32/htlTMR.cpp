#include "HTL/htl.h"
#include "HTL/htlTMR.h"


using namespace htl::tmr;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    tim: Registres de hardware del dispositiu.
///
TMRDevice::TMRDevice(
	TIM_TypeDef *tim) :

	_tim(tim),
	_state(State::reset),
	_triggerEventCallback(nullptr),
	_updateEventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el timer.
///
TMRDevice::Result TMRDevice::initialize() {

	if (_state == State::reset) {

		activate();

		_tim->CR1 &= ~TIM_CR1_CEN;

		_state = State::ready;

		return Result::ok;
	}

	else
		return Result::error;

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


void TMRDevice::setDirection(
	CountDirection direction) {

	if (direction == CountDirection::down)
		_tim->CR1 |= TIM_CR1_DIR;
	else
		_tim->CR1 &= ~TIM_CR1_DIR;
}


void TMRDevice::setResolution(
	CountResolution resolution) {
}


void TMRDevice::setPeriod(
	uint32_t period) {

	_tim->ARR = period;
}


void TMRDevice::setPrescaler(
	uint32_t prescaler) {

	_tim->PSC = prescaler;
}


void TMRDevice::setClockDivider(
	ClockDivider clockDivider) {

	if (IS_TIM_CLOCK_DIVISION_INSTANCE(_tim) ) {
		uint32_t temp = _tim->CR1;
		temp &= ~TIM_CR1_CKD;
		switch (clockDivider) {
			case ClockDivider::_1:
				break;

			case ClockDivider::_2:
				temp |= TIM_CR1_CKD_0;
				break;

			case ClockDivider::_4:
				temp |= TIM_CR1_CKD_1;
				break;
		}
		_tim->CR1 = temp;
	}
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
		if (_triggerEventCallback != nullptr)
			_triggerEventCallback->execute(0);
	}

	// Event UPDATE
	//
	if ((_tim->SR & TIM_SR_UIF) && (_tim->DIER & TIM_DIER_UIE)) {
		_tim->SR &= ~TIM_SR_UIF;
		if (_updateEventCallback != nullptr)
			_updateEventCallback->execute(0);
	}
}
