#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Graphics/eosFont.h"


using namespace eos;


extern const FontTableEntry* fontResourceTable;


struct Font::Impl {
    char chCache;
    CharInfo ciCache;
    const uint8_t *fontResource;
};


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea el font per defecte.
///
Font::Font() :
	_pImpl(allocate()) {

	_pImpl->chCache = -1;
	_pImpl->fontResource = nullptr;
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    fontResource: El recurs del font.
///
Font::Font(
	const uint8_t *fontResource):

	_pImpl(allocate()) {

    _pImpl->chCache = -1;
    _pImpl->fontResource = getFontResource("Tahoma", 12, FontStyle::regular);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    other: L'altre objecte per copiar.
///
Font::Font(
	const Font& font):

	_pImpl(font._pImpl) {
}


/// ----------------------------------------------------------------------
/// \brief    Crea el bloc ded memoria de Impl
/// \return   El punter al bloc.
///
Font::PImpl Font::allocate() {

	return PImpl(new Font::Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    font: L'objecte a asignar.
/// \return   El propi objecte.
///
Font& Font::operator = (
	const Font& font) {

	_pImpl = font._pImpl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'alçada del font.
/// \return   El resultat.
///
int Font::getFontHeight() const {

	return _pImpl->fontResource[1];
}


/// ----------------------------------------------------------------------
/// \brief Crea un font amb els parametres especificats.
/// \param fontName: Nom del font.
/// \param height: Alçada del font.
/// \param style: Estil del font.
///
const uint8_t* Font::getFontResource(
	const String &name,
	int height,
	FontStyle style) {

	const FontTableEntry *pResource = fontResourceTable;

	for (unsigned i = 0; pResource[i].name != nullptr; i++) {
		const FontTableEntry *pEntry = &pResource[i];
		if ((name.isEqual(pEntry->name)) &&
			(pEntry->height == height) &&
			(pEntry->style == style)) {

			return pEntry->resource;
		}
	}

	return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio del font
/// \param fi: Destinacio de la informacio.
///
void Font::getFontInfo(
    FontInfo &fi) const {

    fi.height = _pImpl->fontResource[1];
    fi.ascent = _pImpl->fontResource[2];
    fi.descent = _pImpl->fontResource[3];
    fi.firstChar = _pImpl->fontResource[4];
    fi.lastChar = _pImpl->fontResource[5];
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio d'un caracter del font.
/// \param c: El caracter.
/// \param ci: Destinacio de la informacio.
///
void Font::getCharInfo(
    char ch,
    CharInfo &ci) const {

    updateCache(ch);
    ci = _pImpl->ciCache;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'avan� deun caracter.
/// \param ch: El caracter.
/// \return L'avan� del caracter.
///
int Font::getCharAdvance(
    char ch) const {

    updateCache(ch);
    return _pImpl->ciCache.advance;
}


/// ----------------------------------------------------------------------
/// \brief : Actualitza el cache amb la informacio del caracter.
/// \param ch: El caracter.
///
void Font::updateCache(
    char ch) const {

    if (_pImpl->chCache != ch) {
        _pImpl->chCache = ch;
        if ((ch >= _pImpl->fontResource[4]) && (ch <= _pImpl->fontResource[5])) {
            unsigned offset = _pImpl->fontResource[6] + _pImpl->fontResource[7] * 256u + (ch - _pImpl->fontResource[4]) * 2u;
            unsigned charInfoOffset = _pImpl->fontResource[offset] + _pImpl->fontResource[offset + 1] * 256u;
            unsigned charBitsOffset = _pImpl->fontResource[charInfoOffset + 5u] + _pImpl->fontResource[charInfoOffset + 6u] * 256u;

            _pImpl->ciCache.width = _pImpl->fontResource[charInfoOffset];
            _pImpl->ciCache.height = _pImpl->fontResource[charInfoOffset + 1u];
            _pImpl->ciCache.left = _pImpl->fontResource[charInfoOffset + 2u];
            _pImpl->ciCache.top = _pImpl->fontResource[charInfoOffset + 3u];
            _pImpl->ciCache.advance = _pImpl->fontResource[charInfoOffset + 4u];
            _pImpl->ciCache.bitmap = (charBitsOffset == (unsigned) -1) ? nullptr : &_pImpl->fontResource[charBitsOffset];
        }
        else {
            _pImpl->ciCache.width = 0;
            _pImpl->ciCache.height = 0;
            _pImpl->ciCache.left = 0;
            _pImpl->ciCache.top = 0;
            _pImpl->ciCache.advance = 0;
            _pImpl->ciCache.bitmap = nullptr;
        }
    }
}


