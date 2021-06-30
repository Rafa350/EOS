#ifndef __eosPen__
#define __eosPen__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosBrush.h"


#ifndef eosGraphics_MaxPens
#define eosGraphics_MaxPens 10
#endif


namespace eos {

	enum class PenStyle: uint8_t {
		Null,
		Solid
	};

	enum class PenCapStyle {

	};

	enum class PenJoinStyle {

	};

	class Pen {
		private:
			struct Impl;
			typedef SharedPtr<Impl> PImpl;

		private:
			PImpl _pImpl;

		private:
			PImpl allocate();

		public:
			Pen();
			Pen(Color color);
			Pen(Color color, int thickness, PenStyle style);
			Pen(const Brush &brush);
			Pen(const Brush &brush, int thickness, PenStyle style);
			Pen(const Pen &pen);
			~Pen();

			Pen& operator = (const Pen& pen);
			bool operator == (const Pen& pen) const;
			bool operator != (const Pen& pen) const;

			Color getColor() const;
			int getThickness() const;
			PenStyle getStyle() const;

			//void setColor(const Color& color);
			//void setThickness(int thickness);
			//void setStyle(PenStyle style);
	};
}


#endif // __eosPen__
