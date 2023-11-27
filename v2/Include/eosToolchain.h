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
#elif defined(__GNUC__) && defined(__arm__)
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

		struct Toolchain {
			#ifdef EOS_TOOLCHAIN_XC32
			static constexpr bool is_XC32_Toolchain = true;
			#else
			static constexpr bool is_XC32_Toolchain = false;
			#endif

			#ifdef EOS_TOOLCHAIN_GNU
			static constexpr bool is_GNU_Toolchain = true;
			#else
			static constexpr bool is_GNU_Toolchain = false;
			#endif

			#ifdef EOS_TOOLCHAIN_MVC
			static constexpr bool is_MVC_Toolchain = true;
			#else
			static constexpr bool is_MVC_Toolchain = false;
			#endif
		};
	}
}
#endif


#endf // __eosToolchain__
