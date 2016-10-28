#ifndef __EOS_VDC_HPP
#define	__EOS_VDC_HPP


#include "eos.hpp"
#include "Controllers/Display/eosDisplay.hpp"


namespace eos {
    
    typedef Pixel565 VDC_Pixel;
    
    class VDC_Driver: public IDisplayDriver {
        private:
            VDC_Pixel *canvas;
            int16_t screenWidth;
            int16_t screenHeight;
            
        public:
            VDC_Driver(int16_t screenWidth, int16_t screenHeight);
            ~VDC_Driver();
            void initialize();
            void shutdown();
            void setOrientation(Orientation orientation);
            int16_t getWidth() const { return screenWidth; }
            int16_t getHeight() const { return screenHeight; }
            void clear(Color color);
            void setPixel(int16_t x, int16_t y, Color color);
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color);
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color);
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color);
            void writePixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors);
            void readPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color *colors);
            void vScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height);
            void hScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height);   
            
        private:
            inline int offsetOf(int16_t x, int16_t y) { return x + (y * screenWidth); }
    };
}



#endif	
