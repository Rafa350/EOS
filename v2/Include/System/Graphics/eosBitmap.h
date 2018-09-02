#ifndef __eosBitmap__
#define __eosBitmap__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"

// Standard includes
//
#include "stdint.h"


namespace eos {

	class Bitmap {
		private:
			int width;
			int height;
			PixelFormat format;
			bool allocated;
			bool readonly;
			uint8_t *pixels;

		public:
			Bitmap(int width, int height, PixelFormat format, const Color &color);
			Bitmap(int width, int height, PixelFormat format, uint8_t *pixels);
			Bitmap(int width, int height, PixelFormat format, const uint8_t *pixels);
			~Bitmap();

			void setPixel(int x, int y, Color color);
			Color getPixel(int x, int y);

			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline uint8_t *getPixels() const { return pixels; }
			inline PixelFormat getFormat() const { return format; }
	};
}


#endif // __eosBitmap__
