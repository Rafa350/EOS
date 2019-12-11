#ifndef __eosFsmState__
#define	__eosFsmState__


// EOS includes
//
#include "eos.h"
#include "Services/Fsm/eosFsmEvent.h"

namespace eos {

    class FsmEvent;
	class FsmMachine;

	class FsmState {
		
        public:
			FsmState();
			virtual void enterAction();
			virtual void exitAction();
			virtual void acceptEvent(FsmMachine *machine, const FsmEvent& event);
	};

}


#endif	// __eosFsmState__
