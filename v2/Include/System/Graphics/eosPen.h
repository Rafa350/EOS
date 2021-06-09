#ifndef __eosPen__
#define __eosPen__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"


namespace eos {

	class Pen {
		private:
			struct Impl;
			typedef std::shared_ptr<Impl> PImpl;

		private:
			PImpl _pImpl;

		private:
			PImpl allocate();

		public:
			Pen();
			Pen(const Color& color, int thickness);

			Color getColor() const;
			int getThickness() const;

			void setColor(const Color& color);
			void setThickness(int thickness);
	};
}


#endif // __eosPen__
