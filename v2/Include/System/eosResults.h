#pragma once
#ifndef __eosResults__
#define __eosResults__


namespace eos {

	template <typename Tag_>
	class ErrorCodeX {
		private:
			const uint8_t _value;

		private:
			ErrorCodeX& operator=(const ErrorCodeX&) = delete;
			ErrorCodeX& operator=(ErrorCodeX&&) = default;

		public:
			constexpr ErrorCodeX(uint8_t value): _value {value} {}
			constexpr ErrorCodeX(const ErrorCodeX &other): _value {other._value} {}

			constexpr explicit operator uint8_t() const { return _value; }

			inline bool operator==(ErrorCodeX other) const { return _value == other._value; }
            inline bool operator!=(ErrorCodeX other) const { return _value != other._value; }
	};

	struct ErrorCodeValues {
		static constexpr uint8_t successBaseValue = 0x00;
		static constexpr uint8_t errorBaseValue = 0x80;
	};

	template <typename Tag_>
	class ResultBaseX {
		public:
			using ErrorCode = ErrorCodeX<Tag_>;

		private:
			ErrorCodeX<Tag_> const _errorCode;

		protected:
			constexpr ResultBaseX(ErrorCode errorCode): _errorCode {errorCode} {}

		public:
			operator ErrorCode () const { return _errorCode; }

			ErrorCode errorCode() const { return _errorCode; }

			bool isSuccess() const { return (uint8_t)_errorCode < ErrorCodeValues::errorBaseValue; }
			bool isError() const { return (uint8_t)_errorCode >= ErrorCodeValues::errorBaseValue; }
			bool is(ErrorCode errorCode) const { return _errorCode == errorCode; }
			bool isNot(ErrorCode errorCode) const { return _errorCode != errorCode; }
	};

	template <typename Tag_>
	class SimpleResultX: public ResultBaseX<Tag_> {
		public:
			using ErrorCode = ErrorCodeX<Tag_>;

		public:
			constexpr SimpleResultX(ErrorCode errorCode): ResultBaseX<Tag_> {errorCode} {}
	};

	template <typename Value_, typename Tag_>
	class ComplexResultX: public ResultBaseX<Tag_> {
		public:
			using ErrorCode = ErrorCodeX<Tag_>;

		private:
			Value_ const _value;

		public:
			constexpr ComplexResultX(ErrorCode errorCode, Value_ value): ResultBaseX<Tag_> {errorCode}, _value {value} {}

			constexpr explicit operator Value_() const { return _value; }

			Value_ value() const { return _value; }
	};



	template <typename Tag_>
	class StdErrorCodesX {
		public:
			using ErrorCode = ErrorCodeX<Tag_>;

		public:
			static constexpr ErrorCode success           = ErrorCodeValues::successBaseValue + 0; // Operacio finalitzada correctament
			static constexpr ErrorCode pending           = ErrorCodeValues::successBaseValue + 1; // Operacio correcte pero pendent de finalitzar
			static constexpr ErrorCode timeout           = ErrorCodeValues::successBaseValue + 2; // S'ha produit timeout
			static constexpr ErrorCode busy              = ErrorCodeValues::successBaseValue + 3; // Ocupat
			static constexpr ErrorCode error             = ErrorCodeValues::errorBaseValue + 0;   // Error d'operacio
			static constexpr ErrorCode errorState        = ErrorCodeValues::errorBaseValue + 1;   // Operacio no permesa en l'estat actual
			static constexpr ErrorCode errorParameter    = ErrorCodeValues::errorBaseValue + 2;   // Error ens els parametres
			static constexpr ErrorCode errorUnsupported  = ErrorCodeValues::errorBaseValue + 3;   // No soportado
	};

	template <typename Tag_>
	class StdResultX: public SimpleResultX<Tag_>, StdErrorCodesX<Tag_> {
		public:
			using ErrorCodes = StdErrorCodesX<Tag_>;
			using ErrorCode = ErrorCodes::ErrorCode;
		public:
			constexpr StdResultX(ErrorCode errorCode): SimpleResultX<Tag_>(errorCode) {}
	};
	using Result = StdResultX<struct ResultTag>;

	template <typename Value_, typename Tag_>
	class StdResultUX: public ComplexResultX<Value_, Tag_>, StdErrorCodesX<Tag_> {
		public:
			using ErrorCodes = StdErrorCodesX<Tag_>;
			using ErrorCode = ErrorCodes::ErrorCode;
		public:
			constexpr StdResultUX(ErrorCode errorCode): ComplexResultX<Value_, Tag_>(errorCode, Value_ {}) {}
			constexpr StdResultUX(ErrorCode errorCode, Value_ value): ComplexResultX<Value_, Tag_>(errorCode, value) {}
	};
	using ResultU8 = StdResultUX<uint8_t, struct ResultU8Tag>;
	using ResultU16 = StdResultUX<uint16_t, struct ResultU16Tag>;
	using ResultU32 = StdResultUX<uint32_t, struct ResultU32Tag>;
}


#endif // __eosResults__
