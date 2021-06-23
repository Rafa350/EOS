#ifndef __eosMonoFrameBuffer__
#define __eosMonoFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class MonoFrameBuffer: public FrameBuffer {
        private:
            uint8_t* _buffer;
            unsigned _lineBytes;
		private:
			inline uint32_t getPixelAddr(int x, int y) const { return (int)_buffer + (y * _lineBytes) + (x >> 3); }
            inline uint8_t getPixel(uint32_t addr, int x) const { return  *((uint8_t*)addr) & (0x80 >> (x & 0x07)); }

		protected:
			void put(int x, int y, const Color& color) override;
            void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int dx, int dy, int pitch) override;
    };
}


#endif // __eosMonoFrameBuffer__
