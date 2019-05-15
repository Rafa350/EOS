#ifndef __eosLTDCAdapter__
#define __eosLTDCAdapter__


// EOS includes
//
#include "eos.h"


namespace eos {
    
    struct LTDCInitParamsStruct  {
        uint32_t frameAddr;
        uint32_t screenWidth;
        uint32_t screenHeight;
        uint32_t hSync;
        uint32_t vSync;
        bool hSyncPolarity;
        bool vSyncPolatity;
    };
    typedef struct LTDCInitParamsStruct LTCDinitParams;
    
    class LTDCAdapter {
        public:
            void initialize(const LTDCInitParams &init);
    };
    
}


#endif
