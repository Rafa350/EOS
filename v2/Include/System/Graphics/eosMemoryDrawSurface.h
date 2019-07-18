#ifndef __eosMemoryDrawSurface__
#define __eosMemoryDrawSurface__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosDrawSurface.h"


namespace eos {

        class MemoryDrawSurface: public IDrawSurface {
            private:
                uint8_t *buffer;
                int bufferWidth;
                int bufferHeight;
                int pixSize;
                PixelFormat pixFormat;
                
            public:
                MemoryDrawSurface(uint8_t *buffer, int width, int height, PixelFormat format);
                
                void setPixel(int x, int y, const Color &color) override;
                void setHPixels(int x, int y int length, const Color &color) override;
                void setVPixels(int x, int y int length, const Color &color) override;
                void setPixels(int x, int y int width, int height, const Color &color) override;
                void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
                void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
                void vScroll(int x, int y, int width, int height, int delta) override;
                void hScroll(int x, int y, int width, int height, int delta) override;
        }
}


#endif
