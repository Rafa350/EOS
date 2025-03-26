#pragma once
#ifndef __eosResults__
#define __eosResults__


// STD includes
//
#include <type_traits>


namespace eos {

	constexpr unsigned SUCCESS_VALUE = 0;

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

            inline bool isSuccess() const {
            	return (unsigned)_result == SUCCESS_VALUE;
            }
    };


    template <typename Enum_>
    class SimpleResult: public ResultBase<Enum_> {
    	public:
    		using EnumType = Enum_;

        public:
            constexpr SimpleResult(Enum_ result) :
                ResultBase<Enum_> {result} {
            }
    };


    template <typename Enum_, typename Value_>
    class ComplexResult: public ResultBase<Enum_> {
    	public:
    		using EnumType = Enum_;
    		using ValueType = Value_;

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
		success = SUCCESS_VALUE,  // Operacio finalitzada correctament
		pending,           // Operacio correcte pero pendent de finalitzar
		timeout,           // S'ha produit timeout
		busy,              // Ocupat
		error,             // Error d'operacio
		errorState,        // Operacio no permesa en l'estat actual
		errorParameter,    // Error ens els parametres
		errorUnsupported   // No soportado
	};

	using Result = SimpleResult<Results>;
	using ResultU8 = ComplexResult<Results, uint8_t>;
	using ResultU16 = ComplexResult<Results, uint16_t>;
	using ResultU32 = ComplexResult<Results, uint32_t>;
	using ResultI8 = ComplexResult<Results, int8_t>;
	using ResultI16 = ComplexResult<Results, int16_t>;
	using ResultI32 = ComplexResult<Results, int32_t>;
}


#endif // __eosResults__
