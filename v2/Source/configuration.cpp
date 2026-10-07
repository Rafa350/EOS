module;


#include "eos.h"


export module Eos.Configuration;


export import Eos.Configuration.Platform;
export import Eos.Configuration.Toolchain;


namespace eos {

    export struct Configuration {

        struct Hardware {
            struct Uart {
            };
        };
    };
}
