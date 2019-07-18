#ifndef __eosDisplaySurface__
#define __eosDisplaySurface__


#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class IDisplaySurface {
        public:
    		virtual ~IDisplaySurface() {}
            virtual void setPixel(int x, int y, const Color &color) = 0;
            virtual void setHPixels(int x, int y int length, const Color &color) = 0;
            virtual void setVPixels(int x, int y int length, const Color &color) = 0;
            virtual void setPixels(int x, int y int width, int height, const Color &color) = 0;
    }

}


#endif // __eosDisplaySurface__
