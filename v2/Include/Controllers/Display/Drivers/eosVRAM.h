#ifndef __EOS_VRAM_H
#define	__EOS_VRAM_H


#include "eos.h"
#include "Controllers/Display/eosDisplay.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {
    
    class VRAMDriver: public IDisplayDriver {
        private:
            ColorBuffer canvas;
            int screenWidth;
            int screenHeight;
            
        public:
            VRAMDriver(int screenWidth, int screenHeight);
            ~VRAMDriver();
            void setOrientation(DisplayOrientation orientation);
            int getWidth() const { return screenWidth; }
            int getHeight() const { return screenHeight; }
            void clear(Color color);
            void setPixel(int x, int y, const Color& color);
            void setHPixels(int x, int y, int size, Color color);
            void setVPixels(int x, int y, int size, Color color);
            void setPixels(int x, int y, int width, int height, Color color);
            void writePixels(int x, int y, int width, int height, const Color *colors);
            void readPixels(int x, int y, int width, int height, Color *colors);
            void vScroll(int delta, int x, int y, int width, int height);
            void hScroll(int delta, int x, int y, int width, int height);   
            
        private:
            inline int offsetOf(int x, int y) { return x + (y * screenWidth); }
    };
}



#endif	
