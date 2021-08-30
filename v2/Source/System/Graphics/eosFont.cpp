#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
#include "System/Core/eosPoolAllocator.h"
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


#ifdef EOS_DEBUG
static int __allocatedFontCount = 0;
static int __allocatedFontImplCount = 0;
#endif


class Font::Impl: public PoolAllocatable<Font::Impl, eosGraphics_MaxFonts> {
	private:
    	const uint8_t* _fontResource;

	public:
    	Impl(const uint8_t* fontResource):
    		_fontResource(fontResource) {
#ifdef EOS_DEBUG
			__allocatedFontImplCount++;
#endif
    	}

    	~Impl() {
#ifdef EOS_DEBUG
			__allocatedFontImplCount--;
#endif
    	}

    	bool operator == (const Impl& other) const {
    		return _fontResource == other._fontResource;
    	}

    	inline bool operator != (const Impl& other) const {
    		return !(*this == other);
    	}

    	inline const uint8_t* getFontResource() const {
    		return _fontResource;
    	}
};


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea el font per defecte.
///
Font::Font() :
	_impl(makeImpl(getFontResource(eosGraphics_DefFontName, eosGraphics_DefFontHeight, eosGraphics_DefFontStyle))) {

#ifdef EOS_DEBUG
	__allocatedFontCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    name: Nom del font
/// \param    height: Alçada de la lletra.
/// \param    style: Estil.
///
Font::Font(
	const String& name,
	int height,
	FontStyle style):

	_impl(makeImpl(getFontResource(name, height, style))) {

#ifdef EOS_DEBUG
	__allocatedFontCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia
/// \param    font: L'altre objecte per copiar.
///
Font::Font(
	const Font& font):

	_impl(font._impl) {

#ifdef EOS_DEBUG
	__allocatedFontCount++;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Destructor
///
Font::~Font() {

#ifdef EOS_DEBUG
	__allocatedFontCount--;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Crea el bloc de memoria de Impl
/// \return   El punter al bloc.
///
Font::ImplPtr Font::makeImpl(
	const uint8_t* fontResource) {

	auto& cache = ImplPtrCache::instance();

	eosAssert(fontResource != nullptr);

	// Si ja esta en el cache, el reutilitza.
	//
	for (auto it = cache.begin(); it != cache.end(); it++) {
		ImplPtr impl = *it;
		if (impl->getFontResource() == fontResource)
			return impl;
	}

	ImplPtr impl(new Font::Impl(fontResource));
	cache.pushBack(impl);
	return impl;
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

	const uint8_t* fr = _impl->getFontResource();
	return fr[FR_FONT_HEIGHT];
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'ascendent del font.
/// \return   El resultat.
///
int Font::getFontAscent() const {

	const uint8_t* fr = _impl->getFontResource();
	return fr[FR_FONT_ASCENT];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el descendent del font.
/// \return   El resultat.
///
int Font::getFontDescent() const {

	const uint8_t* fr = _impl->getFontResource();
	return fr[FR_FONT_DESCENT];
}


/// ----------------------------------------------------------------------
/// \brief Obte informacio del font
/// \param fi: Destinacio de la informacio.
///
void Font::getFontInfo(
    FontInfo& fi) const {

	const uint8_t* fr = _impl->getFontResource();

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

    const uint8_t* fr = _impl->getFontResource();

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

	const uint8_t* fr = _impl->getFontResource();

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
extern const FontTableEntry* fontResourceTable;
const uint8_t* Font::getFontResource(
	const String& name,
	int height,
	FontStyle style) {

	const FontTableEntry* pResource = fontResourceTable;

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
