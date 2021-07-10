#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Graphics/eosFont.h"


using namespace eos;


class Font::Impl: public PoolAllocatable<Font::Impl, eosGraphics_MaxFonts> {
	public:
    	char chCache;
    	CharInfo ciCache;
    	const uint8_t *fontResource;

	public:
    	bool operator == (const Impl& other) const {
    		return fontResource == other.fontResource;
    	}

    	bool operator != (const Impl& other) const {
    		return !(*this == other);
    	}
};


extern const FontTableEntry* fontResourceTable;


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea el font per defecte.
///
Font::Font() :
	_impl(makeImpl()) {

	_impl->chCache = -1;
	_impl->fontResource = nullptr;
}

/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    fontResource: El recurs del font.
///
Font::Font(
	const uint8_t *fontResource):

	_impl(makeImpl()) {

    _impl->chCache = -1;
    _impl->fontResource = getFontResource("Tahoma", 12, FontStyle::regular);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    font: L'altre objecte per copiar.
///
Font::Font(
	const Font& font):

	_impl(font._impl) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
Font::~Font() {

}


/// ----------------------------------------------------------------------
/// \brief    Crea el bloc de memoria de Impl
/// \return   El punter al bloc.
///
Font::ImplPtr Font::makeImpl() {

	return ImplPtr(new Font::Impl);
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'assignacio.
/// \param    font: L'objecte a asignar.
/// \return   El propi objecte.
///
Font& Font::operator = (
	const Font& font) {

	_impl = font._impl;

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador ==.
/// \param    font: L'altre font a comparar.
/// \return   True si son iguals.
///
bool Font::operator == (
	const Font& font) const {

	return *_impl == *font._impl;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'alçada del font.
/// \return   El resultat.
///
int Font::getFontHeight() const {

	return _impl->fontResource[1];
}


/// ----------------------------------------------------------------------
/// \brief Crea un font amb els parametres especificats.
/// \param fontName: Nom del font.
/// \param height: Alçada del font.
/// \param style: Estil del font.
///
const uint8_t* Font::getFontResource(
	const String& name,
	int height,
	FontStyle style) {

	const FontTableEntry *pResource = fontResourceTable;

	for (int i = 0; pResource[i].name != nullptr; i++) {
		const FontTableEntry* pEntry = &pResource[i];
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

    fi.height = _impl->fontResource[1];
    fi.ascent = _impl->fontResource[2];
    fi.descent = _impl->fontResource[3];
    fi.firstChar = _impl->fontResource[4];
    fi.lastChar = _impl->fontResource[5];
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
    ci = _impl->ciCache;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'avan� deun caracter.
/// \param ch: El caracter.
/// \return L'avan� del caracter.
///
int Font::getCharAdvance(
    char ch) const {

    updateCache(ch);
    return _impl->ciCache.advance;
}


/// ----------------------------------------------------------------------
/// \brief : Actualitza el cache amb la informacio del caracter.
/// \param ch: El caracter.
///
void Font::updateCache(
    char ch) const {

    if (_impl->chCache != ch) {
        _impl->chCache = ch;
        if ((ch >= _impl->fontResource[4]) && (ch <= _impl->fontResource[5])) {
            unsigned offset = _impl->fontResource[6] + _impl->fontResource[7] * 256u + (ch - _impl->fontResource[4]) * 2u;
            unsigned charInfoOffset = _impl->fontResource[offset] + _impl->fontResource[offset + 1] * 256u;
            unsigned charBitsOffset = _impl->fontResource[charInfoOffset + 5u] + _impl->fontResource[charInfoOffset + 6u] * 256u;

            _impl->ciCache.width = _impl->fontResource[charInfoOffset];
            _impl->ciCache.height = _impl->fontResource[charInfoOffset + 1u];
            _impl->ciCache.left = _impl->fontResource[charInfoOffset + 2u];
            _impl->ciCache.top = _impl->fontResource[charInfoOffset + 3u];
            _impl->ciCache.advance = _impl->fontResource[charInfoOffset + 4u];
            _impl->ciCache.bitmap = (charBitsOffset == (unsigned) -1) ? nullptr : &_impl->fontResource[charBitsOffset];
        }
        else {
            _impl->ciCache.width = 0;
            _impl->ciCache.height = 0;
            _impl->ciCache.left = 0;
            _impl->ciCache.top = 0;
            _impl->ciCache.advance = 0;
            _impl->ciCache.bitmap = nullptr;
        }
    }
}


