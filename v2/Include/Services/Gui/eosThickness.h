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
			int _left;
			int _top;
			int _right;
			int _bottom;

		public:
			Thickness();
			Thickness(int thickness);
			Thickness(int horizontal, int vertical);
			Thickness(int left, int top, int right, int bottom);
			Thickness(const Thickness &t);

			inline int getLeft() const { return _left; }
			inline int getTop() const { return _top; }
			inline int getRight() const { return _right; }
			inline int getBottom() const { return _bottom; }

			bool operator==(const Thickness &other) const;
			inline bool operator!=(const Thickness &other) const { return !operator==(other); }

			Rect inflate(const Rect &rect) const;
			Size inflate(const Size &size) const;
			Rect deflate(const Rect &rect) const;
			Size deflate(const Size &size) const;
	};

}


#endif // __eosThickness__
