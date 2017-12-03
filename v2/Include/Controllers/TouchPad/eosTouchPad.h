#ifndef __eosTouchPad__
#define __eosTouchPad__


#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"


namespace eos {

	class TouchPad {
		private:
			ITouchPadDriver *driver;

		public:
			TouchPad(ITouchPadDriver *driver);
			bool getState(TouchPadState &state);
	};

}


#endif // __eosTouchPad__
