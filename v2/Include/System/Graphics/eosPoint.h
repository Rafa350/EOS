#ifndef __eosPoint__
#define __eosPoint__


#include "eos.h"


namespace eos {

	/// \brief Clase que representa un punt.
	///
	class Point {
		private:
			int16_t _x;
			int16_t _y;

        public:
			Point();
            Point(int16_t x, int16_t y);
            Point(const Point &p);
            Point(const Point &&p);

            inline int16_t getX() const { return _x; }
            inline int16_t getY() const { return _y; }

            Point& translate(int16_t dx, int16_t dy);
            Point& translate(const Point &d);
            Point translated(int16_t dx, int16_t dy) const;
            Point translated(const Point &p) const;

            Point& operator = (const Point &p);

            bool operator == (const Point &p) const;
            inline bool operator != (const Point &p) const { return !(*this == p); }
	};
}


#endif // __eosPoint__
