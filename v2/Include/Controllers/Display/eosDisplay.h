#ifndef __EOS_DISPLAY_H
#define	__EOS_DISPLAY_H


#define DISPLAY_PIXFORMAT_565


#include "eos.h"
#include "Controllers/Display/eosFont.h"
#include "Controllers/Display/eosColor.h"

#include <stdint.h>


namespace eos {

    /// \brief Orientacio de la pantalla.
    enum class Orientation {
        normal,
        rotate90,
        rotate180,
        rotate270,
    };
    
    /// \brief Aliniacio horitzontal del text.
    enum class HorizontalTextAlign {
        left,
        center,
        right
    };
    
    /// \brief Aliniacio vertical del text.
    enum class VerticalTextAlign {
        top,
        middle,
        bottom
    };
    
    /// \brief Interficie del driver del display.
    class IDisplayDriver {
        public:
            virtual void initialize() = 0;
            virtual void shutdown() = 0;
            virtual void setOrientation(Orientation orientation) = 0;
            virtual int16_t getWidth() const = 0;
            virtual int16_t getHeight() const = 0;
            virtual void clear(Color color) = 0;
            virtual void setPixel(int16_t x, int16_t y, Color color) = 0;
            virtual void setHPixels(int16_t x, int16_t y, int16_t length, Color color) = 0;
            virtual void setVPixels(int16_t x, int16_t y, int16_t length, Color color) = 0;
            virtual void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) = 0;
            virtual void writePixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors) = 0;
            virtual void readPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color *colors) = 0;
            virtual void vScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height) = 0;
            virtual void hScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height) = 0;
    };

    /// \brief Control del display.
    class Display {
        private:
            IDisplayDriver *driver;
            int16_t screenWidth;
            int16_t screenHeight;
            bool clipEnabled;
            int16_t clipX1;
            int16_t clipY1;
            int16_t clipX2;
            int16_t clipY2;
            Color color;
            Font *font;
            HorizontalTextAlign hAlign;
            VerticalTextAlign vAlign;
            int16_t cursorX;
            int16_t cursorY;
            uint8_t ttyState;

        public:
            Display(IDisplayDriver *driver);
            ~Display();
            void setClip(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void resetClip();
            void setColor(Color color);
            void setFont(Font *font);
            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            inline IDisplayDriver *getDriver() const { return driver; }
            int16_t getTextWidth(const char *text, int16_t offset = 0, int16_t length = -1);
            int16_t getTextHeight(const char *text);
            inline Font *getFont() const { return font; }
            inline Color getColor() const { return color; }
            void putTTY(char ch);
            void putTTY(const char *s, int16_t offset = 0, int16_t length = -1);
            void clear(Color color);
            void refresh();
            inline void home() { moveTo(0, 0); }
            void moveTo(int16_t x, int16_t y);
            void lineTo(int16_t x, int16_t y);
            void arcTo(int16_t x, int16_t y, int16_t cx, int16_t cy);
            void drawPoint(int16_t x, int16_t y);
            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3);
            void drawCircle(int16_t cx, int16_t cy, int16_t r);
            void drawBitmap1BPP(int16_t x, int16_t y, const uint8_t *bitmap, int16_t width, int16_t height, Color color);
            int16_t drawChar(int16_t x, int16_t y, char c);
            int16_t drawText(int16_t x, int16_t y, const char *s, int16_t offset = 0, int16_t length = -1);
            void fillRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void fillCircle(int16_t cx, int16_t cy, int16_t r);

        private:
            bool clipArea(int16_t &x1, int16_t &y1, int16_t &x2, int16_t &y2);
            bool clipPoint(int16_t x, int16_t y);
            bool clipLine(int16_t &x1, int16_t &y1, int16_t &x2, int16_t &y2);
            bool clipHLine(int16_t &x1, int16_t &x2, int16_t &y);
            bool clipVLine(int16_t &x, int16_t &y1, int16_t &y2);
            uint8_t calcOutCode(int16_t x, int16_t y);
    };

}


#endif

