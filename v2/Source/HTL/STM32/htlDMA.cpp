#include "HTL/htl.h"
#include "HTL/STM32/htlDMA.h"


using namespace htl;
using namespace htl::dma;



DMAChannel::DMAChannel(
	DMA_TypeDef * const dma,
	DMA_Channel_TypeDef * const channel) :

	_dma {dma},
	_channel {channel} {

}
