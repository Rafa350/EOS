module;


#include "HTL/htl.h"


export module Eos.Hardware.Atomic;


import Eos.Types;


export namespace eos {

	namespace hardware {

		class Atomic final: private StaticClass<Atomic> {
			public:
				static UInt32 start();
				static void end(UInt32 pm);
		};

	}
}


using namespace eos;
using namespace eos::hardware;


/// ----------------------------------------------------------------------
/// @brief    Constructor per defecte.
///
UInt32 Atomic::start() {

	UInt32 pm {__get_PRIMASK()};
	__set_PRIMASK(1);
	return pm;
}


/// ---------------------------------------------------------------------------
/// @brief    Finalitza les operacions atimiques.
///
void Atomic::end(UInt32 pm) {

	__set_PRIMASK(pm);
}
