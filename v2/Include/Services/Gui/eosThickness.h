#ifndef __eosThickness__
#define __eosThickness__


#include "eos.h"


namespace eos {

	class Rect;
	class Size;

	/// \Clase que representa l'amplada dels perfils
	///
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

			Rect inflate(const Rect &rect);
			Size inflate(const Size &size);
			Rect deflate(const Rect &rect);
			Size deflate(const Size &size);
	};

}


#endif // __eosThickness__
