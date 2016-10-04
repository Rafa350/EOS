#ifndef __EOS_ILI9341_HPP
#define	__EOS_ILI9341_HPP


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
            int16_t xScreenSize;
            int16_t yScreenSize;
            
        public:
            ILI9341_Driver();
            void initialize();
            void shutdown();
            void setOrientation(Orientation orientation);
            int16_t getXSize() const { return xScreenSize; }
            int16_t getYSize() const { return yScreenSize; }
            void clear(Color color);
            void setPixel(int16_t xPos, int16_t yPos, Color color);
            void setHPixels(int16_t xPos, int16_t yPos, int16_t size, Color color);
            void setVPixels(int16_t xPos, int16_t yPos, int16_t size, Color color);
            void setPixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, Color color);
            void writePixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, const Color *colors);
            void readPixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, Color *colors);
            void vScroll(int16_t delta, int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize);
            void hScroll(int16_t delta, int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize);   
            
        private:
            void writePixel(Color color, int32_t count);
            void writePixel(const Color *colors, int32_t count);
            void readPixel(Color *colors, int32_t count);
            void selectRegion(int16_t x, int16_t y, int16_t width, int16_t height);
            void startMemoryWrite();
            void startMemoryRead();
    };
}



#endif	

