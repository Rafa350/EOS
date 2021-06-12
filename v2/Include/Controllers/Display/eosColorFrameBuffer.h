#ifndef __eosColorFrameBuffer__
#define __eosColorFrameBuffer__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram
	///
	class ColorFrameBuffer: public FrameBuffer {

		public:
			ColorFrameBuffer(int screenWidth, int screenHeight, DisplayOrientation orientation);
			virtual ~ColorFrameBuffer() = default;

            void clear(const Color &color);
            void setPixel(int x, int y, const Color& color);
            inline void setHPixels(int x, int y, int size, const Color& color) { setPixels(x, y, size, 1, color); }
            inline void setVPixels(int x, int y, int size, const Color& color) { setPixels(x, y, 1, size, color); }
            void setPixels(int x, int y, int width, int height, const Color& color);
            void writePixels(int x, int y, int width, int height, const Color* colors, int dx, int dy, int pitch);
            /*void readPixels(int x, int y, int width, int height, uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch);
            void vScroll(int delta, int x, int y, int width, int height);
            void hScroll(int delta, int x, int y, int width, int height);*/
	};
}


#endif // __eosColorFrameBuffer__
