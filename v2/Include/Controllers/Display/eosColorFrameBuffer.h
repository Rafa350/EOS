#pragma once
#ifndef __eosColorFrameBuffer__
#define __eosColorFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	class ColorFrameBuffer: public FrameBuffer {
		private:
			Color::Pixel * const _buffer;
			int16_t const _framePitch;
		protected:
            void put(int16_t x, int16_t y, Color color) override;
            void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

		public:
			ColorFrameBuffer(int16_t frameWidth, int16_t frameHeight, int16_t framePitch, DisplayOrientation orientation, uint8_t *buffer);
	};
}


#endif // __eosColorFrameBuffer__
