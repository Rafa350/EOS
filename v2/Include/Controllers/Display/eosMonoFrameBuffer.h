#ifndef __eosMonoFrameBuffer__
#define __eosMonoFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class MonoFrameBuffer: public FrameBuffer {
        private:
            void* _buffer;
            unsigned _bufferPitch;
		private:
			inline uint32_t getPixelAddr(int x, int y) const { return ((int)_buffer + (y * _bufferPitch) + (x >> 3)); }
            inline uint8_t getPixel(uint32_t addr, int x) const { return  *((uint8_t*)addr) & (0x80 >> (x & 0x07)); }

		protected:
            void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int offset) override;
            void write(int x, int y, int width, int height, const void* pixels, ColorFormat format, int offset) override;

        public:
            MonoFrameBuffer(int frameWidth, int frameHeight, DisplayOrientation orientation, void* buffer, int bufferPitch);
    };
}


#endif // __eosMonoFrameBuffer__
