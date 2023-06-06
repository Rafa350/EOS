#include "HTL/htl.h"
#include "HTL/STM32/htlDMA2D.h"


using namespace htl::dma2d;


DMA2DDevice DMA2DDevice::_device;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DMA2DDevice::DMA2DDevice(){
    
}


/// ----------------------------------------------------------------------
/// \brief Activa el modul
///
void DMA2DDevice::activate() {

    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
    __DSB();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul.
///
void DMA2DDevice::deactivate() {

    RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2DEN;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void DMA2DDevice::initialize() {
    
    activate();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void DMA2DDevice::deinitialize() {
    
    deactivate();
}


/// ----------------------------------------------------------------------
/// \brief    Ompla una regio amb un color solid.
/// \param    ptr: Punter al primer pixel regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pitch: Pitch de la regio.
/// \param    colorMode: El format de color.
/// \param    color: El color.
/// \remarks  En aquest casa no hi ha conversio. El color d'entrada es
///           el mateix que el de sortida.
///
void DMA2DDevice::startFill(
	void *ptr,
	uint16_t width,
	uint16_t height,
	uint16_t pitch,
	OutputColorMode colorMode,
	uint32_t color) {

	// Selecciona el tipus de transferencia com a R2M
	//
	DMA2D->CR = 0b11 << DMA2D_CR_MODE_Pos;

	// Asigna el format de color
	//
	uint32_t opfccr = DMA2D->OPFCCR;
	opfccr &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
	opfccr |= (uint32_t(colorMode) & 0b111) << DMA2D_OPFCCR_CM_Pos;
	// Aqui tambe Swap Blue/Red
	// Aqui tambe Invert Alpha
	DMA2D->OPFCCR = opfccr;

	// Asigna el color
	//
	DMA2D->OCOLR = color;

	// Selecciona l'adressa i el offset del desti
	//
	DMA2D->OMAR = (uint32_t) ptr;
	DMA2D->OOR = (pitch - width) & 0x3FFF;

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
/// \param    ptr: Punter al primer pixel de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    pitch: Pitch de la regio.
/// \param    colorMode: Format de color de la regio.
/// \param    src: Punter al primer pixel del mapa de bits.
/// \param    srcPitch: Pitch del mapa de bits.
/// \param    srcColorMode: Format de color del mapa de bits.
///
void DMA2DDevice::startCopy(
	void *ptr,
	uint16_t width,
	uint16_t height,
	uint16_t pitch,
	OutputColorMode colorMode,
	const void* src,
	uint16_t srcPitch,
	InputColorMode srcColorMode) {

	// Selecciona el tipus de transferencia com a M2M/PFC
	//
	DMA2D->CR = 0b01 << DMA2D_CR_MODE_Pos;

	// Selecciona el format del color del origen
	//
	uint32_t fgpfccr = DMA2D->FGPFCCR;
	fgpfccr &= ~(0b1111 << DMA2D_FGPFCCR_CM_Pos);
	fgpfccr |= (uint32_t(srcColorMode) & 0b1111) << DMA2D_FGPFCCR_CM_Pos;
	DMA2D->FGPFCCR = fgpfccr;

	// Selecciona el format de color del desti
	//
    uint32_t opfccr = DMA2D->OPFCCR;
    opfccr &= ~(0b111 << DMA2D_OPFCCR_CM_Pos);
    opfccr |= (uint32_t(colorMode) & 0b111) << DMA2D_OPFCCR_CM_Pos;
	// Aqui tambe Swap Blue/Red
	// Aqui tambe Invert Alpha
	DMA2D->OPFCCR = opfccr;

	// Selecciona l'adressa i el offset del origen
	//
	DMA2D->FGMAR = (uint32_t) src;
	DMA2D->FGOR = (srcPitch - width) & 0x3FFF;

	// Selecciona l'adressa i el offset del desti.
	//
	DMA2D->OMAR = (uint32_t) ptr;
	DMA2D->OOR = (pitch - width) & 0x3FFF;

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
bool DMA2DDevice::waitForFinish() {

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


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void DMA2DDevice::interruptService() {
      
}
