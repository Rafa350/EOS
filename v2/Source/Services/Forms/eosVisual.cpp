#include "eos.h"
#include "Services/Forms/eosVisual.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    position: La posicio del visual relativa al seu pare.
/// \param    size: El tamany del visual.
///
eos::Visual::Visual(
	const Point &position,
	const Size &size):

	_position {position},
	_size {size},
	_parent {nullptr},
	_renderPending {true} {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un visual a la llista de fills.
/// \param    child: El visual a afeigit.
///
void eos::Visual::addChild(
	Visual *child) {

	if (child->_parent == nullptr) {
		child->_parent = this;
		_childs.pushFront(child);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Retorna l'arrel de l'arbre de visuals.
/// \return   El visual root
///
eos::Visual *eos::Visual::getRoot() {

	Visual *root = this;

	while (root->_parent != nullptr)
		root = root->_parent;

	return root;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge
/// \param    message: El missatge.
///
void eos::Visual::onMessage(
	FormMessage &message) {

}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual.
/// \param    graphic: L'objecte grafic per dibuixar.
///
void eos::Visual::onRender(
	Graphics *graphics) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa el canvi de valor de les propietats.
/// \param    property: La propietat.
///
void eos::Visual::onPropertyChanged(
	void *property) {

	if ((property == &_position) || (property == &_size))
		invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual i els seus fills.
/// \param    graphics: Objecte grafic per dibuixar.
///
void eos::Visual::render(
	Graphics *graphics) {

	for (auto child: _childs)
		child->render(graphics);

	onRender(graphics);

	_renderPending = false;
}


/// ----------------------------------------------------------------------
/// \brief    Invalida el visual i  força el renderitzat.
///
void eos::Visual::invalidate() {

	_renderPending = true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un missatge.
/// \param    message: El missatge.
///
void eos::Visual::message(
	FormMessage &message) {

	onMessage(message);

	//if (_parent)
	//	_parent->onMessage(message);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el visual esta pendent de renderitzar.
/// \return  Trie si esta pendent.
///
bool eos::Visual::isRenderPending() const {

	for (auto child: _childs)
		if (child->isRenderPending())
			return true;

	return _renderPending;
}

