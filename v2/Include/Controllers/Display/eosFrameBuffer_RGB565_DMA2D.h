#ifndef __eosFrameBuffer_RGB565_DMA2D__
#define __eosFrameBuffer_RGB565_DMA2D__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram en format RGB565
	///
	class FrameBuffer_RGB565_DMA2D: public FrameBuffer {
		private:
			void* _buffer;
			int _lineWidth;

		private:
			inline uint32_t getAddr() const { return (uint32_t)_buffer; }
			inline uint32_t getPixelAddr(int x, int y) const { return (int)_buffer + ((y * _lineWidth) + x) * sizeof(uint16_t); }

		protected:
			void put(int x, int y, const Color& color) override;
            void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int dx, int dy, int pitch) override;

		public:
			FrameBuffer_RGB565_DMA2D(int frameWidth, int frameHeight, DisplayOrientation orientation, void* buffer);
	};
}


#endif // __eosFrameBuffer_RGB565_DMA2D__
