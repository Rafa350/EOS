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
	needRender(true),
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

	while (!visuals.isEmpty()) {

		Visual *pVisual = visuals.getFront();
		visuals.remove(pVisual);

		delete pVisual;
	}
}


/// ----------------------------------------------------------------------
/// \brief Marca el visual per ser renderizat.
///
void Visual::invalidate() {

	// Invalida this
	//
	needRender = true;

	// Invalida tots els descendents recursivament
	//
	for (VisualListIterator it(visuals); it.hasNext(); it.next()) {
		Visual *pVisual = it.current();
		pVisual->invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param context: El context de renderitzat.
///
void Visual::render(
	RenderContext &context) {

	if (visible) {

		// Si cal renderitzxar, ho fa.
		//
		if (needRender) {
			needRender = false;
			onRender(context);
		}

		// Continua amb els visuals fills.
		//
		for (VisualListIterator it(visuals); it.hasNext(); it.next()) {
			Visual *pChild = it.current();
			pChild->render(context);
		}
	}
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

	visuals.add(pVisual);
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
	visuals.remove(pVisual);
}


/// --------------------------------------------------------------------
/// \brief Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!visuals.isEmpty())
        removeVisual(visuals.getFront());
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

		for (VisualListIterator it(visuals); it.hasNext(); it.next()) {
			Visual *pVisual = it.current()->getVisualAt(p);
			if (pVisual != nullptr)
				return pVisual;
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
		if (!visible && (pParent != nullptr))
			pParent->invalidate();
		else
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
		if (pParent != nullptr)
			pParent->invalidate();
		else
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
		if (pParent != nullptr)
			pParent->invalidate();
		else
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
