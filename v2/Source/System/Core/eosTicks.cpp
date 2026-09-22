module;


#include "eos.h"


export module Eos.System.Core.Ticks;


import Eos.Math;
import Eos.System.Core.Kernel;


namespace eos {

    /// @brief Clase que encapsula el temps en ticks del sistema.
    ///
    export class Ticks final {

        private:
            static constexpr uint32_t _zeroValue = 0;
            static constexpr uint32_t _infiniteValue = Math::maxU32;

        private:
            uint32_t _value;

        private:
            /// @brief  Constructor.
            /// @param  ticks: Valor inicial.
            ///
            explicit constexpr Ticks(uint32_t value): _value {value} {}

        public:
            /// @brief  Contructor per defecte al valor inicial zero.
            ///
            Ticks(): _value {0} {};

            /// @brief  Constructor copia.
            /// @param  other: L'altre objecte.
            ///
            Ticks(const Ticks &other) = default;

            /// @brief  Construeix un objecte amb valor zero
            /// @return El resultat.
            ///
            static constexpr Ticks zero() { return Ticks(_zeroValue); }

            /// @brief   Construeix un objecte amb valor infinit
            /// @return El resultat.
            ///
            static constexpr Ticks infinite() { return Ticks(_infiniteValue); };

            static Ticks now();
            static Ticks nowISR();
            static constexpr Ticks fromTicks(uint32_t ticks);
            static constexpr Ticks fromMiliseconds(uint32_t ms);

            /// @brief Comprova si es zero.
            /// @return El resultat de l'operacio.
            //
            bool isZero() const { return _value == _zeroValue; }

            /// @brief Comprova si es infinit.
            /// @return El resultat de l'operacio.
            /// @remark Util pels timeouts infinits.
            ///
            bool isInfinite() const { return _value == _infiniteValue; }

            bool hasExpiredNow() const;

            Ticks& operator = (const Ticks ticks) { _value = ticks._value; return *this; }
            Ticks& operator += (const Ticks ticks) { _value += ticks._value; return *this; }
            Ticks& operator += (uint32_t value) { _value += value; return *this; }
            Ticks& operator -= (const Ticks ticks) { _value -= ticks._value; return *this; }
            Ticks& operator -= (uint32_t value) { _value -= value; return *this; }

            Ticks operator + (const Ticks &ticks) const { return Ticks(_value + ticks._value); }
            Ticks operator + (uint32_t value) const { return Ticks(_value + value); }
            Ticks operator - (const Ticks &ticks) const { return Ticks(_value - ticks._value); }
            Ticks operator - (uint32_t value) const { return Ticks(_value - value); }

            bool operator == (const Ticks &ticks) const { return _value == ticks._value; }
            bool operator < (const Ticks &ticks) const { return _value < ticks._value; }
            bool operator > (const Ticks &ticks) const { return _value > ticks._value; }

            explicit operator uint32_t () const { return _value; }
    };
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor en ticks.
/// @param    ms: El valor en ticks.
/// @return   El resultat.
///
constexpr eos::Ticks eos::Ticks::fromTicks(
    uint32_t ticks) {

    return Ticks {ticks};
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor en milisegons.
/// @param    ms: El valor en milisegons.
/// @return   El resultat.
///
constexpr eos::Ticks eos::Ticks::fromMiliseconds(
    uint32_t ms) {

    return Ticks {ms * Kernel::tickFrequency / 1000};
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actual.
/// @return   El resultat.
///
eos::Ticks eos::Ticks::now() {

    return Ticks {Kernel::getTickCount()};
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actua. Per
///           cridar d'ins d'una ISR
/// @return   El resultat.
///
eos::Ticks eos::Ticks::nowISR() {

    return Ticks {Kernel::getTickCountISR()};
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si ha arribal al valor del contador de ticks actual.
/// @return   True si ha expirat.
///
bool eos::Ticks::hasExpiredNow() const {

    if (isZero())
        return true;

    else if (isInfinite())
        return false;

    else {
        auto delta = _value - Kernel::getTickCount();
	    return static_cast<int>(delta) <= 0;
    }
}
