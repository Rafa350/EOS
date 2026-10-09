module;


#include "hardware.h"


export module Eos.Hardware.Flash;


import Eos.Bits;
import Eos.Configuration.Platform;
import Eos.Hardware.Regs;
import Eos.Types;


namespace eos::hardware::flash {

    namespace internal {

        // ---------------------------------
        // Traits depenends de la plataforma
        //
        enum class Latency_Type1 { fl0, fl1, fl2 };
		enum class Latency_Type2 { fl0, fl1, fl2, fl3, fl4, fl5, fl6, fl7};

        template <PlatformID platformId_>
        struct PlatformTraits {
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
    		using Latency = Latency_Type1;
        };
    }


    export class Flash final: private StaticClass<Flash> {
        private:
            using PlatformTraits = internal::PlatformTraits<Platform::id>;

        public:
            using Latency = PlatformTraits::Latency;

            static void setLatency(Latency latency);
            [[nodiscard]] inline static Latency getLatency();
            [[nodiscard]] UInt32 static getKbSize();

            inline static void enablePrefetch();
            inline static void disablePrefetch();
    };
}


using namespace eos;
using namespace eos::hardware::flash;


/// ---------------------------------------------------------------------------
/// @brief    Asigna el valor de la latencia.
/// @param    latency: El valor a asignar.
///
void Flash::setLatency(
    Latency latency) {

    auto value = static_cast<UInt32>(latency);

	auto ACR = FLASH->ACR;
	if (((ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos) != value) {

		Bits::clear(ACR, FLASH_ACR_LATENCY_Msk);
		Bits::set(ACR, (value << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY_Msk);
		FLASH->ACR = ACR;

        // Espera qwue el canvi sigui efectiu
        //
		while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (value << FLASH_ACR_LATENCY_Pos))
			continue;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el valor de la latencia.
/// @return   El resultat.
///
Flash::Latency Flash::getLatency() {

    auto value = (FLASH->ACR & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos;
    return static_cast<Latency>(value);
}


/// ---------------------------------------------------------------------------
/// @brief    Habilita pre-fetch.
///
void Flash::enablePrefetch() {

    Bits::set(FLASH->ACR, FLASH_ACR_PRFTEN);
}


/// ---------------------------------------------------------------------------
/// @brief    Desabilita pre-fetch.
///
void Flash::disablePrefetch() {

    Bits::clear(FLASH->ACR, FLASH_ACR_PRFTEN);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el tamany de la flash en Kbytes.
/// @return   El resultst.
///
UInt32 Flash::getKbSize() {

	return Reg32<FLASHSIZE_BASE + 0>::read();

}
