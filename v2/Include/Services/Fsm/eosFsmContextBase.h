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
            void initialize(FsmStateBase* state);
            FsmStateBase* getState() const;

        public:
            void beginTransition();
			void endTransition(FsmStateBase* state);
            void endTransitionPush(FsmStateBase* state);
            void endTransitionPop();
	};
    
}


#endif	// __eosFsmContextBase__
