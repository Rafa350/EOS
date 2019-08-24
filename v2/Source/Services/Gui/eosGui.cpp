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
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosSimplePanel.h"
#include "Services/Gui/Visuals/eosScreen.h"
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

	screen->setColor(COLOR_Blue);
	setActiveVisual(screen);

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
/// \brief Procesa la tasca del servei.
///
void GuiService::onTask() {

	// Refresca la pantalla si cal
	//
	if (screen->getNeedRender()) {
		screen->render(*context);
		displayDriver->refresh();
	}

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
	msg.msgId = MsgId::touchPad;
	msg.target = getActiveVisual();

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

	halINTDisableInterrupts();
	getVisualAt(Point(args.x, args.y));
	halINTEnableInterrupts();

	msgQueue.send(msg);
}
#endif
