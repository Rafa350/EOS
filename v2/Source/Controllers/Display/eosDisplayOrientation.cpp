module;


#include "eos.h"


export module Eos.Controllers.Display.Orientation;


export namespace eos {

    /// \brief Orientacio de la pantalla.
	///
	enum class DisplayOrientation: uint8_t {
	    rotate0,             ///< Orientacio 0
		rotate90,            ///< Orientacio 90
		rotate180,           ///< Orientacio 180
		rotate270,           ///< Orientacio 270
		normal = rotate0,    ///< Orientacio normal
	};
}
