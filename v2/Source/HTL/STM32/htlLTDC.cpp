#include "HTL/htl.h"
#include "HTL/STM32/htlLTDC.h"


using namespace htl;
using namespace htl::ltdc;


LTDCDevice LTDCDevice::_instance;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
LTDCDevice::LTDCDevice() {
}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu.
///
void LTDCDevice::activate() {

	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
	__DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu.
///
void LTDCDevice::deactivate() {

	RCC->APB2ENR &= ~RCC_APB2ENR_LTDCEN;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void LTDCDevice::initialize(
	uint16_t width,
	uint16_t height,
	uint16_t hSync,
	uint16_t vSync,
	uint16_t hBP,
	uint16_t vBP,
	uint16_t hFP,
	uint16_t vFP) {

	activate();
	disable();

	// Configura el registre SSCR (Sinchronization Size Configuration Register)
	//
	uint32_t sscr = LTDC->SSCR;
	sscr &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
	sscr |= ((hSync - 1) << LTDC_SSCR_HSW_Pos) & LTDC_SSCR_HSW;
	sscr |= ((vSync - 1) << LTDC_SSCR_VSH_Pos) & LTDC_SSCR_VSH;
	LTDC->SSCR = sscr;

	// Configura el registre BPCR (Back Porch Configuration Register)
	//
	uint32_t bpcr = LTDC->BPCR;
	bpcr &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
	bpcr |= ((hSync + hBP - 1) << LTDC_BPCR_AHBP_Pos) & LTDC_BPCR_AHBP;
	bpcr |= ((vSync + vBP - 1) << LTDC_BPCR_AVBP_Pos) & LTDC_BPCR_AVBP;
	LTDC->BPCR = bpcr;

	// Configura el registre AWCR (Active Width Configuration Register)
	// -AAW = HSYNC + HBP + WIDTH - 1
	// -AAH = VSYNC + VBP + HEIGHT - 1
	//
	uint32_t awcr = LTDC->AWCR;
	awcr &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
	awcr |= ((hSync + hBP + width - 1) << LTDC_AWCR_AAW_Pos) & LTDC_AWCR_AAW;
	awcr |= ((vSync + vBP + height - 1) << LTDC_AWCR_AAH_Pos) & LTDC_AWCR_AAH;
	LTDC->AWCR = awcr;

	// Configura el registre TWCR (Total Width Configuration Register)
	// -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
	// -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
	//
	uint32_t twcr = LTDC->TWCR;
	twcr &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
	twcr |= ((hSync + hBP + width + hFP - 1) << LTDC_TWCR_TOTALW_Pos) & LTDC_TWCR_TOTALW;
	twcr |= ((vSync + vBP + height + vFP - 1) << LTDC_TWCR_TOTALH_Pos) & LTDC_TWCR_TOTALH;
	LTDC->TWCR = twcr;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void LTDCDevice::deinitialize() {

	disable();
	deactivate();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el color sde fons.
/// \param    rgb: El color en formar RGB888
///
void LTDCDevice::setBackgroundColor(
	uint32_t rgb) {

	// Configura el registre BCCR (Back Color Configuration Register)
	//
	uint32_t bccr = LTDC->BCCR;
	bccr &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
	bccr |= ((rgb & 0x00FF0000) >> 16) << LTDC_BCCR_BCRED_Pos;
	bccr |= ((rgb & 0x0000FF00) >> 8) << LTDC_BCCR_BCGREEN_Pos;
	bccr |= (rgb & 0x000000FF) << LTDC_BCCR_BCBLUE_Pos;
	LTDC->BCCR = bccr;
}


/// ----------------------------------------------------------------------
/// \brief    Refresca la pantalla
///
void LTDCDevice::reload() {

	// Si el LTDC no esta actiu, fa una actualitzacio immediata
	//
	if ((LTDC->GCR & LTDC_GCR_LTDCEN) == 0)
		LTDC->SRCR |= LTDC_SRCR_IMR;

	// En cas contrari, fa l'actualitzacio durant la sincronitzacio
	// vertical, i espera que finalitzi.
	//
	else {
		LTDC->SRCR |= LTDC_SRCR_VBR;
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) != 0)
			continue;
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
			continue;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void LTDCDevice::interruptService() {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    layer: Registres de hardware del modul LTDC_Layer.
///
LTDCLayerDevice::LTDCLayerDevice(
	LTDC_Layer_TypeDef *layer):

	_layer(layer) {

}


void LTDCLayerDevice::setWindow(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

	// Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
	// -Tamany horitzontal de la finestra
	//
	uint32_t ahbp = (LTDC->BPCR & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos;
	uint32_t whpcr = _layer->WHPCR;
	whpcr &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
	whpcr |= ((ahbp + x + 1) << LTDC_LxWHPCR_WHSTPOS_Pos) & LTDC_LxWHPCR_WHSTPOS;
	whpcr |= ((ahbp + width - x) << LTDC_LxWHPCR_WHSPPOS_Pos) & LTDC_LxWHPCR_WHSPPOS;
	_layer->WHPCR = whpcr;

	// Configura Lx_WHPCR (Window Vertical Position Configuration Register)
	// -Tamany vertical de la finestra
	//
	uint32_t avbp = (LTDC->BPCR & LTDC_BPCR_AVBP) >> LTDC_BPCR_AVBP_Pos;
	uint32_t wvpcr = _layer->WVPCR;
	wvpcr &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
	wvpcr |= ((avbp + y + 1) << LTDC_LxWVPCR_WVSTPOS_Pos) & LTDC_LxWVPCR_WVSTPOS;
	wvpcr |= ((avbp + height - y) << LTDC_LxWVPCR_WVSPPOS_Pos) & LTDC_LxWVPCR_WVSPPOS;
	_layer->WVPCR = wvpcr;
}


void LTDCLayerDevice::setFrameFormat(
	PixelFormat format,
	int16_t width,
	int16_t pitch,
	int16_t lines) {

	// Configura Lx_PFCR (Pixel Format Configuration Register)
	// -Format de color del buffer d'imatge.
	//
	uint32_t pfcr = _layer->PFCR;
	pfcr &= ~(0b111 << LTDC_LxPFCR_PF_Pos);
	pfcr |= (uint32_t(format) & 0b111) << LTDC_LxPFCR_PF_Pos;
	_layer->PFCR = pfcr;

	// Configura Lx_CFBLR (Color Frame Buffer Length Register)
	// -Longitut de la linia en bytes.
	//
	uint32_t cfblr = _layer->CFBLR;
	cfblr &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
	cfblr |= (pitch & 0x1FFF) << LTDC_LxCFBLR_CFBP_Pos;
	cfblr |= ((width + 3) & 0x1FFF) << LTDC_LxCFBLR_CFBLL_Pos;
	_layer->CFBLR = cfblr;

	// Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
	//
	uint32_t cfblnr = _layer->CFBLNR;
	cfblnr  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	cfblnr |= lines & LTDC_LxCFBLNR_CFBLNBR;
	_layer->CFBLNR = cfblnr;
}


/// ----------------------------------------------------------------------
/// \brief Asigna el buffer de la capa.
/// \param buffer: El buffer. Si es null, es desactiva la capa.
///
void LTDCLayerDevice::setFrameBuffer(
	void *buffer) {

	if (buffer == nullptr)
		disable();
	else
		_layer->CFBAR = (uint32_t)buffer;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna i activa la taula de colors (Valid per L8, AL44 i AL88)
/// \param    table: La taula de colors en format RGB888. Si es null,
///                  es desactiva.
///
void LTDCLayerDevice::setCLUTTable(
	uint32_t *rgb) {

	if ((_layer->CR & LTDC_LxCR_LEN) == 0) {
		if (rgb == nullptr)
			_layer->CR &= ~LTDC_LxCR_CLUTEN;
		else {
			for (uint32_t i = 0; i < 256; i++)
				_layer->CLUTWR = (i << LTDC_LxCLUTWR_CLUTADD_Pos) | (*rgb++ & 0x00FFFFFF);
			_layer->CR |= LTDC_LxCR_CLUTEN;
		}

		LTDC->SRCR |= LTDC_SRCR_IMR;
	}
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la taula de colors.
///
void LTDCLayerDevice::disableCLUTTable() {

	_layer->CR &= ~LTDC_LxCR_CLUTEN;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color per defecte.
/// \param    argb: El color en format ARGB8888
///
void LTDCLayerDevice::setDefaultColor(
	uint32_t argb) {

	// Configura Lx_DCCR (Default Color Configuration Register)
	// -Color per defecte
	//
	uint32_t dccr = _layer->DCCR;
	dccr &= ~(LTDC_LxDCCR_DCALPHA | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCBLUE);
	dccr |= ((argb & 0xFF000000) >> 24) << LTDC_LxDCCR_DCALPHA_Pos;
	dccr |= ((argb & 0x00FF0000) >> 16) << LTDC_LxDCCR_DCRED_Pos;
	dccr |= ((argb & 0x0000FF00) >> 8) << LTDC_LxDCCR_DCGREEN_Pos;
	dccr |= (argb & 0x000000FF) << LTDC_LxDCCR_DCBLUE_Pos;
	_layer->DCCR = dccr;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor ALPHA.
/// \param    a: El valor.
///
void LTDCLayerDevice::setConstantAlpha(
	uint8_t a) {

	_layer->CACR = a;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el color croma i l'activa.
/// \param    rgb: El color en format RGB888
///
void LTDCLayerDevice::setKeyColor(
	uint32_t rgb) {

	// Configura Lx_CKCR (Color Key Configuration Register)
	// -Color clau per croma e
	//
	uint32_t ckcr = _layer->CKCR;
	ckcr &= ~(LTDC_LxCKCR_CKRED | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKBLUE);
	ckcr |= ((rgb & 0x00FF0000) >> 16) << LTDC_LxCKCR_CKRED_Pos;
	ckcr |= ((rgb & 0x0000FF00) >> 8) << LTDC_LxCKCR_CKGREEN_Pos;
	ckcr |= (rgb & 0x000000FF) << LTDC_LxCKCR_CKBLUE_Pos;
	_layer->CKCR = ckcr;

	// Activa el color croma
	//
	_layer->CR |= LTDC_LxCR_COLKEN;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el color croma.
///
void LTDCLayerDevice::disableKeyColor() {

	_layer->CR &= ~LTDC_LxCR_COLKEN;
}
