#ifndef __eosEvents__
#define __eosEvents__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	template <typename Sender_>
	struct EventArgs {

		Sender_* sender;

		EventArgs(Sender_* sender):
			sender(sender) {
		}
	};
}


#endif // __eosEvents__

