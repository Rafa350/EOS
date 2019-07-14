#ifndef __eosPoint__
#define __eosPoint__


#include "eos.h"


namespace eos {

	/// \brief Clase que representa un punt.
	class Point {
		private:
			int x;
			int y;

        public:
			Point();
            Point(int x, int y);
            Point(const Point &p);

            inline int getX() const { return x; }
            inline int getY() const { return y; }

            Point offset(int dx, int dy) const;
            Point offset(const Point &d) const;

            bool operator==(const Point &p) const;
            bool operator!=(const Point &p) const;
	};
}


#endif // __eosPoint__
