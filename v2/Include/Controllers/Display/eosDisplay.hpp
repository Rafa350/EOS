#ifndef __EOS_CONTROLLERS_DISPLAY_DISPLAY_HPP
#define	__EOS_CONTROLLERS_DISPLAY_DISPLAY_HPP


#include "eos.hpp"
#include "Controllers/Display/eosFont.hpp"


#define ARGB(a, r, g, b)     ((((uint32_t)a) << 24) | (((uint32_t)r) << 16) | (((uint32_t)g) << 8) | ((uint32_t)b))
#define RGB(r, g, b)         ARGB(255, r, g, b)


namespace eos {

    typedef uint32_t Color;
    
    enum class Orientation {
        normal,
        rotate90,
        rotate180,
        rotate270,
    };
    
    class IDisplayDriver {
        public:
            virtual void initialize() = 0;
            virtual void shutdown() = 0;
            virtual void setOrientation(Orientation orientation) = 0;
            virtual int16_t getXSize() const = 0;
            virtual int16_t getYSize() const = 0;
            virtual void clear(Color color) = 0;
            virtual void setPixel(int16_t xPos, int16_t yPos, Color color) = 0;
            virtual void setHPixels(int16_t xPos, int16_t yPos, int16_t size, Color color) = 0;
            virtual void setVPixels(int16_t xPos, int16_t yPos, int16_t size, Color color) = 0;
            virtual void setPixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, Color color) = 0;
            virtual void writePixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, const Color *colors) = 0;
            virtual void readPixels(int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize, Color *colors) = 0;
            virtual void vScroll(int16_t delta, int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize) = 0;
            virtual void hScroll(int16_t delta, int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize) = 0;
    };
    
    class Display {
        private:
            IDisplayDriver *driver;
            int16_t xClipPos;
            int16_t yClipPos;
            int16_t xClipSize;
            int16_t yClipSize;
            Color color;
            Font *font;
            FontInfo fi;
            int16_t xCursor;
            int16_t yCursor;
            uint8_t ttyState;
            
        public:
            Display(IDisplayDriver *driver);
            ~Display();
            void setClip(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void resetClip();
            Color setColor(Color color);
            Font *setFont(Font *font);
            IDisplayDriver *getDriver() const { return driver; }
            int16_t getTextWidth(const char *text);
            int16_t getTextHeight(const char *text);
            inline Font *getFont() const { return font; }
            inline Color getColor() const { return color; }
            void putTTY(char ch);
            void putTTY(const char *s);
            void putTTY(const char *s, int16_t length);
            void clear(Color color);
            void refresh();
            inline void home() { moveTo(0, 0); }
            void moveTo(int16_t x, int16_t y);
            void lineTo(int16_t x, int16_t y);
            void arcTo(int16_t x, int16_t y, int16_t cx, int16_t cy);
            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3);
            void drawCircle(int16_t cx, int16_t cy, int16_t r);
            void drawBitmap1BPP(int16_t x, int16_t y, const uint8_t *bitmap, int16_t sx, int16_t sy, Color color);
            int16_t drawChar(int16_t x, int16_t y, char c);
            int16_t drawText(int16_t x, int16_t y, const char *s, int16_t offset, int16_t length);
            void fillRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void fillCircle(int16_t cx, int16_t cy, int16_t r);    
    };
}


#endif

