#ifndef __PIC32_halI2C_ex__
#define __PIC32_halI2C_ex__


namespace eos {

    enum class I2cChannel {
        channel1 = HAL_I2C_CHANNEL_1,
        channel2 = HAL_I2C_CHANNEL_2,
        channel3 = HAL_I2C_CHANNEL_3,
        channel4 = HAL_I2C_CHANNEL_4,
        channel5 = HAL_I2C_CHANNEL_5
    };

    template <I2CChannel channel_>
    struct I2CModuleInfo {
        static const uint32_t baseAddr;
    };

    template <I2CChannel channel_, typename sclPin_, typename sdaPin_, bool initPins_ = true>
    class I2CModule {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;

		public:
			constexpr static const I2CChannel channel = channel_;

        private:
            constexpr static const uint32_t _baseAddr = I2CModuleInfo<channel_>::baseAddr;

        private:
			halI2CHandler _handler;
			halI2CData _data;

		private:
			I2CModule() = default;

			I2CModule(const I2CModule &) = delete;
			I2CModule(const I2CModule &&) = delete;

            I2CModule & operator = (const I2CModule &) = delete;
			I2CModule & operator = (const I2CModule &&) = delete;

		public:
			inline static auto & instance() {
				static I2CModule module;
				return module;
			}

			inline I2CResult initMaster() {

				if constexpr (initPins_) {
					initSCLPin();
					initSDAPin();
				}

				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}

			inline I2CResult enable() {
				return I2CResult(halI2CEnable(_handler));
			}

			inline I2CResult disable() {
				return I2CResult(halI2CDisable(_handler));
			}

			inline I2CResult send(uint8_t addr, const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterSend(_handler, addr, data, size, blockTime));
			}

			inline I2CResult receive(uint8_t addr, void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterReceive(_handler, addr, data, size, blockTime));
			}

			inline static void initSCLPin() {
			}

			inline static void initSDAPin() {
			}
    };


    template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_1 = I2CModule<I2CChannel::channel1, sclPin_, sdaPin_, initPins_>;

	template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_2 = I2CModule<I2CChannel::channel2, sclPin_, sdaPin_, initPins_>;


    // I2C 1
    template <>
    struct I2CModuleInfo<HAL_I2C_CHANNEL_1> {
        static const uint32_t baseAddr = I2C1_BASE_ADDRESS;
    };

    // I2C 2
    template <>
    struct I2CModuleInfo<HAL_I2C_CHANNEL_2> {
        static const uint32_t baseAddr = I2C2_BASE_ADDRESS;
    };
}


#endif // __PIC32_halI2C_ex__

