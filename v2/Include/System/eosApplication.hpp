#ifndef __EOS_APPLICATION_HPP
#define	__EOS_APPLICATION_HPP


#include "eos.hpp"


namespace eos {

    class Application {
        public:
            Application();
            void execute();
            bool x(int a)  { return a > 0; }
    };
}


#endif	


