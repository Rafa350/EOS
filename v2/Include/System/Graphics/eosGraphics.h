#ifndef __eosGraphics__
#define	__eosGraphics__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
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
            IDisplayDriver *driver;
            Color color;
            Font *font;
            StateStack stack;
            State state;

        public:
            Graphics(IDisplayDriver *driver);
            ~Graphics();

            inline IDisplayDriver *getDriver() const { return driver; }
            inline int getWidth() const { return driver->getWidth(); }
            inline int getHeight() const { return driver->getHeight(); }
            void clear(const Color &color) const;

            void setColor(const Color &color);
            inline Color getColor() const { return color; }
            void setFont(Font *font);
            inline Font *getFont() const { return font; }

            void setClip(int x1, int y1, int x2, int y2);
            void setClip(const Rect &r) { setClip(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }
            void resetClip();

            void setTransformation(const Transformation &t, bool combine = false);
            void resetTransformation();

            void push();
            void pop();

            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            int getTextWidth(const char *text, int offset = 0, int length = -1) const;
            int getTextHeight(const char *text) const;

            void drawPoint(int x, int y) const;
            inline void drawPoint(const Point &p) const { drawPoint(p.getX(), p.getY()); }

            void drawLine(int x1, int y1, int x2, int y2) const;
            inline void drawLine(const Point p1, const Point &p2) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY()); }
            void drawHLine(int x1, int x2, int y) const;
            void drawVLine(int x, int y1, int y2) const;

            void drawRectangle(int x1, int y1, int x2, int y2) const;
            inline void drawRectangle(const Point &p1, const Point &p2) const { drawRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY()); }
            inline void drawRectangle(const Point &p, const Size &s) const { drawRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1); }
            inline void drawRectangle(const Rect &r) const { drawRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }

            void drawRoundedRectangle(int x1, int y1, int x2, int y2, int rx, int ry) const;
            inline void drawRoundedRectangle(const Point &p1, const Point &p2, int rx, int ry) const { drawRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry);}
            inline void drawRoundedRectangle(const Point &p, const Size &s, int rx, int ry) const { drawRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry);}
            inline void drawRoundedRectangle(const Rect &r, int rx, int ry) const { drawRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry); }

            void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) const;
            inline void drawTriangle(const Point &p1, const Point &p2, const Point &p3) const { drawTriangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY()); }

            void drawCircle(int x, int y, int r) const;
            inline void drawCircle(const Point &p, int r) const { drawCircle(p.getX(), p.getY(), r); }

            void drawEllipse(int x1, int y1, int x2, int y2) const;
            inline void drawEllipse(const Rect &r) const { drawEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }

            void drawBitmap(int x, int y, const Bitmap *pBitmap) const;
            inline void drawBitmap(const Point &p, const Bitmap *pBitmap) const { drawBitmap(p.getX(), p.getY(), pBitmap); }

            int drawChar(int x, int y, char c) const;
            int drawText(int x, int y, const char *s, int offset = 0, int length = -1) const;

            void fillRectangle(int x1, int y1, int x2, int y2) const;
            inline void fillRectangle(const Point &p1, const Point &p2) const { fillRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY()); }
            inline void fillRectangle(const Point &p, const Size &s) const { fillRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1); }
            inline void fillRectangle(const Rect &r) const { fillRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }

            void fillRoundedRectangle(int x1, int y1, int x2, int y2, int rx, int ry) const;
            inline void fillRoundedRectangle(const Point &p1, const Point &p2, int rx, int ry) const { fillRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry);}
            inline void fillRoundedRectangle(const Point &p, const Size &s, int rx, int ry) const { fillRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry);}
            inline void fillRoundedRectangle(const Rect &r, int rx, int ry) const { fillRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry); }

            void fillCircle(int x, int y, int r) const;
            inline void fillCircle(const Point &p, int r) const { fillCircle(p.getX(), p.getY(), r); }

            void fillEllipse(int x1, int y1, int x2, int y2) const;
            inline void fillEllipse(const Rect &r) const { fillRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }

        private:
            bool clipPoint(int x, int y) const;
            bool clipHLine(int &x1, int &x2, int y) const;
            bool clipVLine(int x, int &y1, int &y2) const;
            bool clipLine(int &x1, int &y1, int &x2, int &y2) const;
            bool clipRectangle(int &x1, int &y1, int &x2, int &y2) const;
            static bool clipTest(int p, int q, int &t1, int &t2);
    };

}


#endif // __eosGraphics__

