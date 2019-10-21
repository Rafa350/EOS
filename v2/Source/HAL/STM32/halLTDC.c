#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halLTDC.h"



/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul LTDC.
/// \param    info: Informacio d'inicialitzacio.
///
void halLTDCInitialize(
	const LTDCInitializeInfo *info) {

	eosAssert(info != NULL);

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
   	tmp |= info->polarity.HSYNC << LTDC_GCR_HSPOL_Pos;
   	tmp |= info->polarity.VSYNC << LTDC_GCR_VSPOL_Pos;
  	tmp |= info->polarity.DE << LTDC_GCR_DEPOL_Pos;
    tmp |= info->polarity.PC << LTDC_GCR_PCPOL_Pos;
    LTDC->GCR = tmp;

    // Configura el registre SSCR (Sinchronization Size Configuration Register)
    //
    tmp = LTDC->SSCR;
    tmp &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
    tmp |= (info->HSYNC - 1) << LTDC_SSCR_HSW_Pos;
    tmp |= (info->VSYNC - 1) << LTDC_SSCR_VSH_Pos;
    LTDC->SSCR = tmp;

    // Configura el registre BPCR (Back Porch Configuration Register)
    //
    tmp = LTDC->BPCR;
    tmp &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
    tmp |= (info->HSYNC + info->HBP - 1) << LTDC_BPCR_AHBP_Pos;
    tmp |= (info->VSYNC + info->VBP - 1) << LTDC_BPCR_AVBP_Pos;
    LTDC->BPCR = tmp;

    // Configura el registre AWCR (Active Width Configuration Register)
    // -AAW = HSYNC + HBP + WIDTH - 1
    // -AAH = VSYNC + VBP + HEIGHT - 1
    //
    tmp = LTDC->AWCR;
    tmp &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
    tmp |= (info->HSYNC + info->HBP + info->width - 1) << LTDC_AWCR_AAW_Pos;
    tmp |= (info->VSYNC + info->VBP + info->height - 1) << LTDC_AWCR_AAH_Pos;
    LTDC->AWCR = tmp;

    // Configura el registre TWCR (Total Width Configuration Register)
    // -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
    // -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
    //
    tmp = LTDC->TWCR;
    tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    tmp |= (info->HSYNC + info->HBP + info->width + info->HFP - 1) << LTDC_TWCR_TOTALW_Pos;
    tmp |= (info->VSYNC + info->VBP + info->height + info->VFP - 1) << LTDC_TWCR_TOTALH_Pos;
    LTDC->TWCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul LTDC
///
void halLTDCShutdown() {

    RCC->APB2ENR &= ~RCC_APB2ENR_LTDCEN;
}


/// ----------------------------------------------------------------------
/// \brief    Canvia el color de fons de la pantalla.
/// \param    rgb: El color en formar RGB888
///
void halLTDCSetBackgroundColor(
	uint32_t rgb) {

    // Configura el registre BCCR (Back Color Configuration Register)
    //
    uint32_t tmp = LTDC->BCCR;
    tmp &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
    tmp |= ((rgb & 0x00FF0000) >> 16) << LTDC_BCCR_BCRED_Pos;
    tmp |= ((rgb & 0x0000FF00) >> 8) << LTDC_BCCR_BCGREEN_Pos;
    tmp |= (rgb & 0x000000FF) << LTDC_BCCR_BCBLUE_Pos;
    LTDC->BCCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la finestra de visualitzacio d'una capa.
/// \param    layerNum: Identificador de la capa.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada y de la posicio.
/// \param    width: Amplada de la capa.
/// \param    height: Alçada de la capa.
///
void halLTDCLayerSetWindow(
	LTDCLayerNum layerNum,
	int x,
	int y,
	int width,
	int height) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	uint32_t tmp;

    // Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
    // -Tamany horitzontal de la finestra
    //
	uint32_t ahbp = (LTDC->BPCR & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos;
    tmp = layer->WHPCR;
    tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    tmp |= (ahbp + x + 1) << LTDC_LxWHPCR_WHSTPOS_Pos;
    tmp |= (ahbp + width - x) << LTDC_LxWHPCR_WHSPPOS_Pos;
    layer->WHPCR = tmp;

    // Configura Lx_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
	uint32_t avbp = (LTDC->BPCR & LTDC_BPCR_AVBP) >> LTDC_BPCR_AVBP_Pos;
    tmp = layer->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= (avbp + y + 1) << LTDC_LxWVPCR_WVSTPOS_Pos;
    tmp |= (avbp + height - y) << LTDC_LxWVPCR_WVSPPOS_Pos;
    layer->WVPCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el color per defecte de la capa.
/// \param    layerNum: Identificador de la capa.
/// \param    argb: El color en formar ARGB8888
///
void halLTDCLayerSetDefaultColor(
	LTDCLayerNum layerNum,
	uint32_t argb) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

    // Configura Lx_DCCR (Default Color Configuration Register)
    // -Color per defecte
    //
    uint32_t tmp = layer->DCCR;
    tmp &= ~(LTDC_LxDCCR_DCALPHA | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCBLUE);
    tmp |= ((argb & 0xFF000000) >> 24) << LTDC_LxDCCR_DCALPHA_Pos;
    tmp |= ((argb & 0x00FF0000) >> 16) << LTDC_LxDCCR_DCRED_Pos;
    tmp |= ((argb & 0x0000FF00) >> 8) << LTDC_LxDCCR_DCGREEN_Pos;
    tmp |= (argb & 0x000000FF) << LTDC_LxDCCR_DCBLUE_Pos;
    layer->DCCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona i activa el color de transparencia.
/// \param    rgb: Color en format rgb888.
///
void halLTDCLayerSetKeyColor(
	LTDCLayerNum layerNum,
	uint32_t rgb) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	// Configura Lx_CKCR (Color Key Configuration Register)
    // -Color clau per croma e
    //
    uint32_t tmp = layer->CKCR;
    tmp &= ~(LTDC_LxCKCR_CKRED | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKBLUE);
    tmp |= ((rgb & 0x00FF0000) >> 16) << LTDC_LxCKCR_CKRED_Pos;
    tmp |= ((rgb & 0x0000FF00) >> 8) << LTDC_LxCKCR_CKGREEN_Pos;
    tmp |= (rgb & 0x000000FF) << LTDC_LxCKCR_CKBLUE_Pos;
    layer->CKCR = tmp;

    // Activa el color croma
    //
    layer->CR |= 1 << LTDC_LxCR_COLKEN_Pos;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el color de transparencia.
///
void halLTDCLayerDisableKeyColor(
	LTDCLayerNum layerNum) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;
    layer->CR &= ~(1 << LTDC_LxCR_COLKEN_Pos);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el format de la capa.
/// \param    layerNum: Identificador de la capa.
/// \param    pixelFormat: Format de pixel.
/// \param    lineWidth: Amplada de linia en bytes.
/// \param    linePitch: Pitch entre linies en bytes.
/// ºparam    numLines: Numero de linies.
///
void halLTDCLayerSetFrameFormat(
	LTDCLayerNum layerNum,
	LTDCPixelFormat pixelFormat,
	int lineWidth,
	int linePitch,
	int numLines) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

    // Selecciona la capa de a configurar
    //
	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	uint32_t tmp;

    // Configura Lx_PFCR (Pixel Format Configuration Register)
    //
    tmp = layer->PFCR;
    tmp &= ~(LTDC_LxPFCR_PF);
    switch (pixelFormat) {
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

    // Configura Lx_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = layer->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= linePitch << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= (lineWidth + 3) << LTDC_LxCFBLR_CFBLL_Pos;
    layer->CFBLR = tmp;

    // Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = layer->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= numLines;
    layer->CFBLNR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'adresa del buffer d'una capa.
/// \param    layerNum: Identificador de la capa.
/// \param    frameAddr: L'adresa del buffer.
/// \remarks  Si frameAddr es zeo, aleshores desactiva la capa.
///
void halLTDCLayerSetFrameAddress(
	LTDCLayerNum layerNum,
	int frameAddr) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	if (frameAddr == 0)
	    layer->CR &= (uint32_t) ~LTDC_LxCR_LEN;
	else {
		layer->CFBAR = (uint32_t) frameAddr;
		layer->CR |= (uint32_t) LTDC_LxCR_LEN;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualiza la configuracio de les capes
/// \param    layerNum: Identificador de la capa.
///
void halLTDCLayerUpdate(
	LTDCLayerNum layerNum) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

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
/// \brief    Obte el offset en bytes d'un pixel.
/// \param    layerNum: La capa
/// \param    x: Coordinada X del pixel.
/// \param    y: Coordinada Y del pixel;
/// \return   El offset calculat.
///
int halLTDCGetPixelOffset(
	LTDCLayerNum layerNum,
	int x,
	int y) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	int pitch = (layer->CFBLR & LTDC_LxCFBLR_CFBP_Msk) >> LTDC_LxCFBLR_CFBP_Pos;
	int pixBytes = 0;
	switch ((layer->PFCR & LTDC_LxPFCR_PF_Msk) >> LTDC_LxPFCR_PF_Pos) {
		default:
		case 0b001: // RGB888
		case 0b010: // RGB565
			pixBytes = 2;
			break;

		case 0b101: // L8
			pixBytes = 1;
			break;
	}

	return (y * pitch) + (x * pixBytes);
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

		case HAL_LTDC_FORMAT_L8:
			return 1;
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
