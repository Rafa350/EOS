module;


#include "eos.h"


export module Eos.Configuration;


export import Eos.Configuration.Platform;
export import Eos.Configuration.Toolchain;


namespace eos {

    export struct Configuration {

        struct Hardware {
            struct Uart {
                static constexpr bool use_IRQ = false;
                static constexpr bool use_DMA = true;
                static constexpr bool use_Deinitialization = false;
            };
        };
    };
}
