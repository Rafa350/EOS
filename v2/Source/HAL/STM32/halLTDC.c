#include "HAL/hal.h"
#include "HAL/STM32/halLTDC.h"


/// ----------------------------------------------------------------------
/// \brief    Enable LTDC device clock.
///
static void enableDeviceClock() {

    __set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
    __DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Disable LTDC device clock.
///
static void disableDeviceClock() {

    __clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
}


/// ----------------------------------------------------------------------
/// \brief    Configure LTDC peripheral clocks.
///
__attribute__((weak)) void configureLTDCDeviceClock() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul LTDC.
/// \param    info: Informacio d'inicialitzacio.
///
void halLTDCInitialize(
	const halLTDCSettings *settings) {

	eosAssert(settings != NULL);

	uint32_t tmp;

	configureLTDCDeviceClock();
	enableDeviceClock();

    // Configure el registre GCR (General Configuration Register)
    // -Polaritat HSYNC, VSYNC, DE i PC
    //
    tmp = LTDC->GCR;
    tmp &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL | LTDC_GCR_LTDCEN);
   	tmp |= settings->polarity.HSYNC << LTDC_GCR_HSPOL_Pos;
   	tmp |= settings->polarity.VSYNC << LTDC_GCR_VSPOL_Pos;
  	tmp |= settings->polarity.DE << LTDC_GCR_DEPOL_Pos;
    tmp |= settings->polarity.PC << LTDC_GCR_PCPOL_Pos;
    LTDC->GCR = tmp;

    // Configura el registre SSCR (Sinchronization Size Configuration Register)
    //
    tmp = LTDC->SSCR;
    tmp &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
    tmp |= ((settings->HSYNC - 1) << LTDC_SSCR_HSW_Pos) & LTDC_SSCR_HSW;
    tmp |= ((settings->VSYNC - 1) << LTDC_SSCR_VSH_Pos) & LTDC_SSCR_VSH;
    LTDC->SSCR = tmp;

    // Configura el registre BPCR (Back Porch Configuration Register)
    //
    tmp = LTDC->BPCR;
    tmp &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
    tmp |= ((settings->HSYNC + settings->HBP - 1) << LTDC_BPCR_AHBP_Pos) & LTDC_BPCR_AHBP;
    tmp |= ((settings->VSYNC + settings->VBP - 1) << LTDC_BPCR_AVBP_Pos) & LTDC_BPCR_AVBP;
    LTDC->BPCR = tmp;

    // Configura el registre AWCR (Active Width Configuration Register)
    // -AAW = HSYNC + HBP + WIDTH - 1
    // -AAH = VSYNC + VBP + HEIGHT - 1
    //
    tmp = LTDC->AWCR;
    tmp &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
    tmp |= ((settings->HSYNC + settings->HBP + (uint16_t)settings->width - 1) << LTDC_AWCR_AAW_Pos) & LTDC_AWCR_AAW;
    tmp |= ((settings->VSYNC + settings->VBP + (uint16_t)settings->height - 1) << LTDC_AWCR_AAH_Pos) & LTDC_AWCR_AAH;
    LTDC->AWCR = tmp;

    // Configura el registre TWCR (Total Width Configuration Register)
    // -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
    // -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
    //
    tmp = LTDC->TWCR;
    tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    tmp |= ((settings->HSYNC + settings->HBP + (uint16_t)settings->width + settings->HFP - 1) << LTDC_TWCR_TOTALW_Pos) & LTDC_TWCR_TOTALW;
    tmp |= ((settings->VSYNC + settings->VBP + (uint16_t)settings->height + settings->VFP - 1) << LTDC_TWCR_TOTALH_Pos) & LTDC_TWCR_TOTALH;
    LTDC->TWCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul LTDC
///
void halLTDCDeinitialize() {

	disableDeviceClock();
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
/// \param    x: Coordinada x de la posicio de la finestra.
/// \param    y: Coordinada y de la posicio de la finestra.
/// \param    width: Amplada de la finestra.
/// \param    height: Alçada de la finestra.
///
void halLTDCLayerSetWindow(
	halLTDCLayerNum layerNum,
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
    tmp |= ((ahbp + x + 1) << LTDC_LxWHPCR_WHSTPOS_Pos) & LTDC_LxWHPCR_WHSTPOS;
    tmp |= ((ahbp + width - x) << LTDC_LxWHPCR_WHSPPOS_Pos) & LTDC_LxWHPCR_WHSPPOS;
    layer->WHPCR = tmp;

    // Configura Lx_WHPCR (Window Vertical Position Configuration Register)
    // -Tamany vertical de la finestra
    //
	uint32_t avbp = (LTDC->BPCR & LTDC_BPCR_AVBP) >> LTDC_BPCR_AVBP_Pos;
    tmp = layer->WVPCR;
    tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    tmp |= ((avbp + y + 1) << LTDC_LxWVPCR_WVSTPOS_Pos) & LTDC_LxWVPCR_WVSTPOS;
    tmp |= ((avbp + height - y) << LTDC_LxWVPCR_WVSPPOS_Pos) & LTDC_LxWVPCR_WVSPPOS;
    layer->WVPCR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el color per defecte de la capa.
/// \param    layerNum: Identificador de la capa.
/// \param    argb: El color en format ARGB8888
///
void halLTDCLayerSetDefaultColor(
	halLTDCLayerNum layerNum,
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
	halLTDCLayerNum layerNum,
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
    __set_bit_msk(layer->CR, LTDC_LxCR_COLKEN);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el color de transparencia.
///
void halLTDCLayerDisableKeyColor(
	halLTDCLayerNum layerNum) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;
    __clear_bit_msk(layer->CR, LTDC_LxCR_COLKEN);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el format de la capa.
/// \param    layerNum: Identificador de la capa.
/// \param    format: Format de pixel.
/// \param    lineWidth: Amplada de linia en bytes.
/// \param    linePitch: Pitch entre linies en bytes.
/// \param    numLines: Numero de linies.
///
// TODO: Parametres en pixels i despres convertirlos a bytes;
void halLTDCLayerSetFrameFormat(
	halLTDCLayerNum layerNum,
	halLTDCPixelFormat format,
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
    switch (format) {
    	case HAL_LTDC_FORMAT_RGB565:
    		tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
    		break;

    	case HAL_LTDC_FORMAT_RGB888:
    		tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
    		break;

    	case HAL_LTDC_FORMAT_L8:
    		tmp |= 0b101 << LTDC_LxPFCR_PF_Pos;
    		break;

    	default:
    		break;
    }
    layer->PFCR = tmp;

    // Converteix les mides de pixels a bytes
    //
    //int pixelSize = halLTDCGetPixelBytes(format);

    // Configura Lx_CFBLR (Color Frame Buffer Length Register)
    // -Longitut de la linia en bytes.
    //
    tmp = layer->CFBLR;
    tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    tmp |= (linePitch & 0x1FFF) << LTDC_LxCFBLR_CFBP_Pos;
    tmp |= ((lineWidth + 3) & 0x1FFF) << LTDC_LxCFBLR_CFBLL_Pos;
    layer->CFBLR = tmp;

    // Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
    //
    tmp = layer->CFBLNR;
    tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    tmp |= numLines & LTDC_LxCFBLNR_CFBLNBR;
    layer->CFBLNR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el bufer a una capa.
/// \param    layerNum: Identificador de la capa.
/// \param    buffer: Punter al buffer
/// \remarks  Si frame es nul, aleshores desactiva la capa.
///
void halLTDCLayerSetFrameBuffer(
	halLTDCLayerNum layerNum,
	void *buffer) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	if (buffer == 0)
	    __clear_bit_msk(layer->CR, LTDC_LxCR_LEN);
	else {
		layer->CFBAR = (uint32_t)buffer;
		__set_bit_msk(layer->CR, LTDC_LxCR_LEN);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualiza la configuracio de les capes
/// \param    layerNum: Identificador de la capa.
///
void halLTDCLayerUpdate(
	halLTDCLayerNum layerNum) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	// Si el LTDC esta inactiu, fa l'actualitzacio inmediata
	//
    if ((LTDC->GCR & LTDC_GCR_LTDCEN) == 0)
    	__set_bit_msk(LTDC->SRCR, LTDC_SRCR_IMR);

    // En cas contrari, fa l'actualitzacio durant la sincronitzacio
    // vertical, i espera que finalitzi.
    //
    else {
    	__set_bit_msk(LTDC->SRCR, LTDC_SRCR_VBR);
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
			continue;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Obte el offset en bytes d'un pixel.
/// \param    layerNum: La capa
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \return   El offset calculat.
///
int halLTDCGetPixelOffset(
	halLTDCLayerNum layerNum,
	int x,
	int y) {

	eosAssert((layerNum == HAL_LTDC_LAYER_0) || (layerNum == HAL_LTDC_LAYER_1));

	LTDC_Layer_TypeDef *layer = layerNum == 0 ? LTDC_Layer1 : LTDC_Layer2;

	int lineBytes = (layer->CFBLR & LTDC_LxCFBLR_CFBP_Msk) >> LTDC_LxCFBLR_CFBP_Pos;
	int pixelBytes = 0;
	switch ((layer->PFCR & LTDC_LxPFCR_PF_Msk) >> LTDC_LxPFCR_PF_Pos) {
		default:
		case 0b001: // RGB888
		case 0b010: // RGB565
			pixelBytes = 2;
			break;

		case 0b101: // L8
			pixelBytes = 1;
			break;
	}

	return (y * lineBytes) + (x * pixelBytes);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la tamany en bytes d'un pixel.
/// \param    format: El format de pixel.
/// \return   El resultat.
///
uint8_t halLTDCGetPixelBytes(
	halLTDCPixelFormat format) {

	switch (format) {
		default:
		case HAL_LTDC_FORMAT_RGB565:
		case HAL_LTDC_FORMAT_RGB888:
			return 2;

		case HAL_LTDC_FORMAT_L8:
			return 1;
	}
}


/// ---------------------------------------------------------------------
/// \brief    Procesa les interrupcions del dispositiu.
///
void halLTDCInterruptHandler() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void LTDC_IRQHandler() {

	halLTDCInterruptHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void LTDC_ER_IRQHandler() {

	halLTDCInterruptHandler();
}
