#ifndef __eosPen__
#define __eosPen__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"


#ifndef eosGraphics_MaxPens
#define eosGraphics_MaxPens 10
#endif


namespace eos {

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
			Pen(const Color& color, int thickness);
			Pen(const Pen& pen);
			~Pen();

			Pen& operator = (const Pen& pen);

			Color getColor() const;
			int getThickness() const;

			void setColor(const Color& color);
			void setThickness(int thickness);
	};
}


#endif // __eosPen__
