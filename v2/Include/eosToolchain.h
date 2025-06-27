#pragma once
#ifndef __eosToolchain__
#define __eosToolchain__


// Microchip XC32 compiler
//
#if defined(__XC32)
    #define EOS_TOOLCHAIN_XC32
	#define EOS_TOOLCHAIN_DETECTED 1


// GNU CPP ARM compiler
//
#elif defined(__GNUC__)
    #define EOS_TOOLCHAIN_GNU
	#define EOS_TOOLCHAIN_DETECTED 1


// Microsoft CPP compiler
//
#elif defined(_MSC_VER)
    #define EOS_TOOLCHAIN_MVC
	#define EOS_TOOLCHAIN_DETECTED 1


// Unknown compiler
//
#else
	#define EOS_TOOLCHAIN_DETECTED 0

#endif


// Toolchain patchs
//
#ifdef EOS_TOOLCHAIN_XC32
    #define final
#endif


#ifdef __cplusplus
namespace eos {
	namespace build {

		enum class ToolChainID {
			xc32,
			gnu,
			mvc
		};

		struct Toolchain {
#if defined(EOS_TOOLCHAIN_XC32)
			static constexpr ToolChainID toolChain = ToolChainID::xc32;
#elif defined(EOS_TOOLCHAIN_GNU)
			static constexpr ToolChainID toolChain = ToolChainID::gnu;
#elif defined(EOS_TOOLCHAIN_MVC)
			static constexpr ToolChainID toolChain = ToolChainID::msc;
#else
#	error "Unknown toolchain"
#endif
		};
	}
}
#endif


#endif // __eosToolchain__
