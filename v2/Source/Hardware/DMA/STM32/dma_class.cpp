module;


#include "HTL/htl.h"
#include "eosEvents.h"


export module Eos.Hardware.DMA.__CLASSES;


import Eos.Bits;
import Eos.Hardware.DMA.__PLATFORM_TRAITS;
import Eos.Result;
import Eos.System.Core.Ticks;
import Eos.Types;


export namespace eos::hardware::dma {

    class DMADevice: private NonCopyableClass {
        public:
            enum class RequestID {
                i2c1RX = 10,
                i2c1TX = 11,
                i2c2TX = 12,
                i2c2RX = 13,
                spi1RX = 16,
                spi1TX = 17,
                spi2RX = 18,
                spi2TX = 19,
                uart1RX = 50,
                uart1TX = 51,
                uart2RX = 52,
                uart2TX = 53,
                uart3RX = 54,
                uart3TX = 55,
                uart4RX = 56,
                uart4TX = 57,
                uart5RX = 74,
                uart5TX = 75,
                uart6RX = 76,
                uart6TX = 77
            };

            enum class TransferMode {
                normal,
                circular
            };

            enum class DataSize {
                byte,
                word,
                qword
            };

            enum class AddressIncrement {
                none,
                inc
            };

            enum class Priority {
                low,
                medium,
                hight,
                veryHight
            };

            enum class NotificationID {
                null,
                half,
                completed,
                error
            };
            struct NotificationEventArgs {
                NotificationID id;
                bool irq;
            };
            using NotificationEventRaiser = EventRaiser<DMADevice, NotificationEventArgs>;
            using INotificationEvent = NotificationEventRaiser::IEvent;
            template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

            enum class State {
                reset,
                ready,
                transfering
            };

            enum class ErrorCode {
                ok,
                timeout,
                error,
                errorParam,
                errorState
            };
            using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;

        private:
            DMA_TypeDef * const _dma;
            DMA_Channel_TypeDef * const _dmaChannel;
            DMAMUX_ChannelStatus_TypeDef * const _muxChannelStatus;
            DMAMUX_Channel_TypeDef * const _muxChannel;
            UInt32 const _dmaChannelNumber;
            UInt32 const _muxChannelNumber;
            State _state;
            NotificationEventRaiser _notificationEventRaiser;

        private:
            void notifyTransferCompleted(bool irq);
            void notifyHalfTransfer(bool irq);

            void activate() const;
            void deactivate() const;

        private:
            void enable();
            void disable();
            void enableTransferCompleteInterrupt();
            void enableHalfTransferInterrupt();
            void enableTransferErrorInterrupt();
            void disableAllInterrupts();
            bool isTransferCompleteInterruptEnabled();
            bool isHalfTransferInterruptEnabled();
            bool isTransferErrorInterruptEnabled();
            bool isTransferCompleteFlagSet();
            bool isHalfTransferFlagSet();
            bool isTransferErrorFlagSet();
            void clearTransferCompleteFlag();
            void clearHalfTransferFlag();
            void clearAllFlags();

        protected:
            DMADevice(UInt32 dmaAddr, UInt32 dmaChannelAddr, UInt32 muxChannelStatusAddr, UInt32 muxChannelAddr);

            void interruptService();

            virtual void activateImpl() const = 0;
            virtual void deactivateImpl() const = 0;

        public:
            Result initMemoryToMemory();
            Result initMemoryToPeripheral(Priority priority,
                    DataSize srcSize, DataSize dstSize,
                    AddressIncrement srcInc, AddressIncrement dstInc,
                    TransferMode mode, RequestID requestID);
            Result initPeripheralToMemory(Priority priority,
                    DataSize srcSize, DataSize dstSize,
                    AddressIncrement srcInc, AddressIncrement dstInc,
                    TransferMode mode, RequestID requestID);
            Result deinitialize();

            void enableNotificationEvent(INotificationEvent &event) {
                _notificationEventRaiser.enable(event);
            }
            void disableNotificationEvent() {
                _notificationEventRaiser.disable();
            }

            Result start(const UInt8 *src, UInt8 *dst, UInt32 size);

            // TODO: temporal
            Result waitForFinish(Ticks blockTime);

            State getState() const { return _state; }
            bool isReady() const { return _state == State::ready; }
    };
}


using namespace eos;
using namespace eos::hardware::dma;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    dmaAddr: Adressa dels registres DMA.
/// @param    dmaChannelAddr: Adressa dels registres del canal DMA.
/// @param    muxChannelStatusAddr: Adressa dels registres d'estat de canal del DMAMUX
/// @param    muxChannelAddr: Adressa dels registres de canal del DMAMUX.
///
DMADevice::DMADevice(
    UInt32 dmaAddr,
    UInt32 dmaChannelAddr,
    UInt32 muxChannelStatusAddr,
    UInt32 muxChannelAddr) :

    _dma {reinterpret_cast<DMA_TypeDef*>(dmaAddr)},
    _dmaChannel {reinterpret_cast<DMA_Channel_TypeDef*>(dmaChannelAddr)},
    _muxChannelStatus {reinterpret_cast<DMAMUX_ChannelStatus_TypeDef*>(muxChannelStatusAddr)},
    _muxChannel {reinterpret_cast<DMAMUX_Channel_TypeDef*>(muxChannelAddr)},
    _dmaChannelNumber {((dmaChannelAddr - sizeof(DMA_TypeDef)) & 0x1C) >> 2},
    _muxChannelNumber {(muxChannelAddr & 0x3C) >> 2},
	_state {State::reset} {
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitzacio per transferencies de memoria a memoria.
/// @return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::initMemoryToMemory() {

	if (_state == State::reset) {

        // Activa el dispositiu amb el canal desactivat.
        //
        activate();
        disable();

		auto CCR = _dmaChannel->CCR;
		Bits::clear(CCR, DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
				DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
				DMA_CCR_EN);
		Bits::set(CCR, DMA_CCR_MEM2MEM);      // Memoria a memoria
		_dmaChannel->CCR = CCR;

		return ErrorCode::ok;
	}
	else
		return ErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitzacio en modus transferencia de memoria a periferic.
/// @param    priority: Prioritat.
/// @param    srcSize: Tamany de les dades del origen.
/// @param    dstSize: Tamany de les dades del desti.
/// @param    srcInc: Increment de l'adresa del origen.
/// @param    dstInc: Increment de l'adressa del desti.
/// @param    mode: Tipus de transferencia normal/circular.
/// @param    requestID: Identificador de la solicitut
/// @return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::initMemoryToPeripheral(
    Priority priority,
    DataSize srcSize,
    DataSize dstSize,
    AddressIncrement srcInc,
    AddressIncrement dstInc,
    TransferMode mode,
    RequestID requestID) {

    if (_state == State::reset) {

        uint32_t tmp;

        // Activa el dispositiu amb el canal desactivat.
        //
        activate();
        disable();

        tmp = _dmaChannel->CCR;

        // Transferencia de memoria a periferic
        //
        Bits::clear(tmp, DMA_CCR_DIR | DMA_CCR_MEM2MEM);
        Bits::set(tmp, 1UL << DMA_CCR_DIR_Pos);

        // Selecciona el modus de transferencia
        //
        tmp &= ~DMA_CCR_CIRC_Msk;
        if (mode == TransferMode::circular)
        	Bits::set(tmp, 1UL << DMA_CCR_CIRC_Pos);

        // Selecciona la prioritat
        //
        Bits::clear(tmp, DMA_CCR_PL);
        Bits::set(tmp, ((uint32_t)priority << DMA_CCR_PL_Pos) & DMA_CCR_PL_Msk);

        // Parametres de access a la memoria
        //
        tmp &= ~DMA_CCR_MINC_Msk;
        if (srcInc == AddressIncrement::inc)
            tmp |= 1 << DMA_CCR_MINC_Pos;
        tmp &= ~DMA_CCR_MSIZE_Msk;
        tmp |= (uint32_t(srcSize) << DMA_CCR_MSIZE_Pos) & DMA_CCR_MSIZE_Msk;

        // Parametres d'acces al periferic
        //
        tmp &= ~DMA_CCR_PINC_Msk;
        if (dstInc == AddressIncrement::inc)
            tmp |= 1 << DMA_CCR_PINC_Pos;
        tmp &= ~DMA_CCR_PSIZE_Msk;
        tmp |= (uint32_t(dstSize) << DMA_CCR_PSIZE_Pos) & DMA_CCR_PSIZE_Msk;

        // Desactiva les interrupcions del canal
        //
        tmp &= ~(DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);

        _dmaChannel->CCR = tmp;

        // Borra els flags d'interrupcio del canal
        //
        clearAllFlags();

        // Selecciona el dispositiu de fa la solicitut DMA
        //
        tmp = _muxChannel->CCR;
        Bits::clear(tmp, DMAMUX_CxCR_DMAREQ_ID);
        Bits::set(tmp, (uint32_t(requestID) << DMAMUX_CxCR_DMAREQ_ID_Pos));
        _muxChannel->CCR = tmp;

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return ErrorCode::ok;
    }

    else
        return ErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::deinitialize() {

    // Comprova si l'estat es 'ready'
    //
    if (_state == State::ready) {

        _notificationEventRaiser.disable();

        // Deshabilita el canal.
        //
        disable();
        disableAllInterrupts();

        // Desactiva el dispositiu.
        //
        deactivate();

        // Canvia l'estat a 'reset'
        //
        _state = State::reset;

        return ErrorCode::ok;
    }
    else
        return ErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
///
void DMADevice::activate() const {

    activateImpl();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
///
void DMADevice::deactivate() const {

    activateImpl();
}


/// ---------------------------------------------------------------------------
/// @brief    Inicia la transferencia.
/// @param    startAddr: Adressa inicial.
/// @param    dstAddr: Adressa final;
/// @param    size: El nombre de bytes a transfderir.
/// @return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::start(
    const UInt8 *src,
    UInt8 *dst,
    UInt32 size) {

    // Comprova si l'estat es 'ready'
    //
    if (_state == State::ready) {

        // Comprova si es una transferencua de memoria a periferic
        //
        if (((_dmaChannel->CCR & DMA_CCR_MEM2MEM) == 0) &&
            ((_dmaChannel->CCR & DMA_CCR_DIR) != 0)) {

            // Inicialitza els parametres de la transferencia
            //
            _dmaChannel->CMAR = reinterpret_cast<UInt32>(src);
            _dmaChannel->CPAR = reinterpret_cast<UInt32>(dst);
            _dmaChannel->CNDTR = size;
        }

        enableTransferCompleteInterrupt();
        enable();

        // A partir d'aqui, el DMA esta a l'espera de les solicituts
        // de transferencia.

        // Canvia l'estat a 'transfering'
        //
        _state = State::transfering;

        return ErrorCode::ok;
    }
    else
        return ErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Espera que finalitzi la transferencia.
/// @param    timeout: Limit de temps.
/// @return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::waitForFinish(
    Ticks blockTime) {

    // Comprova si l'estat es 'transfering'
    //
    if (_state == State::transfering) {

        // Espera flag TCIF o TEIF del canal
        //
        auto expired = false;
        auto expirationTime = Ticks::now() + blockTime;
        auto mask = (DMA_ISR_TCIF1 | DMA_ISR_TEIF1) << (_dmaChannelNumber * 4);
        while (((_dma->ISR & mask) == 0) &&
                !expired) {
            expired = expirationTime.hasExpiredNow();
        }

        // Borra els flags d'interrupcio del canal
        //
        clearAllFlags();

        // Deshabilita el canal
        //
        disable();

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return expired ? ErrorCode::timeout : ErrorCode::ok;
    }

    else
        return ErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void DMADevice::interruptService() {

    // Comprova si es una interrupcio TC (Transfer Complete)
    //
    if (isTransferCompleteInterruptEnabled() &&
        isTransferCompleteFlagSet()) {

        clearTransferCompleteFlag();
        disable();
        notifyTransferCompleted(true);

        _state = State::ready;
    }

    // Comprova si es una interrupcio HT (Half Transfer)
    //
    if (isHalfTransferInterruptEnabled() &&
        isHalfTransferFlagSet()) {

        clearHalfTransferFlag();
        notifyHalfTransfer(true);
    }

    // Comprova si es una interrupcio TE (Transfer Error)
    //
    if (isTransferErrorInterruptEnabled() &&
        isTransferErrorFlagSet()) {

        clearAllFlags();
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Notifica que s'ha completat la transferencia.
/// @param    irq: True si la notificacio ve d'una interrupcio.
///
void DMADevice::notifyTransferCompleted(
    bool irq) {

    if (_notificationEventRaiser) {

        NotificationEventArgs args = {
            .id = NotificationID::completed,
            .irq = irq
        };

        _notificationEventRaiser(this, &args);
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Notifica que s'ha completat la mitat de la transferencia.
/// @param    irq: True si la notificacio ve d'una interrupcio.
///
void DMADevice::notifyHalfTransfer(
    bool irq) {

    if (_notificationEventRaiser) {

        NotificationEventArgs args = {
            .id = NotificationID::half,
            .irq = irq
        };

        _notificationEventRaiser(this, &args);
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita la interrrupcio TC
///
void DMADevice::enableTransferCompleteInterrupt() {

	Bits::set(_dmaChannel->CCR, DMA_CCR_TCIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita la interrrupcio HT
///
void DMADevice::enableHalfTransferInterrupt() {

	Bits::set(_dmaChannel->CCR, DMA_CCR_HTIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita la interrrupcio TE
///
void DMADevice::enableTransferErrorInterrupt() {

	Bits::set(_dmaChannel->CCR, DMA_CCR_TEIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Deshabilita totes les interrupcions.
///
void DMADevice::disableAllInterrupts() {

	Bits::clear(_dmaChannel->CCR, DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la interrupcio TC esta habilitada.
/// @return   True si esta habilitada.
///
bool DMADevice::isTransferCompleteInterruptEnabled() {

    return Bits::isSet(_dmaChannel->CCR, DMA_CCR_TCIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la interrupcio HT esta habilitada.
/// @return   True si esta habilitada.
///
bool DMADevice::isHalfTransferInterruptEnabled() {

    return Bits::isSet(_dmaChannel->CCR, DMA_CCR_HTIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la interrupcio TE esta habilitada.
/// @return   True si esta habilitada.
///
bool DMADevice::isTransferErrorInterruptEnabled() {

    return Bits::isSet(_dmaChannel->CCR, DMA_CCR_TEIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el flag TC esta actiu.
/// @return   True si esta actiu.
///
bool DMADevice::isTransferCompleteFlagSet() {

    auto mask = DMA_ISR_TCIF1 << (_dmaChannelNumber * 4);
    return Bits::isSet(_dma->ISR, mask);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el flag HT esta actiu.
/// @return   True si esta actiu.
///
bool DMADevice::isHalfTransferFlagSet() {

    auto mask = DMA_ISR_HTIF1 << (_dmaChannelNumber * 4);
    return Bits::isSet(_dma->ISR, mask);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el flag TH esta actiu.
/// @param    channel: El numero de canal.
/// @return   True si esta actiu.
///
bool DMADevice::isTransferErrorFlagSet() {

    auto mask = DMA_ISR_TEIF1 << (_dmaChannelNumber * 4);
    return Bits::isSet(_dma->ISR, mask);
}


/// ---------------------------------------------------------------------------
/// @brief    Borra el flag TC
/// @param    channel: El numero de canal.
///
void DMADevice::clearTransferCompleteFlag() {

    _dma->IFCR = DMA_IFCR_CTCIF1 << (_dmaChannelNumber * 4);
}


/// ---------------------------------------------------------------------------
/// @brief    Borra el flag HT
/// @param    channel: El numero de canal.
///
void DMADevice::clearHalfTransferFlag() {

    _dma->IFCR = DMA_IFCR_CHTIF1 << (_dmaChannelNumber * 4);
}


/// ---------------------------------------------------------------------------
/// @brief    Borra tots els flags.
/// @param    channel: El numero de canal.
///
void DMADevice::clearAllFlags() {

    _dma->IFCR = DMA_IFCR_CGIF1 << (_dmaChannelNumber * 4);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita el canal DMA.
/// @param    channel: El numero de canal.
///
void DMADevice::enable() {

    Bits::set(_dmaChannel->CCR, DMA_CCR_EN);
}


/// ---------------------------------------------------------------------------
/// @brief    Deshabilita el canal DMA.
/// @param    channel: El numero de canal.
///
void DMADevice::disable() {

    Bits::clear(_dmaChannel->CCR, DMA_CCR_EN);
}
