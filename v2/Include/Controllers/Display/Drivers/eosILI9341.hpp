#ifndef __EOS_CONTROLLERS_DISPLAY_DRIVERS_ILI9341_HPP
#define	__EOS_CONTROLLERS_DISPLAY_DRIVERS_ILI9341_HPP


#include "eos.hpp"
#include "Controllers/Display/eosDisplay.hpp"


namespace eos {
    
    class ILI9341_IO {
        public:
            ILI9341_IO();
            void initialize();
            void reset();
            void begin();
            void end();
            void address(uint8_t addr);
            void write(uint8_t ddata);
            inline void write(uint8_t addr, uint8_t data) { address(addr); write(data); }
            uint8_t read();
    };
    
    class ILI9341_Driver: public IDisplayDriver {
        private:
            ILI9341_IO io;
            int xScreenSize;
            int yScreenSize;
            int xClipPos;
            int yClipPos;
            int xClipSize;
            int yClipSize;
            
        public:
            ILI9341_Driver();
            void initialize();
            void shutdown();
            void setOrientation(Orientation orientation);
            void setClip(int xPos, int yPos, int xSize, int ySize);
            void resetClip();
            int getXSize() const { return xScreenSize; }
            int getYSize() const { return yScreenSize; }
            void clear(Color color);
            void setPixel(int xPos, int yPos, Color color);
            void setHPixels(int xPos, int yPos, int size, Color color);
            void setVPixels(int xPos, int yPos, int size, Color color);
            void setPixels(int xPos, int yPos, int xSize, int ySize, Color color);
            void writePixels(int xPos, int yPos, int xSize, int ySize, const Color *colors);
            void readPixels(int xPos, int yPos, int xSize, int ySize, Color *colors);
            void vScroll(int delta);
            void hScroll(int delta);   
            
        private:
            void writePixel(Color color, unsigned count);
            void writePixel(const Color *colors, unsigned count);
            void readPixel(Color *colors, unsigned count);
            void selectRegion(int x, int y, int width, int height);
            void startMemoryWrite();
            void startMemoryRead();
    };
}



#endif	

