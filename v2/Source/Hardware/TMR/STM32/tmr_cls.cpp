module;


#include "HTL/htl.h"
#include "eosBits.h"
#include "eosEvents.h"
#include "eosResults.h"


export module Eos.Hardware.TMR.Classes;


import Eos.Types;
import Eos.Hardware.TMR.Identifiers;


export
namespace eos {
    namespace hardware {
        namespace tmr {

            class TMRDevice: private NonCopyableClass {
                public:
                    enum class CountDirection {
                        up,
                        down,
                        bidi
                    };

                    enum class CountResolution {
                        _16,
                        _32
                    };

                    /*enum class ClockSource {
                        pclk1,
                        pclk2,
                        pllqclk
                    };*/

                    enum class ClockDivider {
                        _1,
                        _2,
                        _4
                    };

                    enum class Channel {
                        ch1,
                        ch2,
                        ch3,
                        ch4
                    };

                    enum class ChannelPolarity {
                        activeHigh,
                        activeLow
                    };

                public:
                    enum class NotificationID {
                        null,
                        trigger,
                        update,
                        error
                    };
                    struct NotificationEventArgs {
                        NotificationID id;
                        bool isr;
                        union {
                            struct {
                            } trigger;
                            struct {
                            } update;
                        };
                    };
                    using NotificationEventRaiser = eos::EventRaiser<TMRDevice, NotificationEventArgs>;
                    using INotificationEvent = NotificationEventRaiser::IEvent;
                    template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

                    enum class State {
                        reset,
                        ready,
                        busy,
                        busyIRQ,
                        busyDMA
                    };

                private:
                    TIM_TypeDef * const _tim;
                    State _state;
                    NotificationEventRaiser _notificationEventRaiser;

                private:
                    void notifyTrigger();
                    void notifyUpdate();

                protected:
                    TMRDevice(TIM_TypeDef *tim);
                    virtual void activate() = 0;
                    virtual void deactivate() = 0;
                    void interruptService();
                    State getState() const { return _state; }

                public:
                    Result initialize(ClockDivider divider, unsigned prescaler) {
                        return initialize(divider, prescaler, 0, 0);
                    }
                    Result initialize(ClockDivider divider, unsigned prescaler, unsigned reload, unsigned repeat);
                    Result deinitialize();

                    Result setPrescaler(UInt32 value);
                    Result setLimit(UInt32 value);
                    Result setRepeat(UInt32 value);
                    Result setCountDirection(CountDirection value);
                    UInt32 getCounter() const { return _tim->CNT; }

                    Result configurePwmChannel(Channel channel, ChannelPolarity, UInt32 compare);
                    Result configurePwmChannel1(ChannelPolarity polarity, UInt32 compare);
                    Result configurePwmChannel2(ChannelPolarity polarity, UInt32 compare);
                    Result configurePwmChannel3(ChannelPolarity polarity, UInt32 compare);
                    Result configurePwmChannel4(ChannelPolarity polarity, UInt32 compare);

                    void enableChannel(Channel channel);
                    void disableChannel(Channel channel);

                    void enableNotificationEvent(INotificationEvent &event) {
                        _notificationEventRaiser.enable(event);
                    }
                    void disableNotificationEvent() {
                        _notificationEventRaiser.disable();
                    }
                    Result start();
                    Result start_IRQ();
                    Result stop();
            };
        }
    }
}


using namespace eos;
using namespace eos::hardware::tmr;


/// ----------------------------------------------------------------------
/// @brief    Constructor
/// @param    tim: Registres de hardware del dispositiu.
///
TMRDevice::TMRDevice(
	TIM_TypeDef *tim) :

	_tim {tim},
	_state {State::reset} {
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza el temporitzador.
/// @param    divider: Divisor del rellotge.
/// @param    prescaler: Valor del prescaler.
/// @param    reload: Valor de recarrega del contador.
/// @param    repeat: Valor de repeticio.
///
Result TMRDevice::initialize(
	ClockDivider divider,
	unsigned prescaler,
	unsigned reload,
	unsigned repeat) {

	if (!IS_TIM_CLOCK_DIVISION_INSTANCE(_tim) && divider != ClockDivider::_1)
		return eos::Result::ErrorCodes::errorParameter;

	if (!IS_TIM_REPETITION_COUNTER_INSTANCE(_tim) && repeat != 0)
		return eos::Result::ErrorCodes::errorParameter;

	if (_state == State::reset) {

		activate();

		// Inicialitza el timer.
		// -Para el contador (CEN = 0).
		// -Inicialitza ARR de forma in mediata (ARPE = 0).
		// -Inicilitza el divisor del rellotge.
		//
		auto CR1 = _tim->CR1;
		Bits::clear(CR1, TIM_CR1_CEN | TIM_CR1_ARPE);
		if (IS_TIM_CLOCK_DIVISION_INSTANCE(_tim)) {
			Bits::clear(CR1, TIM_CR1_CKD);
			switch (divider) {
				case ClockDivider::_1:
					break;

				case ClockDivider::_2:
					Bits::set(CR1, TIM_CR1_CKD_0);
					break;

				case ClockDivider::_4:
					Bits::set(CR1, TIM_CR1_CKD_1);
					break;
			}
		}
		Bits::set(CR1, TIM_CR1_DIR);
		Bits::set(CR1, 0UL << TIM_CR1_CMS_Pos);
		_tim->CR1 = CR1;

		_tim->PSC = prescaler;
		_tim->ARR = reload;
		if (IS_TIM_REPETITION_COUNTER_INSTANCE(_tim))
			_tim->RCR = repeat;

		_state = State::ready;

		return Result::ErrorCodes::ok;
	}

	else
		return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// @brief    Desinicialitza el timer.
/// @return   El rtresultat de l'operacio.
///
Result TMRDevice::deinitialize() {

	if (_state != State::ready)
		return Result::ErrorCodes::errorState;

	Bits::clear(_tim->CR1, TIM_CR1_CEN);
	Bits::clear(_tim->DIER, TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

	deactivate();

	_state = State::reset;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Canvia el valor del prescaler.
/// @param    value: El nou valor.
/// @return   El resultat de l'operacio.
/// @remarks  L'operacio nomes es valida si el dispositiu esta inicialitzat.
///
Result TMRDevice::setPrescaler(
	UInt32 value) {

	if (_state == State::reset)
		return Result::ErrorCodes::errorState;

	_tim->PSC = value;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Canvia el valor limit del contador.
/// @param    value: El nou valor.
/// @return   El resultat de l'operacio.
/// @remarks  L'operacio nomes es valida si el dispositiu esta inicialitzat.
///
Result TMRDevice::setLimit(
	UInt32 value) {

	if (_state == State::reset)
		return Result::ErrorCodes::errorState;

	else {
		if (_state == State::ready)
			Bits::clear(_tim->CR1, TIM_CR1_ARPE);
		else
			Bits::set(_tim->CR1, TIM_CR1_ARPE);
		_tim->ARR = value;

		return Result::ErrorCodes::ok;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Canvia el valor de repeticions.
/// @param    value: El nou valor.
/// @return   El resultat de l'operacio.
/// @remarks  L'operacio nomes es valida si el dispositiu esta inicialitzat.
///
Result TMRDevice::setRepeat(
	UInt32 value) {

	if (!IS_TIM_REPETITION_COUNTER_INSTANCE(_tim))
		return Result::ErrorCodes::errorUnsupported;

	if (_state == State::reset)
		return Result::ErrorCodes::errorState;

	_tim->RCR = value;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el canal especificat, per generar un senyal PWM
/// @param    channel: El canal.
/// @param    polarity: La polaritat.
/// @param    compare: El valor a comparar del contador
/// @return   El resultat de l'operacio.
///
Result TMRDevice::configurePwmChannel(
	Channel channel,
	ChannelPolarity polarity,
	UInt32 compare) {

	switch (channel) {
		case Channel::ch1:
			return configurePwmChannel1(polarity, compare);

		case Channel::ch2:
			return configurePwmChannel2(polarity, compare);

		case Channel::ch3:
			return configurePwmChannel3(polarity, compare);

		case Channel::ch4:
			return configurePwmChannel4(polarity, compare);
	}

	return Result::ErrorCodes::errorParameter;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el canal 1, per generar un senyal PWM
/// @param    polarity: La polaritat.
/// @param    compare: El valor a comparar del contador
/// @return   El resultat de l'operacio.
///
Result TMRDevice::configurePwmChannel1(
	ChannelPolarity polarity,
	UInt32 compare) {

	if (!IS_TIM_CC1_INSTANCE(_tim))
		return Result::ErrorCodes::errorUnsupported;

	if (_state != State::ready)
		return Result::ErrorCodes::errorState;

	UInt32 CCER = _tim->CCER;
	if (polarity == ChannelPolarity::activeHigh)
		CCER &= ~TIM_CCER_CC1P;
	else
		CCER |= TIM_CCER_CC1P;
	CCER &= ~TIM_CCER_CC1E;
	_tim->CCER = CCER;

	UInt32 CCMR = _tim->CCMR1;
	CCMR &= ~(TIM_CCMR1_OC1M_Msk | TIM_CCMR1_CC1S_Msk);
	CCMR |= 0b110 << TIM_CCMR1_OC1M_Pos;
	CCMR |= TIM_CCMR1_OC1PE;
	_tim->CCMR1 = CCMR;

	_tim->CCR1 = compare;

	return eos::Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el canal 2, per generar un senyal PWM
/// @param    polarity: La polaritat.
/// @param    compare: El valor a comparar del contador
/// @return   El resultat de l'operacio.
///
Result TMRDevice::configurePwmChannel2(
	ChannelPolarity polarity,
	UInt32 compare) {

	if (!IS_TIM_CC2_INSTANCE(_tim))
		return Result::ErrorCodes::errorUnsupported;

	if (_state != State::ready)
		return Result::ErrorCodes::errorState;

	UInt32 CCER = _tim->CCER;
	if (polarity == ChannelPolarity::activeHigh)
		CCER &= ~TIM_CCER_CC2P;
	else
		CCER |= TIM_CCER_CC2P;
	CCER &= ~TIM_CCER_CC2E;
	_tim->CCER = CCER;

	UInt32 CCMR = _tim->CCMR1;
	CCMR &= ~(TIM_CCMR1_OC2M_Msk | TIM_CCMR1_CC2S_Msk);
	CCMR |= 0b110 << TIM_CCMR1_OC2M_Pos;
	CCMR |= TIM_CCMR1_OC2PE;
	_tim->CCMR1 = CCMR;

	_tim->CCR2 = compare;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el canal 3, per generar un senyal PWM
/// @param    polarity: La polaritat.
/// @param    compare: El valor a comparar del contador
/// @return   El resultat de l'operacio.
///
eos::Result TMRDevice::configurePwmChannel3(
	ChannelPolarity polarity,
	UInt32 compare) {

	if (!IS_TIM_CC3_INSTANCE(_tim))
		return Result::ErrorCodes::errorUnsupported;

	if (_state != State::ready)
		return Result::ErrorCodes::errorState;

	unsigned CCER = _tim->CCER;
	if (polarity == ChannelPolarity::activeHigh)
		CCER &= ~TIM_CCER_CC3P;
	else
		CCER |= TIM_CCER_CC3P;
	CCER &= ~TIM_CCER_CC3E;
	_tim->CCER = CCER;

	unsigned CCMR = _tim->CCMR2;
	CCMR &= ~(TIM_CCMR2_OC3M_Msk | TIM_CCMR2_CC3S_Msk);
	CCMR |= 0b110 << TIM_CCMR2_OC3M_Pos;
	CCMR |= TIM_CCMR2_OC3PE;
	_tim->CCMR2 = CCMR;

	_tim->CCR3 = compare;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Configura el canal 4, per generar un senyal PWM
/// @param    polarity: La polaritat.
/// @param    compare: El valor a comparar del contador
/// @return   El resultat de l'operacio.
///
eos::Result TMRDevice::configurePwmChannel4(
	ChannelPolarity polarity,
	UInt32 compare) {

	if (!IS_TIM_CC4_INSTANCE(_tim))
		return Result::ErrorCodes::errorUnsupported;

	if (_state != State::ready)
		return Result::ErrorCodes::errorState;

	unsigned CCER = _tim->CCER;
	if (polarity == ChannelPolarity::activeHigh)
		CCER &= ~TIM_CCER_CC4P;
	else
		CCER |= TIM_CCER_CC4P;
	CCER &= ~TIM_CCER_CC4E;
	_tim->CCER = CCER;

	unsigned CCMR = _tim->CCMR2;
	CCMR &= ~(TIM_CCMR2_OC4M_Msk | TIM_CCMR2_CC4S_Msk);
	CCMR |= 0b110 << TIM_CCMR2_OC4M_Pos;
	CCMR |= TIM_CCMR2_OC4PE;
	_tim->CCMR2 = CCMR;

	_tim->CCR4 = compare;

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita un canal.
/// @param    channel: El canal.
///
void TMRDevice::enableChannel(
	Channel channel) {

	if (!IS_TIM_CC1_INSTANCE(_tim) && (channel == Channel::ch1))
		return;
	if (!IS_TIM_CC2_INSTANCE(_tim) && (channel == Channel::ch2))
		return;
	if (!IS_TIM_CC3_INSTANCE(_tim) && (channel == Channel::ch3))
		return;
	if (!IS_TIM_CC4_INSTANCE(_tim) && (channel == Channel::ch4))
		return;

	switch (channel) {
		case Channel::ch1:
			_tim->CCER |= TIM_CCER_CC1E;
			break;

		case Channel::ch2:
			_tim->CCER |= TIM_CCER_CC2E;
			break;

		case Channel::ch3:
			_tim->CCER |= TIM_CCER_CC3E;
			break;

		case Channel::ch4:
			_tim->CCER |= TIM_CCER_CC4E;
			break;
	}
}


/// ----------------------------------------------------------------------
/// @brief    desabilita un canal.
/// @param    channel: El canal.
///
void TMRDevice::disableChannel(
	Channel channel) {

	if (!IS_TIM_CC1_INSTANCE(_tim) && (channel == Channel::ch1))
		return;
	if (!IS_TIM_CC2_INSTANCE(_tim) && (channel == Channel::ch2))
		return;
	if (!IS_TIM_CC3_INSTANCE(_tim) && (channel == Channel::ch3))
		return;
	if (!IS_TIM_CC4_INSTANCE(_tim) && (channel == Channel::ch4))
		return;

	switch (channel) {
		case Channel::ch1:
			_tim->CCER &= ~TIM_CCER_CC1E;
			break;

		case Channel::ch2:
			_tim->CCER &= ~TIM_CCER_CC2E;
			break;

		case Channel::ch3:
			_tim->CCER &= ~TIM_CCER_CC3E;
			break;

		case Channel::ch4:
			_tim->CCER &= ~TIM_CCER_CC4E;
			break;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Inicia el contador en modus polling
/// @return   El resultat de l'operacio.
///
Result TMRDevice::start() {

	if (_state == State::ready) {

		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.
		_tim->CR1 |= TIM_CR1_CEN;   // Comença a contar.

		_state = State::busy;

		return eos::Result::ErrorCodes::ok;
	}
	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia el contador en modus interrupcio
/// @return   El resultat de l'operacio.
///
Result TMRDevice::start_IRQ() {

	if (_state == State::ready) {

		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.
		_tim->DIER |= TIM_DIER_UIE; // Habilita la interrupcio
		_tim->CR1 |= TIM_CR1_CEN;   // Comença a contar

		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Finalitza el contador en modus polling.
/// @return   El resultat de l'operacio.
///
Result TMRDevice::stop() {

	if ((_state == State::busy) || (_state == State::busyIRQ)) {

		if (_state == State::busyIRQ)
			_tim->DIER &= ~TIM_DIER_UIE;  // Deshabilita la interrupcio.

		_tim->CR1 &= ~TIM_CR1_CEN;  // Deixa de contar.
		_tim->SR &= ~TIM_SR_UIF;    // Borra el flag.

		_state = State::ready;

		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void TMRDevice::interruptService() {

	auto SR = _tim->SR;
	auto DIER = _tim->DIER;

	// Event TRIGGER
	//
	if ((SR & TIM_SR_TIF) && (DIER & TIM_DIER_TIE)) {
		_tim->SR &= ~TIM_SR_TIF;
		notifyTrigger();
	}

	// Event UPDATE
	//
	if ((SR & TIM_SR_UIF) && (DIER & TIM_DIER_UIE)) {
		_tim->SR &= ~TIM_SR_UIF;
		notifyUpdate();
	}

	// Event CAPTURE/COMPARE 1
	//
	if ((SR & TIM_SR_CC1IF) && (DIER & TIM_DIER_CC1IE)) {
		_tim->SR &= ~TIM_SR_CC1IF;
	}

	// Event CAPTURE/COMPARE 2
	//
	if ((SR & TIM_SR_CC2IF) && (DIER & TIM_DIER_CC2IE)) {
		_tim->SR &= ~TIM_SR_CC2IF;
	}

	// Event CAPTURE/COMPARE 3
	//
	if ((SR & TIM_SR_CC3IF) && (DIER & TIM_DIER_CC3IE)) {
		_tim->SR &= ~TIM_SR_CC3IF;
	}

	// Event CAPTURE/COMPARE 4
	//
	if ((SR & TIM_SR_CC4IF) && (DIER & TIM_DIER_CC4IE)) {
		_tim->SR &= ~TIM_SR_CC4IF;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio Trigger
///
void TMRDevice::notifyTrigger() {

	if (_notificationEventRaiser) {
		NotificationEventArgs args = {
			.id {NotificationID::trigger},
			.isr {true}
		};
		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio Update
///
void TMRDevice::notifyUpdate() {

	if (_notificationEventRaiser) {
		NotificationEventArgs args = {
			.id {NotificationID::update},
			.isr {true}
		};
		_notificationEventRaiser(this, &args);
	}
}
