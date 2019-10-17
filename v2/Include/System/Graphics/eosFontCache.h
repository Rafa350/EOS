#ifndef __eosFontCache__
#define __eosFontCache__


#include "eos.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosFont.h"


namespace eos {

	class FontCache {
		private:
		    struct CacheEntry {
		    	String name;
		    	int height;
		    	FontStyle style;
		    	Font *font;
		    };
			typedef List<CacheEntry*> Cache;

		private:
			static FontCache *instance;
			Cache cache;

		private:
			FontCache();
			FontCache(const FontCache &other) = delete;

		public:
			Font *getFont(const String &name, int height, FontStyle style);

			static FontCache* getInstance();
	};
}


#endif // _-eosFontCache__
