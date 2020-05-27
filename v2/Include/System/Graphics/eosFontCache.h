#ifndef __eosFontCache__
#define __eosFontCache__


#include "eos.h"
#include "System/eosString.h"
#include "System/Collections/eosDynamicArray.h"
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
			typedef DynamicArray<CacheEntry*, 10> Cache;

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
