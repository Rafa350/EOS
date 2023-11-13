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
    			int16_t clipX1;
    			int16_t clipY1;
    			int16_t clipX2;
    			int16_t clipY2;
    			Transformation ct;
    		};
    		using StateStack = FixedCapacityStack<State, 10>;

        private:
            IDisplayDriver *_driver;
            StateStack _stack;
            State _state;

        public:
            Graphics(IDisplayDriver *driver);
            ~Graphics();

            inline IDisplayDriver* getDriver() const { return _driver; }
            inline int16_t getMaxX() const { return _driver->getMaxX(); }
            inline int16_t getMaxY() const { return _driver->getMaxY(); }
            void clear(Color color) const;

            void setClip(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            inline void setClip(const Rect &r) { setClip(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }
            void resetClip();

            void setTransformation(const Transformation &t, bool combine = false);
            void resetTransformation();

            void push();
            void pop();

            void paintLine(const Pen &pen, const Point &p1, const Point &p2) const;
            void paintRectangle(const Pen &pen, const Brush &brush, const Rect &box) const;
            void paintRoundedRectangle(const Pen &pen, const Brush &brush, const Rect &box, int16_t rx, int16_t ry) const;
            void paintCircle(const Pen &pen, const Brush &brush, const Point &center, int16_t radius) const;
            void paintEllipse(const Pen &pen, const Brush &brush, const Rect &box) const;
            void paintText(const Point &position, const Text &text) const;
            void paintBitmap(const Point &position, const Bitmap &bitmap) const;

            void drawPoint(int16_t x, int16_t y, Color color) const;
            inline void drawPoint(const Point &p, Color color) const { drawPoint(p.getX(), p.getY(), color); }

            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) const;
            inline void drawLine(const Point &p1, const Point &p2, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t width, Color color) const;
            inline void drawLine(const Point &p1, const Point &p2, int16_t width, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), width, color); }
            void drawHLine(int16_t x1, int16_t x2, int16_t y, Color color) const;
            void drawVLine(int16_t x, int16_t y1, int16_t y2, Color color) const;

            void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) const;
            inline void drawRectangle(const Point &p1, const Point &p2, Color color) const { drawRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void drawRectangle(const Point &p, const Size &s, Color color) const { drawRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void drawRectangle(const Rect &r, Color color) const { drawRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawRoundedRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rx, int16_t ry, Color color) const;
            inline void drawRoundedRectangle(const Point &p1, const Point &p2, int16_t rx, int16_t ry, Color color) const { drawRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void drawRoundedRectangle(const Point &p, const Size &s, int16_t rx, int16_t ry, Color color) const { drawRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void drawRoundedRectangle(const Rect &r, int16_t rx, int16_t ry, Color color) const { drawRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color) const;
            inline void drawTriangle(const Point &p1, const Point &p2, const Point &p3, Color color) const { drawTriangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color); }

            void drawCircle(int16_t x, int16_t y, int16_t r, Color color) const;
            inline void drawCircle(const Point &p, int16_t r, Color color) const { drawCircle(p.getX(), p.getY(), r, color); }

            void drawEllipse(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) const;
            inline void drawEllipse(const Rect &r, Color color) const { drawEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawPolygon(const Point *points, int16_t numPoints, Color color);

            void drawBitmap(int16_t x, int16_t y, const Bitmap &bitmap) const;
            inline void drawBitmap(const Point &p, const Bitmap &bitmap) const { drawBitmap(p.getX(), p.getY(), bitmap); }

            void fillRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) const;
            inline void fillRectangle(const Point &p1, const Point &p2, Color color) const { fillRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void fillRectangle(const Point &p, const Size &s, Color color) const { fillRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void fillRectangle(const Rect &r, Color color) const { fillRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void fillRoundedRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rx, int16_t ry, Color color) const;
            inline void fillRoundedRectangle(const Point &p1, const Point &p2, int16_t rx, int16_t ry, Color color) const { fillRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void fillRoundedRectangle(const Point &p, const Size &s, int16_t rx, int16_t ry, Color color) const { fillRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void fillRoundedRectangle(const Rect &r, int16_t rx, int16_t ry, Color color) const { fillRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void fillCircle(int16_t x, int16_t y, int16_t r, Color color) const;
            inline void fillCircle(const Point &p, int16_t r, Color color) const { fillCircle(p.getX(), p.getY(), r, color); }

            void fillEllipse(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) const;
            inline void fillEllipse(const Rect &r, Color color) const { fillEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void fillPolygon(const Point *points, int16_t numPoints, Color color);

        private:
            bool clipPoint(int16_t x, int16_t y) const;
            bool clipHLine(int16_t &x1, int16_t &x2, int16_t y) const;
            bool clipVLine(int16_t x, int16_t &y1, int16_t &y2) const;
            bool clipLine(int16_t &x1, int16_t &y1, int16_t &x2, int16_t &y2) const;
            bool clipRectangle(int16_t &x1, int16_t &y1, int16_t &x2, int16_t &y2) const;
            static bool clipTest(int16_t p, int16_t q, int32_t &t1, int32_t &t2);
            void transform(int16_t &x, int16_t &y) const;
    };

}


#endif // __eosGraphics__

