#ifndef __eosFsmContextBase__
#define	__eosFsmContextBase__


// EOS includes
//
#include "eos.h"


namespace eos {

    class FsmStateBase;

	class FsmContextBase {
        
		private:
            FsmStateBase* state;
            
		protected:
			FsmContextBase();            
            FsmStateBase* getState() const { return state; }

        public:
			void setState(FsmStateBase* state);
	};
    
}


#endif	// __eosFsmContextBase__
