#ifndef __eosDisplayOrientation__
#define __eosDisplayOrientation__


// EOS includes
//
#include "eos.h"


namespace eos {

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
 
 
#endif // __eosDisplayOrientation__ 
    