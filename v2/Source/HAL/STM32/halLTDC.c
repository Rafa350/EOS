#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halLTDC.h"



/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul LTDC.
/// \param    pInfo: Informacio d'inicialitzacio.
///
void halLTDCInitialize(
	const LTDCInitializeInfo *pInfo) {

	eosAssert(pInfo != NULL);

	uint32_t tmp;

	// Configura el rellotge
	// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
	// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
	// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
	// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
	//
	RCC_PeriphCLKInitTypeDef clkInit;
	clkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	clkInit.PLLSAI.PLLSAIN = 192;
	clkInit.PLLSAI.PLLSAIR = DISPLAY_FDIV;
	clkInit.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&clkInit);

    // Activa el modul LTDC
    //
    RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;

    // Configure el registre GCR (General Configuration Register)
    // -Polaritat HSYNC, VSYNC, DE i PC
    //
    tmp = LTDC->GCR;
    tmp &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
   	tmp |= pInfo->polarity.HSYNC << LTDC_GCR_HSPOL_Pos;
   	tmp |= pInfo->polarity.VSYNC << LTDC_GCR_VSPOL_Pos;
  	tmp |= pInfo->polarity.DE << LTDC_GCR_DEPOL_Pos;
    tmp |= pInfo->polarity.PC << LTDC_GCR_PCPOL_Pos;
    LTDC->GCR = tmp;

    // Configura el registre SSCR (Sinchronization Size Configuration Register)
    //
    tmp = LTDC->SSCR;
    tmp &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
    tmp |= (pInfo->HSYNC - 1) << LTDC_SSCR_HSW_Pos;
    tmp |= (pInfo->VSYNC - 1) << LTDC_SSCR_VSH_Pos;
    LTDC->SSCR = tmp;

    // Configura el registre BPCR (Back Porch Configuration Register)
    //
    tmp = LTDC->BPCR;
    tmp &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
    tmp |= (pInfo->HSYNC + pInfo->HBP - 1) << LTDC_BPCR_AHBP_Pos;
    tmp |= (pInfo->VSYNC + pInfo->VBP - 1) << LTDC_BPCR_AVBP_Pos;
    LTDC->BPCR = tmp;

    // Configura el registre AWCR (Active Width Configuration Register)
    // -AAH = HSYNC + HBP + WIDTH - 1
    // -AAW = VSYNC + VBP + HEIGHT - 1
    //
    tmp = LTDC->AWCR;
    tmp &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
    tmp |= (pInfo->HSYNC + pInfo->HBP + pInfo->width - 1) << LTDC_AWCR_AAW_Pos;
    tmp |= (pInfo->VSYNC + pInfo->VBP + pInfo->height - 1) << LTDC_AWCR_AAH_Pos;
    LTDC->AWCR = tmp;

    // Configura el registre TWCR (Total Width Configuration Register)
    // -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
    // -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
    //
    tmp = LTDC->TWCR;
    tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    tmp |= (pInfo->HSYNC + pInfo->HBP + pInfo->width + pInfo->HFP - 1) << LTDC_TWCR_TOTALW_Pos;
    tmp |= (pInfo->VSYNC + pInfo->VBP + pInfo->height + pInfo->VFP - 1) << LTDC_TWCR_TOTALH_Pos;
    LTDC->TWCR = tmp;

    // Configura el registre BCCR (Back Color Configuration Register)
    //
    tmp = LTDC->BCCR;
    tmp &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
    tmp |= pInfo->backgroundColor.R << LTDC_BCCR_BCRED_Pos;
    tmp |= pInfo->backgroundColor.G << LTDC_BCCR_BCGREEN_Pos;
    tmp |= pInfo->backgroundColor.B << LTDC_BCCR_BCBLUE_Pos;
    LTDC->BCCR = tmp;

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul LTDC.
/// \param    layerNum: Numero de capa.
/// \param    pInfo: Informacio d'inicialitzacio.
///
void halLTDCInitializeLayer(
	LTDCLayerNum layerNum,
	const LTDCInitializeLayerInfo *pInfo) {

	eosAssert(pInfo != NULL);
	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

    // Selecciona la capa de a configurar
    //
	LTDC_Layer_TypeDef *layer =
		layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	uint32_t tmp;

    // Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
    // -Tamany horitzontal de la finestra
    //
	uint32_t aaw = (LTDC->AWCR & LTDC_AWCR_AAW) >> LTDC_AWCR_AAW_Pos;
	uint32_t ahbp = (LTDC->BPCR & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos;

    tmp = layer->WHPCR;
    tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + 1) << LTDC_LxWHPCR_WHSTPOS_Pos;
    tmp |= ((DISPLAY_HSYNC + DISPLAY_HBP - 1) + DISPLAY_IMAGE_WIDTH) << LTDC_LxWHPCR_WHSPPOS_Pos;
    layer->WHPCR = tmp;

    // Configura Lx_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
    tmp = layer->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + 1) << LTDC_LxWVPCR_WVSTPOS_Pos;
    tmp |= ((DISPLAY_VSYNC + DISPLAY_VBP - 1) + DISPLAY_IMAGE_HEIGHT) << LTDC_LxWVPCR_WVSPPOS_Pos;
    layer->WVPCR = tmp;

    // Configura Lx_DCCR (Default Color Configuration Register)
    // -Color per defecte
    //
    tmp = layer->DCCR;
    tmp &= ~(LTDC_LxDCCR_DCALPHA | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCBLUE);
    tmp |= pInfo->defaultColor.A << LTDC_LxDCCR_DCALPHA_Pos;
    tmp |= pInfo->defaultColor.R << LTDC_LxDCCR_DCRED_Pos;
    tmp |= pInfo->defaultColor.G << LTDC_LxDCCR_DCGREEN_Pos;
    tmp |= pInfo->defaultColor.B << LTDC_LxDCCR_DCBLUE_Pos;
    layer->DCCR = tmp;

    // Configura Lx_PFCR (Pixel Format Configuration Register)
    //
    tmp = layer->PFCR;
    tmp &= ~(LTDC_LxPFCR_PF);
    switch (pInfo->pixelFormat) {
    	case HAL_LTDC_FORMAT_RGB565:
    		tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
    		break;

    	case HAL_LTDC_FORMAT_RGB888:
    		tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
    		break;

    	case HAL_LTDC_FORMAT_L8:
    		tmp |= 0b101 << LTDC_LxPFCR_PF_Pos;
    		break;
    }
    layer->PFCR = tmp;

    // Configura Lx_CACR (Constant Alpha Configuration Register)
    //
    tmp = layer->CACR;
    tmp &= ~(LTDC_LxCACR_CONSTA);
    tmp |= pInfo->constantAlpha;
    layer->CACR;

    // Configura Lx_BFCR
    // -Specifies the blending factors
    //
    tmp = layer->BFCR;
    tmp &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
    tmp |= 6 << LTDC_LxBFCR_BF1_Pos;
    tmp |= 7 << LTDC_LxBFCR_BF2_Pos;
    layer->BFCR = tmp;

    // Configura Lx_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = layer->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= (((pInfo->width * halLTDCGetPixelSize(pInfo->pixelFormat)) + 63) & 0xFFFFFFC0) << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= ((pInfo->width * halLTDCGetPixelSize(pInfo->pixelFormat)) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
    layer->CFBLR = tmp;

    // Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = layer->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= pInfo->height;
    layer->CFBLNR = tmp;

    // Actualitza els parametres de la capa inmediatament
    //
	LTDC->SRCR |= LTDC_SRCR_IMR;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'adresa del buffer d'una capa.
/// \param    layerNum: Identificador de la capa.
/// \param    frameAddr: L'adresa del buffer.
///
void halLTDCSetFrameAddress(
	LTDCLayerNum layerNum,
	int frameAddr) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer =
		layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	if (frameAddr == 0)
	    layer->CR &= (uint32_t) ~LTDC_LxCR_LEN;
	else {
		layer->CFBAR = (uint32_t) frameAddr;
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
/// \brief    Obte la longitut en bytes d'un pixel.
/// \param    format: El format de pixel.
/// \return   El resultat.
///
uint8_t halLTDCGetPixelSize(
	LTDCPixelFormat format) {

	switch (format) {
		default:
		case HAL_LTDC_FORMAT_RGB565:
		case HAL_LTDC_FORMAT_RGB888:
			return 2;
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
