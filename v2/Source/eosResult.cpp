module;


#include "eos.h"
#include <concepts>


export module Eos.Result;


namespace eos {

    template <typename T_>
    concept IsEnum = std::is_enum_v<T_>;

    template <IsEnum ErrorType_, ErrorType_ okValue_>
    class Result {
        private:
            /// @brief El codi d'error.
            ///
            ErrorType_ const _error;

        public:
            /// @brief Contructor per defecte.
            ///
            constexpr Result():
                _error {okValue_} {
            }

            /// @brief Contructor.
            /// @param error: El codi d'error
            ///
            constexpr Result(ErrorType_ error):
                _error {error} {
            }

            /// @brief Constructor de copia.
            /// @param other: L'altre objecte.
            ///
            Result(const Result &other):
                _error {other._error} {
            }

            /// @brief Obte el codi d'error.
            /// @return El resultat de l'operacio.
            //
            [[nodiscard]] ErrorType_ getError() const { return _error; }

            /// @brief Comprova si no hi ha cap error.
            /// @return True si tot es correcte i no hi ha error.
            ///
            [[nodiscard]] bool isSuccess() const { return _error == okValue_; }

            /// @brief Comprova si el error es el especificat.
            /// @param error: El codi d'error de referencia.
            /// @return True si el error es el de referencia, false en cas contrari.
            ///
            [[nodiscard]] bool is(ErrorType_ error) const { return _error == error; }

            /// @brief Conversio a bool. True si no hi ha error, false en cas contrari.
            ///
            operator bool () const { return _error == okValue_; }

            /// @brief Conversio al tipus del codi d'error.
            ///
            operator ErrorType_ () const { return _error; }
    };

    export template <IsEnum ErrorType_, ErrorType_ okValue_>
    using SimpleResultX = Result<ErrorType_, okValue_>;

    export template <typename ValueType_, IsEnum ErrorType_, ErrorType_ okValue_>
    class ComplexResultX final: public Result<ErrorType_, okValue_> {
        private:
            ValueType_ const _value;

        public:
            /// @brief Constructor
            /// @param value : El valor del resultat.
            ///
            ComplexResultX(ValueType_ value):
                Result<ErrorType_, okValue_> {okValue_},
                _value {value} {
            }

            /// @brief Constructor.
            /// @param error: El codi d'error.
            ///
            ComplexResultX(ErrorType_ error):
                Result<ErrorType_, okValue_> {error},
                _value {ValueType_{}} {
            }

            /// @brief Constructor de copia.
            /// @param other: L'altre objecte.
            ///
            ComplexResultX(const ComplexResultX &other):
                Result<ErrorType_, okValue_> {other},
                _value {other._value} {
            }

            /// @brief Obte el valor.
            /// @return El resultat de l'operacio.
            ///
            [[nodiscard]] ValueType_ getValue() const { return _value; }

            /// @brief Comprova si el valor es el indicat.
            /// @param value: El valor de referencia.
            /// @return True si el valor coincideix amb el de referencia.
            ///
            [[nodiscard]] bool isValueEqualTo(ValueType_ value) const { return _value == value; }

            /// @brief Conversio al tipus del valor.
            ///
            operator ValueType_ () const { return _value; }
    };
}
