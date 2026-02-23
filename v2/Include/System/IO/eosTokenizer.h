#pragma once
#ifndef __eosTokenizer__
#define __eosTokenizer__


namespace eos {
	
	class Tokenizer {
		public:
			enum class Type {
				none,
				word,
				singleQuotedtext,
				doubleQuotedText,
				space,
				integer,
				real,
				boolean
			};
			enum class Result {
				ok,
				pending,
				error
			};
			
		private:
			uint8_t _state;
			uint8_t _tokenLen;
			uint8_t _token[10];
			
		private:
			static bool isSpace(uint8_t u) const;
			static bool isDigit(uint8_t u) const;
			static bool isLeter(uint8_t u) const;
			static bool isSeparator(uint8_t u) const;
			static bool isEOF(uint8_t u) const;
			
		public:
			Tokenizer(const uint8_t *text, unsigned textLength);
			
			Result parse(uint8_t ch);
			
	};
}


#endif // __eosTokenizer__

