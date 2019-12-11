#ifndef __eosFsmMachine__
#define	__eosFsmMachine__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"


namespace eos {

    class FsmEvent;
    class FsmState;

	class FsmMachine {
        
		private:
			Stack<FsmState*> states;
            
		public:
			FsmMachine();
			~FsmMachine();
			void start(FsmState* initialState);
			void acceptEvent(const FsmEvent& event);
			void setState(FsmState* state);
			void pushState(FsmState* state);
			void popState();
	};

}


#endif	// __eosFsmMachine__
