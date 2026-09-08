module;


#include <concepts>


export module Eos.Result;


namespace eos {

    template <typename T_>
    concept IsEnum = std::is_enum_v<T_>;

    export
    template <IsEnum ErrorType_, ErrorType_ noError_>
    class SimpleResultX {
        private:
            /// @brief El codi d'error pel cas que no hagi error.
            ///
            static constexpr ErrorType_ _noError = noError_;

        private:
            /// @brief El codi d'error.
            ///
            ErrorType_ const _error;

        public:
            /// @brief Contructor.
            /// @param error: El codi d'error
            ///
            inline SimpleResultX():
                _error {_noError} {
            }

            /// @brief Contructor.
            /// @param error: El codi d'error
            ///
            inline SimpleResultX(ErrorType_ error):
                _error {error} {
            }

            /// @brief Constructor de copia.
            /// @param other: L'altre objecte.
            ///
            inline SimpleResultX(const SimpleResultX &other):
                _error {other._error} {
            }

            /// @brief Obte el codi d'error.
            /// @return El resultat de l'operacio.
            //
            inline ErrorType_ getError() const { return _error; }

            /// @brief Comprova si no hi ha cap error.
            /// @return True si tot es correcte i no hi ha error.
            ///
            inline bool isSuccess() const { return _error == _noError; }

            /// @brief Comprova si el error es el especificat.
            /// @param error: El codi d'error de referencia.
            /// @return True si el error es el de referencia, false en cas contrari.
            ///
            inline bool is(ErrorType_ error) const { return _error == error; }

            /// @brief Conversio a bool. True si no hi ha error, false en cas contrari.
            ///
            inline operator bool () const { return _error == _noError; }
    };


    export
    template <typename ValueType_, IsEnum ErrorType_, ErrorType_ noError_>
    class ComplexResultX : public SimpleResultX<ErrorType_, noError_> {
        private:
            ValueType_ const _value;

        public:
            /// @brief Constructor
            /// @param value : El valor del resultat.
            ///
            inline ComplexResultX(ValueType_ value):
                SimpleResultX<ErrorType_, noError_> {noError_},
                _value {value} {
            }

            /// @brief Constructor.
            /// @param error: El codi d'error.
            ///
            inline ComplexResultX(ErrorType_ error):
                SimpleResultX<ErrorType_, noError_> {error},
                _value {ValueType_()} {
            }

            /// @brief Constructor de copia.
            /// @param other: L'altre objecte.
            ///
            inline ComplexResultX(const ComplexResultX &other):
                SimpleResultX<ErrorType_, noError_> {other},
                _value {other._value} {
            }

            /// @brief Obte el valor.
            /// @return El resultat de l'operacio.
            ///
            inline ValueType_ getValue() const { return _value; }

            /// @brief Comprova si el valor es el indicat.
            /// @param value: El valor de referencia.
            /// @return True si el valor coincideix amb el de referencia.
            ///
            inline bool isValue(ValueType_ value) const { return _value == value; }

            /// @brief Conversio al tipus del valor.
            ///
            inline operator ValueType_ () const { return _value; }
    };
}
