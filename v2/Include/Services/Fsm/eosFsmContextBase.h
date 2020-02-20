#ifndef __eosFsmContextBase__
#define	__eosFsmContextBase__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosStack.h"


namespace eos {

    class FsmStateBase;

	class FsmContextBase {
        
        private:
            typedef Stack<FsmStateBase*> StateStack;
            
		private:
            FsmStateBase* state;
            StateStack stateStack;
            
		protected:
			FsmContextBase();            
            FsmStateBase* getState() const;

        public:
            void clearState();
			void setState(FsmStateBase* state);
            void pushState(FsmStateBase* state);
            void popState();
	};
    
}


#endif	// __eosFsmContextBase__
