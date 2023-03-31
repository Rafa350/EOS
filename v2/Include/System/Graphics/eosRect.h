#ifndef __eosRect__
#define __eosRect__


#include "eos.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


namespace eos {

    /// \brief Clase que representa un rectangle aliniat amb els eixos.
    ///
	class Rect {
		private:
			int16_t _x;
			int16_t _y;
			int16_t _width;
			int16_t _height;

        public:
			Rect();
            Rect(int16_t x, int16_t y, int16_t width, int16_t height);
            Rect(const Point &p1, const Point &p2);
            Rect(const Point &p, const Size &s);
            Rect(const Size &s);
            Rect(const Rect &r);
            Rect(const Rect &&r);

            inline int16_t getX() const { return _x; }
            inline int16_t getY() const { return _y; }
            inline Point getPosition() const { return Point(_x, _y); }
            inline int16_t getWidth() const { return _width; }
            inline int16_t getHeight() const { return _height; }
            inline Size getSize() const { return Size(_width, _height); }
            inline int16_t getMinX() const { return _x; };
            inline int16_t getMinY() const { return _y; }
            inline int16_t getMaxX() const { return _x + _width - 1; }
            inline int16_t getMaxY() const { return _y + _height - 1; }

            Rect translated(int16_t x, int16_t y) const;
            inline Rect translated(const Point &p) const { return translated(p.getX(), p.getY()); }
            Rect inflated(int16_t h, int16_t v) const { return inflated(h, v, h, v); }
            Rect inflated(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
            Rect intersected(const Rect &r) const;
            Rect fusioned(const Rect &r) const;

            bool contains(int16_t x, int16_t y) const;
            inline bool contains(const Point &p) const { return contains(p.getX(), p.getY()); }
            bool contains(const Rect &r) const;

            bool isEmpty() const;

            Rect& operator = (const Rect &r);

            bool operator == (const Rect &r) const;
            inline bool operator != (const Rect &r) const { return !(*this == r); }
	};
}


#endif // __eosRect__
