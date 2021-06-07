#ifndef __eosVisualUtils__
#define __eosVisualUtils__


#include "eos.h"


namespace eos {

	class Point;
	class Rect;
	class Visual;

	namespace VisualUtils {

		Rect getClip(Visual *visual);
		Point getPosition(Visual *visual);
		Visual *getVisual(Visual *visual, const Point &p);
		Visual *getVisual(Visual *vosial, unsigned id);
	}

}


#endif // __eosVisualUtils__
