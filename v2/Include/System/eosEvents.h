#ifndef __eosEvents__
#define __eosEvents__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	template <typename Sender>
	struct EventArgs {

		Sender* sender;

		EventArgs(Sender* sender):
			sender(sender) {
		}
	};
}


#endif // __eosEvents__

