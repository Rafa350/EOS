#include "eos.h"
#include "HAL/STM32/halDMA2D.h"


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul DMA2D
///
void halDMA2DInitialize() {

	// Activa el modul DMA2D
	//
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
}


/// ----------------------------------------------------------------------
/// \brief Ompla una regio amb un color solid.
/// \param dstAddr: Adressa del primer pixel de la regio.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param dstPitch: Offset per avançar a la seguent linia de la regio.
/// \param options: Opcions
/// \param color: Color per omplir.
///
void halDMA2DStartFill(
	int dstAddr,
	int width,
	int height,
	int dstPitch,
	DMA2DOptions options,
	uint32_t color) {

	// Selecciona el tipus de transferencia com a R2M
	//
	DMA2D->CR = 0b11 << DMA2D_CR_MODE_Pos;

	// Selecciona el color i el format de color del desti.
	//
	switch (options & HAL_DMA2D_DFMT_mask) {
		case HAL_DMA2D_DFMT_RGB565: // RGB565
			DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;

		default:
		case HAL_DMA2D_DFMT_RGB888: // RGB888
			DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;
	}
	DMA2D->OCOLR = color;

	// Selecciona l'adressa i el pitch del desti
	//
	DMA2D->OMAR = dstAddr;
	DMA2D->OOR = dstPitch;

	// Selecciona el tamany de la finestra
	//
	DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;
}


/// ----------------------------------------------------------------------
/// \brief Copia un mapa de bits a una regio.
/// \param dstAddr: Adresa del primer pixel de la regio.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param dstPitch: Offset per avançar a la seguent linia de la regio.
/// \param options: Opcions.
/// \param srcAddr: Adressa del primer pixel del mapa de bits.
/// \param srcPitch: Offset per avançar a la seguent linia del mapa de bits.
///
void halDMA2DStartCopy(
	int dstAddr,
	int width,
	int height,
	int dstPitch,
	DMA2DOptions options,
	int srcAddr,
	int srcPitch) {

	// Selecciona el tipus de transferencia com a M2M/PFC
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Selecciona el format del color del origen
	//
	switch (options & HAL_DMA2D_SFMT_mask) {
		case HAL_DMA2D_SFMT_RGB888:
			DMA2D->FGPFCCR = 0b0001 << DMA2D_FGPFCCR_CM_Pos;
			break;

		case HAL_DMA2D_SFMT_RGB565:
			DMA2D->FGPFCCR = 0b0010 << DMA2D_FGPFCCR_CM_Pos;
			break;

		default:
		case HAL_DMA2D_SFMT_ARGB8888:
			DMA2D->FGPFCCR = 0b0000 << DMA2D_FGPFCCR_CM_Pos;
			break;
	}

	// Selecciona el format de color del desti
	//
	switch (options & HAL_DMA2D_DFMT_mask) {
		case HAL_DMA2D_DFMT_RGB565:
			DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;

		default:
		case HAL_DMA2D_DFMT_RGB888:
			DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;
	}

	// Selecciona l'adressa i el pitch del origen
	//
	DMA2D->FGMAR = srcAddr;
	DMA2D->FGOR = srcPitch;

	// Selecciona l'adressa i el pitch del desti.
	//
	DMA2D->OMAR = dstAddr;
	DMA2D->OOR = dstPitch;

	// Selecciona el tamany de la finestra
	//
	DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;
}


/// ----------------------------------------------------------------------
/// \brief Espera que acabi la transaccio.
/// \return True si tot es correcte, false en cas d'error.
///
bool halDMA2DWaitForFinish() {

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
	DMA2D->IFCR |= 1 << DMA2D_IFCR_CTCIF_Pos;

	// Retorna OK
	//
	return true;
}


/// ----------------------------------------------------------------------
/// \brief Procesa les interrupcions
///
void DMA2D_IRQHandler() {

}
