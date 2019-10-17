#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosVisual.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
///
Visual::Visual():
	parent(nullptr),
	needRender(false),
	visibility(Visibility::visible),
	position(0, 0),
	size(0, 0),
	minSize(0, 0),
	maxSize(INT32_MAX, INT32_MAX),
	bounds(0, 0, 0, 0),
	margin(0),
	horizontalAlignment(HorizontalAlignment::stretch),
	verticalAlignment(VerticalAlignment::stretch) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor del objecte.
///
Visual::~Visual() {

	if (parent != nullptr)
		parent->removeVisual(this);

	for (auto child: childs)
		delete child;
}


/// ----------------------------------------------------------------------
/// \brief    Marca el visual per ser renderizat.
///
void Visual::invalidate() {

	needRender = true;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si cal renderitzar el visual o algun dels seus fills.
/// \return   True si cal renderitzar.
///
bool Visual::isRenderizable() const {

	if (needRender)
		return true;

	else {
		for (auto child: childs) {
			if (child->isRenderizable())
				return true;
		}
		return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el visual es visible.
/// \return   True si es visible.
///
bool Visual::isVisible() const {

	if (visibility == Visibility::visible) {
		if (parent != nullptr)
			return parent->isVisible();
		else
			return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual.
/// \param    context: El context de renderitzat.
/// \return   True s'ha redibuixat el visual.
///
bool Visual::render(
	RenderContext *context) {

	bool renderized = false;
	needRender = false;

	if (isVisible())
		onRender(context);
	renderized = true;

	// Continua amb els fills.
	//
	for (auto child: childs) {
		if (child->render(context))
			renderized = true;
	}

	return renderized;
}


/// ----------------------------------------------------------------------
/// \brief    Despatcha un missatge.
/// \param    msg: El missatge a despatchar.
///
void Visual::dispatch(
	const Message &msg) {

	onDispatch(msg);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un visual.
/// \param    visual: L'objecte Visual a afeigir.
///
void Visual::addVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->parent == nullptr);

	childs.add(visual);
	visual->parent = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un visual.
/// \param    visual: L'objecte Visual a eliminar.
///
void Visual::removeVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->parent != nullptr);

	visual->parent = nullptr;
	childs.remove(visual);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!childs.isEmpty())
        removeVisual(childs.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual. Primer par del layout.
/// \param    availableSize: Indica el tamany disponible.
///
void Visual::measure(
	const Size &availableSize) {

	if (isVisible()) {

		Size measuredSize = measureOverride(margin.deflate(availableSize));
		int declaredWidth = size.getWidth();
		int declaredHeight = size.getHeight();
		int width = declaredWidth != 0 ? declaredWidth : measuredSize.getWidth();
		int height = declaredHeight != 0 ? declaredHeight : measuredSize.getHeight();

		// Ajusta l'amplada als limits
		//
		width = Math::max(minSize.getWidth(), width);
		width = Math::min(maxSize.getWidth(), width);

		// Ajusta l'alçada als limits
		//
		height = Math::max(minSize.getHeight(), height);
		height = Math::min(maxSize.getHeight(), height);

		desiredSize = margin.inflate(Size(width, height));
	}

	else
		desiredSize = Size();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la mida i la posicio del visual. Segon pas i final del layout.
/// \param    finalSize: Tamany final per asignar al visual.
///
void Visual::arrange(
	const Rect &finalRect) {

	if (isVisible()) {

		// Ajusta el marge
		//
		Rect deflatedFinalRect = margin.deflate(finalRect);
		int deflatedFinalWidth = deflatedFinalRect.getWidth();
		int deflatedFinalHeight = deflatedFinalRect.getHeight();

		int availableWidth = deflatedFinalWidth;
        if (horizontalAlignment != HorizontalAlignment::stretch)
            availableWidth = Math::max(0, Math::min(availableWidth, desiredSize.getWidth() - margin.getLeft() - margin.getRight()));

		int availableHeight = deflatedFinalHeight;
        if (verticalAlignment != VerticalAlignment::stretch)
            availableHeight = Math::max(0, Math::min(availableHeight, desiredSize.getHeight() - margin.getTop() - margin.getBottom()));

        // Obte el tamany definitiu
		//
		Size arrangedSize = arrangeOverride(Size(availableWidth, availableHeight));

		int x = deflatedFinalRect.getX();
		int y = deflatedFinalRect.getY();
		int width = horizontalAlignment == HorizontalAlignment::stretch ? deflatedFinalWidth : arrangedSize.getWidth();
		int height = verticalAlignment == VerticalAlignment::stretch ? deflatedFinalHeight : arrangedSize.getHeight();

		switch (horizontalAlignment) {
			case HorizontalAlignment::center:
			case HorizontalAlignment::stretch:
				x += (deflatedFinalWidth - width) / 2;
				break;

			case HorizontalAlignment::right:
				x += deflatedFinalWidth - width;
				break;

			default:
				break;
		}

		switch (verticalAlignment) {
			case VerticalAlignment::center:
			case VerticalAlignment::stretch:
				y += (deflatedFinalHeight - height) / 2;
				break;

			case VerticalAlignment::bottom:
				y += deflatedFinalHeight - height;
				break;

			default:
				break;
		}

		setPosition(Point(x, y));
		setSize(Size(width, height));

		bounds = Rect(x, y, width, height);
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual i dels seus fills.
/// \param    availableSize: Indica el tamany disponible.
/// \return   El tamany requerit.
/// \remarks  Per defecte, calcula el tamany necesari per encabir tots
///           els fills. Si no te fills, el tamany es zero.
///
Size Visual::measureOverride(
	const Size &availableSize) const {

	int width = 0;
	int height = 0;

	for (auto child: childs) {

		eosAssert(child != nullptr);

		if (child->isVisible()) {

			child->measure(availableSize);
			const Size& childDesiredSize = child->getDesiredSize();

			width = Math::max(width, childDesiredSize.getWidth());
			height = Math::max(height, childDesiredSize.getHeight());
		}
	}

	return Size(width, height);
}


/// ----------------------------------------------------------------------
/// \brief    Ajusta el tamany del visual i els seus fills.
/// \param    finalSize: El tamany final a asignar.
/// \return   El tamany final obtingut.
///
Size Visual::arrangeOverride(
	const Size &finalSize) const {

	for (auto child: childs) {

		eosAssert(child != nullptr);

		if (child->isVisible())
			child->arrange(Rect(finalSize));
	}

	return finalSize;
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat de visibilitat.
/// \param    newVisibility: La nova visibilitat.
///
void Visual::setVisibility(
	Visibility value) {

	if (visibility != value) {
		visibility = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la posicio.
/// \param    value: La nova posicio.
///
void Visual::setPosition(
	const Point &value) {

	if (position != value) {
		position = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany.
/// \param    value: El nou tamany.
///
void Visual::setSize(
	const Size &value) {

    if (size != value) {
    	size = value;
		invalidate();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany minim.
/// \param    value: El nou tamany.
///
void Visual::setMinSize(
	const Size &value) {

	if (minSize != value) {
		minSize = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el marge.
/// \param    value: El nou marge.
///
void Visual::setMargin(
	const Thickness &value) {

	if (margin != value) {
		margin = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief     Asigna l'aliniacio horizontal.
/// \param     value: El nou valor de l'aliniacio.
///
void Visual::setHorizontalAlignment(
	HorizontalAlignment value) {

	if (horizontalAlignment != value) {
		horizontalAlignment = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio vertical
/// \param    value: El nou valor de l'aliniacio.
///
void Visual::setVerticalAlignment(
	VerticalAlignment value) {

	if (verticalAlignment != value) {
		verticalAlignment = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha que despatxar un missatge..
/// \param    msg: El missatge a despatxar.
///
void Visual::onDispatch(
	const Message &msg) {

	switch (msg.msgId) {
#ifdef OPT_GUI_TouchPad
		case MsgId::touchPadEvent:
			onDispatchTouchPadEvent(msg.touchPad);
			break;
#endif

		default:
			// Si no el procesa, pasa al pare.
			if (parent != nullptr)
				parent->onDispatch(msg);
			break;
	}

}


/// ----------------------------------------------------------------------
/// \brief    Es crida al activar el visual.
/// \param    visual: El visual desactivat al activar aquest.
///
void Visual::onActivate(
	Visual *visual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida al desactivar el visual.
/// \param    visual: El visual activat al desactivar aquest.
///
void Visual::onDeactivate(
	Visual *visual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events del touchpad
/// \param    msg: L'event a procesar.
///
#ifdef OPT_GUI_TouchPad
void Visual::onDispatchTouchPadEvent(
	const MsgTouchPad &msg) {

	switch (msg.event) {
		case MsgTouchPadEvent::enter:
			onTouchPadEnter();
			break;

		case MsgTouchPadEvent::leave:
			onTouchPadLeave();
			break;

		case MsgTouchPadEvent::move:
			onTouchPadMove(Point(msg.x, msg.y));
			break;

		case MsgTouchPadEvent::press:
			onTouchPadPress(Point(msg.x, msg.y));
			break;

		case MsgTouchPadEvent::release:
			onTouchPadRelease();
			break;
	}
}
#endif


#ifdef OPT_GUI_TouchPad
void Visual::onTouchPadEnter() {

}
#endif


#ifdef OPT_GUI_TouchPad
void Visual::onTouchPadLeave() {

}
#endif


#ifdef OPT_GUI_TouchPad
void Visual::onTouchPadPress(
	const Point &position) {

}
#endif


#ifdef OPT_GUI_TouchPad
void Visual::onTouchPadRelease() {

}
#endif


#ifdef OPT_GUI_TouchPad
void Visual::onTouchPadMove(
	const Point &position) {

}
#endif
