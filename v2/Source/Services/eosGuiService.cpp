#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "Services/eosGuiService.h"
#ifdef OPT_GUI_TouchPad
#include "Services/eosTouchPadService.h"
#endif
#ifdef OPT_GUI_Selector
#include "Services/eosSelectorService.h"
#endif
#ifdef OPT_GUI_Keyboard
#include "Services/eosKeyboardService.h"
#endif
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "Services/Gui/Visuals/eosCheckButton.h"
#include "Services/Gui/Visuals/eosImage.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosVirtualKbd.h"
#include "Services/Gui/eosRenderContext.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"


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

static Bitmap *createBitmap() {

	extern const unsigned char bitmapBmpMain[];

	const uint8_t *data = bitmapBmpMain;

	int width = (int) (data[0] | (data[1] << 8));
	int height = (int) (data[2] | (data[3] << 8));
	//int flags = (int) (data[4] | (data[5] << 8));

	return new Bitmap(width, height, ColorFormat::rgb565, &data[6]);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pApplication: Aplicacio on afeigir el servei.
///
GuiService::GuiService(Application *pApplication) :
	GuiService(pApplication, defaultConfiguration) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    pApplication: Aplicacio on afeigir el servei.
/// \param    configuration: Parametres de configuracio
///
GuiService::GuiService(
	Application *application,
	const GuiServiceConfiguration &configuration):

	Service(application, configuration.serviceConfiguration),
	screen(new Screen()),
	active(nullptr),
	touchPadEventCallback(this, &GuiService::touchPadEventHandler) {

#ifdef OPT_GUI_TouchPad
	touchPadService = new TouchPadService(application);
	touchPadService->setEventCallback(&touchPadEventCallback);
	touchPadTarget = nullptr;
#endif
#ifdef OPT_GUI_Selector
#endif
#ifdef OPT_GUI_Keyboard
#endif
}


/// ----------------------------------------------------------------------
/// \brief Asigna el visual actiu.
/// \param pVisual: El nou visual a activar.
///
void GuiService::setActiveVisual(
	Visual *pVisual) {

	/*if (active != nullptr)
		active->onDeactivate(pVisual);

	if (pVisual != nullptr)
		pVisual->onActivate(active);
*/
	active = pVisual;
}


/// ----------------------------------------------------------------------
/// \brief Obte el visual en la posicio indicada.
/// \param position: Posicio a verificar.
///
Visual *GuiService::getVisualAt(
	const Point &position) const {

	if (screen != nullptr)
		return VisualUtils::getVisual(screen, position);
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

	setActiveVisual(screen);

	/*x = 0;
	y = 0;

	Border *border1 = new Border();
	border1->setPosition(Point(0, 0));
	border1->setSize(Size(150, 60));
	border1->setColor(COLOR_Red);

	panel = new Panel();
	panel->setPosition(Point(2, 2));
	panel->setSize(Size(146, 56));

	Border *border2 = new Border();
	border2->setPosition(Point(10, 10));
	border2->setSize(Size(10, 40));
	border2->setColor(COLOR_Lime);

	Border* border3 = new Border();
	border3->setPosition(Point(30, 10));
	border3->setSize(Size(10, 40));
	border3->setColor(COLOR_Blue);

	Label *label = new Label();
	label->setPosition(Point(50, 5));
	label->setSize(Size(100, 40));
	label->setText("Hola");

	PushButton *pushButton = new PushButton();
	pushButton->setPosition(Point(100, 100));
	pushButton->setSize(Size(120, 40));

	CheckButton *checkButton = new CheckButton();
	checkButton->setPosition(Point(100, 150));
	checkButton->setSize(Size(120, 30));

	Image *image = new Image();
	image->setPosition(Point(150, 150));
	image->setSize(Size(60, 60));
	image->setBitmap(createBitmap());

	screen->addChild(border1);
	border1->setContent(panel);
	panel->addChild(border2);
	panel->addChild(border3);
	panel->addChild(label);

	screen->addChild(pushButton);
	screen->addChild(checkButton);
	screen->addChild(image);

	VirtualKeyboard *kbd = new VirtualKeyboard();
	kbd->setPosition(Point(250, 20));
	kbd->setSize(Size(120, 200));
	screen->addChild(kbd);
	*/

	/*StackPanel *sp = new StackPanel();
	sp->setPosition(Point(20, 20));
	sp->setSize(Size(100, 250));
	sp->setMargin(Thickness(100, 10, 100, 10));
	sp->setHorizontalAlignment(HorizontalAlignment::center);
	sp->setVerticalAlignment(VerticalAlignment::top);
	screen->addChild(sp);
	for (int i = 0; i < 5; i++) {

		Label *l = new Label();
		l->setHorizontalAlignment(HorizontalAlignment::center);
		l->setVerticalAlignment(VerticalAlignment::center);
		l->setText("hola");

		PushButton *pb = new PushButton();
		pb->setHorizontalAlignment(HorizontalAlignment::center);
		pb->setVerticalAlignment(VerticalAlignment::center);
		pb->setMargin(Thickness(10));
		pb->setContent(l);

		sp->addChild(pb);
	}*/

	Label *l1 = new Label();
	l1->setMargin(5);
	l1->setText("Hola capullo");
	l1->setHorizontalAlignment(HorizontalAlignment::center);
	l1->setVerticalAlignment(VerticalAlignment::center);

	PushButton *pb1 = new PushButton();
	pb1->setHorizontalAlignment(HorizontalAlignment::stretch);
	pb1->setVerticalAlignment(VerticalAlignment::center);
	pb1->setMinSize(Size(100, 20));
	pb1->setMargin(20);
	pb1->setContent(l1);

	screen->addChild(pb1);

	screen->measure(Size(displayDriver->getWidth(), displayDriver->getHeight()));
	screen->arrange(screen->getDesiredSize());
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
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
/// \brief    Procesa les notificacions del touchpad. S'executa en el
///           contexte del que crida a aquest metode.
/// \param    args: Arguments del event.
///
#ifdef OPT_GUI_TouchPad
void GuiService::touchPadEventHandler(
	const TouchPadEventArgs &args) {

	Message msg;
	msg.msgId = MsgId::touchPadEvent;

	// Obte el target.
	//
	Visual *target = getVisualAt(Point(args.x, args.y));

	// Comprova si ha canviat el target.
	//
	if (touchPadTarget != target) {

		// Si cal, notifica la sortida d'un visual.
		//
		if (touchPadTarget != nullptr) {
            msg.target = touchPadTarget;
            msg.touchPad.event = MsgTouchPadEvent::leave;
            msgQueue.send(msg);
		}

		touchPadTarget = target;

		// Si cal, notifica la entrada en un visual.
		//
		if (touchPadTarget != nullptr) {
            msg.target = touchPadTarget;
            msg.touchPad.event = MsgTouchPadEvent::enter;
            msgQueue.send(msg);
		}
	}

	msg.target = target;
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
