#ifndef __eosText__
#define __eosText__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosSize.h"
#include "System/Graphics/eosRect.h"


namespace eos {

	class Graphics;
	class Point;

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
			Font _font;
			Brush _background;
			Brush _foreground;
			HorizontalAlign _horizontalAlign;
			VerticalAlign _verticalAlign;
			int _width;
			int _height;

		private:
			void recalcBounds();
			void drawChar(const Graphics *graphics, int x, int y, Color color, char ch) const;

		public:
			Text();
			Text(const Font &font, HorizontalAlign align);
			Text(const Font &font, HorizontalAlign align, const char *text);

			void setText(const char *text);
			void setFont(const Font &font);
			void setHorizontalAlign(HorizontalAlign align);
			void setVerticalAlign(VerticalAlign align);
			void setBackground(const Brush &background);
			void setForeground(const Brush &foreground);

			const char* getText() const { return _text; }
			const Font& getFont() const { return _font; }
			HorizontalAlign getHorizontalAlign() const { return _horizontalAlign; }
			VerticalAlign getVerticalAlign() const { return _verticalAlign; }
			const Brush& getBackground() const { return _background; }
			const Brush& getForeground() const { return _foreground; }
			Size getBounds() const { return Size(_width, _height); }

			void draw(const Graphics *graphics, const Point &position) const;
			void draw(const Graphics *graphics, const Rect &box) const;
	};
}


#endif // __eosText__
