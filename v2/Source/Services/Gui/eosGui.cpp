#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosGraphics.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosScreen.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosWidged.h"


using namespace eos;


static const char *serviceName = "GuiService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


static IDisplayDriver *displayDriver;
static Graphics *graphics;
static RenderContext *context;

Widget *v1, *v2, *v3;
int x, y, dx, dy;


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

	graphics = new Graphics(displayDriver);

	context = new RenderContext(graphics);

	screen = new Screen();
	screen->setColor(COLOR_Blue);

	x = 0;
	y = 0;

	v1 = new Widget();
	v1->setPosition(x, y);
	v1->setSize(50, 30);
	v1->setBorderColor(COLOR_Red);

	v2 = new Widget();
	v2->setPosition(10, 10);
	v2->setSize(10, 10);
	v2->setBorderColor(COLOR_Green);

	v3 = new Widget();
	v3->setPosition(30, 10);
	v3->setSize(10, 10);
	v3->setBorderColor(COLOR_Yellow);

	screen->addVisual(v1);
	v1->addVisual(v2);
	v1->addVisual(v3);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la tasca del servei
///
void GuiService::onTask() {

	if (x > (graphics->getWidth() - v1->getWidth() / 2))
		dx = -1;
	else if (x <= 0)
		dx = 1;

	if (y > (graphics->getHeight() - v1->getHeight() / 2))
		dy = -1;
	else if (y <= 0)
		dy = 1;

	x += dx;
	y += dy;
	v1->setPosition(x, y);

	screen->render(context);
	displayDriver->refresh();

	Task::delay(25);
}
