#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosFont.h"


using namespace eos;


#define FR_FONT_HEIGHT 1
#define FR_FONT_ASCENT 2
#define FR_FONT_DESCENT 3
#define FR_FONT_FIRST 4
#define FR_FONT_LAST 5

#define FR_CHAR_WIDTH 0
#define FR_CHAR_HEIGHT 1
#define FR_CHAR_LEFT 2
#define FR_CHAR_TOP 3
#define FR_CHAR_ADVANCE 4


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea el font per defecte.
///
Font::Font() :
	_fontResource(getFontResource(eosGraphics_DefFontName, eosGraphics_DefFontHeight, eosGraphics_DefFontStyle)) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    name: Nom del font
/// \param    height: Alçada de la lletra.
/// \param    style: Estil.
///
Font::Font(
	const char *name,
	int height,
	FontStyle style):

	_fontResource(getFontResource(name, height, style)) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    font: L'altre objecte per copiar.
///
Font::Font(
	const Font &font):

	_fontResource(font._fontResource) {

}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    font: L'objecte a asignar.
/// \return   El propi objecte.
///
Font& Font::operator = (
	const Font &font) {

	_fontResource = font._fontResource;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==.
/// \param    font: L'altre font a comparar.
/// \return   True si son iguals.
///
bool Font::operator == (
	const Font& font) const {

	return _fontResource == font._fontResource;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'alçada del font.
/// \return   El resultat.
///
int Font::getFontHeight() const {

	const uint8_t* fr = _fontResource;
	return fr[FR_FONT_HEIGHT];
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'ascendent del font.
/// \return   El resultat.
///
int Font::getFontAscent() const {

	const uint8_t* fr = _fontResource;
	return fr[FR_FONT_ASCENT];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descendent del font.
/// \return   El resultat.
///
int Font::getFontDescent() const {

	const uint8_t* fr = _fontResource;
	return fr[FR_FONT_DESCENT];
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio del font
/// \param fi: Destinacio de la informacio.
///
void Font::getFontInfo(
    FontInfo &fi) const {

	const uint8_t *fr = _fontResource;

	fi.height = fr[FR_FONT_HEIGHT];
    fi.ascent = fr[FR_FONT_ASCENT];
    fi.descent = fr[FR_FONT_DESCENT];
    fi.firstChar = fr[FR_FONT_FIRST];
    fi.lastChar = fr[FR_FONT_LAST];
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio d'un caracter del font.
/// \param c: El caracter.
/// \param ci: Destinacio de la informacio.
///
void Font::getCharInfo(
    char ch,
    CharInfo &ci) const {

    const uint8_t *fr = _fontResource;

    if ((ch >= fr[FR_FONT_FIRST]) && (ch <= fr[FR_FONT_LAST])) {
        int offset = fr[6] + fr[7] * 256 + (ch - fr[4]) * 2;
        int charInfoOffset = fr[offset] + fr[offset + 1] * 256;
        int charBitsOffset = fr[charInfoOffset + 5] + fr[charInfoOffset + 6] * 256;

        ci.width = fr[charInfoOffset + FR_CHAR_WIDTH];
        ci.height = fr[charInfoOffset + FR_CHAR_HEIGHT];
        ci.left = fr[charInfoOffset + FR_CHAR_LEFT];
        ci.top = fr[charInfoOffset + FR_CHAR_TOP];
        ci.advance = fr[charInfoOffset + FR_CHAR_ADVANCE];
        ci.bitmap = (charBitsOffset == -1) ? nullptr : &fr[charBitsOffset];
    }
    else {
        ci.width = 0;
        ci.height = 0;
        ci.left = 0;
        ci.top = 0;
        ci.advance = 0;
        ci.bitmap = nullptr;
    }
}


/// ----------------------------------------------------------------------
/// \brief Obte l'avanç d,un caracter.
/// \param ch: El caracter.
/// \return L'avan� del caracter.
///
int Font::getCharAdvance(
    char ch) const {

	const uint8_t *fr = _fontResource;

    if ((ch >= fr[FR_FONT_FIRST]) && (ch <= fr[FR_FONT_LAST])) {
		int offset = fr[6] + fr[7] * 256 + (ch - fr[4]) * 2;
		int charInfoOffset = fr[offset] + fr[offset + 1] * 256;
		return fr[charInfoOffset + FR_CHAR_ADVANCE];
    }
    else
    	return 0;
}


/// ----------------------------------------------------------------------
/// \brief Crea un font amb els parametres especificats.
/// \param fontName: Nom del font.
/// \param height: Alçada del font.
/// \param style: Estil del font.
///
extern const FontTableEntry *fontResourceTable;
const uint8_t* Font::getFontResource(
	const char *name,
	int height,
	FontStyle style) {

	const FontTableEntry *pResource = fontResourceTable;

	for (int i = 0; pResource[i].name != nullptr; i++) {
		const FontTableEntry *pEntry = &pResource[i];
		if ((strcmp(name, pEntry->name) == 0) &&
			(pEntry->height == height) &&
			(pEntry->style == style)) {

			return pEntry->resource;
		}
	}

	return nullptr;
}
