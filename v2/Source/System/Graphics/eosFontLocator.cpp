#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosFont.h"


using namespace eos;


#ifdef FONT_USE_Arial14pt
extern const unsigned char *fontArial14pt;
#endif
#ifdef FONT_USE_Arial18pt
extern const unsigned char *fontArial18pt;
#endif
#ifdef FONT_USE_Arial24pt
extern const unsigned char *fontArial24pt;
#endif
extern const unsigned char *fontConsolas8pt;
extern const unsigned char *fontConsolas10pt;
extern const unsigned char *fontConsolas12pt;
extern const unsigned char *fontConsolas14pt;
extern const unsigned char *fontConsolas18pt;
extern const unsigned char *fontConsolas24pt;

typedef struct {
    const char *faceName;
    int16_t height;
    FontStyle style;
    const unsigned char *resource;
} FontTableEntry;


static const FontTableEntry fontTable[] = {

#ifdef FONT_USE_Arial14pt
    { "Arial", 14, FontStyle::Regular, fontArial14pt },
#endif

#ifdef FONT_USE_Arial18pt
    { "Arial", 18, FontStyle::Regular, fontArial18pt },
#endif

#ifdef FONT_USE_Arial24pt
    { "Arial", 24, FontStyle::Regular, fontArial24pt },
#endif

#ifdef FONT_USE_Consolas8pt
    { "Consolas", 8, FontStyle::Regular, fontConsolas8pt },
#endif

#ifdef FONT_USE_Consolas10pt
    { "Consolas", 10, FontStyle::Regular, fontConsolas10pt },
#endif

#ifdef FONT_USE_Consolas12pt
    { "Consolas", 12, FontStyle::Regular, fontConsolas12pt },
#endif

#ifdef FONT_USE_Consolas14pt
    { "Consolas", 14, FontStyle::Regular, fontConsolas14pt },
#endif

#ifdef FONT_USE_Consolas18pt
    { "Consolas", 18, FontStyle::Regular, fontConsolas18pt },
#endif

#ifdef FONT_USE_Consolas24pt
    { "Consolas", 24, FontStyle::Regular, fontConsolas24pt },
#endif
};


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param resourceId: Identificador del font.
///
Font::Font(
    const uint8_t *fontResource):

    chCache(-1),
    fontResource(fontResource) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param fontName: Nom del font.
/// \param height: Al�ada del font.
/// \param style: Estil del font.
///
Font::Font(
    const String &fontName,
    int height,
    FontStyle style):

    chCache(-1),
    fontResource(nullptr) {

    for (uint16_t i = 0; i < sizeof(fontTable) / sizeof(fontTable[0]); i++) {
        const FontTableEntry *entry = &fontTable[i];
        if ((fontName.compare(entry->faceName) == 0) &&
            (height == entry->height)) {
            fontResource = entry->resource;
            break;
        }
    }
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