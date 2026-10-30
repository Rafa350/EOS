export module Eos.System.Graphics.Canvas;

import Eos.Controllers.Display;
import Eos.System.Collections.Stack;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.Brush;
import Eos.System.Graphics.Font;
import Eos.System.Graphics.Pen;
import Eos.System.Graphics.Point;
import Eos.System.Graphics.Rect;
import Eos.System.Graphics.Size;
import Eos.System.Graphics.Transformation;
import Eos.System.Core.PoolAllocator;
import Eos.Types;


using namespace eos;


constexpr UInt32 maxBitmaps = 10;


export namespace eos {


    class Bitmap;
    class Text;


    /// \brief Superficie de dibuix.
    class Graphics {
    	private:
    		struct State {
    			Int16 clipX1;
    			Int16 clipY1;
    			Int16 clipX2;
    			Int16 clipY2;
    			Transformation ct;
    		};
    		using StateStack = FixedCapacityStack<State, 10>;

        private:
            DisplayDriver *_driver;
            StateStack _stack;
            State _state;

        public:
            Graphics(DisplayDriver *driver);
            ~Graphics();

            inline DisplayDriver* getDriver() const { return _driver; }
            inline Int16 getMaxX() const { return _driver->getMaxX(); }
            inline Int16 getMaxY() const { return _driver->getMaxY(); }
            void clear(Color color) const;

            void setClip(Int16 x1, Int16 y1, Int16 x2, Int16 y2);
            inline void setClip(const Rect &r) { setClip(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY()); }
            void resetClip();

            void setTransformation(const Transformation &t, bool combine = false);
            void resetTransformation();

            void push();
            void pop();

            void paintLine(const Pen &pen, const Point &p1, const Point &p2) const;
            void paintRectangle(const Pen &pen, const Brush &brush, const Rect &box) const;
            void paintRoundedRectangle(const Pen &pen, const Brush &brush, const Rect &box, Int16 rx, Int16 ry) const;
            void paintCircle(const Pen &pen, const Brush &brush, const Point &center, Int16 radius) const;
            void paintEllipse(const Pen &pen, const Brush &brush, const Rect &box) const;
            void paintText(const Point &position, const Text &text) const;
            void paintText(const Rect &box, const Text &text) const;
            void paintBitmap(const Point &position, const Bitmap &bitmap) const;

            void drawPoint(Int16 x, Int16 y, Color color) const;
            inline void drawPoint(const Point &p, Color color) const { drawPoint(p.getX(), p.getY(), color); }

            void drawLine(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Color color) const;
            inline void drawLine(const Point &p1, const Point &p2, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            void drawLine(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Int16 width, Color color) const;
            inline void drawLine(const Point &p1, const Point &p2, Int16 width, Color color) const { drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), width, color); }
            void drawHLine(Int16 x1, Int16 x2, Int16 y, Color color) const;
            void drawVLine(Int16 x, Int16 y1, Int16 y2, Color color) const;

            void drawRectangle(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Color color) const;
            inline void drawRectangle(const Point &p1, const Point &p2, Color color) const { drawRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void drawRectangle(const Point &p, const Size &s, Color color) const { drawRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void drawRectangle(const Rect &r, Color color) const { drawRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawRoundedRectangle(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Int16 rx, Int16 ry, Color color) const;
            inline void drawRoundedRectangle(const Point &p1, const Point &p2, Int16 rx, Int16 ry, Color color) const { drawRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void drawRoundedRectangle(const Point &p, const Size &s, Int16 rx, Int16 ry, Color color) const { drawRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void drawRoundedRectangle(const Rect &r, Int16 rx, Int16 ry, Color color) const { drawRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void drawTriangle(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Int16 x3, Int16 y3, Color color) const;
            inline void drawTriangle(const Point &p1, const Point &p2, const Point &p3, Color color) const { drawTriangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color); }

            void drawCircle(Int16 x, Int16 y, Int16 r, Color color) const;
            inline void drawCircle(const Point &p, Int16 r, Color color) const { drawCircle(p.getX(), p.getY(), r, color); }

            void drawEllipse(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Color color) const;
            inline void drawEllipse(const Rect &r, Color color) const { drawEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void drawPolygon(const Point *points, Int16 numPoints, Color color);

            void drawBitmap(Int16 x, Int16 y, const Bitmap &bitmap) const;
            inline void drawBitmap(const Point &p, const Bitmap &bitmap) const { drawBitmap(p.getX(), p.getY(), bitmap); }

            void fillRectangle(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Color color) const;
            inline void fillRectangle(const Point &p1, const Point &p2, Color color) const { fillRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color); }
            inline void fillRectangle(const Point &p, const Size &s, Color color) const { fillRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, color); }
            inline void fillRectangle(const Rect &r, Color color) const { fillRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void fillRoundedRectangle(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Int16 rx, Int16 ry, Color color) const;
            inline void fillRoundedRectangle(const Point &p1, const Point &p2, Int16 rx, Int16 ry, Color color) const { fillRoundedRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), rx, ry, color);}
            inline void fillRoundedRectangle(const Point &p, const Size &s, Int16 rx, Int16 ry, Color color) const { fillRoundedRectangle(p.getX(), p.getY(), p.getX() + s.getWidth() - 1, p.getY() + s.getHeight() - 1, rx, ry, color);}
            inline void fillRoundedRectangle(const Rect &r, Int16 rx, Int16 ry, Color color) const { fillRoundedRectangle(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), rx, ry, color); }

            void fillCircle(Int16 x, Int16 y, Int16 r, Color color) const;
            inline void fillCircle(const Point &p, Int16 r, Color color) const { fillCircle(p.getX(), p.getY(), r, color); }

            void fillEllipse(Int16 x1, Int16 y1, Int16 x2, Int16 y2, Color color) const;
            inline void fillEllipse(const Rect &r, Color color) const { fillEllipse(r.getMinX(), r.getMinY(), r.getMaxX(), r.getMaxY(), color); }

            void fillPolygon(const Point *points, Int16 numPoints, Color color);

        private:
            bool clipPoint(Int16 x, Int16 y) const;
            bool clipHLine(Int16 &x1, Int16 &x2, Int16 y) const;
            bool clipVLine(Int16 x, Int16 &y1, Int16 &y2) const;
            bool clipLine(Int16 &x1, Int16 &y1, Int16 &x2, Int16 &y2) const;
            bool clipRectangle(Int16 &x1, Int16 &y1, Int16 &x2, Int16 &y2) const;
            static bool clipTest(Int16 p, Int16 q, Int32 &t1, Int32 &t2);

            void transform(Int16 &x, Int16 &y) const;
    };


    class Text {
		public :
			enum class HorizontalAlign {
				left,
				center,
				right,
				justify
			};
			enum class VerticalAlign {
				top,
				middle,
				bottom,
				baseline
			};

		private:
			const char *_text;
			UInt32 _textLength;
			Font _font;
			Brush _background;
			Brush _foreground;
			HorizontalAlign _horizontalAlign;
			VerticalAlign _verticalAlign;
			Int16 _width;
			Int16 _height;

		private:
			void recalcBounds();
			void drawChar(const Graphics *graphics, Int16 x, Int16 y, Color color, char ch) const;

		public:
			Text();
			Text(const Font &font, HorizontalAlign align);
			Text(const Font &font, HorizontalAlign align, const char *text, UInt32 textLength);

			void setText(const char *text);
			void setText(const char *text, UInt32 textLength);
			void setFont(const Font &font);
			void setHorizontalAlign(HorizontalAlign align);
			void setVerticalAlign(VerticalAlign align);
			void setBackground(const Brush &background);
			void setForeground(const Brush &foreground);

			//const char* getText() const { return _text; }
			const Font& getFont() const { return _font; }
			HorizontalAlign getHorizontalAlign() const { return _horizontalAlign; }
			VerticalAlign getVerticalAlign() const { return _verticalAlign; }
			const Brush& getBackground() const { return _background; }
			const Brush& getForeground() const { return _foreground; }
			Size getBounds() const { return Size(_width, _height); }

			void draw(const Graphics *graphics, const Point &position) const;
			void draw(const Graphics *graphics, const Rect &box) const;
	};


	class Bitmap {
		private:
			struct Impl;
			typedef Impl *ImplPtr;

    	private:
    		ImplPtr _impl;

		private:
            ImplPtr makeImpl();

		public:
			Bitmap(const void* bitmapResource);
			Bitmap(Int16 width, Int16 height, ColorFormat format, Color color);
			Bitmap(Int16 width, Int16 height, ColorFormat format, void* pixels);
			Bitmap(Int16 width, Int16 height, ColorFormat format, const void* pixels);
			Bitmap(const Bitmap& bitmap);
			~Bitmap();

			Bitmap& operator = (const Bitmap& bitmap);

			void setPixel(Int16 x, Int16 y, Color color);
			inline void setPixel(const Point& point, Color color) { setPixel(point.getX(), point.getY(), color); }
			Color getPixel(Int16 x, Int16 y);
			inline Color getPixel(const Point& point) { return getPixel(point.getX(), point.getY()); }

			Int16 getWidth() const;
			Int16 getHeight() const;
			void* getPixels() const;
			ColorFormat getFormat() const;
			Int16 getBytesPerPixel() const;
			Int16 getBytesPerLine() const;

			void draw(const Graphics* graphics, const Point& position) const;
	};


	class Bitmap::Impl: public PoolAllocatable<Bitmap::Impl, maxBitmaps> {
		public:
			Int16 width;
			Int16 height;
			ColorFormat format;
			bool allocated;
			bool readonly;
			void *pixels;
	};
}
