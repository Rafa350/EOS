#pragma once
#ifndef __eosResults__
#define __eosResults__


// STD includes
//
#include <type_traits>


namespace eos {

    template <typename Enum_>
    class ResultBase {

		static_assert(std::is_enum_v<Enum_>);

        private:
            Enum_ const _result;

        protected:
            constexpr ResultBase(Enum_ result) :
                _result {result} {
            }

        public:
            inline operator Enum_() const {
            	return _result;
            }

            inline bool operator == (Enum_ result) const {
            	return _result == result;
            }

            inline bool operator == (ResultBase result) const {
            	return _result == result._result;
            }
    };


    template <typename Enum_>
    class SimpleResult: public ResultBase<Enum_> {
        public:
            constexpr SimpleResult(Enum_ result) :
                ResultBase<Enum_> {result} {
            }
    };


    template <typename Enum_, typename Value_>
    class ComplexResult: public ResultBase<Enum_> {
        private:
            Value_ const _value;

        public:
            constexpr ComplexResult(Enum_ status, Value_ value = {}) :
                ResultBase<Enum_> {status},
                _value {value} {
            }

        public:
            inline operator Value_() const {
            	return _value;
            }
    };


	enum class Results {   // Codis d'error
		success,           // Operacio finalitzada correctament
		pending,           // Operacio correcte pero pendent de finalitzar
		timeout,           // S'ha produit timeout
		busy,              // Ocupat
		error,             // Error d'operacio
		errorState,        // Operacio no permesa en l'estat actual
		errorParameter,    // Error ens els parametres
		errorUnsupported   // No soportado
	};

	class Result: public SimpleResult<Results> {
        public:
            constexpr Result(Results result) :
                SimpleResult {result} {
            }
			inline bool isSuccess() const {
				return *this == Results::success;
			}
	};

	class ResultU32: public ComplexResult<Results, uint32_t> {
    public:
        constexpr ResultU32(Results result) :
            ComplexResult {result} {
        }
        constexpr ResultU32(Results result, unsigned value) :
            ComplexResult {result, value} {
        }
		inline bool isSuccess() const {
			return *this == Results::success;
		}
	};
}


#endif // __eosResults__
