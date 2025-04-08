module;


#include "HTL/htl.h"


export module htl.platform;

export namespace htl::platform {

	enum class PlatformID {
		
		stm32f030r8,
		
		stm32f429zi,
		
		stm32f746ng,
		
		stm32g071r8,
		stm32g071rb
	};

#if defined(EOS_PLATFORM_STM32F030R8)
	struct PlatformInfo {
		static constexpr PlatformID id = PlatformID::stm32f030r8;
		static constexpr const char *name = "STM32F030R8";
		static constexpr unsigned ramSize = 36 * 1024;
		static constexpr unsigned romSize = 128 * 1024;
	};
#elif defined(EOS_PLATFORM_STM32G071RB)
	struct PlatformInfo {
		static constexpr PlatformID id = PlatformID::stm32g071rb;
		static constexpr const char *name = "STM32G071RB";
		static constexpr unsigned ramSize = 36 * 1024;
		static constexpr unsigned romSize = 128 * 1024;
	};
#else
	#error 'Unknown platform'
#endif

	constexpr bool isPlatform(PlatformID id) {
		return PlatformInfo::id == id;
	}

}
