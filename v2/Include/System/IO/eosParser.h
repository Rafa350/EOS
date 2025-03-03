#pragma once
#ifndef __eosParser__
#define __eosParser__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

	class Parser {
		private:
			Stream * const _stream;
			char _ungetCh;

		private:
			char get();
			void unget(char ch);

		public:
			Parser(Stream *stream);

			bool parseU32(uint32_t &value);
			bool parseChar(char &value);
	};
}


#endif // __eosParser__
