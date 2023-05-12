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
	_triggerEventCallback(nullptr),
	_updateEventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el timer.
///
void TMRDevice::initialize() {

	activate();

	_tim->CR1 &= ~TIM_CR1_CEN;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el timer.
///
void TMRDevice::deinitialize() {

	_tim->CR1 &= ~TIM_CR1_CEN;
	_tim->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

	deactivate();
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

	//if constexpr (HI::type != TMRType::basic) {
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
	//}
}


void TMRDevice::enableInterrupt(
	TMRInterrupt interrupt) {

	switch (interrupt) {
		case TMRInterrupt::update:
			_tim->DIER |= TIM_DIER_UIE;
			break;

		case TMRInterrupt::trigger:
			_tim->DIER |= TIM_DIER_TIE;
			break;

		case TMRInterrupt::com:
			_tim->DIER |= TIM_DIER_COMIE;
			break;

		default:
			break;
	}
}

bool TMRDevice::disableInterrupt(
	TMRInterrupt interrupt) {

	bool status = false;

	switch (interrupt) {
		case TMRInterrupt::update:
			status = (_tim->DIER & TIM_DIER_UIE) != 0;
			_tim->DIER &= ~TIM_DIER_UIE;
			break;

		case TMRInterrupt::trigger:
			status = (_tim->DIER & TIM_DIER_TIE) != 0;
			_tim->DIER &= ~TIM_DIER_TIE;
			break;

		case TMRInterrupt::com:
			status = (_tim->DIER & TIM_DIER_COMIE) != 0;
			_tim->DIER &= ~TIM_DIER_COMIE;
			break;
	}

	return status;
}


bool TMRDevice::isInterruptEnabled(
	TMRInterrupt interrupt) {

	bool status = false;

	switch (interrupt) {
		case TMRInterrupt::update:
			status = (_tim->DIER & TIM_DIER_UIE) != 0;
			break;

		case TMRInterrupt::trigger:
			status = (_tim->DIER & TIM_DIER_TIE) != 0;
			break;

		case TMRInterrupt::com:
			status = (_tim->DIER & TIM_DIER_COMIE) != 0;
			break;
	}

	return status;
}


bool TMRDevice::getFlag(
	TMRFlag flag) {

	switch (flag) {
		case TMRFlag::update:
			return (_tim->SR & TIM_SR_UIF) != 0;

		case TMRFlag::trigger:
			return (_tim->SR & TIM_SR_TIF) != 0;

		case TMRFlag::com:
			return (_tim->SR & TIM_SR_COMIF) != 0;

		default:
			return false;
	}
}


void TMRDevice::clearFlag(
	TMRFlag flag) {

	switch (flag) {
		case TMRFlag::update:
			_tim->SR &= ~TIM_SR_UIF;
			break;

		case TMRFlag::trigger:
			_tim->SR &= ~TIM_SR_TIF;
			break;

		case TMRFlag::com:
			_tim->SR &= ~TIM_SR_COMIF;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void TMRDevice::interruptService() {

	if ((_tim->SR & TIM_SR_TIF) && (_tim->DIER & TIM_DIER_TIE)) {
		_tim->SR &= ~TIM_SR_TIF;
		if (_triggerEventCallback != nullptr)
			_triggerEventCallback->execute(0);
	}

	if ((_tim->SR & TIM_SR_UIF) && (_tim->DIER & TIM_DIER_UIE)) {
		_tim->SR &= ~TIM_SR_UIF;
		if (_updateEventCallback != nullptr)
			_updateEventCallback->execute(0);
	}
}
