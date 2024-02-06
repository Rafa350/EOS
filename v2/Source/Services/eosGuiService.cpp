#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#include "Services/eosGuiService.h"
#if eosGuiService_TouchpadEnabled
#include "Services/eosTouchpadService.h"
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
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"


using namespace eos;


static DisplayDriver *displayDriver;
static Graphics *graphics;
static RenderContext *context;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
GuiService::GuiService():
	_screen(new Screen()),
	_active(nullptr),
	_focus(nullptr),
	_msgQueue(MessageQueue::instance()) {

#if eosGuiService_TouchpadEnabled
	_touchpadTarget = nullptr;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el visual actiu.
/// \param    visual: El visual.
///
void GuiService::setActive(
	Visual* visual) {

	/*if (active != nullptr)
		_active->deactivate(visual);

	if (visual != nullptr)
		visual->activate(_active);*/

	_active = visual;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el visual focus.
/// \param    visual: El visual.
///
void GuiService::setFocus(
	Visual *visual) {

	_focus = visual;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual en la posicio indicada.
/// \param    position: Posicio a verificar.
///
Visual* GuiService::getVisualAt(
	const Point& position) const {

	if (_screen != nullptr)
		return VisualUtils::getVisual(_screen, position);
	else
		return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
bool GuiService::onTaskStart() {

#if defined(DISPLAY_DRV_ILI9341LTDC)
	displayDriver = new ILI9341LTDCDriver();

#elif defined(DISPLAY_DRV_ILI9341)
	displayDriver = new ILI9341Driver();

#elif defined(DISPLAY_DRV_RGBLTDC)

	constexpr int frameBufferPitchBytes = (_displayWidth * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferPitchBytes / Color::bytes;
	constexpr int frameSize = frameBufferPitchBytes * _displayHeight;

	FrameBuffer *frameBuffer1 = new ColorFrameBuffer_DMA2D(
		_displayWidth,
		_displayHeight,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(_displayBuffer));

	FrameBuffer *frameBuffer2 = new ColorFrameBuffer_DMA2D(
		_displayWidth,
		_displayHeight,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(_displayBuffer + frameSize));

	frameBuffer1->clear(Colors::black);
	frameBuffer2->clear(Colors::black);

	displayDriver = new DisplayDriver_RGBLTDC(frameBuffer1, frameBuffer2);

#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif

	displayDriver->initialize();
	displayDriver->enable();

	graphics = new Graphics(displayDriver);
	context = new RenderContext(graphics);

	setActive(_screen);

	_screen->measure(Size(displayDriver->getWidth(), displayDriver->getHeight()));
	_screen->arrange(_screen->getDesiredSize());

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
bool GuiService::onTask() {
        
    // Repeteix indefinidament
    //
    while (true) {

        // Refresca la pantalla si cal
        //
        if (_screen->isRenderizable())
            if (_screen->render(context))
                displayDriver->refresh();

        // procesa els missatges.
        //
        Message msg;
        if (_msgQueue.receive(msg)) {

            if ((msg.msgId == MsgId::keyboard) && (msg.target == nullptr))
                msg.target = _focus;

            if (msg.target != nullptr)
                msg.target->dispatch(msg);
        }
    
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les notificacions del touchpad. S'executa en el
///           contexte del que crida a aquest metode.
/// \param    args: Arguments del event.
///
#if eosGuiService_TouchpadEnabled
void GuiService::touchPadNotifyEventHandler(
	TouchPadService *sender,
	TouchPadService::NotifyEventArgs &args) {

	Message msg;
	msg.msgId = MsgId::touchpad;

	// Obte el target.
	//
	Visual *target = getVisualAt(Point(args.x, args.y));

	// Comprova si ha canviat el target.
	//
	if (_touchpadTarget != target) {

		// Si cal, notifica la sortida d'un visual.
		//
		if (_touchpadTarget != nullptr) {
            msg.target = _touchpadTarget;
            msg.touchpad.event = MsgTouchpadEvent::leave;
            _msgQueue.send(msg);
		}

		_touchpadTarget = target;

		// Si cal, notifica la entrada en un visual.
		//
		if (_touchpadTarget != nullptr) {
            msg.target = _touchpadTarget;
            msg.touchpad.event = MsgTouchpadEvent::enter;
            _msgQueue.send(msg);
		}
	}

	msg.target = target;
	switch (args.notifyType) {
		case TouchPadService::NotifyType::press:
			msg.touchpad.event = MsgTouchpadEvent::press;
			msg.touchpad.x = args.x;
			msg.touchpad.y = args.y;
			break;

		case TouchPadService::NotifyType::release:
			msg.touchpad.event = MsgTouchpadEvent::release;
			break;

		case TouchPadService::NotifyType::move:
			msg.touchpad.event = MsgTouchpadEvent::move;
			msg.touchpad.x = args.x;
			msg.touchpad.y = args.y;
			break;
	}

	_msgQueue.send(msg);
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
