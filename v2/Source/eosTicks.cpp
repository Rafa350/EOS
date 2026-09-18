module;


#include "eos.h"

#include "FreeRTOS.h"
#include "task.h"


export module Eos.Ticks;


import Eos.Math;


export namespace eos {

    /// @brief Clase que encapsula el temps en ticks del sistema.
    ///
    class Ticks {

        private:
            static constexpr uint32_t _zeroValue = 0;
            static constexpr uint32_t _infiniteValue = Math::maxU32;

        private:
            uint32_t const _ticks;

        private:
            /// @brief  Constructor per defecte.
            /// @param  ticks
            ///
            explicit constexpr Ticks(uint32_t ticks): _ticks {ticks} {}

        public:
            /// @brief  Constructor copia.
            /// @param  t: L'altre objecte.
            ///
            Ticks(const Ticks &t) = default;

            /// @brief  Construeix un objecte amb valor zero
            /// @return El resultat.
            ///
            static constexpr Ticks zero() { return Ticks(_zeroValue); }

            /// @brief   Construeix un objecte amb valor infinit
            /// @return El resultat.
            ///
            static constexpr Ticks infinite() { return Ticks(_infiniteValue); };

            static Ticks fromNow();
            static Ticks fromNowISR();
            static Ticks fromFuture(Ticks t);
            static Ticks fromFutureISR(Ticks t);
            static constexpr Ticks fromMiliseconds(uint32_t ms);

            /// @brief Comprova si es zero.
            /// @return El resultat de l'operacio.
            //
            bool isZero() const { return _ticks == _zeroValue; }

            /// @brief Comprova si es infinit.
            /// @return El resultat de l'operacio.
            /// @remark Util pels timeouts infinits.
            ///
            bool isInfinite() const { return _ticks == _infiniteValue; }

            bool hasExpired() const;

            explicit operator uint32_t () const { return _ticks; }
    };
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor en milisegons.
/// @param    ms: El valor en milisegons.
/// @return   El resultat.
///
constexpr eos::Ticks eos::Ticks::fromMiliseconds(
    uint32_t ms) {

    return Ticks(ms / portTICK_PERIOD_MS);
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actual.
/// @return   El resultat.
///
eos::Ticks eos::Ticks::fromNow() {

    return Ticks(xTaskGetTickCount());
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actua. Per
///           cridar d'ins d'una ISR
/// @return   El resultat.
///
eos::Ticks eos::Ticks::fromNowISR() {

    return Ticks(xTaskGetTickCountFromISR());
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks futurs.
/// @return   El resultat.
///
eos::Ticks eos::Ticks::fromFuture(
    Ticks t) {

    return Ticks(xTaskGetTickCount() + t._ticks);
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks futurs. Per
///           cridar d'ins d'una ISR
/// @return   El resultat.
///
eos::Ticks eos::Ticks::fromFutureISR(
    Ticks ticks) {

    return Ticks(xTaskGetTickCountFromISR() + ticks._ticks);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si ha expirat respecte el contador de ticks.
/// @return   True si ha expirat.
///
bool eos::Ticks::hasExpired() const {

    if (isZero())
        return true;

    else if (isInfinite())
        return false;

    else {
        auto delta = xTaskGetTickCount() - _ticks;
	    return static_cast<int>(delta) <= 0;
    }
}
