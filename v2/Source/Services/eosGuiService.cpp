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
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/eosRenderContext.h"
#include "System/eosString.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"


using namespace eos;


static IDisplayDriver *displayDriver;
static Graphics *graphics;
static RenderContext *context;


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte.
///
GuiService::Configuration::Configuration() {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: Aplicacio on afeigir el servei.
/// \param    cfg: Parametres de configuracio
///
GuiService::GuiService(
	Application *application,
	const Configuration *cfg):

	Service(application),
	screen(new Screen()),
	active(nullptr),
	msgQueue(MsgQueue::getInstance())
#ifdef OPT_GUI_TouchPad
	, touchPadEventCallback(this, &GuiService::touchPadEventHandler)
#endif
	{

	if (cfg != nullptr)
		this->cfg = *cfg;

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
/// \brief    Asigna el visual actiu.
/// \param    visual: El nou visual a activar.
///
void GuiService::setActiveVisual(
	Visual *visual) {

	/*if (active != nullptr)
		active->deactivate(pVisual);

	if (pVisual != nullptr)
		pVisual->activate(active);*/

	active = visual;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual en la posicio indicada.
/// \param    position: Posicio a verificar.
///
Visual *GuiService::getVisualAt(
	const Point &position) const {

	if (screen != nullptr)
		return VisualUtils::getVisual(screen, position);
	else
		return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void GuiService::onInitialize() {

#if defined(DISPLAY_DRV_ILI9341LTDC)
	displayDriver = new ILI9341LTDCDriver();
#elif defined(DISPLAY_DRV_ILI9341)
	displayDriver = new ILI9341Driver();
#elif defined(DISPLAY_DRV_RGBLTDC)
	displayDriver = new RGBDirectDriver();
#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
	displayDriver->initialize();
	displayDriver->displayOn();

	graphics = new Graphics(displayDriver);
	context = new RenderContext(graphics);

	setActiveVisual(screen);

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
		if (screen->render(context))
			displayDriver->refresh();

	// Espera que arrivin missatges.
	//
	Message msg;
	if (msgQueue->receive(msg)) {

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
	const TouchPadService::EventArgs &args) {

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
            msgQueue->send(msg);
		}

		touchPadTarget = target;

		// Si cal, notifica la entrada en un visual.
		//
		if (touchPadTarget != nullptr) {
            msg.target = touchPadTarget;
            msg.touchPad.event = MsgTouchPadEvent::enter;
            msgQueue->send(msg);
		}
	}

	msg.target = target;
	switch (args.event) {
		case TouchPadService::EventType::press:
			msg.touchPad.event = MsgTouchPadEvent::press;
			msg.touchPad.x = args.x;
			msg.touchPad.y = args.y;
			break;

		case TouchPadService::EventType::release:
			msg.touchPad.event = MsgTouchPadEvent::release;
			break;

		case TouchPadService::EventType::move:
			msg.touchPad.event = MsgTouchPadEvent::move;
			msg.touchPad.x = args.x;
			msg.touchPad.y = args.y;
			break;
	}
	msgQueue->send(msg);
}
#endif


#ifdef OPT_GUI_Keyboard
void GuiService::keyboardEventhandler(
	const KeyboardEventArgs &aargs) {

}
#endif

#ifdef OPT_GUI_Selector
void GuiService::selectorEventhandler(
	const SelectorEventArgs &args) {

}
#endif
