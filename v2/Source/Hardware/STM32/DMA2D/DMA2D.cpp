module;

#include "hardware.h"


export module Eos.Hardware.DMA2D;

import Eos.Bits;
import Eos.Types;


export namespace eos::hardware::dma2d {

    class DMA2DDevice final: private NonCopyableClass {
		public:
			/// @brief Format de color d'entrada.
			/// @remarks Els valors corresponen al registre hardware. No modificar.
			///
			enum class InputColorMode {
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

			/// @brief Format de color de sortida.
			/// @remarks Els valors corresponen al registre hardware. No modificar.
			///
			enum class OutputColorMode {
				argb8888 = 0,
				rgb888 = 1,
				rgb565 = 2,
				argb1555 = 3,
				argb4444 = 4
			};

        private:
			DMA2D_TypeDef * const _dma2d;
            static DMA2DDevice _instance;

        public:
            static constexpr DMA2DDevice *pInst = &_instance;
            static constexpr DMA2DDevice &rInst = _instance;

        private:
            DMA2DDevice();

            void activate();
            void deactivate();

        public:
            void initialize();
            void deinitialize();

            void startFill(void *ptr, UInt16 width, UInt16 height, UInt16 pitch, OutputColorMode colorMode, UInt32 color);
            void startCopy(void *ptr, UInt16 width, UInt16 height, UInt16 pitch, OutputColorMode colorMode, const void *src, UInt16 srcPitch, InputColorMode srcColorMode);
            bool waitForFinish();

            void interruptService();
            inline static void interruptHandler() {
                _instance.interruptService();
            }
    };
}


using namespace eos;
using namespace eos::hardware::dma2d;


DMA2DDevice DMA2DDevice::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
DMA2DDevice::DMA2DDevice() :
	_dma2d { reinterpret_cast<DMA2D_TypeDef*>(DMA2D_BASE)} {

}


/// ---------------------------------------------------------------------------
/// @brief Activa el modul
///
void DMA2DDevice::activate() {

    Bits::set(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);
    __DSB();
}


/// ---------------------------------------------------------------------------
/// @brief Desactiva el modul.
///
void DMA2DDevice::deactivate() {

    Bits::clear(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitzacio.
///
void DMA2DDevice::initialize() {

    activate();
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitzacio.
///
void DMA2DDevice::deinitialize() {

    deactivate();
}


/// ---------------------------------------------------------------------------
/// @brief    Ompla una regio amb un color solid.
/// @param    ptr: Punter al primer pixel regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    pitch: Pitch de la regio.
/// @param    colorMode: El format de color.
/// @param    color: El color.
/// @remarks  En aquest casa no hi ha conversio. El color d'entrada es
///           el mateix que el de sortida.
///
void DMA2DDevice::startFill(
	void *ptr,
	UInt16 width,
	UInt16 height,
	UInt16 pitch,
	OutputColorMode colorMode,
	UInt32 color) {

	// Selecciona el tipus de transferencia com a R2M
	//
	_dma2d->CR = 0b11 << DMA2D_CR_MODE_Pos;

	// Asigna el format de color
	//
	UInt32 opfccr = _dma2d->OPFCCR;
	opfccr &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
	opfccr |= (UInt32(colorMode) & 0b111) << DMA2D_OPFCCR_CM_Pos;
	// Aqui tambe Swap Blue/Red
	// Aqui tambe Invert Alpha
	_dma2d->OPFCCR = opfccr;

	// Asigna el color
	//
	_dma2d->OCOLR = color;

	// Selecciona l'adressa i el offset del desti
	//
	_dma2d->OMAR = (UInt32) ptr;
	_dma2d->OOR = (pitch - width) & 0x3FFF;

	// Selecciona el tamany de la finestra
	//
	_dma2d->NLR =
		((width & 0x3FFF) << DMA2D_NLR_PL_Pos) |
		((height & 0xFFFF) << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	_dma2d->CR |= DMA2D_CR_START;
}


/// ---------------------------------------------------------------------------
/// @brief    Copia un mapa de bits a una regio
/// @param    ptr: Punter al primer pixel de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    pitch: Pitch de la regio.
/// @param    colorMode: Format de color de la regio.
/// @param    src: Punter al primer pixel del mapa de bits.
/// @param    srcPitch: Pitch del mapa de bits.
/// @param    srcColorMode: Format de color del mapa de bits.
///
void DMA2DDevice::startCopy(
	void *ptr,
	UInt16 width,
	UInt16 height,
	UInt16 pitch,
	OutputColorMode colorMode,
	const void* src,
	UInt16 srcPitch,
	InputColorMode srcColorMode) {

	// Selecciona el tipus de transferencia com a M2M/PFC
	//
	_dma2d->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Selecciona el format del color del origen
	//
	UInt32 fgpfccr = _dma2d->FGPFCCR;
	fgpfccr &= ~(0b1111 << DMA2D_FGPFCCR_CM_Pos);
	fgpfccr |= (UInt32(srcColorMode) & 0b1111) << DMA2D_FGPFCCR_CM_Pos;
	_dma2d->FGPFCCR = fgpfccr;

	// Selecciona el format de color del desti
	//
    UInt32 opfccr = _dma2d->OPFCCR;
    opfccr &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
    opfccr |= (UInt32(colorMode) & 0b111) << DMA2D_OPFCCR_CM_Pos;
	// Aqui tambe Swap Blue/Red
	// Aqui tambe Invert Alpha
	_dma2d->OPFCCR = opfccr;

	// Selecciona l'adressa i el offset del origen
	//
	_dma2d->FGMAR = (UInt32) src;
	_dma2d->FGOR = (srcPitch - width) & 0x3FFF;

	// Selecciona l'adressa i el offset del desti.
	//
	_dma2d->OMAR = (UInt32) ptr;
	_dma2d->OOR = (pitch - width) & 0x3FFF;

	// Selecciona el tamany de la finestra
	//
	_dma2d->NLR =
		((width & 0x3FFF) << DMA2D_NLR_PL_Pos) |
		((height & 0xFFFF) << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	_dma2d->CR |= DMA2D_CR_START;
}


/// ---------------------------------------------------------------------------
/// @brief    Espera que acabi la transaccio.
/// \return   True si tot es correcte, false en cas d'error.
///
bool DMA2DDevice::waitForFinish() {

	// Espera que acabi
	//
	while ((_dma2d->ISR & DMA2D_ISR_TCIF_Msk) == 0) {

		// Si troba errors, finalitza
		//
		volatile UInt32 isr = _dma2d->ISR;
		if (((isr & DMA2D_ISR_CEIF_Msk) != 0) ||
			((isr & DMA2D_ISR_TEIF_Msk) != 0) ||
			((isr & DMA2D_ISR_CAEIF_Msk) != 0)) {

			// Borra els flags d'error
			//
			UInt32 tmp = _dma2d->IFCR;
			tmp |= (1 << DMA2D_IFCR_CCEIF_Pos);
			tmp |= (1 << DMA2D_IFCR_CTEIF_Pos);
			tmp |= (1 << DMA2D_IFCR_CAECIF_Pos);
			_dma2d->IFCR = tmp;

			// Retorna error
			//
			return false;
		}
	}

	// Borra el flag de transferencia complerta
	//
	_dma2d->IFCR |= DMA2D_IFCR_CTCIF;

	// Retorna OK
	//
	return true;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void DMA2DDevice::interruptService() {

}
