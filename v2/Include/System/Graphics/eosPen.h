#ifndef __eosPen__
#define __eosPen__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"
#include "System/Graphics/eosColor.h"


#ifndef eosGraphics_MaxPens
#define eosGraphics_MaxPens 10
#endif


namespace eos {

	enum class PenStyle: uint8_t {
		Null,
		Solid
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
			Pen(const Color& color, int thickness, PenStyle style);
			Pen(const Pen& pen);
			~Pen();

			Pen& operator = (const Pen& pen);

			Color getColor() const;
			int getThickness() const;
			PenStyle getStyle() const;

			void setColor(const Color& color);
			void setThickness(int thickness);
			void setStyele(PenStyle style);
	};
}


#endif // __eosPen__
