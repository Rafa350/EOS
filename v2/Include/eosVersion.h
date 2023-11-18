#pragma once


#define EOS_HI_VERSION       2
#define EOS_LO_VERSION       0
#define EOS_REVISION         100
#define EOS_BUILD            100


#include <stdint.h>


#ifdef __cplusplus
namespace eos {
	namespace build {

		struct Version {
			static constexpr uint8_t hiVersion = EOS_HI_VERSION;
			static constexpr uint8_t loVersion = EOS_LO_VERSION;
			static constexpr uint8_t revision = EOS_REVISION;
			static constexpr uint16_t build = EOS_BUILD;
		};
	}
}
#endif
