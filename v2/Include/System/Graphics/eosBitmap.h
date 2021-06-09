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
			uint8_t *_pixels;

		public:
			Bitmap(const uint8_t *bitmapResource);
			Bitmap(int width, int height, ColorFormat format, const Color &color);
			Bitmap(int width, int height, ColorFormat format, uint8_t *pixels);
			Bitmap(int width, int height, ColorFormat format, const uint8_t *pixels);
			~Bitmap();

			void setPixel(int x, int y, const Color &color);
			Color getPixel(int x, int y);

			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }
			inline uint8_t *getPixels() const { return _pixels; }
			inline ColorFormat getFormat() const { return _format; }
			int getBytesPerPixel() const;
			int getBytesPerLine() const;
	};
}


#endif // __eosBitmap__
