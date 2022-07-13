#ifndef __PIC32_htlSPI__
#define __PIC32_htlSPI__


// EOS includes
//
#include "eos.h"
#include "HAL/PIC32/halSPI.h"
#include "HTL/PIC32/htlGPIO.h"


namespace eos {

	enum class SPIChannel: halSPIChannel {
        #ifdef HAL_SPI_CHANNEL_1
            channel1 = HAL_SPI_CHANNEL_1,
        #endif
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

	template <SPIChannel channel_>
	class SPI_x {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;
			constexpr static const SPISize _defaultSize = SPISize::size8;
			constexpr static const SPIFirstBit _defaultFirstBit = SPIFirstBit::lsb;

		private:
		    static halSPIData _data;
			static halSPIHandler _handler;

        public:
			constexpr static const SPIChannel channel = channel_;

		private:
			SPI_x() = delete;
			SPI_x(const SPI_x &) = delete;
			SPI_x(const SPI_x &&) = delete;
            ~SPI_x() = delete;
			
            SPI_x & operator = (const SPI_x &) = delete;
			SPI_x & operator = (const SPI_x &&) = delete;

		public:
			inline static void initMaster(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_MASTER |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline static void initSlave(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_SLAVE |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline static void initi(halSPIOptions options) {
				halSPISettings settings;
				settings.channel = halSPIChannel(channel);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}
            
            inline static void deInit() { 
            }

			inline static void setClock(SPIClockDivider clkdiv) {

			}

			inline static void setISRFunction(halSPIInterruptFunction function, void* params) {

			}

            template <typename gpio_>
			inline static void initSCKPin() {
                #ifdef HAL_SPI_CHANNEL_1
                    if constexpr (channel_ == SPIChannel::channel1)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi1_SCK);
                #endif
                #ifdef HAL_SPI_CHANNEL_2
                    if constexpr (channel_ == SPIChannel::channel2)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi2_SCK);
                #endif
                #ifdef HAL_SPI_CHANNEL_3
                    if constexpr (channel_ == SPIChannel::channel3)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi3_SCK);
                #endif
                #ifdef HAL_SPI_CHANNEL_4
                    if constexpr (channel_ == SPIChannel::channel4)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi4_SCK);
                #endif
                #ifdef HAL_SPI_CHANNEL_5
                    if constexpr (channel_ == SPIChannel::channel5)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi5_SCK);
                #endif
                #ifdef HAL_SPI_CHANNEL_6
                    if constexpr (channel_ == SPIChannel::channel6)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi6_SCK);
                #endif
			}

            template <typename gpio_>
			inline static void initMOSIPin() {
                #ifdef HAL_SPI_CHANNEL_1
                    if constexpr (channel_ == SPIChannel::channel1)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi1_MOSI);
                #endif                        
                #ifdef HAL_SPI_CHANNEL_2
                    if constexpr (channel_ == SPIChannel::channel2)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi2_MOSI);
                #endif
                #ifdef HAL_SPI_CHANNEL_3
                    if constexpr (channel_ == SPIChannel::channel3)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi3_MOSI);
                #endif
                #ifdef HAL_SPI_CHANNEL_4
                    if constexpr (channel_ == SPIChannel::channel4)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::spi4_MOSI);
                #endif
                #ifdef HAL_SPI_CHANEL_5
                    if constexpr (channel_ == SPIChannel::channel5)
                        mosiPin_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            mosiPin_::GPIOAlt::spi5_MOSI);
                #endif
                #ifdef HAL_SPI_CHANNEL_6
                    if constexpr (channel_ == SPIChannel::channel6)
                        mosiPin_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            mosiPin_::GPIOAlt::spi6_MOSI);
                #endif
			}

			inline static void initMISOPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi1_MISO);
#ifdef HAL_SPI_CHANNEL_2
				if constexpr (channel_ == SPIChannel::channel2)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi2_MISO);
#endif
#ifdef HAL_SPI_CHANNEL_3
				if constexpr (channel_ == SPIChannel::channel3)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi3_MISO);
#endif
#ifdef HAL_SPI_CHANNEL_4
				if constexpr (channel_ == SPIChannel::channel4)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi4_MISO);
#endif
#ifdef HAL_SPI_CHANNEL_5
				if constexpr (channel_ == SPIChannel::channel5)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi5_MISO);
#endif
#ifdef HAL_SPI_CHANNEL_6
				if constexpr (channel_ == SPIChannel::channel6)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi6_MISO);
#endif
			}

			inline void send(const uint8_t data, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, &data, sizeof(data), blockTime);
			}

			inline void send(const uint8_t *data, int size, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, data, size, blockTime);
			}
	};


    #ifdef HAL_SPI_CHANNEL_1
        typedef SPI_x<SPIChannel::channel1> SPI_1;
    #endif
    #ifdef HAL_SPI_CHANNEL_2
        typedef SPI_x<SPIChannel::channel2> SPI_2;
    #endif
    #ifdef HAL_SPI_CHANNEL_3
        typedef SPI_x<SPIChannel::channel3> SPI_3;
    #endif
    #ifdef HAL_SPI_CHANNEL_4
        typedef SPI_x<SPIChannel::channel4> SPI_4;
    #endif
    #ifdef HAL_SPI_CHANNEL_5
        typedef SPI_x<SPIChannel::channel5> SPI_5;
    #endif
    #ifdef HAL_SPI_CHANNEL_6
        typedef SPI_x<SPIChannel::channel6> SPI_6;
    #endif

}


#endif // __PIC32_halSPI_ex__
