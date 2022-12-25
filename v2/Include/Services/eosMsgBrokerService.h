#ifndef __eosMsgBrokerService__
#define __eosMsgBrokerService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"


namespace eos {

    class MsgBrokerService: public Service {

        protected:
            void onInitialize() override;
            void onTask(Task *task) override;
#if Eos_ApplicationTickEnabled
            void onTick() override;
#endif
        public:
            void publish();
            void subscribe();
    };
}


#endif // __eosMsgBrokerService__
