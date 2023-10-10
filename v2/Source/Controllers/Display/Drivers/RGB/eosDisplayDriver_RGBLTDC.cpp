#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColorDefinitions.h"


#ifndef HTL_LTDC_EXIST
#error "LTDC hardware unavailable"
#endif


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    frameBuffer1: Buffer d'imatge
/// \param    frameBuffer2: Buffer d'imatge (Si es vol doble buffer)
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC(
	FrameBuffer *frameBuffer1,
	FrameBuffer *frameBuffer2):

	_displayFrameBuffer(frameBuffer1),
	_workFrameBuffer(frameBuffer2 == nullptr? frameBuffer1 : frameBuffer2) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void DisplayDriver_RGBLTDC::initialize() {

	_displayFrameBuffer->clear(Colors::black);
	if (_displayFrameBuffer != _workFrameBuffer)
		_workFrameBuffer->clear(Colors::black);

	initializeGPIO();
	initializeLTDC();
}


/// ---------------------------------------------------------------------
/// \brief    Finalitza el driver.
///
void DisplayDriver_RGBLTDC::deinitialize() {

	disable();
}


/// ----------------------------------------------------------------------
/// \brief    Activa el display.
///
void DisplayDriver_RGBLTDC::enable() {

	auto ltdc(ltdc::LTDCDevice::getHandler());
	ltdc->enable();

	auto pinLCDE(PinLCDE::getHandler());
	pinLCDE->set();

	auto pinBKE(PinBKE::getHandler());
	pinBKE->set();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::disable() {

	auto pinLCDE(PinLCDE::getHandler());
	pinLCDE->clear();

	auto pinBKE(PinBKE::getHandler());
	pinBKE->clear();

	auto ltdc(ltdc::LTDCDevice::getHandler());
	ltdc->disable();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'orientacio de la pantalla.
/// \param    orientation: L'orientacio.
///
void DisplayDriver_RGBLTDC::setOrientation(
	DisplayOrientation orientation) {

	_workFrameBuffer->setOrientation(orientation);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la imatge.
/// \param    color: Color de borrat.
///
void DisplayDriver_RGBLTDC::clear(
	Color color) {

	_workFrameBuffer->clear(color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a un pixel.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixel(
	int16_t x,
	int16_t y,
	Color color) {

	_workFrameBuffer->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a una linia horitzontal.
/// \param    x: Coordinada x.
/// \param    y: Coordinada y.
/// \param    length: Longitut.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setHPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, size, 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Assigna un color a una linia vertical.
/// \param    x: Coordinada x.
/// \param    y: Coordinada x.
/// \param    length: Longitut de la linia.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, 1, size, color);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un color a una regio rectangular.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color color) {

	_workFrameBuffer->setPixels(x, y, width, height, color);
}


/// ----------------------------------------------------------------------
/// \brief    Copia una regio rectangular.
/// \param    x: Posicio x.
/// \param    y: Posicio y.
/// \param    width: Amplada.
/// \param    height: Alçada.
/// \param    colors: Regio a copiar
/// \param    pitch: Pitch de la regio a copiar.
///
void DisplayDriver_RGBLTDC::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors,
	int16_t pitch) {

	_workFrameBuffer->setPixels(x, y, width, height, colors, pitch);
}


/// ----------------------------------------------------------------------
/// \brief    Copia una lliosta de pixels una regio rectangular.
/// \param    x: Posicio x de la regio.
/// \param    y: Posicio y de la regio.
/// \param    width: Amplada de la regio.
/// \param    height: Alçada de la regio.
/// \param    colors: La llista de colors.
/// \param    colorFormat: Format de la llista de colors.
/// \param    colorPitch: Pitch de la llista de colors.
///
void DisplayDriver_RGBLTDC::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const void *colors,
	ColorFormat colorFormat,
	int16_t colorPitch) {

	_workFrameBuffer->setPixels(x, y, width, height, colors, colorFormat, colorPitch);
}


/// ----------------------------------------------------------------------
/// \brief Refresca la pantalla.
///
void DisplayDriver_RGBLTDC::refresh() {

	if (_workFrameBuffer != _displayFrameBuffer) {

		// Intercanvia els buffers
		//
		Math::swap(_displayFrameBuffer, _workFrameBuffer);

		// Asigna l'adresa de la capa
		//
		auto layer(ltdc::LTDCLayerDevice1::getHandler());
		layer->setFrameBuffer(_displayFrameBuffer->getBuffer());

		auto ltdc(ltdc::LTDCDevice::getHandler());
		ltdc->reload();
	}
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul GPIO.
///
void DisplayDriver_RGBLTDC::initializeGPIO() {

	auto hPinBKE = PinBKE::getHandler();
	hPinBKE->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, false);

	auto hPinLCDE = PinLCDE::getHandler();
	hPinLCDE->initOutput(gpio::OutputMode::pushPull, gpio::Speed::low, false);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void DisplayDriver_RGBLTDC::initializeLTDC() {

	// Inicialitza el modul LTDC
	//
	auto hLTDC = ltdc::LTDCDevice::getHandler();
	hLTDC->initPinPC<DISPLAY_PC_Pin, _pcPol>();
	hLTDC->initPinHSYNC<DISPLAY_HSYNC_Pin, _hSyncPol>();
	hLTDC->initPinVSYNC<DISPLAY_VSYNC_Pin, _vSyncPol>();
	hLTDC->initPinDE<DISPLAY_DE_Pin, _dePol>();
	hLTDC->initPinRX<PinR0, PinR1, PinR2, PinR3, PinR4, PinR5, PinR6, PinR7>();
	hLTDC->initPinGX<PinG0, PinG1, PinG2, PinG3, PinG4, PinG5, PinG6, PinG7>();
	hLTDC->initPinBX<PinB0, PinB1, PinB2, PinB3, PinB4, PinB5, PinB6, PinB7>();
	hLTDC->initialize(_displayWidth, _displayHeight, _hSync, _vSync, _hBP, _vBP, _hFP, _vFP);
	hLTDC->setBackgroundColor(0x0000FF);

	// Inicialitza la capa 1
	// La capa ocupa tota la superficie de la pantalla
	//
	constexpr ltdc::PixelFormat pixelFormat =
		Color::format == ColorFormat::argb8888 ? ltdc::PixelFormat::argb8888 :
		Color::format == ColorFormat::argb4444 ? ltdc::PixelFormat::argb4444 :
		Color::format == ColorFormat::argb1555 ? ltdc::PixelFormat::argb1555 :
		Color::format == ColorFormat::rgb888 ? ltdc::PixelFormat::rgb888 :
		Color::format == ColorFormat::al88 ? ltdc::PixelFormat::al88 :
		Color::format == ColorFormat::al44 ? ltdc::PixelFormat::al44 :
		Color::format == ColorFormat::l8 ? ltdc::PixelFormat::l8 :
				ltdc::PixelFormat::rgb565;

	auto hLayer = ltdc::LTDCLayerDevice1::getHandler();
	hLayer->setWindow(0, 0, _displayWidth, _displayHeight);
	hLayer->setFrameFormat(
		pixelFormat,
		_displayWidth * Color::bytes,
		((_displayWidth * Color::bytes) + 63) & 0xFFFFFFC0,
		_displayHeight);
	hLayer->setConstantAlpha(255);
	hLayer->setDefaultColor(0x000000);

	if (Color::format == ColorFormat::l8) {
		static uint32_t clut[256];
		for (unsigned i = 0; i < (sizeof(clut) / sizeof(clut[0])); i++)
			clut[i] = i << 8;
		hLayer->setCLUTTable(clut);
	}

	hLayer->setFrameBuffer(_displayFrameBuffer->getBuffer());
	hLayer->enable();

	hLTDC->reload();
}
