module;


#include "hardware.h"


module Eos.Hardware.UART.__CLASSES;


import Eos.Bits;
import Eos.Hardware.Atomic;


using namespace eos;
using namespace eos::hardware::uart;
using namespace eos::hardware::dma;


/// ----------------------------------------------------------------------
/// @brief    Transmiteix un bloc de dades utilitzant DMA.
/// @param    devDMA: Dispositiu DMA.
/// @param    buffer: Buffer de dades.
/// @param    length: El nombre de bytes a transmetre.
/// \return   El resultat de l'operacio
///
UARTDevice::Result UARTDevice::transmit_DMA(
    DMADevice *devDMA,
    const UInt8 *buffer,
    UInt32 length) {

    if (_state == State::ready) {

        _state = State::transmiting;

        _txBuffer = buffer;
        _txCount = 0;
        _txMaxCount = length;

        enable();
        enableTransmissionDMA();

        // Inicia la transferencia per DMA
        //
        devDMA->enableNotificationEvent(_dmaNotificationEvent);
        devDMA->start(buffer, (UInt8*)&(_usart->TDR), _txMaxCount);

        return ErrorCode::ok;
    }

    else if ((_state == State::transmiting) || (_state == State::receiving))
        return ErrorCode::busy;

    else
        return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Reb un bloc de dades utilitzan DMA.
/// @param    devDMA: El dispositiu DMA.
/// @param    buffer: El buffer de dades.
/// @param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
UARTDevice::Result UARTDevice::receive_DMA(
    DMADevice *devDMA,
    UInt8 *buffer,
    UInt32 bufferSize) {

	return ErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita la transmissio de dades en modus DMA
///
void UARTDevice::enableTransmissionDMA() const {

	//TODO: Comprovar si es necesari
	_usart->ICR = USART_ICR_TCCF;  // Borra el flag TC

	auto a = Atomic::start();

	Bits::set(_usart->CR1,
    	USART_CR1_TE);            // Habilita transmissio
	Bits::set(_usart->CR3,
    	USART_CR3_DMAT);          // Habilita DMA

    Atomic::end(a);
}


/// ----------------------------------------------------------------------
/// @brief    Reb les notificacions del DMA
/// @param    sender: El dispositiu DMA que genera l'event.
/// @param    args: Parametres del event.
///
void UARTDevice::dmaNotificationEventHandler(
	DMADevice *sender,
	DMADevice::NotificationEventArgs *args) {

    switch (args->id) {

        // Transmissio complerta de tots els bytes.
        //
        case DMADevice::NotificationID::completed: {
            _txCount = _txMaxCount;
            _usart->ICR = USART_ICR_TCCF;
            auto a = Atomic::start();
            Bits::set(_usart->CR1, USART_CR1_TCIE);
            Atomic::end(a);
            sender->disableNotificationEvent();
            break;
        }

        // Error en la transmissio DMA.
        //
        case DMADevice::NotificationID::error:
            break;

        default:
        	break;
    }
}
