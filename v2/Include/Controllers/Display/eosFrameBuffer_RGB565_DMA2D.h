#ifndef __eosFrameBuffer_RGB565_DMA2D__
#define __eosFrameBuffer_RGB565_DMA2D__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram en format RGB565
	///
	class RGB565_DMA2D_FrameBuffer: public FrameBuffer {
		private:
			uint8_t* _buffer;
			int _lineWidth;
			int _lineBytes;
			constexpr static int _pixelBytes = sizeof(uint16_t);

		private:
			inline uint32_t getPixelAddr(int x, int y) const { return (int)_buffer + (y * _lineBytes) + (x * _pixelBytes); }

		protected:
			void put(int x, int y, const Color& color) override;
            void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int dx, int dy, int pitch) override;

		public:
			RGB565_DMA2D_FrameBuffer(int frameWidth, int frameHeight, DisplayOrientation orientation, uint8_t* buffer, int lineBytes);
	};
}


#endif // __eosFrameBuffer_RGB565_DMA2D__
