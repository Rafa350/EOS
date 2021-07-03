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
		null,
		solid
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
			Pen(PenStyle style, Color color, int thickness);
			Pen(const Pen &pen);
			~Pen();

			Pen& operator = (const Pen& pen);
			bool operator == (const Pen& pen) const;
			inline bool operator != (const Pen& pen) const { return !(*this == pen); }

			Color getColor() const;
			int getThickness() const;
			PenStyle getStyle() const;

			bool isNull() const;
	};
}


#endif // __eosPen__
