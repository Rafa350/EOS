export module Eos.Hardware.CAN.__PLATFORM_TRAITS;


import Eos.Configuration.Platform;


namespace eos::hardware::can {

    namespace internal {

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

    export using CANDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
}
