#ifndef __eosFsmContextBase__
#define	__eosFsmContextBase__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosFIFOContainer.h"


namespace eos {

    class FsmStateBase;

	class FsmContextBase {

        private:
            typedef FIFOContainer<FsmStateBase*, 20> StateStack;

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
