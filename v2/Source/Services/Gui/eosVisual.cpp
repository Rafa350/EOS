#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Visual::Visual():
	parent(nullptr),
	firstChild(nullptr),
	lastChild(nullptr),
	nextSibling(nullptr),
	prevSibling(nullptr),
	numChilds(0),
	needRender(true),
	visible(true),
	position(0, 0),
	size(0, 0) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor del objecte.
///
Visual::~Visual() {

	if (parent != nullptr)
		parent->removeVisual(this);

	while (firstChild != nullptr)
		delete firstChild;
}


/// ----------------------------------------------------------------------
/// \brief Marca el visual per ser renderizat.
///
void Visual::invalidate() {

	needRender = true;

	Visual *visual = getFirstChild();
	while (visual != nullptr) {
		visual->invalidate();
		visual = visual->getNextSibling();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param context: El context de renderitzat.
///
void Visual::render(
	RenderContext *context) {

	if (visible) {

		// Si cal renderitzxar, ho fa.
		//
		if (needRender) {
			needRender = false;
			onRender(context);
		}

		// Continua amb els visuals fills.
		//
		Visual *visual = getFirstChild();
		while (visual != nullptr) {
			visual->render(context);
			visual = visual->getNextSibling();
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un visual.
/// \param visual: L'objecte Visual a afeigir.
///
void Visual::addVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->getParent() == nullptr);

	// Cas que sigui el primer visual que s'afegeix;
	//
	if (numChilds == 0) {
		firstChild = visual;
		lastChild = visual;
	}

	// Cas que hi hagin mes visuals en el contenidor
	//
	else {
		visual->prevSibling = lastChild;
		lastChild->nextSibling = visual;
		lastChild = visual;
	}
	visual->parent = this;
	numChilds++;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un visual.
/// \param visual: L'objecte Visual a eliminar.
///
void Visual::removeVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->getParent() != nullptr);
	eosAssert(firstChild != nullptr);
	eosAssert(numChilds > 0);

	if (visual->prevSibling == nullptr)
		firstChild = visual->nextSibling;
	else
		visual->prevSibling->nextSibling = visual->nextSibling;

	if (visual->nextSibling == nullptr)
		lastChild = visual->prevSibling;
	else
		visual->nextSibling->prevSibling = visual->prevSibling;

	visual->parent = nullptr;
	visual->nextSibling = nullptr;
	visual->prevSibling = nullptr;

	numChilds--;
}


/// ----------------------------------------------------------------------
/// \brief Canvia l'estat de visibilitat.
/// \param visible: True per fer el visual visible.
///
void Visual::setVisible(
	bool visible) {

	if (this->visible != visible) {
		this->visible = visible;
		if (!visible && (parent != nullptr))
			parent->invalidate();
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
		Visual *parent = getParent();
		if (parent)
			parent->invalidate();
		else
			invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Asigna el tamany.
/// \param width: Amplada.
/// \param height: Alçada.
///
void Visual::setSize(
	const Size &s) {

    if (size != s) {
    	size = s;
    	Visual *parent = getParent();
		if (parent)
			parent->invalidate();
		else
			invalidate();
    }
}
