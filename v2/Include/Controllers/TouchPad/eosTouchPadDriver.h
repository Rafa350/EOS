#ifndef __eosTouchPadDriver__
#define __eosTouchPadDriver__


// EOS includes
#include "eos.h"

// Standard includes
#include <stdint.h>


#ifndef EOS_TOUCHPAD_MAX_POINTS
#define EOS_TOUCHPAD_MAX_POINTS  5
#endif


namespace eos {

	/// \brief Orientacio del touchpad.
	enum class TouchPadOrientation {
		normal,
		rotate90,
		rotate180,
		rotate270,
	};

	/// \brief Accio detectada.
	enum class TouchPadAction {
		evUp = 0b01,
		evDown = 0b00,
		evContact = 0b10
	};

	/// \brief Dades d'estat del touchpad.
	typedef struct {
		uint8_t numPoints;
		uint8_t maxPoints;
		TouchPadAction action[EOS_TOUCHPAD_MAX_POINTS];
		int16_t x[EOS_TOUCHPAD_MAX_POINTS];
		int16_t y[EOS_TOUCHPAD_MAX_POINTS];
	} TouchPadState;

	class ITouchPadDriver {
		public:
			virtual ~ITouchPadDriver() {}
			virtual int16_t getWidth() = 0;
			virtual int16_t getHeight() = 0;
			virtual void setOrientation(TouchPadOrientation orientation) = 0;
			virtual bool getState(TouchPadState &state) = 0;
	};
}


#endif // __eosTouchPadDriver__
