#ifndef __eosGraphics__
#define	__eosGraphics__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"
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
	class Text;

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
            IDisplayDriver* _driver;
            StateStack _stack;
            State _state;

        public:
            Graphics(IDisplayDriver* driver);
            ~Graphics();

            inline IDisplayDriver* getDriver() const { return _driver; }
            inline int getMaxX() const { return _driver->getMaxX(); }
            inline int getMaxY() const { return _driver->getMaxY(); }
            void clear(Color color) const;

            void setClip(int x1, int y1, int x2, int y2);
            inline void setClip(const Rect& r) { setClip(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }
            void resetClip();

            void setTransformation(const Transformation& t, bool combine = false);
            void resetTransformation();

            void push();
            void pop();

            void paintLine(const Pen& pen, const Point& p1, const Point& p2) const;
            void paintRectangle(const Pen& pen, const Brush& brush, const Rect& box) const;
            void paintRoundedRectangle(const Pen& pen, const Brush& brush, const Rect& box, int rx, int ry) const;
            void paintCircle(const Point& center, int radius) const;
            void paintEllipse(const Rect& box) const;
            void paintText(const Point& position, const Text& text) const;
            void paintBitmap(const Point& position, const Bitmap& bitmap) const;

            void drawPoint(int x, int y, Color color) const;
            inline void drawPoint(const Point& p, Color color) const { drawPoint(p.getX(), p.getY(), color); }

            void drawLine(int x1, int y1, int x2, int y2, Color color) const;
            inline void drawLine(const Point& p1, const Point& p2, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            void drawLine(int x1, int y1, int x2, int y2, int width, Color color) const;
            inline void drawLine(const Point& p1, const Point& p2, int width, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), width, color); }
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

            void drawPolygon(const Point* points, int numPoints, Color color);

            void drawBitmap(int x, int y, const Bitmap& bitmap) const;
            inline void drawBitmap(const Point& p, const Bitmap& bitmap) const { drawBitmap(p.getX(), p.getY(), bitmap); }

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

            void fillPolygon(const Point* points, int numPoints, Color color);

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

