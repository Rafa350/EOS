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
	_triggerCallback(nullptr) {

}


void TMRDevice::initialize() {

	activate();

	_tim->CR1 &= ~TIM_CR1_CEN;
}


void TMRDevice::deinitialize() {

	_tim->CR1 &= ~TIM_CR1_CEN;
	_tim->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

	deactivate();
}


void TMRDevice::setDirection(
	TMRDirection direction) {

	if (direction == TMRDirection::down)
		_tim->CR1 |= TIM_CR1_DIR;
	else
		_tim->CR1 &= ~TIM_CR1_DIR;
}

void TMRDevice::setResolution(
	TMRResolution resolution) {
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
	TMRClockDivider clockDivider) {

	//if constexpr (HI::type != TMRType::basic) {
		uint32_t temp = _tim->CR1;
		temp &= ~TIM_CR1_CKD;
		switch (clockDivider) {
			case TMRClockDivider::_1:
				break;

			case TMRClockDivider::_2:
				temp |= TIM_CR1_CKD_0;
				break;

			case TMRClockDivider::_4:
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
		if (_triggerCallback != nullptr)
			_triggerCallback->execute(0);
	}
}
