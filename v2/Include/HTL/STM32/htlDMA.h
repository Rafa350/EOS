#pragma once
#ifndef __STM32_htlDMA__
#define __STM32_htlDMA__


#include "htl/STM32/htl.h"


namespace htl {

	namespace dma {

		enum class Channel {
			dma1_1,
			dma1_2,
			dma1_3,
			dma1_4,
			dma1_5,
			dma1_6,
			dma1_7
		};

		class DMAChannel {
			private:
				DMA_TypeDef * const _dma;
				DMA_Channel_TypeDef * const _channel;
			protected:
				DMAChannel(DMA_TypeDef * const dma, DMA_Channel_TypeDef * const channel);
			public:
				void Start(uint32_t startAddr, uint32_t dstAddr, uint32_t size);
				void Start_IRQ(uint32_t startAddr, uint32_t dstAddr, uint32_t size);
		};

	}
}


#endif // __STM32_htlDMA__
