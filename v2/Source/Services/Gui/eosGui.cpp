#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"
#include "Services/Gui/eosGui.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/Visuals/eosVirtualKbd.h"
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
#include "HAL/halINT.h"


using namespace eos;


static GuiServiceConfiguration defaultConfiguration = {
	.serviceConfiguration = {
		.serviceName = "GuiService",
		.stackSize = OPT_GUI_ServiceStack,
		.priority = OPT_GUI_ServicePriority
	}
};


static IDisplayDriver *displayDriver;
static Graphics *graphics;
static RenderContext *context;

Panel *panel;
int x, y, dx, dy;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: Aplicacio on afeigir el servei.
///
GuiService::GuiService(Application *pApplication) :
	GuiService(pApplication, defaultConfiguration) {

}


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param pApplication: Aplicacio on afeigir el servei.
/// \param configuration: Parametres de configuracio
///
GuiService::GuiService(
	Application *application,
	const GuiServiceConfiguration &configuration):

	Service(application, configuration.serviceConfiguration),
	screen(new Screen()),
	active(nullptr) {

#ifdef OPT_GUI_TouchPad
	touchPadService = new GuiTouchPadService(application);
	touchPadService->setNotifyEvent<GuiService>(this, &GuiService::touchPadServiceNotify);
	touchPadPressed = false;
	touchPadX = -1;
	touchPadY = -1;
#endif
#ifdef OPT_GUI_Selector
#endif
#ifdef OPT_GUI_Keyboard
#endif
}


/// ----------------------------------------------------------------------
/// \brief Asigna el visual actiu.
/// \param visual: El nou visual a activar.
///
void GuiService::setActiveVisual(
	Visual *visual) {

	if (active != nullptr) {
		Message msg = {
			.msgId = MsgId::deactivate,
			.target = active
		};
		active->dispatch(msg);
	}

	active = visual;

	if (active != nullptr) {
		Message msg = {
			.msgId = MsgId::activate,
			.target = active
		};
		active->dispatch(msg);
	}
}


/// ----------------------------------------------------------------------
/// \brief Obte el visual en la posicio indicada.
/// \param position: Posicio a verificar.
///
Visual *GuiService::getVisualAt(
	const Point &position) const {

	if (screen != nullptr)
		return screen->getVisualAt(position);
	else
		return nullptr;
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

	context = new RenderContext(*graphics);

	screen->setColor(0xFF202020);
	setActiveVisual(screen);

	x = 0;
	y = 0;

	Border *border1 = new Border();
	border1->setPosition(Point(0, 0));
	border1->setSize(Size(150, 60));
	border1->setBorderColor(COLOR_Red);

	panel = new Panel();
	panel->setColor(COLOR_Yellow);
	panel->setPosition(Point(2, 2));
	panel->setSize(Size(146, 56));

	Border *border2 = new Border();
	border2->setPosition(Point(10, 10));
	border2->setSize(Size(10, 40));
	border2->setBorderColor(COLOR_Lime);

	Border* border3 = new Border();
	border3->setPosition(Point(30, 10));
	border3->setSize(Size(10, 40));
	border3->setBorderColor(COLOR_Blue);

	Label *label = new Label();
	label->setPosition(Point(50, 5));
	label->setSize(Size(100, 40));
	label->setText("Hola");

	PushButton *button = new PushButton();
	button->setPosition(Point(100, 100));
	button->setSize(Size(120, 40));

	screen->addChild(border1);
	border1->setContent(panel);
	panel->addChild(border2);
	panel->addChild(border3);
	panel->addChild(label);

	screen->addChild(button);

	VirtualKeyboard *kbd = new VirtualKeyboard();
	kbd->setPosition(Point(250, 20));
	kbd->setSize(Size(120, 200));
	screen->addChild(kbd);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la tasca del servei.
///
void GuiService::onTask() {

	// Refresca la pantalla si cal
	//
	if (screen->isRenderizable())
		if (screen->render(*context))
			displayDriver->refresh();

	// Espera que arrivin missatges.
	//
	Message msg;
	if (msgQueue.receive(msg)) {

		// Procesa el missatge
		//
		if (msg.target != nullptr)
			msg.target->dispatch(msg);
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa les notificacions del touchpad. S'executa en el
///        contexte del que crida a aquest metode.
/// \param args: Arguments del event.
///
#ifdef OPT_GUI_TouchPad
void GuiService::touchPadServiceNotify(
	const TouchPadEventArgs &args) {

	Message msg;
	msg.msgId = MsgId::touchPadEvent;
	msg.target = getVisualAt(Point(args.x, args.y));

	switch (args.event) {
		case TouchPadEventType::press:
			msg.touchPad.event = MsgTouchPadEvent::press;
			msg.touchPad.x = args.x;
			msg.touchPad.y = args.y;
			break;

		case TouchPadEventType::release:
			msg.touchPad.event = MsgTouchPadEvent::release;
			break;

		case TouchPadEventType::move:
			msg.touchPad.event = MsgTouchPadEvent::move;
			msg.touchPad.x = args.x;
			msg.touchPad.y = args.y;
			break;
	}

	msgQueue.send(msg);
}
#endif


#ifdef OPT_GUI_Keyboard
#endif

#ifdef OPT_GUI_Selector
#endif
