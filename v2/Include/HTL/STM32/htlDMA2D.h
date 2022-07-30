#ifndef __STM32_htlDMA2D__
#define __STM32_htlDMA2D__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"


namespace htl {

	enum class DMA2DColorMode {
		argb8888,
		rgb888,
		rgb565,
		argb1555,
		argb4444,
		l8,
		al44,
		al88,
		l4,
		a8,
		a4
	};

	enum class DMA2DEvent {

	};

	using DMA2DInterruptParam = void*;
	using DMA2DInterruptFunction = void (*)(DMA2DEvent, DMA2DInterruptParam);

	void DMA2D_startFill(void*,	int, int, int, DMA2DColorMode, uint32_t);
	void DMA2D_startCopy(void*, int, int, int, DMA2DColorMode, const void*, int, DMA2DColorMode);
	bool DMA2D_waitForFinish();

	template <int dummy>
	class DMA2D_x final {
		private:
			static DMA2DInterruptParam _isrParam;
			static DMA2DInterruptFunction _isrFunction;

		private:
			DMA2D_x() = delete;
			DMA2D_x(const DMA2D_x &) = delete;
			DMA2D_x(const DMA2D_x &&) = delete;
			~DMA2D_x() = delete;

			DMA2D_x & operator = (const DMA2D_x &) = delete;
			DMA2D_x & operator = (const DMA2D_x &&) = delete;

			static void activate() {

				RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
				__DSB();
			}

			static void deactivate() {

				RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2DEN;
			}

		public:
			static void init() {

				activate();
			}

			static void deInit() {

				deactivate();
			}

			static void startFill(
				void *dst,
				int width,
				int height,
				int offset,
				DMA2DColorMode colorMode,
				uint32_t color) {

				DMA2D_startFill(dst, width, height, offset, colorMode, color);
			}

			static void startCopy(
				void *dst,
				int width,
				int height,
				int offset,
				DMA2DColorMode colorMode,
				const void *src,
				int srcOffset,
				DMA2DColorMode srcColorMode) {

				DMA2D_startCopy(dst, width, height, offset, colorMode, src, srcOffset, srcColorMode);
			}

			inline static bool waitForFinish() {

				return DMA2D_waitForFinish();
			}

			static void InterruptHandler(
				DMA2DEvent event) {

				if (_isrFunction != nullptr)
					_isrFunction(event, _isrParam);
			}
	};

	template<int dummy_> DMA2DInterruptFunction DMA2D_x<dummy_>::_isrFunction = nullptr;
    template<int dummy_> DMA2DInterruptParam DMA2D_x<dummy_>::_isrParam = nullptr;


	using DMA2D_1 = DMA2D_x<1>;
}


#endif // __STM32_htlDMA2D__
