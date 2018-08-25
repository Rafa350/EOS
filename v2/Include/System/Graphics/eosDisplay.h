#ifndef __eosDisplay__
#define	__eosDisplay__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"

// Standard includes
//
#include "stdint.h"


namespace eos {

	class IDisplayDriver;
	class Bitmap;
	class Font;

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

    /// \brief Control del display.
    class Display {
        private:
            IDisplayDriver *driver;
            int screenWidth;
            int screenHeight;
            bool clipEnabled;
            int clipX1;
            int clipY1;
            int clipX2;
            int clipY2;
            Color color;
            Font *font;
            HorizontalTextAlign hAlign;
            VerticalTextAlign vAlign;
            int cursorX;
            int cursorY;
            unsigned ttyState;

        public:
            Display(IDisplayDriver *driver);
            ~Display();
            void setClip(int x1, int y1, int x2, int y2);
            void resetClip();
            void setColor(const Color &color);
            void setFont(Font *font);
            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            inline IDisplayDriver *getDriver() const { return driver; }
            int getTextWidth(const char *text, int offset = 0, int length = -1);
            int getTextHeight(const char *text);
            inline Font *getFont() const { return font; }
            inline Color getColor() const { return color; }
            void putTTY(char ch);
            void putTTY(const char *s, int offset = 0, int length = -1);
            void clear(const Color &color);
            void refresh();
            inline void home() { moveTo(0, 0); }
            void moveTo(int x, int y);
            void lineTo(int x, int y);
            void arcTo(int x, int y, int cx, int cy);
            void drawPoint(int x, int y);
            void drawLine(int x1, int y1, int x2, int y2);
            void drawRectangle(int x1, int y1, int x2, int y2);
            void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
            void drawCircle(int cx, int cy, int r);
            void drawBitmap(int x, int y, const Bitmap *bitmap);
            int drawChar(int x, int y, char c);
            int drawText(int x, int y, const char *s, int offset = 0, int length = -1);
            void fillRectangle(int x1, int y1, int x2, int y2);
            void fillCircle(int cx, int cy, int r);

        private:
            bool clipArea(int &x1, int &y1, int &x2, int &y2);
            bool clipPoint(int x, int y);
            bool clipLine(int &x1, int &y1, int &x2, int &y2);
            bool clipHLine(int &x1, int &x2, int &y);
            bool clipVLine(int &x, int &y1, int &y2);
            unsigned calcOutCode(int x, int y);
    };

}


#endif // __eosDisplay__

