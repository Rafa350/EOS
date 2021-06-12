#ifndef __eosFrameBuffer_RGB565__
#define __eosFrameBuffer_RGB565__


#include "eos.h"
#include "Controllers/Display/eosColorFrameBuffer.h"


namespace eos {

	class RGB565_FrameBuffer: public ColorFrameBufferBase {
		private:
			uint8_t* _buffer;
			int _lineBytes;

		protected:
        	void put(int x, int y, const Color& color) override;
        	void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, int dx, int dy) override;

		public:
			RGB565_FrameBuffer(int screenWidth, int screenHeight, DisplayOrientation orientation, uint8_t* buffer, int lineBytes);

            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) = 0;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
	};
}


#endif // __eosFrameBuffer_RGB565__
