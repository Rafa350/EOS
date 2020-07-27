#ifndef __eosFrameBuffer_RGB565_DMA2D__
#define __eosFrameBuffer_RGB565_DMA2D__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	class RGB565_DMA2D_FrameBuffer: public FrameBuffer {
		private:
			uint8_t* buffer;
			int lineWidth;
			int lineBytes;

		protected:
			void put(int x, int y, const Color& color) override;
            void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, const uint8_t* pixels, int dx, int dy, int pitch) override;

		public:
			RGB565_DMA2D_FrameBuffer(int screenWidth, int screenHeight, DisplayOrientation orientation, uint8_t* buffer, int lineBytes);
	};
}


#endif // __eosFrameBuffer_RGB565_DMA2D__
