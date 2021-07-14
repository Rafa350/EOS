#include "eos.h"
#include "eosAssert.h"
#include "System/eosString.h"
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
	for (auto entry: cache) {
		if ((entry->name == name) &&
			(entry->height == height) &&
			(entry->style == style))
			font = entry->font;
	}

	// Si no el troba, crea un de nou i l'afegeix al cache.
	//
	if (font == nullptr) {
		font = new Font(name, height, style);
		CacheEntry *entry = new  CacheEntry {
			.name = name,
			.height = height,
			.style = style,
			.font = font
		};
		cache.pushBack(entry);
	}

	return font;
}


FontCache *FontCache::getInstance() {

	if (instance == nullptr)
		instance = new FontCache();
	return instance;
}
