#pragma once
#ifndef __eosColorFrameBuffer__
#define __eosColorFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	class ColorFrameBuffer: public FrameBuffer {
		private:
			Color::Pixel* _buffer;
			int _bufferPitch;

		protected:
            void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color *colors, int offset) override;
            void write(int x, int y, int width, int height, const void *pixels, ColorFormat format, int offset) override;

		public:
			ColorFrameBuffer(int frameWidth, int frameHeight, DisplayOrientation orientation, void *buffer, int bufferPitch);
	};
}


#endif // __eosColorFrameBuffer__
