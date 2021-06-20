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
    IDisplayDriver *driver) :

    _driver(driver),
	_pen(COLOR_Black, 1, PenStyle::Solid),
	_brush(COLOR_White) {

	resetClip();
	resetTransformation();
    setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::bottom);

    const uint8_t *fontResource = Font::getFontResource("Tahoma", 12, FontStyle::regular);
    setFont(Font(fontResource));
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
    const Font &font) {

    _font = font;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona la regio de retall.
/// \param    x1: Coordinada X esquerra.
/// \param    y1: Coodinada Y superior.
/// \param    x2: Coordinada X dreta.
/// \param    y2: Coordinada Y inferior.
/// \remarks  Utilitza les coordinades fisiques.
///
void Graphics::setClip(
    int x1,
    int y1,
    int x2,
    int y2) {

	// Normalitzacio de coordinades
	//
    if (x1 > x2)
        Math::swap(x1, x2);
    if (y1 > y2)
        Math::swap(y1, y2);

    // Asigna la nova area de retall
    //
	_state.clipX1 = Math::max(0, x1);
	_state.clipY1 = Math::max(0, y1);
	_state.clipX2 = Math::min(x2, _driver->getImageWidth() - 1);
	_state.clipY2 = Math::min(y2, _driver->getImageHeight() - 1);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina l'area de retall.
///
void Graphics::resetClip() {

	_state.clipX1 = 0;
	_state.clipY1 = 0;
	_state.clipX2 = _driver->getImageWidth() - 1;
	_state.clipY2 = _driver->getImageHeight() - 1;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la transformacio.
/// \param    t: La transformacio.
/// \param    combine: True si cal combinar la transformacio amb l'actual.
///
void Graphics::setTransformation(
	const Transformation &t,
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
    const Color &color) const {

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
	const Color& color) const {

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
    const String &text,
    int offset,
    int length) const {

    int w = 0;
    for (unsigned i = offset, j = length; j && text[i]; i++, j--)
        w += _font.getCharAdvance(text[i]);

    return w;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'alçada d'una cadena de texte.
/// \param    text: La cadena de texte.
/// \return   L'al�ada de la cadena.
///
int Graphics::getTextHeight(
    const String &text) const {

    return _font.getFontHeight();
}


/// ----------------------------------------------------------------------
/// \brief    Retalla un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
/// \return    True si es visible.
///
bool Graphics::clipPoint(
    int x,
    int y) const {

    return
    	(x >= _state.clipX1) && (x <= _state.clipX2) &&
    	(y >= _state.clipY1) && (y <= _state.clipY2);
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia horitzontal.
/// \param    x1: Coordinada X del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y: Coordinada Y comu ambdos punts.
/// \return   True si es visible.
///
bool Graphics::clipHLine(
	int &x1,
	int &x2,
	int y) const {

	// Descarta si es fora de l'area de visualitzacio
	//
	if ((y < _state.clipY1) || (y > _state.clipY2))
		return false;

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);

	// Ajusta els punts d'interseccio
	//
	x1 = Math::max(_state.clipX1, x1);
	x2 = Math::min(x2, _state.clipX2);

	return x1 <= x2;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia vertical.
/// \param    x: Coordinada X comu ambdos punts.
/// \param    y1: Coordinada Y del primer punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipVLine(
	int x,
	int &y1,
	int &y2) const {

	// Descarta si es fora de l'area de visualitzacio
	//
	if ((x < _state.clipX1) || (x > _state.clipX2))
		return false;

	// Normalitza les coordinades
	//
	if (y1 > y2)
		Math::swap(y1, y2);

	// Ajusta els punts d'interseccio
	//
	y1 = Math::max(_state.clipY1, y1);
	y2 = Math::min(y2, _state.clipY2);

	return y1 <= y2;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla una linia arbitraria. Amb l'algorisme Liang-Barsky.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipLine(
    int &x1,
    int &y1,
    int &x2,
    int &y2) const {

	// La descarta si es fora de l'area de visualitzacio
	//
    if (((x1 < _state.clipX1) && (x2 < _state.clipX1)) ||
        ((x1 > _state.clipX2) && (x2 > _state.clipX2)) ||
        ((y1 < _state.clipY1) && (y2 < _state.clipY1)) ||
        ((y1 > _state.clipY2) && (y2 > _state.clipY2)))
        return false;

    int t1 = 0;
    int t2 = 1 << 16;

    int dx = x2 - x1;
    if (!clipTest(-dx, x1 - _state.clipX1, t1, t2))
        return false;
    if (!clipTest(dx, _state.clipX2 - x1, t1, t2))
        return false;

    int dy = y2 - y1;
    if (!clipTest(-dy, y1 - _state.clipY1, t1, t2))
        return false;
    if (!clipTest(dy, _state.clipY2 - y1, t1, t2))
        return false;

    // Ajusta el punt d'interseccio x2, y2
    //
    if (t2 < (1 << 16)) {
        x2 = x1 + ((t2 * dx) >> 16);
        y2 = y1 + ((t2 * dy) >> 16);
    }

    // Ajusta el punt d'interseccio x1, y1
    //
    if (t1 > 0) {
        x1 = x1 + ((t1 * dx) >> 16);
        y1 = y1 + ((t1 * dy) >> 16);
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Realitza el calcul de visibilitat per la funcio 'clipLine'
/// \param    p: Coordinada X o Y del punt inicial.
/// \param    q: Coordinada X o Y del puint final.
/// \param    t1: Correccio del punt inicial.
/// \param    t2: Correccio del punt final.
/// \return:  True si es visible, false en cas contrari.
///
bool Graphics::clipTest(
    int p,
    int q,
    int &t1,
    int &t2) {

    int r;

    if (p < 0) {
        if (q < 0) {
            r = (q << 16) / p;
            if (r > t2)
                return false;
            else if (r > t1)
                t1 = r;
        }
    }

    else if (p > 0) {
        if (q < p) {
            r = (q << 16) / p;
            if (r < t1)
                return false;
            else if (r < t2)
                t2 = r;
        }
    }

    else
        if (q < 0)
            return false;

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Retalla un area.
/// \param    x1: Coordinada X del primer punt.
/// \param    y1: Coordinada Y del primer punt.
/// \param    x2: Coordinada X del segon punt.
/// \param    y2: Coordinada Y del segon punt.
/// \return   True si es visible.
///
bool Graphics::clipRectangle(
    int &x1,
    int &y1,
    int &x2,
    int &y2) const {

	// Normalitza les coordinades
	//
	if (x1 > x2)
		Math::swap(x1, x2);
	if (y1 > y2)
		Math::swap(y1, y2);

	// Calcula la interseccio
	//
	x1 = Math::max(x1, _state.clipX1);
	y1 = Math::max(y1, _state.clipY1);
	x2 = Math::min(x2, _state.clipX2);
	y2 = Math::min(y2, _state.clipY2);

	return (x1 <= x2) && (y1 <= y2);
}


/// ----------------------------------------------------------------------
/// \brief    Transforma les coordinades d'un punt.
/// \param    x: Coordinada X del punt.
/// \param    y: Coordinada Y del punt.
///
void Graphics::transform(
	int &x,
	int &y) const {

	_state.ct.apply(x, y);
}
