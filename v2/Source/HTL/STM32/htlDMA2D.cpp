#include "eos.h"
#include "HTL/STM32/htlDMA2D.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Ompla una regio amb un pixel solid.
/// \param    dst: Punter al primer pixel regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    offset: Offset per avançar a la seguent linia de la regio.
/// \param    colorMode: El format de color
/// \param    color: El color per omplir.
///
void htl::DMA2D_startFill(
	void* dst,
	int width,
	int height,
	int offset,
	DMA2DColorMode colorMode,
	uint32_t color) {

	// Selecciona el tipus de transferencia com a R2M
	//
	DMA2D->CR = 0b11 << DMA2D_CR_MODE_Pos;

	// Asigna el format de color
	//
	uint32_t temp = DMA2D->OPFCCR;
	temp &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
	switch (colorMode) {
		default:
		case DMA2DColorMode::argb8888:
			temp |= 0b000 << DMA2D_OPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb888:
			temp |= 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb565:
			temp |= 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;
	}
	DMA2D->OPFCCR = temp;

	// Asigna el color
	//
	DMA2D->OCOLR = color;

	// Selecciona l'adressa i el offset del desti
	//
	DMA2D->OMAR = (uint32_t) dst;
	DMA2D->OOR = offset & 0x3FFF;

	// Selecciona el tamany de la finestra
	//
	DMA2D->NLR =
		((width & 0x3FFF) << DMA2D_NLR_PL_Pos) |
		((height & 0xFFFF) << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= DMA2D_CR_START;
}


/// ----------------------------------------------------------------------
/// \brief    Copia un mapa de bits a una regio
/// \param    dst: Punter al primer pixel de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    offset: Offset per avançar a la seguent linia de la regio.
/// \param    colorMode: Format de color de la regio.
/// \param    src: Punter al primer pixel del mapa de bits.
/// \param    srcOffset: Offset per avançar a la seguent linia del mapa de bits.
/// \param    srcColorMode: Format de color del mapa de bits.
///
void htl::DMA2D_startCopy(
	void* dst,
	int width,
	int height,
	int offset,
	DMA2DColorMode colorMode,
	const void* src,
	int srcOffset,
	DMA2DColorMode srcColorMode) {

	uint32_t temp;

	// Selecciona el tipus de transferencia com a M2M/PFC
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Selecciona el format del color del origen
	//
	temp = DMA2D->FGPFCCR;
	temp &= ~(0b1111 << DMA2D_FGPFCCR_CM_Pos);
	switch (srcColorMode) {
		default:
		case DMA2DColorMode::argb8888:
			temp |= 0b0000 << DMA2D_FGPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb888:
			temp |= 0b0001 << DMA2D_FGPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb565:
			temp |= 0b0010 << DMA2D_FGPFCCR_CM_Pos;
			break;
	}
	DMA2D->FGPFCCR = temp;

	// Selecciona el format de color del desti
	//
    temp = DMA2D->OPFCCR;
    temp &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
	switch (colorMode) {
		default:
		case DMA2DColorMode::argb8888:
			temp &= 0b000 << DMA2D_OPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb888:
			temp &= 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;

		case DMA2DColorMode::rgb565:
			temp &= 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;
	}
	DMA2D->OPFCCR = temp;

	// Selecciona l'adressa i el offset del origen
	//
	DMA2D->FGMAR = (uint32_t) src;
	DMA2D->FGOR = srcOffset & 0x3FFF;

	// Selecciona l'adressa i el offset del desti.
	//
	DMA2D->OMAR = (uint32_t) dst;
	DMA2D->OOR = offset & 0x3FFF;

	// Selecciona el tamany de la finestra
	//
	DMA2D->NLR =
		((width & 0x3FFF) << DMA2D_NLR_PL_Pos) |
		((height & 0xFFFF) << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= DMA2D_CR_START;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que acabi la transaccio.
/// \return   True si tot es correcte, false en cas d'error.
///
bool htl::DMA2D_waitForFinish() {

	// Espera que acabi
	//
	while ((DMA2D->ISR & DMA2D_ISR_TCIF_Msk) == 0) {

		// Si troba errors, finalitza
		//
		volatile uint32_t isr = DMA2D->ISR;
		if (((isr & DMA2D_ISR_CEIF_Msk) != 0) ||
			((isr & DMA2D_ISR_TEIF_Msk) != 0) ||
			((isr & DMA2D_ISR_CAEIF_Msk) != 0)) {

			// Borra els flags d'error
			//
			uint32_t tmp = DMA2D->IFCR;
			tmp |= (1 << DMA2D_IFCR_CCEIF_Pos);
			tmp |= (1 << DMA2D_IFCR_CTEIF_Pos);
			tmp |= (1 << DMA2D_IFCR_CAECIF_Pos);
			DMA2D->IFCR = tmp;

			// Retorna error
			//
			return false;
		}
	}

	// Borra el flag de transferencia complerta
	//
	DMA2D->IFCR |= DMA2D_IFCR_CTCIF;

	// Retorna OK
	//
	return true;
}
