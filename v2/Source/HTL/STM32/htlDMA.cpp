#include "HTL/htl.h"
#include "HTL/STM32/htlDMA.h"


using namespace htl;
using namespace htl::dma;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    dma: Bloc de registres del DMA
/// \param    channel: Bloc de registres del canal DMA.
///
DMAChannel::DMAChannel(
	DMA_TypeDef * const dma,
	DMA_Channel_TypeDef * const channel) :

	_dma {dma},
	_channel {channel} {

}


void DMAChannel::initM2M() {

    uint32_t tmp;

    tmp = _channel->CCR;
    tmp = ~(DMA_CCR_PL | DMA_CCR_MSIZE | DMA_CCR_PSIZE | DMA_CCR_MINC |
            DMA_CCR_PINC | DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MEM2MEM |
            DMA_CCR_EN);
    tmp |= DMA_CCR_MEM2MEM;      // Memoria a memoria
    _channel->CCR = tmp;

    enable();
}


void DMAChannel::deinitialize() {

    disable();
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la transferencia en modus polling.
/// \param    startAddr: Adressa inicial.
/// \param    dstAddr: Adressa final;
/// \param    size: El nombre de bytes a transfderir.
///
void DMAChannel::Start(
    const uint8_t *src,
    uint8_t *dst,
    uint32_t size) {

    _channel->CPAR = reinterpret_cast<uint32_t>(src);    // Adressa d'origen.
    _channel->CMAR = reinterpret_cast<uint32_t>(dst);    // Adressa de destinacio.
    _channel->CNDTR = size;      // Nombre de bytes a moure.
}
