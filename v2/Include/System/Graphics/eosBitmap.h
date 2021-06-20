#ifndef __eosBitmap__
#define __eosBitmap__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class Bitmap {
		private:
			int _width;
			int _height;
			ColorFormat _format;
			bool _allocated;
			bool _readonly;
			void *_pixels;

		public:
			Bitmap(const uint8_t *bitmapResource);
			Bitmap(int width, int height, ColorFormat format, Color color);
			Bitmap(int width, int height, ColorFormat format, void *pixels);
			Bitmap(int width, int height, ColorFormat format, const void *pixels);
			~Bitmap();

			void setPixel(int x, int y, const Color &color);
			Color getPixel(int x, int y);

			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }
			inline void *getPixels() const { return _pixels; }
			inline ColorFormat getFormat() const { return _format; }
			int getBytesPerPixel() const;
			int getBytesPerLine() const;
	};
}


#endif // __eosBitmap__
