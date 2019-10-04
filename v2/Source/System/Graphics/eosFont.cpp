#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosFont.h"


extern const eos::FontTableEntry* fontResourceTable;


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param fontResource: El recurs del font.
///
Font::Font(
	const uint8_t *fontResource):

    chCache(-1),
    fontResource(fontResource) {
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
		if ((name == String(pEntry->name)) &&
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

    fi.height = fontResource[1];
    fi.ascent = fontResource[2];
    fi.descent = fontResource[3];
    fi.firstChar = fontResource[4];
    fi.lastChar = fontResource[5];
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio d'un caracter del font.
/// \param c: El caracter.
/// \param ci: Destinacio de la informacio.
///
void Font::getCharInfo(
    char ch,
    CharInfo &ci) {

    updateCache(ch);
    ci = ciCache;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'avan� deun caracter.
/// \param ch: El caracter.
/// \return L'avan� del caracter.
///
int Font::getCharAdvance(
    char ch) {

    updateCache(ch);
    return ciCache.advance;
}


/// ----------------------------------------------------------------------
/// \brief : Actualitza el cache amb la informacio del caracter.
/// \param ch: El caracter.
///
void Font::updateCache(
    char ch) {

    if (chCache != ch) {
        if ((ch >= fontResource[4]) && (ch <= fontResource[5])) {
            unsigned offset = fontResource[6] + fontResource[7] * 256u + (ch - fontResource[4]) * 2u;
            unsigned charInfoOffset = fontResource[offset] + fontResource[offset + 1] * 256u;
            unsigned charBitsOffset = fontResource[charInfoOffset + 5u] + fontResource[charInfoOffset + 6u] * 256u;
            chCache = ch;

            ciCache.width = fontResource[charInfoOffset];
            ciCache.height = fontResource[charInfoOffset + 1u];
            ciCache.left = fontResource[charInfoOffset + 2u];
            ciCache.top = fontResource[charInfoOffset + 3u];
            ciCache.advance = fontResource[charInfoOffset + 4u];
            ciCache.bitmap = (charBitsOffset == (unsigned) -1) ? nullptr : &fontResource[charBitsOffset];
        }
    }
}


