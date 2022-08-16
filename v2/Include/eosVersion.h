#pragma once
#ifndef __eosVersion__
#define __eosVersion__


#define EOS_HI_VERSION       2
#define EOS_LO_VERSION       0
#define EOS_REVISION         100


#ifdef __cplusplus
namespace eos {
	namespace build {
		static constexpr int eosHiVersion = EOS_HI_VERSION;
		static constexpr int eosLoVersion = EOS_LO_VERSION;
		static constexpr int eosVersion = (eosHiVersion * 100) + eosLoVersion;
		static constexpr int eosRevision = EOS_REVISION;
	}
}
#endif


#endif // __eosVersion__
