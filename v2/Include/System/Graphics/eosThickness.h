#ifndef __eosThickness__
#define __eosThickness__


#include "eos.h"


namespace eos {

	class Thickness {
		private:
			int left;
			int top;
			int right;
			int bottom;

		public:
			Thickness();
			Thickness(int thickness);
			Thickness(int hThickness, int vThickness);
			Thickness(int left, int top, int right, int bottom);
			Thickness(const Thickness &t);

			inline int getLeft() const { return left; }
			inline int getTop() const { return top; }
			inline int getRight() const { return right; }
			inline int getBottom() const { return bottom; }

			bool operator==(const Thickness &other) const;
			inline bool operator!=(const Thickness &other) const { return !operator==(other); }
	};
	
}


#endif // __eosThickness__
