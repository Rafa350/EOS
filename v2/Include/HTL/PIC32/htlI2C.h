#ifndef __PIC32_htlI2C__
#define __PIC32_htlI2C__


namespace htl {

    enum class I2CChannel {
        #ifdef _I2C1
            channel1 = HAL_I2C_CHANNEL_1,
        #endif
        #ifdef _I2C2
            channel2 = HAL_I2C_CHANNEL_2,
        #endif
        #ifdef _I2C3
            channel3 = HAL_I2C_CHANNEL_3,
        #endif
        #ifdef _I2C4
            channel4 = HAL_I2C_CHANNEL_4,
        #endif
        #ifdef _I2C5
            channel5 = HAL_I2C_CHANNEL_5
        #endif
    };

    template <I2CChannel channel_>
    struct I2CInfo {
        static const uint32_t addr;
    };

    template <I2CChannel channel_>
    class I2C_x {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;

		public:
			constexpr static const I2CChannel channel = channel_;

        private:
            constexpr static const uint32_t _addr = I2CInfo<channel_>::addr;

        private:
			static halI2CHandler _handler;
			static halI2CData _data;

		private:
			I2C_x() = delete;
			I2C_x(const I2CModule &) = delete;
			I2C_x(const I2CModule &&) = delete;
            ~I2C() = delete;

            I2C_x & operator = (const I2C_x &) = delete;
			I2C_x & operator = (const I2C_x &&) = delete;

		public:
			inline static I2CResult initMaster() {
				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}

			inline static I2CResult enable() {
				return I2CResult(halI2CEnable(_handler));
			}

			inline static I2CResult disable() {
				return I2CResult(halI2CDisable(_handler));
			}

			inline static I2CResult send(uint8_t addr, const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterSend(_handler, addr, data, size, blockTime));
			}

			inline static I2CResult receive(uint8_t addr, void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterReceive(_handler, addr, data, size, blockTime));
			}

			inline static void initSCLPin() {
			}

			inline static void initSDAPin() {
			}
    };


    #ifdef _I2C1
        using I2C_1 = I2C_x<I2CChannel::channel1;
    #endif
    #ifdef _I2C2
        using I2C_2 = I2C_x<I2CChannel::channel2;
    #endif


    #ifdef _I2C1
        template <>
        struct I2CInfo<HAL_I2C_CHANNEL_1> {
            static const uint32_t addr = I2C1_BASE_ADDRESS;
        };
    #endif

    #ifdef _I2C1
        template <>
        struct I2CInfo<HAL_I2C_CHANNEL_2> {
            static const uint32_t addr = I2C2_BASE_ADDRESS;
        };
    #endif
}


#endif // __PIC32_htlI2C__

