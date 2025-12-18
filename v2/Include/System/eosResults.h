#pragma once
#ifndef __eosResults__
#define __eosResults__


namespace eos {

	template <typename Error_>
	struct ResultTraits;

	template <>
	struct ResultTraits<uint8_t> {

		using Error = uint8_t;
		using ErrorCode = uint8_t;

		static constexpr ErrorCode successLO {0x00};
		static constexpr ErrorCode successHI {0x3F};
		static constexpr ErrorCode warningLO {0x40};
		static constexpr ErrorCode warningHI {0x7F};
		static constexpr ErrorCode errorLO   {0x80};
		static constexpr ErrorCode errorHI   {0xFF};
	};

	template <>
	struct ResultTraits<uint16_t> {

		using Error = uint16_t;
		using ErrorType = uint16_t;

		static constexpr ErrorType successLO {0x0000};
		static constexpr ErrorType successHI {0x3FFF};
		static constexpr ErrorType warningLO {0x4000};
		static constexpr ErrorType warningHI {0x7FFF};
		static constexpr ErrorType errorLO   {0x8000};
		static constexpr ErrorType errorHI   {0xFFFF};
	};

	template <>
	struct ResultTraits<uint32_t> {

		using Error = uint32_t;
		using ErrorType = uint32_t;

		static constexpr ErrorType successLO {0x00000000};
		static constexpr ErrorType successHI {0x3FFFFFFF};
		static constexpr ErrorType warningLO {0x40000000};
		static constexpr ErrorType warningHI {0x7FFFFFFF};
		static constexpr ErrorType errorLO   {0x80000000};
		static constexpr ErrorType errorHI   {0xFFFFFFFF};
	};

	/// Clase que representa un resultat associat amb un codi d'error
	///
	template <typename Error_>
	class ResultBase {
		private:
			using Traits = ResultTraits<Error_>;
			using ErrorCode = typename Traits::ErrorCode;

		private:
			ErrorCode const _error;

		public:
			static constexpr ErrorCode successLO {Traits::successLO};
			static constexpr ErrorCode successHI {Traits::successHI};
			static constexpr ErrorCode warningLO {Traits::warningLO};
			static constexpr ErrorCode warningHI {Traits::warningHI};
			static constexpr ErrorCode errorLO {Traits::errorLO};
			static constexpr ErrorCode errorHI {Traits::errorHI};

		protected:
			constexpr ResultBase(ErrorCode error):
				_error {error} {
			}

		public:
			inline operator ErrorCode() const {
				return _error;
			}

			inline ErrorCode error() const {
				return _error;
			}

			inline bool isOK() const {
				return _error == successLO;
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

			inline bool is(const Error_ error) const {
				return _error == error;
			}

			inline bool isNot(const Error_ error) const {
				return _error != error;
			}
	};

	/// Clase que representa un resultat simple associat amb un codi d'error
	///
	template <typename Error_>
	class SimpleResult: public ResultBase<Error_> {
		private:
			using Traits = ResultTraits<Error_>;
			using ErrorCode = typename Traits::ErrorCode;

		public:
			constexpr SimpleResult(ErrorCode error):
				ResultBase<Error_> {error} {
			}
	};

	/// Clase que representa un resultat complex associat amb un codi d'error i a
	/// un valor de retorn.
	///
	template <typename Error_, typename Value_>
	class ComplexResult: public ResultBase<Error_> {
		private:
			using Traits = ResultTraits<Error_>;
			using ErrorCode = typename Traits::ErrorCode;

		private:
			Value_ const _value;

		public:
			constexpr ComplexResult(ErrorCode error, Value_ value):
				ResultBase<Error_> {error},
				_value {value} {
			}

			inline explicit operator Value_() const {
				return _value;
			}

			inline Value_ value() const {
				return _value;
			}
	};



	class StdErrorCodes {
		private:
			using Traits = ResultTraits<uint8_t>;

		public:
			using Error = Traits::Error;
			using ErrorCode = Traits::ErrorCode;

		public:
			static constexpr ErrorCode ok                {Traits::successLO + 0}; // Operacio finalitzada correctament
			static constexpr ErrorCode pending           {Traits::successLO + 1}; // Operacio correcte pero pendent de finalitzar
			static constexpr ErrorCode timeout           {Traits::successLO + 2}; // S'ha produit timeout
			static constexpr ErrorCode busy              {Traits::successLO + 3}; // Ocupat
			static constexpr ErrorCode error             {Traits::errorLO + 0};   // Error d'operacio
			static constexpr ErrorCode errorState        {Traits::errorLO + 1};   // Operacio no permesa en l'estat actual
			static constexpr ErrorCode errorParameter    {Traits::errorLO + 2};   // Error ens els parametres
			static constexpr ErrorCode errorUnsupported  {Traits::errorLO + 3};   // No soportado
	};

	template <typename Codes_>
	class SimpleResultCode: public SimpleResult<typename Codes_::Error>, Codes_ {
		private:
			using Error = typename Codes_::Error;
			using ErrorCode = typename Codes_::ErrorCode;

		public:
			using ErrorCodes = Codes_;

		public:
			constexpr SimpleResultCode(ErrorCode error):
				SimpleResult<Error> {error} {
			}
	};
	using Result = SimpleResultCode<StdErrorCodes>;

	template <typename Codes_, typename Value_>
	class ComplexResultCode: public ComplexResult<typename Codes_::Error, Value_>, Codes_ {
		private:
			using Error = typename Codes_::Error;
			using ErrorCode = typename Codes_::ErrorCode;

		public:
			using ErrorCodes = Codes_;

		public:
			constexpr ComplexResultCode(ErrorCode error):
				ComplexResult<Error, Value_> {error, Value_ {}} {
			}

			constexpr ComplexResultCode(ErrorCode error, Value_ value):
				ComplexResult<Error, Value_> {error, value} {
			}
	};
	using ResultU8 = ComplexResultCode<StdErrorCodes, uint8_t>;
	using ResultU16 = ComplexResultCode<StdErrorCodes, uint16_t>;
	using ResultU32 = ComplexResultCode<StdErrorCodes, uint32_t>;
}


#endif // __eosResults__
