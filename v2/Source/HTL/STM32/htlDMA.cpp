#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlDMA.h"


using namespace htl;
using namespace htl::dma;


struct DMARegisters {
    DMA_TypeDef * const dma;
    DMA_Channel_TypeDef * const dmaChannel;
    DMAMUX_Channel_TypeDef * const muxChannel;
    unsigned const flagOffset;
};

static DMARegisters const __dma[] = {
    #ifdef HTL_DMA1_CHANNEL1_EXIST
    { DMA1, DMA1_Channel1, DMAMUX1_Channel0, 0 },
    #endif
    #ifdef HTL_DMA1_CHANNEL2_EXIST
    { DMA1, DMA1_Channel2, DMAMUX1_Channel1, 4 },
    #endif
    #ifdef HTL_DMA1_CHANNEL3_EXIST
    { DMA1, DMA1_Channel3, DMAMUX1_Channel2, 8 },
    #endif
    #ifdef HTL_DMA1_CHANNEL4_EXIST
    { DMA1, DMA1_Channel4, DMAMUX1_Channel3, 12 },
    #endif
    #ifdef HTL_DMA1_CHANNEL5_EXIST
    { DMA1, DMA1_Channel5, DMAMUX1_Channel4, 16 },
    #endif
    #ifdef HTL_DMA1_CHANNEL6_EXIST
    { DMA1, DMA1_Channel6, DMAMUX1_Channel5, 20 },
    #endif
    #ifdef HTL_DMA1_CHANNEL7_EXIST
    { DMA1, DMA1_Channel7, DMAMUX1_Channel6, 24 },
    #endif
};


static bool isTransferCompletedInterruptEnabled(unsigned channel);
static bool isHalfTransferInterruptEnabled(unsigned channel);
static bool isTransferErrorInterruptEnabled(unsigned channel);

static void enableTransferCompletedInterrupt(unsigned channel);
static void enableHalfTransferInterrupt(unsigned channel);
static void enableTransferErrorInterrupt(unsigned channel);

static bool isTransferCompletedFlagSet(unsigned channel);
static bool isHalfTransferFlagSet(unsigned channel);
static bool isTransferErrorFlagSet(unsigned channel);

static void clearTransferCompletedFlag(unsigned channel);
static void clearHalfTransferFlag(unsigned channel);
static void clearAllFlags(unsigned channel);

static void enable(unsigned channel);
static void disable(unsigned channel);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    channel: El numero de canal (0..n).
///
DMADevice::DMADevice(
	unsigned channel) :

	_channel {channel},
	_state {State::reset} {

}


Result DMADevice::initMemoryToMemory() {

    auto dmaChannel =__dma[_channel].dmaChannel;

    uint32_t tmp = dmaChannel->CCR;
    tmp = ~(DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
            DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
            DMA_CCR_EN);
    tmp |= DMA_CCR_MEM2MEM;      // Memoria a memoria
    dmaChannel->CCR = tmp;

    return Result::success();
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

        auto dma = __dma[_channel].dma;
        auto dmaChannel = __dma[_channel].dmaChannel;
        auto muxChannel = __dma[_channel].muxChannel;

        // Activa el dispositiu
        //
        activate();

        tmp = dmaChannel->CCR;

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

        // El canal queda deshabilitat. Nomes activa durant les
        // transferencies.
        //
        tmp &= ~DMA_CCR_EN;

        dmaChannel->CCR = tmp;

        // Selecciona el dispositiu de fa la solicitut DMA
        //
        tmp = muxChannel->CCR;
        tmp &= ~DMAMUX_CxCR_DMAREQ_ID;
        tmp |= (uint32_t(requestID) << DMAMUX_CxCR_DMAREQ_ID_Pos);
        muxChannel->CCR = tmp;

        // Borra els flags d'interrupcio del canal
        //
        clearAllFlags(channel);

        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return Result::success();
    }

    else
        return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
Result DMADevice::deinitialize() {

    // Comprova si l'estat es 'ready'
    //
    if (_state == State::ready) {

        // Deshabilita el canal.
        //
        disable(_channel);

        // Desactiva el dispositiu.
        //
        deactivate();

        // Canvia l'estat a 'reset'
        //
        _state = State::reset;

        return Result::success();
    }
    else
        return Result::error();
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

        auto dmaChannel = __dma[_channel].dmaChannel;

        // Comprova si es una transferencua de memoria a periferic
        //
        if (((dmaChannel->CCR & DMA_CCR_MEM2MEM) == 0) &&
            ((dmaChannel->CCR & DMA_CCR_DIR) != 0)) {

            // Inicialitza els parametres de la transferencia
            //
            dmaChannel->CMAR = reinterpret_cast<uint32_t>(src);
            dmaChannel->CPAR = reinterpret_cast<uint32_t>(dst);
            dmaChannel->CNDTR = size;
        }

        // Habilita el dispositiu, les interrupcions i entra en espera de
        // solicituts de transferencia.
        //
        dmaChannel->CCR |= DMA_CCR_TCIE | DMA_CCR_EN;

        // Canvia l'estat a 'transfering'
        //
        _state = State::transfering;

        return Result::success();
    }
    else
        return Result::error();

}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzi la transferencia.
/// \param    timeout: Limit de temps.
/// \return   El resultat de l'operacio.
///
Result DMADevice::waitForFinish(
    Tick timeout) {

    // Comprova si l'estat es 'transfering'
    //
    if (_state == State::transfering) {

        auto dma = __dma[_channel].dma;
        auto dmaChannel = __dma[_channel].dmaChannel;
        auto flagOffset = __dma[_channel].flagOffset;

        // Espera flag TCIF o TEIF del canal
        //
        auto expired = false;
        auto expireTime = htl::getTick() + timeout;
        while (((dma->ISR & ((DMA_ISR_TCIF1 | DMA_ISR_TEIF1) << flagOffset)) == 0) &&
                !expired) {
            expired = timeout == Tick(-1) ? false : hasTickExpired(expireTime);
        }

        // Borra els flags d'interrupcio del canal
        //
        dma->IFCR = (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CTEIF1 | DMA_IFCR_CHTIF1) << flagOffset;

        // Deshabilita el canal
        //
        disableChannel(_channel);


        // Canvia l'estat a 'ready'
        //
        _state = State::ready;

        return expired ? Result::timeout() : Result::success();
    }

    else
        return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void DMADevice::interruptService() {

    if (isTransferCompletedInterruptEnabled(_channel) && isTransferCompleted(_channel)) {

        clearTransferCompletedFlag(_channel);
        disableChannel(_channel);

        notifyTransferCompleted(true);

        _state = State::ready;
    }

    if (isHalfTransferInterruptEnabled(_channel) && isHalfTransfer(_channel)) {

        clearHalfTransferFlag(channel);
        
        notifyHalfTransfer(true);
        
    }

    if (isTransferErrorInterruptEnabled(channel) && isTransferError(_channel)) {

        clearAllFlags(channel);
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
/// \brief    Comprova si la interrupcio TC esta habilitada.
/// \param    channel: El numero de canal.
/// \return   True si esta habilitada.
///
static inline bool isTransferCompletedInterruptEnabled(
    unsigned channel) {

    return (__dma[channel].dmaChannel->CCR & DMA_CCR_TCIE) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag TC esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isTransferCompletedFlagSet(
    unsigned channel) {

    auto flag = DMA_ISR_TCIF1 << __dma[channel].flagOffset;
    return (__dma[channel].dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag HT esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isHalfTransferFlagSet(
    unsigned channel) {

    auto flag = DMA_ISR_HTIF1 << __dma[channel].flagOffset;
    return (__dma[channel].dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el flag TH esta actiu.
/// \param    channel: El numero de canal.
/// \return   True si esta actiu.
///
static inline bool isTransferErrorFlagSet(
    unsigned channel) {

    auto flag = DMA_ISR_TEIF1 << __dma[channel].flagOffset;
    return (__dma[channel].dma->ISR & ~flag) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag TC
/// \param    channel: El numero de canal.
///
static inline void clearTransferCompletedFlag(
    unsigned channel) {
    
    auto flag = DMA_IFCR_CTCIF1 << __dma[_channel].flagOffset;
    __dma[channel].dma->IFCR = flag;
}


static inline void clearAllFlags(
    unsigned channel) {
    
    auto flag = (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_ICFR_CHTIF1 | FMA_ICFR_CTEIF1) << __dma[_channel].flagOffset;
    __dma[channel].dma->IFCR = flag;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el canal DMA.
/// \param    channel: El numero de canal.
/// 
static inline void enable(
    unsigned channel) {
    
    auto dmaChannel = __dma[channel].dmaChannel;
    dmaChannel->CCR |= DMA_CCR_EN;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita el canal DMA.
/// \param    channel: El numero de canal.
/// 
static inline void disable(
    unsigned channel) {
    
    auto dmaChannel = __dma[channel].dmaChannel;
    dmaChannel->CCR &= ~DMA_CCR_EN;
}
