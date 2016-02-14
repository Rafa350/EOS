#include "Controllers/Display/eosFont.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param fontId: Identificador del font.
///
Font::Font(
    const uint8_t *fontResource):
    font(fontResource) {
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio del font.
/// \param fi: Destinacio de la informacio.
///
void Font::getFontInfo(
    FontInfo &fi) const {

    fi.height = font[1];
    fi.ascent = font[2];
    fi.descent = font[3];
    fi.firstChar = font[4];
    fi.lastChar = font[5];
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

    offset = font[6] + font[7] * 256 + (c - font[4]) * 2;
    offset = font[offset] + font[offset + 1] * 256;

    ci.width = font[offset];
    ci.height = font[offset + 1];
    ci.left = font[offset + 2];
    ci.top = font[offset + 3];
    ci.advance = font[offset + 4];
    
    unsigned charBitsOffset = font[offset + 5] + font[offset + 6] * 256;
    if (charBitsOffset == -1)
        ci.bitmap = nullptr;
    else
        ci.bitmap = &font[charBitsOffset];
}

