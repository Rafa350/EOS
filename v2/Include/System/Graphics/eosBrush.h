#ifndef __eosBrush__
#define __eosBrush__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	enum class BrushStyle {
		null,
		solid,
		linearGradient,
		radialGradient
	};

	class Brush {
		private:
			BrushStyle _style;
			Color _color;

		public:
			Brush();
			Brush(BrushStyle style, Color color);
			Brush(const Brush &brush);

			Brush& operator = (const Brush &brush);
			bool operator == (const Brush &brush) const;
			inline bool operator != (const Brush &brush) const { return !(*this == brush); }

			inline Color getColor() const { return _color; }
			inline BrushStyle getStyle() const { return _style; }

			inline bool isNull() const { return _color.isTransparent(); }
	};

}


#endif // __eosBrush__
