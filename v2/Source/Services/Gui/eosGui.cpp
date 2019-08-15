#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosGraphics.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosBorder.h"
#include "Services/Gui/eosLabel.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosSimplePanel.h"
#include "Services/Gui/eosScreen.h"
#include "Services/Gui/eosRenderContext.h"
#ifdef OPT_GUI_TouchPad
#include "Services/Gui/eosGuiTouchPad.h"
#endif
#ifdef OPT_GUI_Selector
#include "Services/Gui/eosGuiSelector.h"
#endif
#ifdef OPT_GUI_Keyboard
#include "Services/Gui/eosGuiKeyboard.h"
#endif


using namespace eos;


static const char *serviceName = "GuiService";
static const unsigned stackSize = OPT_GUI_ServiceStack;
static const TaskPriority priority = OPT_GUI_ServicePriority;


static IDisplayDriver *displayDriver;
static Graphics *graphics;
static RenderContext *context;

Panel *panel;
int x, y, dx, dy;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param info: Parametres d'inicialitzacio
///
GuiService::GuiService(
	Application *application,
	const GuiServiceInitInfo *info):

	Service(application, serviceName, stackSize, priority),
	screen(new Screen()),
	touchPadPressed(false),
	touchPadX(-1),
	touchPadY(-1) {

#ifdef OPT_GUI_TouchPad
	touchPadService = new GuiTouchPadService(application);
	touchPadService->setNotifyEvent<GuiService>(this, &GuiService::touchPadServiceNotify);
#endif
#ifdef OPT_GUI_Selector
#endif
#ifdef OPT_GUI_Keyboard
#endif
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

	screen->setColor(COLOR_Blue);

	x = 0;
	y = 0;

	panel = new SimplePanel();
	panel->setPosition(Point(x, y));
	panel->setSize(Size(150, 30));

	Border *border1 = new Border();
	border1->setPosition(Point(0, 0));
	border1->setSize(Size(150, 30));
	border1->setBorderColor(COLOR_Red);

	Border *border2 = new Border();
	border2->setPosition(Point(10, 10));
	border2->setSize(Size(10, 10));
	border2->setBorderColor(COLOR_Green);

	Border* border3 = new Border();
	border3->setPosition(Point(30, 10));
	border3->setSize(Size(10, 10));
	border3->setBorderColor(COLOR_Yellow);

	Label *label = new Label();
	label->setPosition(Point(50, 5));
	label->setSize(Size(100, 20));
	label->setText("Hola");

	screen->addChild(panel);
	panel->addChild(border1);
	panel->addChild(border2);
	panel->addChild(border3);
	panel->addChild(label);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la tasca del servei
///
void GuiService::onTask() {

	Size panelSize(panel->getSize());

	if (x > (graphics->getWidth() - panelSize.getWidth() / 2))
		dx = -1;
	else if (x <= 0)
		dx = 1;

	if (y > (graphics->getHeight() - panelSize.getHeight() / 2))
		dy = -1;
	else if (y <= 0)
		dy = 1;

	x += dx;
	y += dy;
	panel->setPosition(Point(x, y));

	screen->render(context);
	displayDriver->refresh();

	Task::delay(20);
}


/// ----------------------------------------------------------------------
/// \brief Procesa les notificacions del touchpad.
/// \param args: Arguments del event.
///
void GuiService::touchPadServiceNotify(
	TouchPadEventArgs *args) {

	if (touchPadPressed != args->isPressed) {
		touchPadPressed = args->isPressed;
		if (touchPadPressed) {
			dx = -dx;
			dy = -dy;
		}
	}
}
