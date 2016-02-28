#include "Controllers/Display/eosFont.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param resourceId: Identificador del font.
///
Font::Font(
    const uint8_t *_fontResource):
    fontResource(_fontResource) {
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

    unsigned offset;

    offset = fontResource[6] + fontResource[7] * 256 + (c - fontResource[4]) * 2;
    offset = fontResource[offset] + fontResource[offset + 1] * 256;

    ci.width = fontResource[offset];
    ci.height = fontResource[offset + 1];
    ci.left = fontResource[offset + 2];
    ci.top = fontResource[offset + 3];
    ci.advance = fontResource[offset + 4];
    
    unsigned charBitsOffset = fontResource[offset + 5] + fontResource[offset + 6] * 256;
    if (charBitsOffset == -1)
        ci.bitmap = nullptr;
    else
        ci.bitmap = &fontResource[charBitsOffset];
}

