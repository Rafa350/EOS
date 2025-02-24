#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlDMA.h"


using namespace eos;
using namespace htl;
using namespace htl::dma;
using namespace htl::dma::internal;


#ifdef HTL_DMA1_CHANNEL1_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev11 = {
    DMA1, DMA1_Channel1, DMAMUX1_Channel0, 0 };
#endif

#ifdef HTL_DMA1_CHANNEL2_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev12 = {
    DMA1, DMA1_Channel2, DMAMUX1_Channel1, 4 };
#endif

#ifdef HTL_DMA1_CHANNEL3_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev13 = {
    DMA1, DMA1_Channel3, DMAMUX1_Channel2, 8 };
#endif

#ifdef HTL_DMA1_CHANNEL4_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev14 = {
    DMA1, DMA1_Channel4, DMAMUX1_Channel3, 12 };
#endif

#ifdef HTL_DMA1_CHANNEL5_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev15 = {
    DMA1, DMA1_Channel5, DMAMUX1_Channel4, 16 };
#endif

#ifdef HTL_DMA1_CHANNEL6_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev16 = {
    DMA1, DMA1_Channel6, DMAMUX1_Channel2, 20 };
#endif

#ifdef HTL_DMA1_CHANNEL7_EXIST
constexpr DMADEV_TypeDef const internal::__dmadev17 = {
    DMA1, DMA1_Channel7, DMAMUX1_Channel2, 24 };
#endif


static bool isTransferCompleteInterruptEnabled(const DMADEV_TypeDef *dmadev);
static bool isHalfTransferInterruptEnabled(const DMADEV_TypeDef *dmadev);
static bool isTransferErrorInterruptEnabled(const DMADEV_TypeDef *dmadev);

static void enableTransferCompleteInterrupt(const DMADEV_TypeDef *dmadev);
static void enableHalfTransferInterrupt(const DMADEV_TypeDef *dmadev);
static void enableTransferErrorInterrupt(const DMADEV_TypeDef *dmadev);
static void disableAllInterrupts(const DMADEV_TypeDef *dmadev);

static bool isTransferCompleteFlagSet(const DMADEV_TypeDef *dmadev);
static bool isHalfTransferFlagSet(const DMADEV_TypeDef *dmadev);
static bool isTransferErrorFlagSet(const DMADEV_TypeDef *dmadev);

static void clearTransferCompleteFlag(const DMADEV_TypeDef *dmadev);
static void clearHalfTransferFlag(const DMADEV_TypeDef *dmadev);
static void clearAllFlags(const DMADEV_TypeDef *dmadev);

static void enable(const DMADEV_TypeDef *dmadev);
static void disable(const DMADEV_TypeDef *dmadev);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    channel: El numero de canal (0..n).
///
DMADevice::DMADevice(
    const internal::DMADEV_TypeDef *dmadev):

    _dmadev {dmadev},
	_state {State::reset} {

}


Result DMADevice::initMemoryToMemory() {

	if (_state == State::reset) {

        // Activa el dispositiu amb el canal desactivat.
        //
        activate();
        disable(_dmadev);

		uint32_t tmp = _dmadev->dmac->CCR;
		tmp = ~(DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
				DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
				DMA_CCR_EN);
		tmp |= DMA_CCR_MEM2MEM;      // Memoria a memoria
		_dmadev->dmac->CCR = tmp;

		return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio en modus transferencia de memoria a periferic.
/// \param    priority: Prioritat.
/// \param    srcSize: Tamany de les dades del origen.
/// \param    dstSize: Tamany de les dades del desti.
/// \param    srcInc: Increment de l'adresa del origen.
/// \param    dstInc: Increment de l'adressa del desti.
/// \param    mode: Tipus de transferencia normal/circular.
/// \param    requestID: Identificador de la solicitut
/// \return   El resultat de l'operacio.
///
Result DMADevice::initMemoryToPeripheral(
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
        tmp &= ~DMA_CCR_DIR_Msk;
        tmp |= 1 << DMA_CCR_DIR_Pos;
        tmp &= ~DMA_CCR_MEM2MEM;

        // Selecciona el modus de transferencia
        //
        tmp &= ~DMA_CCR_CIRC_Msk;
        if (mode == TransferMode::circular)
            tmp |= 1 << DMA_CCR_CIRC_Pos;

        // Selecciona la prioritat
        //
        tmp &= ~DMA_CCR_PL_Msk;
        tmp |= ((uint32_t)priority << DMA_CCR_PL_Pos) & DMA_CCR_PL_Msk;

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
        tmp &= ~DMAMUX_CxCR_DMAREQ_ID;
        tmp |= (uint32_t(requestID) << DMAMUX_CxCR_DMAREQ_ID_Pos);
        _dmadev->muxc->CCR = tmp;

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return Results::success;
    }

    else
        return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
Result DMADevice::deinitialize() {

    // Comprova si l'estat es 'ready'
    //
    if (_state == State::ready) {

        _notifyEvent = nullptr;
        _notifyEventEnabled = false;

        // Deshabilita el canal.
        //
        disable(_dmadev);
        disableAllInterrupts(_dmadev);

        // Desactiva el dispositiu.
        //
        deactivate();

        // Canvia l'estat a 'reset'
        //
        _state = State::reset;

        return Results::success;
    }
    else
        return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'event de notificacio.
/// \param    event: L'event.
/// \param    enabled: Indica si esta habilitat.
//
void DMADevice::setNotifyEvent(
    INotifyEvent &event,
    bool enabled) {

    _notifyEvent = &event;
    _notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transferencia.
/// \param    startAddr: Adressa inicial.
/// \param    dstAddr: Adressa final;
/// \param    size: El nombre de bytes a transfderir.
/// \return   El resultat de l'operacio.
///
Result DMADevice::start(
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

        return Results::success;
    }
    else
        return Results::error;

}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzi la transferencia.
/// \param    timeout: Limit de temps.
/// \return   El resultat de l'operacio.
///
Result DMADevice::waitForFinish(
    unsigned timeout) {

    // Comprova si l'estat es 'transfering'
    //
    if (_state == State::transfering) {

        // Espera flag TCIF o TEIF del canal
        //
        auto expired = false;
        auto expireTime = htl::getTick() + timeout;
        while (((_dmadev->dma->ISR & ((DMA_ISR_TCIF1 | DMA_ISR_TEIF1) << _dmadev->flagPos)) == 0) &&
                !expired) {
            expired = timeout == unsigned(-1) ? false : hasTickExpired(expireTime);
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

        return expired ? Results::timeout : Results::success;
    }

    else
        return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
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


/// ----------------------------------------------------------------------
/// \brief    Notifica que s'ha completat la transferencia.
/// \param    irq: True si la notificacio ve d'una interrupcio.
///
void DMADevice::notifyTransferCompleted(
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .id = NotifyID::completed,
            .irq = irq
        };
        _notifyEvent->execute(this, args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que s'ha completat la mitat de la transferencia.
/// \param    irq: True si la notificacio ve d'una interrupcio.
///
void DMADevice::notifyHalfTransfer(
    bool irq) {

    if (_notifyEventEnabled) {
        NotifyEventArgs args = {
            .id = NotifyID::half,
            .irq = irq
        };
        _notifyEvent->execute(this, args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrrupcio TC
/// \param    channel: El numero de canal.
///
static inline void enableTransferCompleteInterrupt(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR |= DMA_CCR_TCIE;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrrupcio HT
/// \param    channel: El numero de canal.
///
static inline void enableHalfTransferInterrupt(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR |= DMA_CCR_HTIE;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrrupcio TE
/// \param    channel: El numero de canal.
///
static inline void enableTransferErrorInterrupt(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR |= DMA_CCR_TEIE;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita totes les interrupcions.
/// \param    channel: El numero de canal.
///
static void disableAllInterrupts(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR &= ~(DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la interrupcio TC esta habilitada.
/// \param    channel: El numero de canal.
/// \return   True si esta habilitada.
///
static inline bool isTransferCompleteInterruptEnabled(
    const DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_TCIE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la interrupcio HT esta habilitada.
/// \param    channel: El numero de canal.
/// \return   True si esta habilitada.
///
static inline bool isHalfTransferInterruptEnabled(
    const DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_HTIE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la interrupcio TE esta habilitada.
/// \param    channel: El numero de canal.
/// \return   True si esta habilitada.
///
static inline bool isTransferErrorInterruptEnabled(
    const DMADEV_TypeDef *dmadev) {

    return (dmadev->dmac->CCR & DMA_CCR_TEIE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag TC esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isTransferCompleteFlagSet(
    const DMADEV_TypeDef *dmadev) {

      auto flag = DMA_ISR_TCIF1 << dmadev->flagPos;
      return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag HT esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isHalfTransferFlagSet(
    const DMADEV_TypeDef *dmadev) {

    auto flag = DMA_ISR_HTIF1 << dmadev->flagPos;
    return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag TH esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isTransferErrorFlagSet(
    const DMADEV_TypeDef *dmadev) {

    auto flag = DMA_ISR_TEIF1 << dmadev->flagPos;
    return (dmadev->dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag TC
/// \param    channel: El numero de canal.
///
static inline void clearTransferCompleteFlag(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CTCIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag HT
/// \param    channel: El numero de canal.
///
static inline void clearHalfTransferFlag(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CHTIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// \brief    Borra tots els flags.
/// \param    channel: El numero de canal.
///
static inline void clearAllFlags(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dma->IFCR = DMA_IFCR_CGIF1 << dmadev->flagPos;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el canal DMA.
/// \param    channel: El numero de canal.
///
static inline void enable(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR |= DMA_CCR_EN;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita el canal DMA.
/// \param    channel: El numero de canal.
///
static inline void disable(
    const DMADEV_TypeDef *dmadev) {

    dmadev->dmac->CCR &= ~DMA_CCR_EN;
}
