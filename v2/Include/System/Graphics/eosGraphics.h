#ifndef __eosGraphics__
#define	__eosGraphics__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosTransformation.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

	class Bitmap;
	class String;

    /// \brief Aliniacio horitzontal del text.
    enum class HorizontalTextAlign: uint8_t {
        left,
        center,
        right
    };

    /// \brief Aliniacio vertical del text.
    enum class VerticalTextAlign: uint8_t {
        top,
        center,
        bottom
    };

    /// \brief Superficie de dibuix.
    class Graphics {
    	private:
    		struct State {
                HorizontalTextAlign hAlign;
                VerticalTextAlign vAlign;
    			int clipX1;
    			int clipY1;
    			int clipX2;
    			int clipY2;
    			Transformation ct;
    		};
    		typedef Stack<State> StateStack;

        private:
            IDisplayDriver* _driver;
            Font _font;
            StateStack _stack;
            State _state;

        public:
            Graphics(IDisplayDriver* driver);
            ~Graphics();

            inline IDisplayDriver* getDriver() const { return _driver; }
            inline int getWidth() const { return _driver->getImageWidth(); }
            inline int getHeight() const { return _driver->getImageHeight(); }
            void clear(Color color) const;

            void setFont(const Font& font);
            inline const Font& getFont() const { return _font; }
            inline Font getFont() { return _font; }

            void setClip(int x1, int y1, int x2, int y2);
            void setClip(const Rect& r) { setClip(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }
            void resetClip();

            void setTransformation(const Transformation& t, bool combine = false);
            void resetTransformation();

            void push();
            void pop();

            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            int getTextWidth(const String& text, int offset = 0, int length = -1) const;
            int getTextHeight(const String& text) const;

            void paintLine(const Pen& pen, const Point& p1, const Point& p2);
            void paintRectangle(const Pen &pen, const Brush &brush, const Rect& rect);
            void paintRoundedRectangle(const Pen &pen, const Brush &brush, const Rect& rect, int rx, int ry);
            void paintCircle(const Point& center, int radius);
            void paintEllipse(const Rect& rect);

            void drawPoint(int x, int y, Color color) const;
            inline void drawPoint(const Point& p, Color color) const { drawPoint(p.getX(), p.getY(), color); }

            void drawLine(int x1, int y1, int x2, int y2, Color color) const;
            inline void drawLine(const Point& p1, const Point& p2, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            void drawLine(int x1, int y1, int x2, int y2, int width, Color color);
            void drawHLine(int x1, int x2, int y, Color color) const;
            void drawVLine(int x, int y1, int y2, Color color) const;


            void drawRectangle(int x1, int y1, int x2, int y2, Color color) const;
            inline void drawRectangle(const Point& p1, const Point& p2, Color color) const { drawRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void drawRectangle(const Point& p, const Size& s, Color color) const { drawRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void drawRectangle(const Rect& r, Color color) const { drawRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawRoundedRectangle(int x1, int y1, int x2, int y2, int rx, int ry, Color color) const;
            inline void drawRoundedRectangle(const Point& p1, const Point& p2, int rx, int ry, Color color) const { drawRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void drawRoundedRectangle(const Point& p, const Size& s, int rx, int ry, Color color) const { drawRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void drawRoundedRectangle(const Rect& r, int rx, int ry, Color color) const { drawRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color) const;
            inline void drawTriangle(const Point& p1, const Point& p2, const Point &p3, Color color) const { drawTriangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color); }

            void drawCircle(int x, int y, int r, Color color) const;
            inline void drawCircle(const Point& p, int r, Color color) const { drawCircle(p.getX(), p.getY(), r, color); }

            void drawEllipse(int x1, int y1, int x2, int y2, Color color) const;
            inline void drawEllipse(const Rect& r, Color color) const { drawEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawBitmap(int x, int y, const Bitmap* bitmap) const;
            inline void drawBitmap(const Point& p, const Bitmap *bitmap) const { drawBitmap(p.getX(), p.getY(), bitmap); }

            int drawChar(int x, int y, Color color, char c) const;
            int drawText(int x, int y, Color color, const String& text, unsigned offset = 0, unsigned length = unsigned(-1)) const;

            void fillRectangle(int x1, int y1, int x2, int y2, Color color) const;
            inline void fillRectangle(const Point& p1, const Point& p2, Color color) const { fillRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void fillRectangle(const Point& p, const Size& s, Color color) const { fillRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void fillRectangle(const Rect& r, Color color) const { fillRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void fillRoundedRectangle(int x1, int y1, int x2, int y2, int rx, int ry, Color color) const;
            inline void fillRoundedRectangle(const Point& p1, const Point& p2, int rx, int ry, Color color) const { fillRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void fillRoundedRectangle(const Point& p, const Size& s, int rx, int ry, Color color) const { fillRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void fillRoundedRectangle(const Rect& r, int rx, int ry, Color color) const { fillRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void fillCircle(int x, int y, int r, Color color) const;
            inline void fillCircle(const Point& p, int r, Color color) const { fillCircle(p.getX(), p.getY(), r, color); }

            void fillEllipse(int x1, int y1, int x2, int y2, Color color) const;
            inline void fillEllipse(const Rect& r, Color color) const { fillEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

        private:
            bool clipPoint(int x, int y) const;
            bool clipHLine(int& x1, int& x2, int y) const;
            bool clipVLine(int x, int& y1, int& y2) const;
            bool clipLine(int& x1, int& y1, int& x2, int& y2) const;
            bool clipRectangle(int& x1, int& y1, int& x2, int& y2) const;
            static bool clipTest(int p, int q, int& t1, int& t2);
            void transform(int& x, int& y) const;
    };

}


#endif // __eosGraphics__

