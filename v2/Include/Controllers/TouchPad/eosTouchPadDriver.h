#ifndef __eosTouchPadDriver__
#define __eosTouchPadDriver__


#include "eos.h"

#include <stdint.h>


namespace eos {

	class ITouchPadDriver {
		public:
			virtual ~ITouchPadDriver() {}
			virtual int16_t getWidth() = 0;
			virtual int16_t getHeight() = 0;
			virtual uint8_t getTouches() = 0;
			virtual void queryState() = 0;
	};
}


#endif // __eosTouchPadDriver__
