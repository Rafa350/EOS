#ifndef __eosVisualUtils__
#define __eosVisualUtils__


#include "eos.h"


namespace eos {

	class Point;
	class Rect;
	class Visual;

	namespace VisualUtils {

		Rect getClip(Visual *pVisual);
		Point getPosition(Visual *pVisual);
		Visual *getVisual(Visual *pVisual, const Point &p);

	}

}


#endif // __eosVisualUtils__
