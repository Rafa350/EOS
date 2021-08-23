#ifndef __eosText__
#define __eosText__


// EOS includes
//
#include "eos.h"
#include "System/eosString.h"
//#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosSize.h"


namespace eos {

	class Graphics;
	class Point;

	enum class TextAlign {
		left,
		center,
		right,
		justify
	};

	class Text {
		private:
			String _text;
			Font _font;
			Brush _background;
			Brush _foreground;
			TextAlign _align;
			int _width;
			int _height;

		private:
			void recalcBounds();
			void drawChar(const Graphics* graphics, int x, int y, Color color, char ch) const;

		public:
			Text();
			Text(const Font& font, TextAlign align);
			Text(const Font& font, TextAlign align, const String& text);

			void setText(const String& text);
			void setFont(const Font& font);
			void setAlign(TextAlign align);
			void setBackground(const Brush& background);
			void setForeground(const Brush& foreground);

			const String& getText() const { return _text; }
			const Font& getFont() const { return _font; }
			TextAlign getAlign() const { return _align; }
			const Brush& getBackground() const { return _background; }
			const Brush& getForeground() const { return _foreground; }
			Size getBounds() const { return Size(_width, _height); }

			void draw(const Graphics* graphics, const Point& position) const;
	};
}


#endif // __eosText__
