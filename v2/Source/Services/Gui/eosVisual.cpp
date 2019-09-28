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
	pParent(nullptr),
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

	if (pParent != nullptr)
		pParent->removeVisual(this);

	while (!childs.isEmpty()) {

		Visual *pChild = childs.getFront();
		childs.remove(pChild);

		delete pChild;
	}
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
bool Visual::isRenderizable() {

	if (needRender)
		return true;

	else {
		for (VisualListIterator it(childs); it.hasNext(); it.next()) {
			if (it.current()->isRenderizable())
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
		if (pParent != nullptr)
			return pParent->isVisible();
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
	RenderContext &context) {

	bool renderized = false;
	needRender = false;

	if (isVisible())
		onRender(context);
	renderized = true;

	// Continua amb els fills.
	//
	for (VisualListIterator it(childs); it.hasNext(); it.next()) {
		Visual *pChild = it.current();
		if (pChild->render(context))
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
/// \param    pVisual: L'objecte Visual a afeigir.
///
void Visual::addVisual(
	Visual *pVisual) {

	eosAssert(pVisual != nullptr);
	eosAssert(pVisual->pParent == nullptr);

	childs.add(pVisual);
	pVisual->pParent = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un visual.
/// \param    pVisual: L'objecte Visual a eliminar.
///
void Visual::removeVisual(
	Visual *pVisual) {

	eosAssert(pVisual != nullptr);
	eosAssert(pVisual->pParent != nullptr);

	pVisual->pParent = nullptr;
	childs.remove(pVisual);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!childs.isEmpty())
        removeVisual(childs.getFront());
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual. Primer par del layout.
/// \param    availableSize: Indica el tamany disponible.
///
void Visual::measure(
	const Size &availableSize) {

	if (isVisible()) {

		Size measuredSize = measureOverride(availableSize.deflate(margin));
		int width = measuredSize.getWidth();
		int height = measuredSize.getHeight();

		// Ajusta l'amplada als limits
		//
		width = Math::max(minSize.getWidth(), width);
		width = Math::min(maxSize.getWidth(), width);

		// Ajusta l'alçada als limits
		//
		height = Math::max(minSize.getHeight(), height);
		height = Math::min(maxSize.getHeight(), height);

		desiredSize = Size(width, height).inflate(margin);
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
		Rect deflatedFinalRect = finalRect.deflate(margin);
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

	for (VisualListIterator it(childs); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible()) {

			pChild->measure(availableSize);
			const Size& childDesiredSize = pChild->getDesiredSize();

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

	for (VisualListIterator it(childs); it.hasNext(); it.next()) {

		Visual *pChild = it.current();
		eosAssert(pChild != nullptr);

		if (pChild->isVisible())
			pChild->arrange(Rect(finalSize));
	}

	return finalSize;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el visual en la posicio indicada.
/// \param    position: La posicio.
/// \return   El visual, o null si no el troba.
///
Visual *Visual::getVisualAt(
	const Point &position) {

	Rect r(getAbsolutePosition(), size);
	if (r.contains(position)) {

		for (VisualListIterator it(childs); it.hasNext(); it.next()) {
			Visual *pChild = it.current()->getVisualAt(position);
			if (pChild != nullptr)
				return pChild;
		}

		return this;
	}

	else
		return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la posicio absoluta del visual.
/// \return   La posicio absoluta.
///
Point Visual::getAbsolutePosition() const {

	int x = position.getX();
	int y = position.getY();

	for (Visual *pVisual = pParent; pVisual != nullptr; pVisual = pVisual->pParent) {
		x += pVisual->position.getX();
		y += pVisual->position.getY();
	}

	return Point(x, y);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat de visibilitat.
/// \param    visible: True per fer el visual visible.
///
void Visual::setVisibility(
	Visibility visibility) {

	if (this->visibility != visibility) {
		this->visibility = visibility;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la posicio.
/// \param    position: La nova posicio.
///
void Visual::setPosition(
	const Point &position) {

	if (this->position != position) {
		this->position = position;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany.
/// \param    size: El nou tamany.
///
void Visual::setSize(
	const Size &size) {

    if (this->size != size) {
    	this->size = size;
		invalidate();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany minim.
/// \param    size: El nou tamany.
///
void Visual::setMinSize(
	const Size &size) {

	if (minSize != size) {
		minSize = size;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el marge.
/// \param    margin: El nou marge.
///
void Visual::setMargin(
	const Thickness &margin) {

	if (this->margin != margin) {
		this->margin = margin;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio horizontal.
/// \param horizontalAlignment: L'aliniacio.
///
void Visual::setHorizontalAlignment(
	HorizontalAlignment horizontalAlignment) {

	if (this->horizontalAlignment != horizontalAlignment) {
		this->horizontalAlignment = horizontalAlignment;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna l'aliniacio vertical
/// \param verticalAlignment: L'aliniacio.
///
void Visual::setVerticalAlignment(
	VerticalAlignment verticalAlignment) {

	if (this->verticalAlignment != verticalAlignment) {
		this->verticalAlignment = verticalAlignment;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quent hi ha que despatxar un missatge..
/// \param    msg: El missatge a despatxar.
///
void Visual::onDispatch(
	const Message &msg) {

	switch (msg.msgId) {
#ifdef OPT_GUI_TouchPad
		case MsgId::touchPadEvent:
			onDispatchTouchPadEvent(msg);
			break;
#endif

		default:
			// Si no el procesa, pasa al pare.
			if (pParent != nullptr)
				pParent->onDispatch(msg);
			break;
	}

}


/// ----------------------------------------------------------------------
/// \brief    Es crida al activar el visual.
/// \param    pVisual: El visual desactivat al activar aquest.
///
void Visual::onActivate(
	Visual *pVisual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida al desactivar el visual.
/// \param    pVisual: El visual activat al desactivar aquest.
///
void Visual::onDeactivate(
	Visual *pVisual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'touchPadEvent'
///
#ifdef OPT_GUI_TouchPad
void Visual::onDispatchTouchPadEvent(
	const Message &msg) {

	switch (msg.touchPad.event) {
		case MsgTouchPadEvent::enter:
			onTouchPadEnter();
			break;

		case MsgTouchPadEvent::leave:
			onTouchPadLeave();
			break;

		case MsgTouchPadEvent::move:
			onTouchPadMove(Point(msg.touchPad.x, msg.touchPad.y));
			break;

		case MsgTouchPadEvent::press:
			onTouchPadPress(Point(msg.touchPad.x, msg.touchPad.y));
			break;

		case MsgTouchPadEvent::release:
			onTouchPadRelease();
			break;

		default:
			// Si no el procesa, pasa al pare.
			if (pParent != nullptr)
				pParent->onDispatchTouchPadEvent(msg);
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
