module;


#include "hardware.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Types;
import Eos.Hardware.Atomic;
import Eos.Hardware.Clock;
import Eos.Hardware.DMA;
import Eos.System.Core.Ticks;


using namespace eos;
using namespace eos::hardware::uart;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    usartAddr: Adressa dels registres USART.
///
UARTDevice::UARTDevice(
	UInt32 usartAddr):

	_usart {reinterpret_cast<USART_TypeDef*>(usartAddr)},
	_state {State::reset},
	_dmaNotificationEvent {*this, &UARTDevice::dmaNotificationEventHandler}
{
}


/// ----------------------------------------------------------------------
/// @brief    Habilita el dispositiu.
///
void UARTDevice::enable() const {

	Bits::set(_usart->CR1,
		USART_CR1_UE);  // Habilita el dispositiu
}


/// ----------------------------------------------------------------------
/// @brief    Desabilita el dispositiu.
///
void UARTDevice::disable() const {

	Bits::clear(_usart->CR1,
		USART_CR1_UE |  // Desabilita el dispositiu
		USART_CR1_TE |  // Desabilita la transmissio
		USART_CR1_RE);  // Deshabilita la recepcio
}
