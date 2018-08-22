#ifndef __eosBitmap__
#define __eosBitmap__


// EOS includes
//
#include "eos.h"
#include "Controllers/Display/eosColor.h"


namespace eos {

	class Bitmap {
		private:
			int width;
			int height;
			Color *pixels;
		public:
			Bitmap(int width, int height);
			Bitmap(int width, int height, Color *pixels);
			~Bitmap();
			void setPixel(int x, int y, Color color);
			Color getPixel(int x, int y);
	};
}


#endif // __eosBitmap__
