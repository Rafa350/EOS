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
	visible(true),
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

	if (visible) {
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


/// --------------------------------------------------------------------
/// \brief Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!childs.isEmpty())
        removeVisual(childs.getFront());
}


/// ---------------------------------------------------------------------
/// \brief Obte el visual en la posicio indicada.
/// \param p: La posicio.
/// \return El visual, o null si no el troba.
///
Visual *Visual::getVisualAt(
	const Point &p) {

	Rect r(getAbsolutePosition(), size);
	if (r.contains(p)) {

		for (VisualListIterator it(childs); it.hasNext(); it.next()) {
			Visual *pChild = it.current()->getVisualAt(p);
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
void Visual::setVisible(
	bool visible) {

	if (this->visible != visible) {
		this->visible = visible;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna la posicio.
/// \param p: Coordinades de la posicio.
///
void Visual::setPosition(
	const Point &p) {

	if (position != p) {
		position = p;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el tamany.
/// \param width: Amplada.
/// \param height: Al�ada.
///
void Visual::setSize(
	const Size &s) {

    if (size != s) {
    	size = s;
		invalidate();
    }
}


/// ----------------------------------------------------------------------
/// \brief Despatch del missatge per defecte.
/// \param msg: El missatge a despatxar.
///
void Visual::onDispatch(
	const Message &msg) {

	switch (msg.msgId) {
		case MsgId::activate:
			onActivate(msg);
			break;

		case MsgId::deactivate:
			onDeactivate(msg);
			break;

		default:
			break;
	}

}


/// ----------------------------------------------------------------------
/// \brief Despatxa el missagte 'activate'
/// \param msg: El missatge.
///
void Visual::onActivate(
	const Message &msg) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief Despatxa el missagte 'deactivate'
/// \param msg: El missatge.
///
void Visual::onDeactivate(
	const Message &msg) {

	invalidate();
}
