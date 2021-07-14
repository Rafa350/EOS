#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/eosString.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosFont.h"
#include "Controllers/Display/eosDisplayDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    driver: Driver del display
///
Graphics::Graphics(
    IDisplayDriver* driver) :

    _driver(driver) {

	resetClip();
	resetTransformation();
    setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::bottom);

    setFont(Font());
}


/// ---------------------------------------------------------------------
/// \brief    Destructor.
///
Graphics::~Graphics() {

}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'aliniacio del texte.
/// \param    hAlign: Aliniacio horitzontal.
/// \param    vAlign: Aliniacio vertical.
///
void Graphics::setTextAlign(
    HorizontalTextAlign hAlign,
    VerticalTextAlign vAlign) {

    _state.hAlign = hAlign;
    _state.vAlign = vAlign;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el font per dibuixar caracters i cadenes de texte.
/// \param    font: El font a seleccionar.
/// \return   L'anterior font seleccionat.
///
void Graphics::setFont(
    const Font& font) {

    _font = font;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la transformacio.
/// \param    t: La transformacio.
/// \param    combine: True si cal combinar la transformacio amb l'actual.
///
void Graphics::setTransformation(
	const Transformation& t,
	bool combine) {

	// Asigna la nova transformacio
	//
	_state.ct = t;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la transformacio.
///
void Graphics::resetTransformation() {

	_state.ct.identity();
}


/// ----------------------------------------------------------------------
/// \brief    Salva l'estat.
///
void Graphics::push() {

	//if (!stack.isFull())
		_stack.push(_state);
}


/// ----------------------------------------------------------------------
/// \brief    Recupera l'estat.
///
void Graphics::pop() {

	if (!_stack.isEmpty()) {
		_state = _stack.peek();
		_stack.pop();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Borrat de la pantalla al color especificat.
/// \param    color: El color per realitzar el borrat.
///
void Graphics::clear(
    Color color) const {

	int x1 = 0;
	int y1 = 0;
	int x2 = _driver->getImageWidth() - 1;
	int y2 = _driver->getImageHeight() - 1;

    if (clipRectangle(x1, y1, x2, y2))
        _driver->setPixels(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un pixel.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
/// \param    color: Colcor
///
void Graphics::drawPoint(
    int x,
    int y,
	Color color) const {

	// Transforma a coordinades fisiques
	//
	_state.ct.apply(x, y);

    if (clipPoint(x, y))
        _driver->setPixel(x, y, color);
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'amplada d'una cadena de texte.
/// \param    s: La cadena de texte.
/// \param    offset: El primer caracter del text.
/// \param    length: Numero de caracters a mesurar. -1 si es la longitut
///           total del text.
/// \return    L'amplada de la cadena en pixels.
///
int Graphics::getTextWidth(
    const String& text,
    int offset,
    int length) const {

    int w = 0;
    for (int i = offset, j = length; (j != 0) && (text[i] != 0); i++, j--)
        w += _font.getCharAdvance(text[i]);

    return w;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'alçada d'una cadena de texte.
/// \param    text: La cadena de texte.
/// \return   L'al�ada de la cadena.
///
int Graphics::getTextHeight(
    const String& text) const {

    return _font.getFontHeight();
}


/// ----------------------------------------------------------------------
/// \brief    Transforma les coordinades d'un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
///
void Graphics::transform(
	int& x,
	int& y) const {

	_state.ct.apply(x, y);
}
