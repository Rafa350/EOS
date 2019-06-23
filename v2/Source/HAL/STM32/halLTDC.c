#include "eos.h"
#include "HAL/STM32/halLTDC.h"


/// ----------------------------------------------------------------------
/// \brief Asigna l'adresa del buffer d'una capa.
///
void halLTDCSetFrameAddress(
	int layerNum,
	int frameAddr) {

	LTDC_Layer_TypeDef *layer =
		layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	if (frameAddr == 0)
	    layer->CR &= (uint32_t) ~LTDC_LxCR_LEN;
	else {
		layer->CFBAR = frameAddr;
		layer->CR |= (uint32_t) LTDC_LxCR_LEN;
	}

	// Si el LTDC esta inactiu, fa l'actualitzacio inmediata
	//
    if ((LTDC->GCR & LTDC_GCR_LTDCEN) == 0)
    	LTDC->SRCR |=  LTDC_SRCR_IMR;

    // En cas contrari, fa l'actualitzacio durant la sincronitzacio
    // vertical, i espera que finalitzi.
    //
    else {
    	LTDC->SRCR |=  LTDC_SRCR_VBR;
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
			continue;
    }
}


/// ----------------------------------------------------------------------
/// \brief procesa les interrupcions.
///
void LTDC_IRQHandler() {

}


/// ----------------------------------------------------------------------
/// \brief procesa les interrupcions.
///
void LTDC_ER_IRQHandler() {

}
