#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlDMA.h"


using namespace htl;
using namespace htl::dma;

struct DMAAddress {
    uint32_t dma;
    uint32_t dmaChannel;
    uint32_t mux;
    uint32_t muxChannel;
};

static DMAAddress __dmaAddressTbl[] = {
    #ifdef HTL_DMA1_CHANNEL1_EXIST
    { DMA1_BASE, DMA1_Channel1_BASE, DMAMUX1_BASE, DMAMUX1_Channel0_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL2_EXIST
    { DMA1_BASE, DMA1_Channel2_BASE, DMAMUX1_BASE, DMAMUX1_Channel1_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL3_EXIST
    { DMA1_BASE, DMA1_Channel3_BASE, DMAMUX1_BASE, DMAMUX1_Channel2_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL4_EXIST
    { DMA1_BASE, DMA1_Channel4_BASE, DMAMUX1_BASE, DMAMUX1_Channel3_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL5_EXIST
    { DMA1_BASE, DMA1_Channel5_BASE, DMAMUX1_BASE, DMAMUX1_Channel4_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL6_EXIST
    { DMA1_BASE, DMA1_Channel6_BASE, DMAMUX1_BASE, DMAMUX1_Channel5_BASE },
    #endif
    #ifdef HTL_DMA1_CHANNEL7_EXIST
    { DMA1_BASE, DMA1_Channel7_BASE, DMAMUX1_BASE, DMAMUX1_Channel6_BASE },
    #endif
};


static DMA_TypeDef* getDMA(uint32_t channel);
static DMA_Channel_TypeDef* getDMAChannel(uint32_t channel);
static DMAMUX_Channel_TypeDef* getDMAMUXChannel(uint32_t channel);

static void enable(DMA_Channel_TypeDef *dmaChannel);
static void disable(DMA_Channel_TypeDef *dmaChannel);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    channel: El numero de canal (0..n).
///
DMADevice::DMADevice(
	uint32_t channel) :

	_channel {channel},
	_state {State::reset} {

}


void DMADevice::initMemoryToMemory() {

    auto dmaChannel = getDMAChannel(_channel);

    uint32_t tmp = dmaChannel->CCR;
    tmp = ~(DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
            DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
            DMA_CCR_EN);
    tmp |= DMA_CCR_MEM2MEM;      // Memoria a memoria
    dmaChannel->CCR = tmp;
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
///
void DMADevice::initMemoryToPeripheral(
    Priority priority,
    DataSize srcSize,
    DataSize dstSize,
    AddressIncrement srcInc,
    AddressIncrement dstInc,
    TransferMode mode,
    RequestID requestID) {

    uint32_t tmp;

    auto dma = getDMA(_channel);
    auto dmaChannel = getDMAChannel(_channel);
    auto muxChannel = getDMAMUXChannel(_channel);

    // Activa el dispositiu
    //
    activate();
    disable(dmaChannel);

    tmp = dmaChannel->CCR;

    // Inicialitza els valor a configurar a zero
    //
    tmp = ~(DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
            DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
            DMA_CCR_EN);

    // Selecciona la prioritat
    //
    tmp |= ((uint32_t)priority << DMA_CCR_PL_Pos) & DMA_CCR_PL_Msk;

    // Direccio de transferncia de memoria a periferic
    //
    tmp |= 1 << DMA_CCR_DIR_Pos;

    // Parametres de access a la memoria
    //
    if (srcInc == AddressIncrement::inc)
        tmp |= 1 << DMA_CCR_MINC_Pos;
    tmp |= (uint32_t(srcSize) << DMA_CCR_MSIZE_Pos) & DMA_CCR_MSIZE_Msk;

    // Parametres d'acces al periferic
    //
    if (dstInc == AddressIncrement::inc)
        tmp |= 1 << DMA_CCR_PINC_Pos;
    tmp |= (uint32_t(dstSize) << DMA_CCR_PSIZE_Pos) & DMA_CCR_PSIZE_Msk;

    dmaChannel->CCR = tmp;

    // Borra els flags d'interrupcio
    //
    dma->IFCR = 0xF << _channel;

    // Configura el multiplexor
    //
    tmp = muxChannel->CCR;
    tmp &= ~(DMAMUX_CxCR_DMAREQ_ID);
    tmp |= (uint32_t(requestID) << DMAMUX_CxCR_DMAREQ_ID_Pos);
    muxChannel->CCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void DMADevice::deinitialize() {

    auto dmaChannel = getDMAChannel(_channel);
    disable(dmaChannel);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transferencia en modus polling.
/// \param    startAddr: Adressa inicial.
/// \param    dstAddr: Adressa final;
/// \param    size: El nombre de bytes a transfderir.
///
void DMADevice::start(
    const uint8_t *src,
    uint8_t *dst,
    uint32_t size) {

    auto dmaChannel = getDMAChannel(_channel);

    if (((dmaChannel->CCR & DMA_CCR_MEM2MEM) == 0) &&
        ((dmaChannel->CCR & DMA_CCR_DIR) != 0)) {

        // Transferencia de memoria a periferic
        //
        dmaChannel->CMAR = reinterpret_cast<uint32_t>(src);
        dmaChannel->CPAR = reinterpret_cast<uint32_t>(dst);
        dmaChannel->CNDTR = size;
    }

    // Activa el dispositiu
    //
    enable(dmaChannel);
}


bool DMADevice::waitForFinish(
    uint16_t timeout) {

    auto dmaChannel = getDMAChannel(_channel);

    return true;
}


void DMADevice::finish() {

    auto dmaChannel = getDMAChannel(_channel);
    disable(dmaChannel);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void DMADevice::interruptService() {

}


/// ----------------------------------------------------------------------
/// \brief    Obte els registres de hardware el DMA del canal.
/// \param    channel: El numero de canal.
/// \return   L'adressa.
///
static DMA_TypeDef* getDMA(
    uint32_t channel) {

    return reinterpret_cast<DMA_TypeDef*>(__dmaAddressTbl[channel].dma);
}


/// ----------------------------------------------------------------------
/// \brief    Obte els registres de hardware el DMAChannel del canal.
/// \param    channel: El numero de canal.
/// \return   L'adressa.
///
static DMA_Channel_TypeDef* getDMAChannel(
    uint32_t channel) {

    return reinterpret_cast<DMA_Channel_TypeDef*>(__dmaAddressTbl[channel].dmaChannel);
}


/// ----------------------------------------------------------------------
/// \brief    Obte els registres de hardware el DMAMUXChannel del canal.
/// \param    channel: El numero de canal.
/// \return   L'adressa.
///
static DMAMUX_Channel_TypeDef* getDMAMUXChannel(
    uint32_t channel) {

    return reinterpret_cast<DMAMUX_Channel_TypeDef*>(__dmaAddressTbl[channel].muxChannel);
}


static void enable(
    DMA_Channel_TypeDef *dmaChannel) {

    dmaChannel->CCR |= DMA_CCR_EN;
}


static void disable(
    DMA_Channel_TypeDef *dmaChannel) {

    dmaChannel->CCR &= ~DMA_CCR_EN;
}
