export module Eos.Hardware.FDCAN._PlatformTraits;

import Eos.Platform;


namespace eos::hardware::fdcan::internal {

    namespace hidden {

        enum class DeviceID_Type1 { can1, can2 };

        template<PlatformID>
        class PlatformTraits {
        };

        template<>
        class PlatformTraits<PlatformID::STM32_G0B1_RE> {
            public:
                using DeviceID = DeviceID_Type1;
        };

    }

    export using PlatformTraits = hidden::PlatformTraits<Platform::id>;
}
