#pragma once


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class Pen final {
		public:
			enum class Style {
				null,
				solid
			};

			enum class CapStyle {

			};

			enum class JoinStyle {

			};

		private:
			Style _style;
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
			inline Style getStyle() const { return _style; }

			inline bool isNull() const { return _style == Style::null; }
	};
}
