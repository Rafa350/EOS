#ifndef __STM32_halSPITpl__
#define __STM32_halSPITpl__


#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"


namespace eos {

	template <SPIChannel channel>
	class SPIAdapter {
		private:
		    SPIData _spiData;
			SPIHandler _spiHandler;
		public:
			inline void initialize(SPIOptions options) {
				SPISettings settings;
				settings.channel = channel;
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_spiHandler = halSPIInitialize(&_spiData, &settings);
			}

			inline void send(const uint8_t* data, int length) {
				halSPISendBuffer(_spiHandler, data, length);
			}
	};
}


#endif // __STM32_halSPITpl__
