#ifndef __EOS_ILI9341_HPP
#define	__EOS_ILI9341_HPP


#include "eos.hpp"
#include "Controllers/Display/eosDisplay.hpp"

#include <stdint.h>


namespace eos {

    class ILI9341_IO {
        public:
            ILI9341_IO();
            void initialize();
            void reset();
            void begin();
            void end();
            void wrCommand(uint8_t data);
            void wrData(uint8_t data);
            uint8_t rdData();
    };

    class ILI9341_Driver: public IDisplayDriver {
        private:
            ILI9341_IO io;
            int16_t screenWidth;
            int16_t screenHeight;

        public:
            ILI9341_Driver();
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
            void ctrlInitialize();
            void ctrlWriteProgram(const uint8_t *data);
            void ctrlWritePixel(Color color, int32_t count);
            void ctrlWritePixel(const Color *colors, int32_t count);
            void ctrlReadPixel(Color *colors, int32_t count);
            void ctrlDisplayOff();
            void ctrlSelectRegion(int16_t x, int16_t y, int16_t width, int16_t height);
            void ctrlStartMemoryWrite();
            void ctrlStartMemoryRead();
    };
}


#endif

