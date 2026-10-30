export module Eos.Controllers.Display.Drivers.RGBLTDC;

import Eos.Controllers.Display;
import Eos.Controllers.Display.Buffers.Color;
import Eos.Hardware.GPIO;
import Eos.Hardware.LTDC;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


using namespace eos::hardware::gpio;
using namespace eos::hardware::ltdc;


export namespace eos {

	class DisplayDriver_RGBLTDC: public DisplayDriver {
		private:
            LTDCDevice * const _devLTDC;
			LTDCLayerDevice * const _devLTDCLayer;
			PinDevice * const _pinLCDE;
			PinDevice * const _pinBKE;
    		DisplayBuffer *_displayFrameBuffer;
    		DisplayBuffer *_workFrameBuffer;

            void initializeGPIO();

		public:
    		DisplayDriver_RGBLTDC(
    			LTDCDevice *devLTDC, LTDCLayerDevice *devLTDCLayer,
				PinDevice *pinLCDE, PinDevice *pinBKE,
				DisplayBuffer *frameBuffer1, DisplayBuffer *frameBuffer2);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            inline Int16 getWidth() const override { return _displayFrameBuffer->getWidth(); }
            inline Int16 getHeight() const override { return _displayFrameBuffer->getHeight(); }
            inline Int16 getMaxX() const override { return _displayFrameBuffer->getMaxX(); }
            inline Int16 getMaxY() const override { return _displayFrameBuffer->getMaxY(); }

            void clear(Color color) override;

            void setPixel(Int16 x, Int16 y, Color color) override;
            void setHPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setVPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 colorPitch) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *colors, ColorFormat colorFormat, Int16 colorPitch) override;

            void refresh() override;
    };
}


using namespace eos;


/// --------------------------------------------------------------------------
/// @brief    Contructor.
/// @param    devLTDC: Dispositiu LTDC.
/// @param    devLTDCLayer: Dispositiu LTDCLayer.
/// @param    pinLCDE: Pin per habilitar el controlador.
/// @param    pinBKE: Pin per habilitar la retroiluminacio.
/// @param    frameBuffer1: Buffer d'imatge.
/// @param    frameBuffer2: Buffer d'imatge (Si es vol doble buffer).
///
DisplayDriver_RGBLTDC::DisplayDriver_RGBLTDC(
	LTDCDevice *devLTDC,
	LTDCLayerDevice *devLTDCLayer,
	PinDevice *pinLCDE,
	PinDevice *pinBKE,
	DisplayBuffer *frameBuffer1,
	DisplayBuffer *frameBuffer2):

	_devLTDC {devLTDC},
	_devLTDCLayer {devLTDCLayer},
	_pinLCDE {pinLCDE},
	_pinBKE {pinBKE},
	_displayFrameBuffer {frameBuffer1},
	_workFrameBuffer {frameBuffer2 == nullptr? frameBuffer1 : frameBuffer2} {
}


/// --------------------------------------------------------------------------
/// @brief    Inicialitza el driver.
///
void DisplayDriver_RGBLTDC::initialize() {

	_displayFrameBuffer->clear(Colors::black);
	if (_displayFrameBuffer != _workFrameBuffer)
		_workFrameBuffer->clear(Colors::black);

	initializeGPIO();
}


/// -------------------------------------------------------------------------
/// @brief    Finalitza el driver.
///
void DisplayDriver_RGBLTDC::deinitialize() {

	disable();
}


/// --------------------------------------------------------------------------
/// @brief    Activa el display.
///
void DisplayDriver_RGBLTDC::enable() {

	_devLTDCLayer->setFrameBuffer(_displayFrameBuffer->getBuffer());
	_devLTDCLayer->enable();

	_devLTDC->enable();
	_devLTDC->reload();

	_pinLCDE->set();
	_pinBKE->set();
}


/// --------------------------------------------------------------------------
/// @brief    Desactiva el display.
///
void DisplayDriver_RGBLTDC::disable() {

	_pinLCDE->clear();
	_pinBKE->clear();

	_devLTDC->disable();
	_devLTDCLayer->disable();
}


/// --------------------------------------------------------------------------
/// @brief    Borra la imatge.
/// @param    color: Color de borrat.
///
void DisplayDriver_RGBLTDC::clear(
	Color color) {

	_workFrameBuffer->clear(color);
}


/// --------------------------------------------------------------------------
/// @brief    Asigna un color a un pixel.
/// @param    x: Coordinada x.
/// @param    y: Coordinada y.
/// @param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixel(
	Int16 x,
	Int16 y,
	Color color) {

	_workFrameBuffer->setPixel(x, y, color);
}


/// --------------------------------------------------------------------------
/// @brief    Asigna un color a una linia horitzontal.
/// @param    x: Coordinada x.
/// @param    y: Coordinada y.
/// @param    length: Longitut.
/// @param    color: Color.
///
void DisplayDriver_RGBLTDC::setHPixels(
	Int16 x,
	Int16 y,
	Int16 size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, size, 1, color);
}


/// --------------------------------------------------------------------------
/// @brief    Assigna un color a una linia vertical.
/// @param    x: Coordinada x.
/// @param    y: Coordinada x.
/// @param    length: Longitut de la linia.
/// @param    color: Color.
///
void DisplayDriver_RGBLTDC::setVPixels(
	Int16 x,
	Int16 y,
	Int16 size,
	Color color) {

	_workFrameBuffer->setPixels(x, y, 1, size, color);
}


/// --------------------------------------------------------------------------
/// @brief    Asigna un color a una regio rectangular.
/// @param    x: Posicio x.
/// @param    y: Posicio y.
/// @param    width: Amplada.
/// @param    height: Alçada.
/// @param    color: Color.
///
void DisplayDriver_RGBLTDC::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	Color color) {

	_workFrameBuffer->setPixels(x, y, width, height, color);
}


/// --------------------------------------------------------------------------
/// @brief    Copia una regio rectangular.
/// @param    x: Posicio x.
/// @param    y: Posicio y.
/// @param    width: Amplada.
/// @param    height: Alçada.
/// @param    colors: Regio a copiar
/// @param    pitch: Pitch de la regio a copiar.
///
void DisplayDriver_RGBLTDC::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const Color *colors,
	Int16 colorPitch) {

	_workFrameBuffer->setPixels(x, y, width, height, colors, colorPitch);
}


/// --------------------------------------------------------------------------
/// @brief    Copia una lliosta de pixels una regio rectangular.
/// @param    x: Posicio x de la regio.
/// @param    y: Posicio y de la regio.
/// @param    width: Amplada de la regio.
/// @param    height: Alçada de la regio.
/// @param    colors: La llista de colors.
/// @param    colorFormat: Format de la llista de colors.
/// @param    colorPitch: Pitch de la llista de colors.
///
void DisplayDriver_RGBLTDC::setPixels(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height,
	const void *colors,
	ColorFormat colorFormat,
	Int16 colorPitch) {

	_workFrameBuffer->setPixels(x, y, width, height, colors, colorFormat, colorPitch);
}


/// --------------------------------------------------------------------------
/// @brief Refresca la pantalla.
///
void DisplayDriver_RGBLTDC::refresh() {

	if (_workFrameBuffer != _displayFrameBuffer) {

		// Intercanvia els buffers
		//
		auto tmp = _displayFrameBuffer;
		_displayFrameBuffer = _workFrameBuffer;
		_workFrameBuffer = tmp;

		// Asigna l'adresa de la capa
		//
		_devLTDCLayer->setFrameBuffer(_displayFrameBuffer->getBuffer());
		_devLTDC->reload();
	}
}


/// --------------------------------------------------------------------------
/// @brief Inicialitza el modul GPIO.
///
void DisplayDriver_RGBLTDC::initializeGPIO() {

	_pinBKE->initOutput(OutputType::pushPull, PullUpDown::none, Speed::low, false);
	_pinLCDE->initOutput(OutputType::pushPull, PullUpDown::none, Speed::low, false);
}
