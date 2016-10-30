#include "Controllers/Display/eosFont.hpp"
#include <string.h>


using namespace eos;


extern const unsigned char *fontArial14pt;
extern const unsigned char *fontArial18pt;
extern const unsigned char *fontArial24pt;
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


static FontTableEntry fontTable[] = {
    
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
    const uint8_t *_fontResource):
    
    fontResource(_fontResource) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param fontName: Nom del font.
/// \param height: Alçada del font.
/// \param style: Estil del font.
///
Font::Font(
    const char* fontName, 
    int16_t height, 
    FontStyle style):
    fontResource(nullptr) {
    
    for (uint16_t i = 0; i < sizeof(fontTable) / sizeof(fontTable[0]); i++) {
        FontTableEntry *entry = &fontTable[i];
        if ((strcmp(fontName, entry->faceName) == 0) &&
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
    char c, 
    CharInfo &ci) const {

    unsigned offset = fontResource[6] + fontResource[7] * 256 + (c - fontResource[4]) * 2;
    unsigned charInfoOffset = fontResource[offset] + fontResource[offset + 1] * 256;
    unsigned charBitsOffset = fontResource[charInfoOffset + 5] + fontResource[charInfoOffset + 6] * 256;

    ci.width = fontResource[charInfoOffset];
    ci.height = fontResource[charInfoOffset + 1];
    ci.left = fontResource[charInfoOffset + 2];
    ci.top = fontResource[charInfoOffset + 3];
    ci.advance = fontResource[charInfoOffset + 4];
    ci.bitmap = (charBitsOffset == (unsigned) -1) ? nullptr : &fontResource[charBitsOffset];
}

