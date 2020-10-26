#ifndef __appLoop__
#define __appLoop__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "Services//eosUARTService.h"


namespace app {

	class MyAppLoopService: public eos::AppLoopService {
		private:
			UARTService* uartService;

		public:
			MyAppLoopService(eos::Application* application);

		protected:
			void onSetup() override;
			void onLoop() override;

			char getChar();
			void putChar(char ch);
			void putString(char *s);
	};
}


#endif // __appLoop__

