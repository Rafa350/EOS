#pragma once
#ifndef __eosResults__
#define __eosResults__


#include <type_traits>


namespace eos {

	template <typename ErrorType_>
	struct ResultTraits;

	template <>
	struct ResultTraits<uint8_t> {

		using ErrorType = uint8_t;

		static constexpr ErrorType successLO = 0x00;
		static constexpr ErrorType successHI = 0x3F;
		static constexpr ErrorType warningLO = 0x40;
		static constexpr ErrorType warningHI = 0x7F;
		static constexpr ErrorType errorLO   = 0x80;
		static constexpr ErrorType errorHI   = 0xFF;
	};

	template <>
	struct ResultTraits<uint16_t> {

		using ErrorType = uint16_t;

		static constexpr ErrorType successLO = 0x0000;
		static constexpr ErrorType successHI = 0x3FFF;
		static constexpr ErrorType warningLO = 0x4000;
		static constexpr ErrorType warningHI = 0x7FFF;
		static constexpr ErrorType errorLO   = 0x8000;
		static constexpr ErrorType errorHI   = 0xFFFF;
	};

	template <>
	struct ResultTraits<uint32_t> {

		using ErrorType = uint32_t;

		static constexpr ErrorType successLO = 0x00000000;
		static constexpr ErrorType successHI = 0x3FFFFFFF;
		static constexpr ErrorType warningLO = 0x40000000;
		static constexpr ErrorType warningHI = 0x7FFFFFFF;
		static constexpr ErrorType errorLO   = 0x80000000;
		static constexpr ErrorType errorHI   = 0xFFFFFFFF;
	};

	/// Clase que representa un resultat associat amb un codi d'error
	///
	template <typename ErrorType_>
	class ResultBaseX {
		private:
			using Traits = ResultTraits<ErrorType_>;

		public:
			using ErrorType = Traits::ErrorType;

		private:
			ErrorType const _error;

		public:
			static constexpr ErrorType successLO = Traits::successLO;
			static constexpr ErrorType successHI = Traits::successHI;
			static constexpr ErrorType warningLO = Traits::warningLO;
			static constexpr ErrorType warningHI = Traits::warningHI;
			static constexpr ErrorType errorLO = Traits::errorLO;
			static constexpr ErrorType errorHI = Traits::errorHI;

		protected:
			constexpr ResultBaseX(ErrorType error):
				_error {error} {
			}

		public:
			inline operator ErrorType () const {
				return _error;
			}

			inline ErrorType error() const {
				return _error;
			}

			inline bool isSuccess() const {
				return (_error >= successLO) && (_error <= successHI);
			}

			inline bool isWarning() const {
				return (_error >= warningLO) && (_error <= warningHI);
			}

			inline bool isError() const {
				return (_error >= errorLO) && (_error <= errorHI);
			}

			inline bool is(const ErrorType error) const {
				return _error == error;
			}

			inline bool isNot(const ErrorType error) const {
				return _error != error;
			}
	};

	/// Clase que representa un resultat simple associat amb un codi d'error
	///
	template <typename ErrorType_>
	class SimpleResultX: public ResultBaseX<ErrorType_> {
		public:
			constexpr SimpleResultX(ErrorType_ error):
				ResultBaseX<ErrorType_> {error} {
			}
	};

	/// Clase que representa un resultat complex associat amb un codi d'error i a
	/// un valor de retorn.
	///
	template <typename ErrorType_, typename ValueType_>
	class ComplexResultX: public ResultBaseX<ErrorType_> {
		public:
			using ValueType = ValueType_;
			using ErrorType = ResultBaseX<ErrorType_>::ErrorType;

		private:
			ValueType const _value;

		public:
			constexpr ComplexResultX(ErrorType error, ValueType value):
				ResultBaseX<ErrorType_> {error},
				_value {value} {
			}

			constexpr explicit operator ValueType() const {
				return _value;
			}

			inline ValueType value() const {
				return _value;
			}
	};

	class StdErrorCodes {
		public:
			using Traits = ResultTraits<uint8_t>;
			using ErrorType = Traits::ErrorType;

		public:
			static constexpr ErrorType success           = Traits::successLO + 0; // Operacio finalitzada correctament
			static constexpr ErrorType pending           = Traits::successLO + 1; // Operacio correcte pero pendent de finalitzar
			static constexpr ErrorType timeout           = Traits::successLO + 2; // S'ha produit timeout
			static constexpr ErrorType busy              = Traits::successLO + 3; // Ocupat
			static constexpr ErrorType error             = Traits::errorLO + 0;   // Error d'operacio
			static constexpr ErrorType errorState        = Traits::errorLO + 1;   // Operacio no permesa en l'estat actual
			static constexpr ErrorType errorParameter    = Traits::errorLO + 2;   // Error ens els parametres
			static constexpr ErrorType errorUnsupported  = Traits::errorLO + 3;   // No soportado
	};

	class StdSimpleResultX: public SimpleResultX<StdErrorCodes::ErrorType> {
		public:
			constexpr StdSimpleResultX(StdErrorCodes::ErrorType error):
				SimpleResultX<StdErrorCodes::ErrorType>(error) {
			}
	};

	class StdResultX: public StdSimpleResultX, StdErrorCodes {
		public:
			using ErrorCodes = StdErrorCodes;

		public:
			constexpr StdResultX(ErrorCodes::ErrorType error):
				StdSimpleResultX(error) {
			}
	};
	using Result = StdResultX;

	template <typename ValueType_>
	class StdResultUX: public ComplexResultX<StdErrorCodes::ErrorType, ValueType_>, StdErrorCodes {
		public:
			using ErrorCodes = StdErrorCodes;

		public:
			constexpr StdResultUX(ErrorCodes::ErrorType error):
				ComplexResultX<ErrorCodes::ErrorType, ValueType_> {error, ValueType_ {}} {
			}

			constexpr StdResultUX(ErrorCodes::ErrorType error, ValueType_ value):
				ComplexResultX<ErrorCodes::ErrorType, ValueType_> {error, value} {
			}
	};
	using ResultU8 = StdResultUX<uint8_t>;
	using ResultU16 = StdResultUX<uint16_t>;
	using ResultU32 = StdResultUX<uint32_t>;
}


#endif // __eosResults__
