#pragma once


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class Brush final {
		public:
			enum class Style {
				null,
				solid,
				linearGradient,
				radialGradient
			};

		private:
			Style _style;
			Color _color;

		public:
			Brush();
			Brush(Color color);
			Brush(const Brush &brush);

			Brush& operator = (const Brush &brush);
			bool operator == (const Brush &brush) const;
			inline bool operator != (const Brush &brush) const { return !(*this == brush); }

			inline Color getColor() const { return _color; }
			inline Style getStyle() const { return _style; }

			inline bool isNull() const { return _style == Style::null; }
	};

}
