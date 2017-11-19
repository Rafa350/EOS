#ifndef __eosTouchPad__
#define __eosTouchPad__


#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"


namespace eos {

	typedef struct {

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
