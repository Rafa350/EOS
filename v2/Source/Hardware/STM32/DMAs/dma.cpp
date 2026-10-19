module;

#include "hardware.h"


export module Eos.Hardware.DMA;


import Eos.System.Core.Ticks;
import Eos.Result;
import Eos.Types;


namespace eos::hardware::dma {

}

export namespace eos::hardware::dma {

    class DMADevice: private NonCopyableClass {
        public:
            StdResult start(const UInt8 *src, UInt8 *dst, UInt32 size);
            StdResult waitForFinish(Ticks blockTime);
    };

    template <typename deviceId_>
    class DMADeviceX: public DMADevice {

    };
}
