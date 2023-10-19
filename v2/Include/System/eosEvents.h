#ifndef __eosEvents__
#define __eosEvents__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {
    
    // TODO: Revisar la utilitat

	template <typename Sender_>
	class EventArgs {
        private:
            Sender_ * const _sender;

        public:
            EventArgs(Sender_ * sender):
                _sender {sender} {
            }
            
            inline Sender_ *getSender() const { return _sender; }
	};
}


#endif // __eosEvents__

