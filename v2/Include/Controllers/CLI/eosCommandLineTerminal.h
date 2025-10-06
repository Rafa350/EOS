#pragma once
#ifndef __eosCommandLineTerminal__
#define __eosCommandLineTerminal__


// EOS includes
//
#include "eos.h"


namespace eos {

	class CommandLineTerminal final {
		public:
			unsigned ReadLine(char *rxBuffer, unsigned rxBufferSize);
			void WriteLine(const char *txBuffer, unsigned length);
	};
}


#endif // __eosCommandLineTerminal__
