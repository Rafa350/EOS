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
			bool allocated;
			Color *pixels;

		public:
			Bitmap(int width, int height);
			Bitmap(int width, int height, const Color &color);
			Bitmap(int width, int height, Color *pixels);
			~Bitmap();

			void setPixel(int x, int y, Color color);
			Color getPixel(int x, int y);

			int getWidth() const { return width; }
			int getHeight() const { return height; }
			Color *getPixels() const { return pixels; }
	};
}


#endif // __eosBitmap__
