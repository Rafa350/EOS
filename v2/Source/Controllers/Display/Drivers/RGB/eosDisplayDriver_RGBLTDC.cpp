#include "eos.h"

#if !((defined(LTDC) && (defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7))))
#error "LTDC hardware unavailable"
#endif


// Utilitza una sola capa (LTDC_Layer1). Pot treballar en modus simple
// o doble buffer.

#include "eosAssert.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/eosMath.h"
#include "System/Graphics/eosColorDefinitions.h"


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

	auto pinBKE(PinBKE::getHandler());
	pinBKE->initOutput(gpio::OutDriver::pushPull, gpio::Speed::low);

	auto pinLCDE(PinLCDE::getHandler());
	pinLCDE->initOutput(gpio::OutDriver::pushPull, gpio::Speed::low);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul LTDC.
/// \remarks Prepara la capa Layer1, pero no s'activara fins que s'asigni
/// una adressa per buffer de video.
///
void DisplayDriver_RGBLTDC::initializeLTDC() {

	// Inicialitza el modul LTDC
	//
	auto ltdc(ltdc::LTDCDevice::getHandler());
	ltdc->initPCPin<DISPLAY_PC_GPIO>(_pcPol);
	ltdc->initHSYNCPin<DISPLAY_HSYNC_GPIO>(_hSyncPol);
	ltdc->initVSYNCPin<DISPLAY_VSYNC_GPIO>(_vSyncPol);
	ltdc->initDEPin<DISPLAY_DE_GPIO>(_dePol);
	ltdc->initRPins<PinR0, PinR1, PinR2, PinR3, PinR4, PinR5, PinR6, PinR7>();
	ltdc->initGPins<PinG0, PinG1, PinG2, PinG3, PinG4, PinG5, PinG6, PinG7>();
	ltdc->initBPins<PinB0, PinB1, PinB2, PinB3, PinB4, PinB5, PinB6, PinB7>();
	ltdc->initialize(_displayWidth, _displayHeight, _hSync, _vSync, _hBP, _vBP, _hFP, _vFP);
	ltdc->setBackgroundColor(0x0000FF);

	// Inicialitza la capa 1
	// La capa ocupa tota la superficie de la pantalla
	//
	constexpr ltdc::LTDCPixelFormat pixelFormat =
		Color::format == ColorFormat::argb8888 ? ltdc::LTDCPixelFormat::argb8888 :
		Color::format == ColorFormat::argb4444 ? ltdc::LTDCPixelFormat::argb4444 :
		Color::format == ColorFormat::argb1555 ? ltdc::LTDCPixelFormat::argb1555 :
		Color::format == ColorFormat::rgb888 ? ltdc::LTDCPixelFormat::rgb888 :
		Color::format == ColorFormat::al88 ? ltdc::LTDCPixelFormat::al88 :
		Color::format == ColorFormat::al44 ? ltdc::LTDCPixelFormat::al44 :
		Color::format == ColorFormat::l8 ? ltdc::LTDCPixelFormat::l8 :
				ltdc::LTDCPixelFormat::rgb565;

	auto layer(ltdc::LTDCLayerDevice1::getHandler());
	layer->setWindow(0, 0, _displayWidth, _displayHeight);
	layer->setFrameFormat(
		pixelFormat,
		_displayWidth * Color::bytes,
		((_displayWidth * Color::bytes) + 63) & 0xFFFFFFC0,
		_displayHeight);
	layer->setConstantAlpha(255);
	layer->setDefaultColor(0x000000);

	if (Color::format == ColorFormat::l8) {
		static uint32_t clut[256];
		for (unsigned i = 0; i < (sizeof(clut) / sizeof(clut[0])); i++)
			clut[i] = i << 8;
		layer->setCLUTTable(clut);
	}

	layer->setFrameBuffer(_displayFrameBuffer->getBuffer());
	layer->enable();

	ltdc->reload();
}
