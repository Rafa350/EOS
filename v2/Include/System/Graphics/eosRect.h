#ifndef __eosRect__
#define __eosRect__


#include "eos.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


namespace eos {

    /// \brief Clase que representa un rectangle.
	class Rect {
		private:
			int x;
			int y;
			int width;
			int height;

        public:
			Rect();
            Rect(int x, int y, int width, int height);
            Rect(const Point &p1, const Point &p2);
            Rect(const Point &p, const Size &s);
            Rect(const Rect &r);

            inline int getX() const { return x; }
            inline int getY() const { return y; }
            inline Point getPosition() const { return Point(x, y); }
            inline int getWidth() const { return width; }
            inline int getHeight() const { return height; }
            inline Size getSize() const { return Size(width, height); }
            inline int getMinX() const { return x; };
            inline int getMinY() const { return y; }
            inline int getMaxX() const { return x + width - 1; }
            inline int getMaxY() const { return y + height - 1; }

            Rect offset(int x, int y) const;
            inline Rect offset(const Point &p) const { return offset(p.getX(), p.getY()); }
            Rect inflate(int x, int y) const;
            Rect intersect(const Rect &r) const;
            Rect fusion(const Rect &r) const;

            bool contains(int x, int y) const;
            inline bool contains(const Point &p) const { return contains(p.getX(), p.getY()); }
            bool contains(const Rect &r) const;

            bool isEmpty() const;

            bool operator==(const Rect &r) const;
            bool operator!=(const Rect &r) const;
	};
}


#endif // __eosRect__
