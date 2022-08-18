#include "eos.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte
/// \param application: Aplicacio a la que pertany el servei.
///
DisplayService::DisplayService(
	eos::Application *application):

	eos::AppLoopService(application),
	_driver(nullptr),
	_graphics(nullptr) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

	constexpr int frameBufferLineBytes = (board::display::width * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferLineBytes / Color::bytes;

	FrameBuffer *frameBuffer = new ColorFrameBuffer_DMA2D(
		board::display::width,
		board::display::height,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(board::display::buffer));

	_driver = new DisplayDriver_RGBLTDC(frameBuffer);
    _driver->initialize();
    _driver->displayOn();

    _graphics = new eos::Graphics(_driver);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

    Task::delay(5000);
}
