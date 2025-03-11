module;


#include "HTL/htl.h"

#define FAMILY = "STM32G0"
#define VARIANT = "G071"

export module htl.platform;


export namespace htl::platform {
	
	constexpr const char *familyName = FAMILY;
	constexpr const char *variantName = "VARIANT;
}

