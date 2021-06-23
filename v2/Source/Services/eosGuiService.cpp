#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "Services/eosGuiService.h"
#if eosGuiService_TouchPadEnabled
#include "Services/eosTouchPadService.h"
#endif
#if eosGuiService_SelectorEnabled
#include "Services/eosSelectorService.h"
#endif
#if eosGuiService_KeyboardEnabled
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


static IDisplayDriver* displayDriver;
static Graphics* graphics;
static RenderContext* context;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: Aplicacio on afeigir el servei.
/// \param    cfg: Parametres de configuracio
///
GuiService::GuiService(
	Application* application):

	Service(application),
	_screen(new Screen()),
	_active(nullptr),
	_msgQueue(MsgQueue::getInstance())
#if eosGuiService_TouchPadEnabled
	, _touchPadEventCallback(this, &GuiService::touchPadEventHandler)
#endif
	{

#if eosGuiService_TouchPadEnabled
	_touchPadService = new TouchPadService(application);
	_touchPadService->setEventCallback(&_touchPadEventCallback);
	_touchPadTarget = nullptr;
#endif

#if eosGuiService_SelectorEnabled
#endif

#if eosGuiService_KeyboardEnabled
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

	_active = visual;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual en la posicio indicada.
/// \param    position: Posicio a verificar.
///
Visual *GuiService::getVisualAt(
	const Point &position) const {

	if (_screen != nullptr)
		return VisualUtils::getVisual(_screen, position);
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
	displayDriver = new DisplayDriver_RGBLTDC();
#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
	displayDriver->initialize();
	displayDriver->displayOn();

	graphics = new Graphics(displayDriver);
	context = new RenderContext(graphics);

	setActiveVisual(_screen);

	_screen->measure(Size(displayDriver->getImageWidth(), displayDriver->getImageHeight()));
	_screen->arrange(_screen->getDesiredSize());
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void GuiService::onTask(
	Task *task) {

	// Refresca la pantalla si cal
	//
	if (_screen->isRenderizable())
		if (_screen->render(context))
			displayDriver->refresh();

	// Espera que arrivin missatges.
	//
	Message msg;
	if (_msgQueue->receive(msg)) {

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
#if eosGuiService_TouchPadEnabled
void GuiService::touchPadEventHandler(
	const TouchPadService::EventArgs &args) {

	Message msg;
	msg.msgId = MsgId::touchPadEvent;

	// Obte el target.
	//
	Visual *target = getVisualAt(Point(args.x, args.y));

	// Comprova si ha canviat el target.
	//
	if (_touchPadTarget != target) {

		// Si cal, notifica la sortida d'un visual.
		//
		if (_touchPadTarget != nullptr) {
            msg.target = _touchPadTarget;
            msg.touchPad.event = MsgTouchPadEvent::leave;
            _msgQueue->send(msg);
		}

		_touchPadTarget = target;

		// Si cal, notifica la entrada en un visual.
		//
		if (_touchPadTarget != nullptr) {
            msg.target = _touchPadTarget;
            msg.touchPad.event = MsgTouchPadEvent::enter;
            _msgQueue->send(msg);
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
	_msgQueue->send(msg);
}
#endif


#if eosGuiService_KeyboardEnabled
void GuiService::keyboardEventHandler(
	const KeyboardEventArgs &args) {

}
#endif

#if eosGuiService_SelectorEnabled
void GuiService::selectorEventHandler(
	const SelectorEventArgs &args) {

}
#endif
