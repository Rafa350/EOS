#ifndef __eosTouchPadDriver__
#define __eosTouchPadDriver__


// EOS includes
#include "eos.h"


#ifndef TOUCHPAD_MAX_POINTS
#define TOUCHPAD_MAX_POINTS  5
#endif


namespace eos {

	/// \brief Orientacio del touchpad.
	enum class TouchPadOrientation: uint8_t {
		normal = 0,
		rotate0 = normal,
		rotate90,
		rotate180,
		rotate270,
	};

	/// \brief Accio detectada.
	enum class TouchPadAction: uint8_t {
		press = 0b00,
		release = 0b01,
		contact = 0b10,
		none = 0b11
	};

	/// \brief Dades d'estat del touchpad.
	struct TouchPadState {
		uint8_t numPoints;
		uint8_t maxPoints;
		TouchPadAction action[TOUCHPAD_MAX_POINTS];
		int16_t x[TOUCHPAD_MAX_POINTS];
		int16_t y[TOUCHPAD_MAX_POINTS];
	};

	class ITouchPadDriver {
		public:
			virtual ~ITouchPadDriver() = default;

			virtual void initialize() = 0;
			virtual void shutdown() = 0;
			virtual int getPadWidth() const = 0;
			virtual int getPadHeight() const = 0;
			virtual void setOrientation(TouchPadOrientation orientation) = 0;
			virtual int getTouchCount() = 0;
			virtual bool getState(TouchPadState &state) = 0;
	};
}


#endif // __eosTouchPadDriver__
