#ifndef __eosFsmState__
#define	__eosFsmState__


// EOS includes
//
#include "eos.h"


namespace eos {
    
    class FsmContextBase;

	class FsmStateBase {	
        private:
            FsmContextBase* context;
    
        protected:
			FsmStateBase(FsmContextBase* context);
            virtual ~FsmStateBase();
        
            inline FsmContextBase* getContext() const { return context; }

            void beginTransition();
			void endTransition(FsmStateBase* state);
            void endTransitionPush(FsmStateBase* state);
            void endTransitionPop();
        
        public:
            virtual void enter() = 0;
            virtual void exit() = 0;
	};

}


#endif	// __eosFsmState__
