#ifndef __eosColorFrameBuffer_DMA2D__
#define __eosColorFrameBuffer_DMA2D__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram en format RGB565
	///
	class ColorFrameBuffer_DMA2D: public FrameBuffer {
		private:
			typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;
			typedef CI::color_t pixel_t;

		private:
			pixel_t* _buffer;
			int _bufferPitch;

		private:
			inline pixel_t* getPixelPtr(int x, int y) const { return &_buffer[(y * _bufferPitch) + x]; }
            inline static pixel_t toPixel(Color color) { return color.convertTo<CI::format>(); }


		protected:
			void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int pitch) override;

		public:
			ColorFrameBuffer_DMA2D(int frameWidth, int frameHeight, DisplayOrientation orientation, void* buffer, int bufferPitch);
	};
}


#endif // __eosFrameBuffer_RGB565_DMA2D__
