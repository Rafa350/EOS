#ifndef __eosPen__
#define __eosPen__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	enum class PenStyle {
		null,
		solid
	};

	enum class PenCapStyle {

	};

	enum class PenJoinStyle {

	};

	class Pen final {
		private:
			PenStyle _style;
			Color _color;
			int16_t _thickness;

		public:
			Pen();
			Pen(Color color, int thickness);
			Pen(const Pen &pen);

			Pen& operator = (const Pen &pen);
			bool operator == (const Pen &pen) const;
			inline bool operator != (const Pen &pen) const { return !(*this == pen); }

			inline Color getColor() const { return _color; }
			inline int16_t getThickness() const { return _thickness; }
			inline PenStyle getStyle() const { return _style; }

			inline bool isNull() const { return _style == PenStyle::null; }
	};
}


#endif // __eosPen__
