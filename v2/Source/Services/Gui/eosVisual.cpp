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
	visible(true) {
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
/// \param[in] graphics: El display on dibuixar.
///
void Visual::render(
	Graphics *graphics) {

	if (visible) {

		// Si cal renderitzxar, ho fa.
		//
		if (needRender) {
			needRender = false;
			onRender(graphics);
		}

		// Continua amb els visuals fills.
		//
		Visual *visual = getFirstChild();
		while (visual != nullptr) {
			visual->render(graphics);
			visual = visual->getNextSibling();
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un visual.
/// \param[in] visual: L'objecte Visual a afeigir.
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
/// \param[in] visual: L'objecte Visual a eliminar.
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
/// \param[in] visible: True per fer el visual visible.
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
