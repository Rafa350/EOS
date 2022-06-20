#ifndef __PIC32_halSPITpl__
#define __PIC32_halSPITpl__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/PIC32/halSPI.h"
#include "HAL/PIC32/halGPIOTpl.h"


namespace eos {

	enum class SPIChannel: halSPIChannel {
		channel1 = HAL_SPI_CHANNEL_1,
#ifdef HAL_SPI_CHANNEL_2
		channel2 = HAL_SPI_CHANNEL_2,
#endif
#ifdef HAL_SPI_CHANNEL_3
		channel3 = HAL_SPI_CHANNEL_3,
#endif
#ifdef HAL_SPI_CHANNEL_4
		channel4 = HAL_SPI_CHANNEL_4,
#endif
#ifdef HAL_SPI_CHANNEL_5
		channel5 = HAL_SPI_CHANNEL_5,
#endif
#ifdef HAL_SPI_CHANNEL_6
		channel6 = HAL_SPI_CHANNEL_6
#endif
	};

	enum class SPIMode: halSPIOptions {
		mode0 = HAL_SPI_MODE_0,
		mode1 = HAL_SPI_MODE_1,
		mode2 = HAL_SPI_MODE_2,
		mode3 = HAL_SPI_MODE_3,
	};

	enum class SPISize: halSPIOptions {
		size8 = HAL_SPI_SIZE_8,
		size16 = HAL_SPI_SIZE_16
	};

	enum class SPIFirstBit: halSPIOptions {
		lsb = HAL_SPI_FIRSTBIT_LSB,
		msb = HAL_SPI_FIRSTBIT_MSB
	};

	enum class SPIClockDivider: halSPIOptions {
		clkdiv_2 = HAL_SPI_CLOCKDIV_2,
		clkdiv_4 = HAL_SPI_CLOCKDIV_4,
		clkdiv_8 = HAL_SPI_CLOCKDIV_8,
		clkdiv_16 = HAL_SPI_CLOCKDIV_16,
		clkdiv_32 = HAL_SPI_CLOCKDIV_32,
		clkdiv_64 = HAL_SPI_CLOCKDIV_64,
		clkdiv_128 = HAL_SPI_CLOCKDIV_128,
		clkdiv_256 = HAL_SPI_CLOCKDIV_256
	};

	template <SPIChannel channel>
	class SPIAdapter {
		private:
			constexpr static const int _defaultBlockTime = 1000;
			constexpr static const SPISize _defaultSize = SPISize::size8;
			constexpr static const SPIFirstBit _defaultFirstBit = SPIFirstBit::lsb;

		private:
		    halSPIData _data;
			halSPIHandler _handler;

		public:
			inline void initMaster(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_MASTER |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline void initSlave(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_SLAVE |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline void initialize(halSPIOptions options) {
				halSPISettings settings;
				settings.channel = halSPIChannel(channel);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline void setClock(SPIClockDivider clkdiv) {

			}

			inline void setISRFunction(halSPIInterruptFunction function, void* params) {

			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setSCKPin(GPIOPinAdapter<port, pin> pinAdapter) {
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setMOSIPin(GPIOPinAdapter<port, pin> pinAdapter) {
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setMISOPin(GPIOPinAdapter<port, pin> pinAdapter) {
			}

			inline void send(const uint8_t* data, int length, unsigned blockTime = _defaultBlockTime) {
				halSPISendBuffer(_handler, data, length, blockTime);
			}
	};


	typedef SPIAdapter<SPIChannel::channel1> SPI_1;
#ifdef HAL_SPI_CHANNEL_2
	typedef SPIAdapter<SPIChannel::channel2> SPI_2;
#endif
#ifdef HAL_SPI_CHANNEL_3
	typedef SPIAdapter<SPIChannel::channel3> SPI_3;
#endif
#ifdef HAL_SPI_CHANNEL_4
	typedef SPIAdapter<SPIChannel::channel4> SPI_4;
#endif
#ifdef HAL_SPI_CHANNEL_5
	typedef SPIAdapter<SPIChannel::channel5> SPI_5;
#endif
#ifdef HAL_SPI_CHANNEL_6
	typedef SPIAdapter<SPIChannel::channel6> SPI_6;
#endif

}


#endif // __cplusplus

#endif // __PIC32_halSPITpl__
