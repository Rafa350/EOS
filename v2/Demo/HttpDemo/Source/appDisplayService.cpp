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
DisplayService::DisplayService():

	_driver(nullptr),
	_graphics(nullptr) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onInitialize() {

	constexpr int frameBufferLineBytes = (DISPLAY_WIDTH * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferLineBytes / Color::bytes;

	FrameBuffer *frameBuffer = new ColorFrameBuffer_DMA2D(
		DISPLAY_WIDTH,
		DISPLAY_HEIGHT,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(DISPLAY_BUFFER));

	_driver = new DisplayDriver_RGBLTDC(frameBuffer);
    _driver->initialize();
    _driver->enable();

    _graphics = new eos::Graphics(_driver);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onTask() {

    Task::delay(5000);
}
