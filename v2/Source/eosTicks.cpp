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
            /// @param  t: L'altre objecte.
            ///
            Ticks(const Ticks &ticks) = default;

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

            bool hasExpired() const;
            bool hasExpired(Ticks limit) const;

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
/// @brief    Crea l'objecte a partir del valor en milisegons.
/// @param    ms: El valor en milisegons.
/// @return   El resultat.
///
constexpr eos::Ticks eos::Ticks::fromMiliseconds(
    uint32_t ms) {

    return Ticks(pdMS_TO_TICKS(ms));
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actual.
/// @return   El resultat.
///
eos::Ticks eos::Ticks::now() {

    return Ticks(xTaskGetTickCount());
}


/// ---------------------------------------------------------------------------
/// @brief    Crea l'objecte a partir del valor de ticks actua. Per
///           cridar d'ins d'una ISR
/// @return   El resultat.
///
eos::Ticks eos::Ticks::nowISR() {

    return Ticks(xTaskGetTickCountFromISR());
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
        auto delta = _value - xTaskGetTickCount();
	    return static_cast<int>(delta) <= 0;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si ha expirat respecte a un limit.
/// @return   True si ha expirat.
///
bool eos::Ticks::hasExpired(Ticks limit) const {

    if (isZero())
        return true;

    else if (isInfinite())
        return false;

    else {
        auto delta = _value - limit._value;
	    return static_cast<int>(delta) <= 0;
    }
}
