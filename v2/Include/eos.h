#pragma once
#ifndef __eos__
#define __eos__


// Environment detection includes
//
#include "eosVersion.h"
#include "eosToolchain.h"
#include "eosPlatform.h"


#if EOS_TOOLCHAIN_DETECTED != 1
#error "Unknown toolchain"
#endif

#if EOS_PLATFORM_DETECTED != 1
#error "Unknown platform"
#endif


// Standard includes
//
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>


// Modus de depuracio
//
#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG)
	#define EOS_DEBUG
#endif


// EOS includes
//
#ifndef EOS_NO_INCLUDE_CONFIG
#include "eosConfig.h"
#endif
#ifndef EOS_NO_INCLUDE_BOARD
#include "eosBoard.h"
#endif


// Application entry point
//
void appMain();
void appInitialize();


#endif // __eos__
