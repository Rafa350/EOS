#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Screen::Screen() {

	setPosition(Point(0, 0));
	setSize(Size(DISPLAY_IMAGE_WIDTH, DISPLAY_IMAGE_HEIGHT));
}


/// ----------------------------------------------------------------------
/// \brief Assigna el color.
/// \param newColor: El color.
///
void Screen::setColor(
	const Color &newColor) {

	if (color != newColor) {
		color = newColor;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param context: El context de renderitzat.
///
void Screen::onRender(
	RenderContext &context) {

	Graphics &g = context.beginRender(this);

	Rect r = getRect();

	g.setColor(color);
	g.fillRectangle(r);

	context.endRender();
}


/// ----------------------------------------------------------------------
/// \brief Despatxa els missatges.
/// \param msg: El missatge a despatxar.
///
void Screen::onDispatch(
	const Message &msg) {

	switch (msg.msgId) {
		case MsgId::touchPadEvent:
			switch (msg.touchPad.event) {
				case MsgTouchPadEvent::press:
					setColor(COLOR_Red);
					break;

				case MsgTouchPadEvent::move:
					break;

				default:
				case MsgTouchPadEvent::release:
					setColor(COLOR_Blue);
					break;
			}
			break;

		default:
			Panel::onDispatch(msg);
			break;
	}
}
