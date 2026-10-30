module;

#include <string.h>


export module Eos.System.Graphics.Font;

import Eos.Types;


export namespace eos {

    enum class FontStyle: UInt8 {
        regular,
        bold,
        italic,
        boldItalic
    };

    struct FontInfo {             // Informacio del font
        Int16 height;             // -Alçada
        Int16 ascent;             // -Ascendent
        Int16 descent;            // -Descendent
        char firstChar;           // -Primer caracter definit en el font
        char lastChar;            // -Ultim caracter definit en el font
    };

    struct CharInfo {             // Informacio del caracter
        Int16 width;              // -Amplada del bitmap
        Int16 height;             // -Alçada del bitmap
        Int16 left;               // -Offset horitzontal del bitmap
        Int16 top;                // -Offset vertical del bitmap
        Int16 advance;            // -Offset fins al origen del seguent bitmap
        const UInt8 *bitmap;      // -Punter al primer byte del caracter
    };

    class Font final {
        private:
            struct FontTableEntry {       // Entrada de la taula de fonts
                const char *name;         // -Nom del font
                Int16 height;           // -Alçada
                FontStyle style;          // -Estil
                const UInt8 *resource;  // -Taula d'informacio del font
            };

        private:
            static const FontTableEntry _fontTable[];
            const UInt8 * _fontResource;

        private:
            static const UInt8* getFontResource(const char *name, Int16 height, FontStyle style);

        public:
            Font();
            Font(const char *name, Int16 height, FontStyle style);
            Font(const Font &font);

            Font& operator = (const Font &font);

            bool operator == (const Font &font) const;

            void getFontInfo(FontInfo &fi) const;
            void getCharInfo(char ch, CharInfo &ci) const;
            Int16 getFontHeight() const;
            Int16 getFontAscent() const;
            Int16 getFontDescent() const;
            Int16 getCharAdvance(char ch) const;
    };
}

namespace eos {

    struct FontTableEntry {       // Entrada de la taula de fonts
        const char *name;         // -Nom del font
        Int16 height;             // -Alçada
        FontStyle style;          // -Estil
        const UInt8 *resource;    // -Taula d'informacio del font
    };
}

#define FONT_USE_5x7practical12pt
#define eosGraphics_DefFontName "5x7practical12pt"
#define eosGraphics_DefFontHeight 12
#define eosGraphics_DefFontStyle FontStyle::regular
#define eosGraphics_DefFontResource font5x7practical12pt

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


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor. Crea el font per defecte.
///
Font::Font() :

	_fontResource {getFontResource(eosGraphics_DefFontName, eosGraphics_DefFontHeight, eosGraphics_DefFontStyle)} {
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    name: Nom del font
/// @param    height: Alçada de la lletra.
/// @param    style: Estil.
///
Font::Font(
	const char *name,
	Int16 height,
	FontStyle style):

	_fontResource {getFontResource(name, height, style)} {

}


/// ---------------------------------------------------------------------------
/// @brief    Constructor copia
/// @param    font: L'altre objecte per copiar.
///
Font::Font(
	const Font &font):

	_fontResource {font._fontResource} {

}


/// ---------------------------------------------------------------------------
/// @brief    Operador d'assignacio.
/// @param    font: L'objecte a asignar.
/// @return   El propi objecte.
///
Font& eos::Font::operator = (
	const Font &font) {

	_fontResource = font._fontResource;

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief    Operador ==.
/// @param    font: L'altre font a comparar.
/// @return   True si son iguals.
///
bool Font::operator == (
	const Font &font) const {

	return _fontResource == font._fontResource;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'alçada del font.
/// @return   El resultat.
///
Int16 Font::getFontHeight() const {

	const UInt8* fr = _fontResource;
	return fr[FR_FONT_HEIGHT];
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'ascendent del font.
/// @return   El resultat.
///
Int16 Font::getFontAscent() const {

	const UInt8* fr = _fontResource;
	return fr[FR_FONT_ASCENT];
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el descendent del font.
/// @return   El resultat.
///
Int16 Font::getFontDescent() const {

	const UInt8* fr = _fontResource;
	return fr[FR_FONT_DESCENT];
}


/// ---------------------------------------------------------------------------
/// @brief Obte informacio del font
/// @param fi: Destinacio de la informacio.
///
void Font::getFontInfo(
    FontInfo &fi) const {

	const UInt8 *fr = _fontResource;

	fi.height = fr[FR_FONT_HEIGHT];
    fi.ascent = fr[FR_FONT_ASCENT];
    fi.descent = fr[FR_FONT_DESCENT];
    fi.firstChar = fr[FR_FONT_FIRST];
    fi.lastChar = fr[FR_FONT_LAST];
}


/// ---------------------------------------------------------------------------
/// @brief Obte informacio d'un caracter del font.
/// @param c: El caracter.
/// @param ci: Destinacio de la informacio.
///
void Font::getCharInfo(
    char ch,
    CharInfo &ci) const {

    const UInt8 *fr = _fontResource;

    if ((ch >= fr[FR_FONT_FIRST]) && (ch <= fr[FR_FONT_LAST])) {
        Int16 offset = fr[6] + fr[7] * 256 + (ch - fr[4]) * 2;
        Int16 charInfoOffset = fr[offset] + fr[offset + 1] * 256;
        Int16 charBitsOffset = fr[charInfoOffset + 5] + fr[charInfoOffset + 6] * 256;

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


/// ---------------------------------------------------------------------------
/// @brief Obte l'avanç d,un caracter.
/// @param ch: El caracter.
/// @return L'avanç del caracter.
///
Int16 Font::getCharAdvance(
    char ch) const {

	const UInt8 *fr = _fontResource;

    if ((ch >= fr[FR_FONT_FIRST]) && (ch <= fr[FR_FONT_LAST])) {
		Int16 offset = fr[6] + fr[7] * 256 + (ch - fr[4]) * 2;
		Int16 charInfoOffset = fr[offset] + fr[offset + 1] * 256;
		return fr[charInfoOffset + FR_CHAR_ADVANCE];
    }
    else
    	return 0;
}


#ifdef FONT_USE_Arial14pt
    const unsigned char *fontArial14pt;
#endif
#ifdef FONT_USE_Arial18pt
    const unsigned char *fontArial18pt;
#endif
#ifdef FONT_USE_Arial24pt
    const unsigned char *fontArial24pt;
#endif
#ifdef FONT_USE_Consolas8pt
    const unsigned char *fontConsolas8pt;
#endif
#ifdef FONT_USE_Consolas10pt
    const unsigned char *fontConsolas10pt;
#endif
#ifdef FONT_USE_Consolas12pt
    const unsigned char *fontConsolas12pt;
#endif
#ifdef FONT_USE_Consolas14pt
    const unsigned char *fontConsolas14pt;
#endif
#ifdef FONT_USE_Consolas18pt
    const unsigned char *fontConsolas18pt;
#endif
#ifdef FONT_USE_Consolas24pt
    const unsigned char *fontConsolas24pt;
#endif
#ifdef FONT_USE_Tahoma10pt
    const unsigned char *fontTahoma10pt;
#endif
#ifdef FONT_USE_Tahoma12pt
    const unsigned char *fontTahoma12pt;
#endif
#ifdef FONT_USE_5x7practical12pt
    extern "C++" const unsigned char *font5x7practical12pt;
#endif
#ifdef FONT_USE_MicrosoftSansSerif18pt
    const unsigned char *fontMicrosoftSansSerif18pt;
#endif


const Font::FontTableEntry Font::_fontTable[] = {

	// Primer sempre el font per defecte
	{ eosGraphics_DefFontName, eosGraphics_DefFontHeight, eosGraphics_DefFontStyle, eosGraphics_DefFontResource },

#ifdef FONT_USE_Arial14pt
    { "Arial", 14, FontStyle::regular, fontArial14pt },
#endif

#ifdef FONT_USE_Arial18pt
    { "Arial", 18, FontStyle::regular, fontArial18pt },
#endif

#ifdef FONT_USE_Arial24pt
    { "Arial", 24, FontStyle::regular, fontArial24pt },
#endif

#ifdef FONT_USE_Consolas8pt
    { "Consolas", 8, FontStyle::regular, fontConsolas8pt },
#endif

#ifdef FONT_USE_Consolas10pt
    { "Consolas", 10, FontStyle::regular, fontConsolas10pt },
#endif

#ifdef FONT_USE_Consolas12pt
    { "Consolas", 12, FontStyle::regular, fontConsolas12pt },
#endif

#ifdef FONT_USE_Consolas14pt
    { "Consolas", 14, FontStyle::regular, fontConsolas14pt },
#endif

#ifdef FONT_USE_Consolas18pt
    { "Consolas", 18, FontStyle::regular, fontConsolas18pt },
#endif

#ifdef FONT_USE_Consolas24pt
    { "Consolas", 24, FontStyle::regular, fontConsolas24pt },
#endif

#ifdef FONT_USE_Tahoma10pt
    { "Tahoma", 10, FontStyle::regular, fontTahoma10pt },
#endif

#ifdef FONT_USE_Tahoma12pt
    { "Tahoma", 12, FontStyle::regular, fontTahoma12pt },
#endif

#ifdef FONT_USE_5x7practical12pt
    { "5x7practical", 12, FontStyle::regular, font5x7practical12pt },
#endif

#ifdef FONT_USE_MicrosoftSansSerif18pt
    { "MicrosoftSansSerif", 18, FontStyle::regular, fontMicrosoftSansSerif18pt },
#endif

	// Marca de final de taula
	{ nullptr, 0, FontStyle::regular, nullptr }
};


/// ----------------------------------------------------------------------
/// @brief Crea un font amb els parametres especificats.
/// @param fontName: Nom del font.
/// @param height: Alçada del font.
/// @param style: Estil del font.
///
const UInt8* Font::getFontResource(
	const char *name,
	Int16 height,
	FontStyle style) {

	const FontTableEntry *pResource = _fontTable;

	for (Int16 i = 0; pResource[i].name != nullptr; i++) {
		const FontTableEntry *pEntry = &pResource[i];
		if ((strcmp(name, pEntry->name) == 0) &&
			(pEntry->height == height) &&
			(pEntry->style == style)) {

			return pEntry->resource;
		}
	}

	return nullptr;
}
