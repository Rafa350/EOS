#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosFontCache.h"


using namespace eos;


FontCache* FontCache::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
FontCache::FontCache() {

}


/// ----------------------------------------------------------------------
/// \brief Obte un objece, si no en troba en el cache, el crea de nou.
/// \param name: Nom.
/// \param height: Alçada.
/// \param style: Estil.
/// \return L'objecte font.
///
Font *FontCache::getFont(
	const String &name,
	int height,
	FontStyle style) {

	Font *font = nullptr;

	// Busca el font en el cache.
	//
	for (CacheIterator it(cache); it.hasNext() && (font == nullptr); it.next()) {
		const CacheEntry &entry = it.current();
		if ((entry.name == name) &&
			(entry.height == height) &&
			(entry.style == style))
			font = entry.font;
	}

	// Si no el troba, crea un de nou i l'afegeix al cache.
	//
	if (font == nullptr) {
		const uint8_t * fontResource = Font::getFontResource(name, height, style);
		font = new Font(fontResource);
		CacheEntry entry = {
			.name = name,
			.height = height,
			.style = style,
			.font = font
		};
		cache.add(entry);
	}

	return font;
}


FontCache *FontCache::getInstance() {

	if (instance == nullptr)
		instance = new FontCache();
	return instance;
}
