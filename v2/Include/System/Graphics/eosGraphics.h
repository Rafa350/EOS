#ifndef __eosGraphics__
#define	__eosGraphics__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosTransformation.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

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

    /// \brief Superficie de dibuix.
    class Graphics {
    	private:
    		struct State {
    			int clipX1;
    			int clipY1;
    			int clipX2;
    			int clipY2;
    			Transformation ct;
    		};
    		typedef Stack<State> StateStack;

        private:
            IDisplayDriver *driver;
            Color color;
            Font *font;
            HorizontalTextAlign hAlign;
            VerticalTextAlign vAlign;
            StateStack stack;
            State state;

        public:
            Graphics(IDisplayDriver *driver);
            ~Graphics();
            void setColor(const Color &color);
            void setFont(Font *font);
            void setClip(int x1, int y1, int x2, int y2);
            void resetClip();
            void setTransformation(const Transformation &t, bool combine = false);
            void resetTransformation();
            void push();
            void pop();
            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            inline IDisplayDriver *getDriver() const { return driver; }
            int getTextWidth(const char *text, int offset = 0, int length = -1) const;
            int getTextHeight(const char *text) const;
            inline Font *getFont() const { return font; }
            inline Color getColor() const { return color; }
            inline int getWidth() const { return driver->getWidth(); }
            inline int getHeight() const { return driver->getHeight(); }
            void clear(const Color &color) const;
            void refresh() const;
            void drawPoint(int x, int y) const;
            void drawLine(int x1, int y1, int x2, int y2) const;
            void drawRectangle(int x1, int y1, int x2, int y2) const;
            void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) const;
            void drawCircle(int cx, int cy, int r) const;
            void drawBitmap(int x, int y, const Bitmap *bitmap) const;
            int drawChar(int x, int y, char c) const;
            int drawText(int x, int y, const char *s, int offset = 0, int length = -1) const;
            void fillRectangle(int x1, int y1, int x2, int y2) const;
            void fillCircle(int cx, int cy, int r) const;

        private:
            bool clipArea(int &x1, int &y1, int &x2, int &y2) const;
            bool clipPoint(int x, int y) const;
            bool clipHLine(int &x1, int &x2, int y) const;
            bool clipLine(int &x1, int &y1, int &x2, int &y2) const;
            static bool clipTest(int p, int q, int &t1, int &t2);
    };

}


#endif // __eosGraphics__

