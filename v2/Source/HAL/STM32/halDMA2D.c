#include "eos.h"
#include "HAL/STM32/halDMA2D.h"


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul DMA2D
///
void halDMA2DInitialize(void) {

	// Activa el modul DMA2D
	//
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
}


/// ----------------------------------------------------------------------
/// \brief Ompla una regio amb un color.
/// \param[in] addr: Adressa del primer pixel del desti.
/// \param[in] width: Amplada de la regio.
/// \param[in] height: Alçáda de la regio.
/// \param[in] pitch: Offset entre linies.
/// \param[in] options: Opcions
/// \param[in] color: Color per omplir.
///
void halDMA2DFill(
	int addr,
	int width,
	int height,
	int pitch,
	DMA2DOptions options,
	uint32_t color) {

	// Tipus de transferencia R2M
	//
	DMA2D->CR = 0b11 << DMA2D_CR_MODE_Pos;

	// Format de color del desti
	//
	switch (options & HAL_DMA2D_DFMT_MASK) {
		case HAL_DMA2D_DFMT_RGB565: // RGB565
			DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;

		default:
		case HAL_DMA2D_DFMT_RGB888: // RGB888
			DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;
	}
	DMA2D->OCOLR = color;

	// Adressa i pitch del desti
	//
	DMA2D->OMAR = addr;
	DMA2D->OOR = pitch;

	// Tamany de la finestra
	//
	DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);

	// Inicia la transferencia
	//
	DMA2D->CR |= 1 << DMA2D_CR_START_Pos;
}


/// ----------------------------------------------------------------------
/// \brief Copia una regio.
/// \param[in] addr: Adresa del primer pixel del desti.
/// \param[in] width: Amplada de la regio.
/// \param[in] height: Alçada de la regio.
/// \param[in] pitch: Offset entre linies.
/// \param[in] options: Opcions.
/// \param[in] srcAddr: Adressa del primer pixel del origen.
///
void halDMA2DCopy(
	int addr,
	int width,
	int height,
	int pitch,
	DMA2DOptions options,
	int srcAddr,
	int dx,
	int dy,
	int sPitch) {

	// Tipus de transferencia M2M/PFC
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Format del color del origen
	//
	switch (options & HAL_DMA2D_SFMT_MASK) {
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

	// Format de color del desti
	//
	switch (options & HAL_DMA2D_DFMT_MASK) {
		case HAL_DMA2D_DFMT_RGB565:
			DMA2D->OPFCCR = 0b010 << DMA2D_OPFCCR_CM_Pos;
			break;

		default:
		case HAL_DMA2D_DFMT_RGB888:
			DMA2D->OPFCCR = 0b001 << DMA2D_OPFCCR_CM_Pos;
			break;
	}

	// Adressa i pitch del origen
	//
	int orgAddr = (dy * sPitch) + dx;
	switch (options & HAL_DMA2D_SFMT_MASK) {
		default:
		case HAL_DMA2D_SFMT_RGB888:
		case HAL_DMA2D_SFMT_ARGB8888:
			orgAddr *= sizeof(uint32_t);
			break;

		case HAL_DMA2D_SFMT_RGB565:
			orgAddr *= sizeof(uint16_t);
			break;
	}
	orgAddr += srcAddr;
	DMA2D->FGMAR = orgAddr;
	DMA2D->FGOR = sPitch - width;

	// Adressa i pitch del desti
	//
	DMA2D->OMAR = addr;
	DMA2D->OOR = pitch;

	// Tamany de la finestra
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
bool halDMA2DWaitForFinish(void) {

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

