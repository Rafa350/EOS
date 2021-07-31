#ifndef __eosPoint__
#define __eosPoint__


#include "eos.h"


namespace eos {

	/// \brief Clase que representa un punt.
	///
	class Point {
		private:
			int _x;
			int _y;

        public:
			Point();
            Point(int x, int y);
            Point(const Point& p);
            Point(const Point&& p);

            inline int getX() const { return _x; }
            inline int getY() const { return _y; }

            Point& translate(int dx, int dy);
            Point& translate(const Point& d);
            Point translated(int dx, int dy) const;
            Point translated(const Point& p) const;

            Point& operator = (const Point& p);

            bool operator == (const Point& p) const;
            inline bool operator != (const Point& p) const { return !(*this == p); }
	};
}


#endif // __eosPoint__
