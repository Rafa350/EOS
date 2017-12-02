#ifndef __eosTouchPad__
#define __eosTouchPad__


#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"


namespace eos {

	typedef struct {
		uint8_t dummy;
	} TouchPadState;

	class TouchPad {
		private:
			ITouchPadDriver *driver;

		public:
			TouchPad(ITouchPadDriver *driver);
			void queryState(const TouchPadState &state);
	};

}


#endif // __eosTouchPad__
