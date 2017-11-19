#ifndef __eosTouchPadDriver__
#define __eosTouchPadDriver__


#include "eos.h"

#include <stdint.h>


namespace eos {

	class ITouchPadDriver {
		public:
			virtual ~ITouchPadDriver() {}
			virtual int16_t getWidth() const = 0;
			virtual int16_t getHeight() const = 0;;
	};
}


#endif // __eosTouchPadDriver__
