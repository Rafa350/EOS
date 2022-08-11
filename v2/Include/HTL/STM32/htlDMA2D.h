#pragma once
#ifndef __STM32_htlDMA2D__
#define __STM32_htlDMA2D__


// EOS includes
//
#include "HTL/htl.h"
#include "HAL/STM32/halDMA2D.h"
#include "System/Graphics/eosColor.h"


namespace htl {

	/// \brief Format de color d'entrada
	/// \remarks Els valors corresponen al registre hardware. No modificar
	///
	enum class DMA2DInputColorMode {
		argb8888 = 0,
		rgb888 = 1,
		rgb565 = 2,
		argb1555 = 3,
		argb4444 = 4,
		l8 = 5,
		al44 = 6,
		al88 = 7,
		l4 = 8,
		a8 = 9,
		a4 = 10
	};

	/// \brief Format de color de sortida
    /// \remarks Els valors corresponen al registre hardware. No modificar
	///
	enum class DMA2DOutputColorMode {
		argb8888 = 0,
		rgb888 = 1,
		rgb565 = 2,
		argb1555 = 3,
		argb4444 = 4
	};

	enum class DMA2DEvent {
		configurationError,
		clutTransferComplete,
		clutAccessError,
		transferWatermark,
		transferComplete,
		transferError
	};

	using DMA2DInterruptParam = void*;
	using DMA2DInterruptFunction = void (*)(DMA2DEvent, DMA2DInterruptParam);

	void DMA2D_startFill(void*,	int, int, int, DMA2DOutputColorMode, uint32_t);
	void DMA2D_startCopy(void*, int, int, int, DMA2DOutputColorMode, const void*, int, DMA2DInputColorMode);
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
			/// \brief Inicialitza el modul.
			///
			inline static void init() {

				activate();
			}

			/// \brief Desinicialitza el modul
			///
			inline static void deInit() {

				deactivate();
			}

			/// \brief Inicia el proces de omprit una regio
			/// \param dst: Adressa del primer pixel de la regio.
			/// \param width: Amplada.
			/// \param height: Alçada.
			/// \param pitch: Amplada fins a la seguent linia.
			/// \param colorMode: Format de color.
			/// \param color: El color en el format especificat.
			///
			inline static void startFill(
				void *ptr,
				int width,
				int height,
				int pitch,
				DMA2DOutputColorMode colorMode,
				uint32_t color) {

				DMA2D_startFill(ptr, width, height, pitch, colorMode, color);
			}

			inline static void startCopy(
				void *ptr,
				int width,
				int height,
				int pitch,
				DMA2DOutputColorMode colorMode,
				const void *src,
				int srcPitch,
				DMA2DInputColorMode srcColorMode) {

				DMA2D_startCopy(ptr, width, height, pitch, colorMode, src, srcPitch, srcColorMode);
			}

			/// \brief Espera que finalitzi l'operacio de transferencia.
			///
			inline static bool waitForFinish() {

				return DMA2D_waitForFinish();
			}

			/// \brief Invoca la funcio d'interruipcio.
			/// \param event: El event.
			///
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
