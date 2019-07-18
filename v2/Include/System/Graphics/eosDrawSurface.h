#ifndef __eosDrawSurface__
#define __eosDrawSurface__


#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {
    
    class IDrawSurface {
        public:
            virtual ~IDrawSurface() {}
            virtual void setPixel(int x, int y, const Color &color) = 0;
            virtual void setHPixels(int x, int y int length, const Color &color) = 0;
            virtual void setVPixels(int x, int y int length, const Color &color) = 0;
            virtual void setPixels(int x, int y int width, int height, const Color &color) = 0;
            virtual void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) = 0;
            virtual void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) = 0;
            virtual void vScroll(int x, int y, int width, int height, int delta) = 0;
            virtual void hScroll(int x, int y, int width, int height, int delta) = 0;
    }
    
}


#endif // __eosDrawSurface__