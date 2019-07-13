#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosGraphics.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosBorder.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosSimplePanel.h"
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

Panel *panel;
Border *border1, *border2, *border3;
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

	panel = new SimplePanel();
	panel->setPosition(x, y);
	panel->setSize(50, 30);

	border1 = new Border();
	border1->setPosition(0, 0);
	border1->setSize(50, 30);
	border1->setBorderColor(COLOR_Red);

	border2 = new Border();
	border2->setPosition(10, 10);
	border2->setSize(10, 10);
	border2->setBorderColor(COLOR_Green);

	border3 = new Border();
	border3->setPosition(30, 10);
	border3->setSize(10, 10);
	border3->setBorderColor(COLOR_Yellow);

	screen->addChild(panel);
	panel->addChild(border1);
	panel->addChild(border2);
	panel->addChild(border3);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la tasca del servei
///
void GuiService::onTask() {

	if (x > (graphics->getWidth() - panel->getWidth() / 2))
		dx = -1;
	else if (x <= 0)
		dx = 1;

	if (y > (graphics->getHeight() - panel->getHeight() / 2))
		dy = -1;
	else if (y <= 0)
		dy = 1;

	x += dx;
	y += dy;
	panel->setPosition(x, y);

	screen->render(context);
	displayDriver->refresh();

	Task::delay(25);
}
