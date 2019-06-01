#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiVisuals.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Afegeix un visual a un contenidor de visuals.
/// \param[in] container: L'objecte contenidor de visuals.
/// \param[in] visual: L'objecte visual a afeigir.
/// \remarks No fa cap comprovacio previa. Es suposa que els
///          parametres son correctes i tant el contenidor com
///          el visual estan en un estat coherent.
///
void eos::addVisual(
	VisualContainer *container,
	Visual *visual) {

	// Cas que sigui el primer visual que s'afegeix;
	//
	if (container->numChilds == 0) {
		visual->parent = container;
		container->firstChild = visual;
		container->lastChild = visual;
	}

	// Cas que hi hagin mes visuals en el contenidor
	//
	else {
		visual->parent = container;
		visual->prevSibling = container->lastChild;
		container->lastChild->nextSibling = visual;
		container->lastChild = visual;
	}

	container->numChilds++;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un visual del contenidos de visuals.
/// \param[in] container: L'objecte contenidor de visuals.
/// \param[in] visual: L'objecte visual a eliminar.
/// \remarks No fa cap comprovacio previa. Es suposa que els
///          parametres son correctes i tant el contenidor com
///          el visual estan en un estat coherent.
///
void eos::removeVisual(
	VisualContainer *container,
	Visual *visual) {

	if (visual->prevSibling == nullptr)
		container->firstChild = visual->nextSibling;
	else
		visual->prevSibling->nextSibling = visual->nextSibling;

	if (visual->nextSibling == nullptr)
		container->lastChild = visual->prevSibling;
	else
		visual->nextSibling->prevSibling = visual->prevSibling;

	visual->parent = nullptr;
	visual->nextSibling = nullptr;
	visual->prevSibling = nullptr;

	container->numChilds--;
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
Visual::Visual():
	parent(nullptr),
	nextSibling(nullptr),
	prevSibling(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
VisualContainer::VisualContainer():
	firstChild(nullptr),
	lastChild(nullptr),
	numChilds(0) {

}


/// ----------------------------------------------------------------------
/// \brief Afegeix un visual.
/// \param[in] visual: L'objecte Visual a afeigir.
///
void VisualContainer::addVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->getParent() == nullptr);

	eos::addVisual(this, visual);
}


/// ----------------------------------------------------------------------
/// \brief Elimina un visual.
/// \param[in] visual: L'objecte Visual a eliminar.
///
void VisualContainer::removeVisual(
	Visual *visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->getParent() != nullptr);
	eosAssert(firstChild != nullptr);
	eosAssert(numChilds > 0);

	eos::removeVisual(this, visual);
}


void VisualContainer::render() {

	renderChilds();
}


void VisualContainer::renderChilds() {

	for (Visual *visual = getFirstChild(); visual != nullptr; visual = visual->getNextSibling())
		visual->render();
}
