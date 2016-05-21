#ifndef __EOS_CONTROLLERS_DISPLAY_DISPLAY_HPP
#define	__EOS_CONTROLLERS_DISPLAY_DISPLAY_HPP


#include "eos.hpp"
#include "Controllers/Display/eosFont.hpp"


#define RGB(r, g, b)       (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))
#define ARGB(a, r, g, b)   (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))


namespace eos {

    typedef unsigned Color;
    
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
            virtual int getXSize() const = 0;
            virtual int getYSize() const = 0;
            virtual void clear(Color color) = 0;
            virtual void setPixel(int xPos, int yPos, Color color) = 0;
            virtual void setHPixels(int xPos, int yPos, int size, Color color) = 0;
            virtual void setVPixels(int xPos, int yPos, int size, Color color) = 0;
            virtual void setPixels(int xPos, int yPos, int xSize, int ySize, Color color) = 0;
    };
    
    class Display {
        private:
            IDisplayDriver *driver;
            Color color;
            Font *font;
            FontInfo fontInfo;
            int xCursor;
            int yCursor;
            int ttyState;
            
        public:
            Display(IDisplayDriver *driver);
            ~Display();
            void setColor(Color color);
            void setFont(Font *font);
            IDisplayDriver *getDriver() const { return driver; }
            int getTextWidth(const char *text);
            int getTextHeight(const char *text);
            void putTTY(char ch);
            void putTTY(const char *s);
            void putTTY(const char *s, int length);
            void clear(Color color);
            void refresh();
            inline void home() { moveTo(0, 0); }
            void moveTo(int x, int y);
            void lineTo(int x, int y);
            void arcTo(int x, int y, int cx, int cy);
            void drawLine(int x1, int y1, int x2, int y2);
            void drawRectangle(int x1, int y1, int x2, int y2);
            void drawCircle(int cx, int cy, int r);
            void drawBitmap1BPP(int x, int y, const uint8_t *bitmap, int sx, int sy, Color color);
            int drawChar(int x, int y, char c);
            int drawString(int x, int y, const char *s, int offset, int length);
            void fillRectangle(int x1, int y1, int x2, int y2);
            void fillCircle(int cx, int cy, int r);    
    };
}


#endif

