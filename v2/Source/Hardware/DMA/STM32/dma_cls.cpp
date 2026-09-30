module;


#include "HTL/htl.h"
#include "eosEvents.h"


export module Eos.Hardware.DMA.Classes;


import Eos.Bits;
import Eos.Result;
import Eos.Types;
import Eos.Hardware.DMA.Identifiers;
import Eos.System.Core.Ticks;


export namespace eos::hardware::dma::internal {

    struct DMADEV_TypeDef {
        DMA_TypeDef * const dma;
#if defined(EOS_PLATFORM_STM32G0)
        DMA_Channel_TypeDef * const dmac;
        DMAMUX_Channel_TypeDef * const muxc;
#endif
        unsigned const flagPos;
    };

#ifdef HTL_DMA1_CHANNEL1_EXIST
    constexpr DMADEV_TypeDef const __dmadev11 = {
        DMA1, DMA1_Channel1, DMAMUX1_Channel0, 0
    };
#endif

#ifdef HTL_DMA1_CHANNEL2_EXIST
    constexpr DMADEV_TypeDef const __dmadev12 = {
        DMA1, DMA1_Channel2, DMAMUX1_Channel1, 4
    };
#endif

#ifdef HTL_DMA1_CHANNEL3_EXIST
    constexpr DMADEV_TypeDef const __dmadev13 = {
        DMA1, DMA1_Channel3, DMAMUX1_Channel2, 8
    };
#endif

#ifdef HTL_DMA1_CHANNEL4_EXIST
    constexpr DMADEV_TypeDef const __dmadev14 = {
        DMA1, DMA1_Channel4, DMAMUX1_Channel3, 12
    };
#endif

#ifdef HTL_DMA1_CHANNEL5_EXIST
    constexpr DMADEV_TypeDef const __dmadev15 = {
        DMA1, DMA1_Channel5, DMAMUX1_Channel4, 16
    };
#endif

#ifdef HTL_DMA1_CHANNEL6_EXIST
    constexpr DMADEV_TypeDef const __dmadev16 = {
        DMA1, DMA1_Channel6, DMAMUX1_Channel2, 20
    };
#endif

#ifdef HTL_DMA1_CHANNEL7_EXIST
    constexpr DMADEV_TypeDef const __dmadev17 = {
        DMA1, DMA1_Channel7, DMAMUX1_Channel2, 24
    };
#endif

}


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
            const internal::DMADEV_TypeDef * const _dmadev;
            State _state;
            NotificationEventRaiser _notificationEventRaiser;

        private:
            void notifyTransferCompleted(bool irq);
            void notifyHalfTransfer(bool irq);

            void activate() const {
                activateImpl();
            }
#if HTL_DMA_OPTION_DEACTIVATE == 1
            void deactivate() const {
                activateImpl();
            }
#endif

        protected:
            DMADevice(const internal::DMADEV_TypeDef *dmadev);

            void interruptService();

            virtual void activateImpl() const = 0;
#if HTL_DMA_OPTION_DEACTIVATE == 1
            virtual void deactivateImpl() const = 0;
#endif

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

            Result start(const uint8_t *src, uint8_t *dst, unsigned size);

            // TODO: temporal
            Result waitForFinish(Ticks blockTime);

            State getState() const { return _state; }
            bool isReady() const { return _state == State::ready; }
    };
}


namespace i = eos::hardware::dma::internal;

using namespace eos::hardware::dma;


bool isTransferCompleteInterruptEnabled(const i::DMADEV_TypeDef *dmadev);
bool isHalfTransferInterruptEnabled(const i::DMADEV_TypeDef *dmadev);
bool isTransferErrorInterruptEnabled(const i::DMADEV_TypeDef *dmadev);

void enableTransferCompleteInterrupt(const i::DMADEV_TypeDef *dmadev);
void enableHalfTransferInterrupt(const i::DMADEV_TypeDef *dmadev);
void enableTransferErrorInterrupt(const i::DMADEV_TypeDef *dmadev);
void disableAllInterrupts(const i::DMADEV_TypeDef *dmadev);

bool isTransferCompleteFlagSet(const i::DMADEV_TypeDef *dmadev);
bool isHalfTransferFlagSet(const i::DMADEV_TypeDef *dmadev);
bool isTransferErrorFlagSet(const i::DMADEV_TypeDef *dmadev);

void clearTransferCompleteFlag(const i::DMADEV_TypeDef *dmadev);
void clearHalfTransferFlag(const i::DMADEV_TypeDef *dmadev);
void clearAllFlags(const i::DMADEV_TypeDef *dmadev);

void enable(const i::DMADEV_TypeDef *dmadev);
void disable(const i::DMADEV_TypeDef *dmadev);


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    channel: El numero de canal (0..n).
///
DMADevice::DMADevice(
    const i::DMADEV_TypeDef *dmadev):

    _dmadev {dmadev},
	_state {State::reset} {

}


DMADevice::Result DMADevice::initMemoryToMemory() {

	if (_state == State::reset) {

        // Activa el dispositiu amb el canal desactivat.
        //
        activate();
        disable(_dmadev);

		auto CCR = _dmadev->dmac->CCR;
		Bits::clear(CCR, DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
				DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
				DMA_CCR_EN);
		Bits::set(CCR, DMA_CCR_MEM2MEM);      // Memoria a memoria
		_dmadev->dmac->CCR = CCR;

		return ErrorCode::ok;
	}
	else
		return ErrorCode::error;
}


/// ----------------------------------------------------------------------
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
        disable(_dmadev);

        tmp = _dmadev->dmac->CCR;

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

        _dmadev->dmac->CCR = tmp;

        // Borra els flags d'interrupcio del canal
        //
        clearAllFlags(_dmadev);

        // Selecciona el dispositiu de fa la solicitut DMA
        //
        tmp = _dmadev->muxc->CCR;
        Bits::clear(tmp, DMAMUX_CxCR_DMAREQ_ID);
        Bits::set(tmp, (uint32_t(requestID) << DMAMUX_CxCR_DMAREQ_ID_Pos));
        _dmadev->muxc->CCR = tmp;

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return ErrorCode::ok;
    }

    else
        return ErrorCode::error;
}


/// ----------------------------------------------------------------------
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
        disable(_dmadev);
        disableAllInterrupts(_dmadev);

        // Desactiva el dispositiu.
        //
#if HTL_DMA_OPTION_DEACTIVATEW == 1
        deactivate();
#endif

        // Canvia l'estat a 'reset'
        //
        _state = State::reset;

        return ErrorCode::ok;
    }
    else
        return ErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia la transferencia.
/// @param    startAddr: Adressa inicial.
/// @param    dstAddr: Adressa final;
/// @param    size: El nombre de bytes a transfderir.
/// @return   El resultat de l'operacio.
///
DMADevice::Result DMADevice::start(
    const uint8_t *src,
    uint8_t *dst,
    unsigned size) {

    // Comprova si l'estat es 'ready'
    //
    if (_state == State::ready) {

        // Comprova si es una transferencua de memoria a periferic
        //
        if (((_dmadev->dmac->CCR & DMA_CCR_MEM2MEM) == 0) &&
            ((_dmadev->dmac->CCR & DMA_CCR_DIR) != 0)) {

            // Inicialitza els parametres de la transferencia
            //
            _dmadev->dmac->CMAR = reinterpret_cast<uint32_t>(src);
            _dmadev->dmac->CPAR = reinterpret_cast<uint32_t>(dst);
            _dmadev->dmac->CNDTR = size;
        }

        enableTransferCompleteInterrupt(_dmadev);
        enable(_dmadev);

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


/// ----------------------------------------------------------------------
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
        while (((_dmadev->dma->ISR & ((DMA_ISR_TCIF1 | DMA_ISR_TEIF1) << _dmadev->flagPos)) == 0) &&
                !expired) {
            expired = expirationTime.hasExpiredNow();
        }

        // Borra els flags d'interrupcio del canal
        //
        clearAllFlags(_dmadev);

        // Deshabilita el canal
        //
        disable(_dmadev);

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return expired ? ErrorCode::timeout : ErrorCode::ok;
    }

    else
        return ErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void DMADevice::interruptService() {

    // Comprova si es una interrupcio TC (Transfer Complete)
    //
    if (isTransferCompleteInterruptEnabled(_dmadev) &&
        isTransferCompleteFlagSet(_dmadev)) {

        clearTransferCompleteFlag(_dmadev);
        disable(_dmadev);
        notifyTransferCompleted(true);

        _state = State::ready;
    }

    // Comprova si es una interrupcio HT (Half Transfer)
    //
    if (isHalfTransferInterruptEnabled(_dmadev) &&
        isHalfTransferFlagSet(_dmadev)) {

        clearHalfTransferFlag(_dmadev);
        notifyHalfTransfer(true);
    }

    // Comprova si es una interrupcio TE (Transfer Error)
    //
    if (isTransferErrorInterruptEnabled(_dmadev) &&
        isTransferErrorFlagSet(_dmadev)) {

        clearAllFlags(_dmadev);
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
/// @param    channel: El numero de canal.
///
void enableTransferCompleteInterrupt(
    const i::DMADEV_TypeDef *dmadev) {

	eos::Bits::set(dmadev->dmac->CCR, DMA_CCR_TCIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita la interrrupcio HT
/// @param    channel: El numero de canal.
///
void enableHalfTransferInterrupt(
    const i::DMADEV_TypeDef *dmadev) {

	eos::Bits::set(dmadev->dmac->CCR, DMA_CCR_HTIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita la interrrupcio TE
/// @param    channel: El numero de canal.
///
void enableTransferErrorInterrupt(
    const i::DMADEV_TypeDef *dmadev) {

	eos::Bits::set(dmadev->dmac->CCR, DMA_CCR_TEIE);
}


/// ---------------------------------------------------------------------------
/// @brief    Deshabilita totes les interrupcions.
/// @param    channel: El numero de canal.
///
void disableAllInterrupts(
    const i::DMADEV_TypeDef *dmadev) {

	eos::Bits::clear(dmadev->dmac->CCR, DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si la interrupcio TC esta habilitada.
/// @param    channel: El numero de canal.
/// @return   True si esta habilitada.
///
bool isTransferCompleteInterruptEnabled(
    const i::DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_TCIE) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si la interrupcio HT esta habilitada.
/// @param    channel: El numero de canal.
/// @return   True si esta habilitada.
///
bool isHalfTransferInterruptEnabled(
    const i::DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_HTIE) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si la interrupcio TE esta habilitada.
/// @param    channel: El numero de canal.
/// @return   True si esta habilitada.
///
bool isTransferErrorInterruptEnabled(
    const i::DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_TEIE) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si el flag TC esta actiu.
/// @param    channel: El numero de canal.
/// @return   True si esta actiu.
///
bool isTransferCompleteFlagSet(
    const i::DMADEV_TypeDef *dmadev) {

    auto flag = DMA_ISR_TCIF1 << dmadev->flagPos;
    return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si el flag HT esta actiu.
/// @param    channel: El numero de canal.
/// @return   True si esta actiu.
///
bool isHalfTransferFlagSet(
    const i::DMADEV_TypeDef *dmadev) {

    auto flag = DMA_ISR_HTIF1 << dmadev->flagPos;
    return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si el flag TH esta actiu.
/// @param    channel: El numero de canal.
/// @return   True si esta actiu.
///
bool isTransferErrorFlagSet(
    const i::DMADEV_TypeDef *dmadev) {

    auto flag = DMA_ISR_TEIF1 << dmadev->flagPos;
    return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// @brief    Borra el flag TC
/// @param    channel: El numero de canal.
///
void clearTransferCompleteFlag(
    const i::DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CTCIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// @brief    Borra el flag HT
/// @param    channel: El numero de canal.
///
void clearHalfTransferFlag(
    const i::DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CHTIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// @brief    Borra tots els flags.
/// @param    channel: El numero de canal.
///
void clearAllFlags(
    const i::DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CGIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// @brief    Habilita el canal DMA.
/// @param    channel: El numero de canal.
///
void enable(
    const i::DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR |= DMA_CCR_EN;
}


/// ----------------------------------------------------------------------
/// @brief    Deshabilita el canal DMA.
/// @param    channel: El numero de canal.
///
void disable(
    const i::DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR &= ~DMA_CCR_EN;
}
