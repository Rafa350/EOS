#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosGuiVisuals.h"
#include "System/Graphics/eosDisplay.h"


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
	needRender(true) {
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


void Visual::invalidate() {

	needRender = true;
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param[in] display: El display on dibuixar.
///
void Visual::render(
	Display *display) {

	if (needRender) {
		needRender = false;

		onRender(display);

		for (Visual *visual = getFirstChild(); visual != nullptr; visual = visual->getNextSibling())
			visual->render(display);
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
/// \brief Asigna el color de fons de la pantalla.
/// \param[in] color: El color.
///
void Screen::setColor(
	const Color &color) {

	if (this->color != color) {
		this->color = color;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Renderitza el visual.
/// \param[in] display: El display on dibuixar.
///
void Screen::onRender(
	Display *display) {

	display->clear(color);
}


void Window::setPosition(
	int x,
	int y) {

	if ((this->x != x) || (this->y != y)) {
		this->x = x;
		this->y = y;
		invalidate();
	}
}


void Window::setSize(
	int width,
	int height) {

    if ((this->width != width) || (this->height != height)) {
    	this->width = width;
    	this->height = height;
    	invalidate();
    }
}


void Widget::setBorderColor(
	const Color &color) {

	borderColor = color;
}

void Widget::onRender(
	Display *display) {

	display->setColor(borderColor);
	display->drawRectangle(getX(), getY(), getWidth(), getHeight());
}
