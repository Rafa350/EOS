#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiMessageQueue.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Visual::Visual():
	pParent(nullptr),
	needRender(false),
	visibility(Visibility::visible),
	position(0, 0),
	size(0, 0) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor del objecte.
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
/// \brief Marca el visual per ser renderizat.
///
void Visual::invalidate() {

	needRender = true;
}


/// ----------------------------------------------------------------------
/// \brief Comprova si cal renderitzar el visual o algun dels seus fills.
/// \return True si cal renderitzar.
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
/// \brief Comprova si el visual es visible.
/// \return True si es visible.
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
/// \brief Renderitza el visual.
/// \param context: El context de renderitzat.
/// \return True s'ha redibuixat el visual.
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
/// \brief Despatcha un missatge.
/// \param msg: El missatge a despatchar.
///
void Visual::dispatch(
	const Message &msg) {

	onDispatch(msg);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un visual.
/// \param pVisual: L'objecte Visual a afeigir.
///
void Visual::addVisual(
	Visual *pVisual) {

	eosAssert(pVisual != nullptr);
	eosAssert(pVisual->pParent == nullptr);

	childs.add(pVisual);
	pVisual->pParent = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un visual.
/// \param pVisual: L'objecte Visual a eliminar.
///
void Visual::removeVisual(
	Visual *pVisual) {

	eosAssert(pVisual != nullptr);
	eosAssert(pVisual->pParent != nullptr);

	pVisual->pParent = nullptr;
	childs.remove(pVisual);
}


/// ----------------------------------------------------------------------
/// \brief Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!childs.isEmpty())
        removeVisual(childs.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Calcula la mida del visual. Primer par del layout.
/// \param availableSize: Indica el tamany disponible.
///
void Visual::measure(
	const Size &availableSize) {

}


/// ----------------------------------------------------------------------
/// \brief Obte el resultat del method 'measure'.
/// \return El tamany calculat.
///
const Size& Visual::getDesiredSize() const {

	return size;
}


/// ----------------------------------------------------------------------
/// \brief Obte el visual en la posicio indicada.
/// \param position: La posicio.
/// \return El visual, o null si no el troba.
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
/// \brief Obte la posicio absoluta del visual.
/// \return La posicio absoluta.
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
/// \brief Canvia l'estat de visibilitat.
/// \param visible: True per fer el visual visible.
///
void Visual::setVisibility(
	Visibility visibility) {

	if (this->visibility != visibility) {
		this->visibility = visibility;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna la posicio.
/// \param position: La nova posicio.
///
void Visual::setPosition(
	const Point &position) {

	if (this->position != position) {
		this->position = position;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el tamany.
/// \param size: El nou tamany.
///
void Visual::setSize(
	const Size &size) {

    if (this->size != size) {
    	this->size = size;
		invalidate();
    }
}


/// ----------------------------------------------------------------------
/// \brief Es crida quent hi ha que despatxar un missatge..
/// \param msg: El missatge a despatxar.
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
/// \brief Es crida al activar el visual.
/// \param pVisual: El visual desactivat al activar aquest.
///
void Visual::onActivate(
	Visual *pVisual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief Es crida al desactivar el visual.
/// \param pVisual: El visual activat al desactivar aquest.
///
void Visual::onDeactivate(
	Visual *pVisual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief Procesa el missatge 'touchPadEvent'
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
