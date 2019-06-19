#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosDisplay.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosGuiVisuals.h"


using namespace eos;


static const char *serviceName = "GuiService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


static IDisplayDriver *displayDriver;
static Display *display;

Widget *v;
int x, y;

/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param info: Parametres d'inicialitzacio
///
GuiService::GuiService(
	Application *application,
	const GuiServiceInitializeInfo *info):

	Service(application, serviceName, stackSize, priority),
	screen(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void GuiService::onInitialize() {

#if defined(DISPLAY_DRV_ILI9341LTDC)
	displayDriver = ILI9341LTDCDriver::getInstance();
#elif defined(DISPLAY_DRV_ILI9341)
	displayDriver = ILI9341Driver::getInstance();
#elif defined(DISPLAY_DRV_RGBLTDC)
	displayDriver = RGBDirectDriver::getInstance();
#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
	displayDriver->initialize();
	displayDriver->displayOn();

	display = new Display(displayDriver);
	display->clear(COLOR_Black);

	screen = new Screen();
	screen->setColor(COLOR_Blue);

	x = 0;
	y = 0;
	v = new Widget();
	v->setPosition(x, y);
	v->setSize(100, 100);
	v->setBorderColor(COLOR_Red);
	screen->addVisual(v);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la tasca del servei
///
void GuiService::onTask() {

	if (x++ > 200)
		x = 0;
	if (y++ > 100)
		y = 0;
	v->setPosition(x, y);

	screen->render(display);
	//displayDriver->refresh();

	Task::delay(50);
}
