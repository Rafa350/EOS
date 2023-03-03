#pragma once
#ifndef __htlI2C__
#define	__htlI2C__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlI2C.h"

#elif defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
	#include "HTL/STM32/htlI2C.h"
    
#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlI2C.h"

#endif


namespace htl {

	class II2C {
		protected:
			virtual ~II2C() = default;

		public:
			virtual void write(uint8_t data) const = 0;
			virtual uint8_t read() const = 0;
			virtual void nack() const = 0;
			virtual void enable() const = 0;
			virtual void disable() const = 0;
			virtual void setInterruptFunction(I2CInterruptFunction function, I2CInterruptParam param) const = 0;
			virtual void enableInterrupt(I2CInterrupt interrupt) const = 0;
			virtual bool disableInterrupt(I2CInterrupt interrupt) const = 0;
			virtual bool isInterruptEnabled(I2CInterrupt interrupt) const = 0;
			virtual bool getFlag(I2CFlag flag) const = 0;
			virtual void clearFlag(I2CFlag flag) const = 0;
	};

	typedef II2C *I2CHandler;

	template <typename i2c_>
	class I2C final: public II2C {
		private:
			I2C() = default;
			I2C(const I2C &) = delete;
			I2C(const I2C &&) = delete;

			I2C & operator = (const I2C &) = delete;
			I2C & operator = (const I2C &&) = delete;

		public:
			static I2CHandler instance() {
				static I2C i2c;
				return &i2c;
			}

			void write(uint8_t data) const override {
				i2c_::write(data);
			}

			uint8_t read() const override {
				return i2c_::read();
			}

			void nack() const override {
				i2c_::nack();
			}

			void enable() const override {
				i2c_::enable();
			}

			void disable() const override {
				i2c_::disable();
			}

			void setInterruptFunction(I2CInterruptFunction function, I2CInterruptParam param) const override {
				i2c_::setInterruptFunction(function, param);
			}

			void enableInterrupt(I2CInterrupt interrupt) const override {
				i2c_::enableInterrupt(interrupt);
			}

			bool disableInterrupt(I2CInterrupt interrupt) const override {
				return i2c_::disableInterrupt(interrupt);
			}

			bool isInterruptEnabled(I2CInterrupt interrupt) const override {
				return i2c_::isInterruptEnabled(interrupt);
			}

			bool getFlag(I2CFlag flag) const override {
				return i2c_::getFlag(flag);
			}

			void clearFlag(I2CFlag flag) const override {
				i2c_::clearFlag(flag);
			}
	};

	template <typename i2c_>
	I2CHandler getI2C() {
		return I2C<i2c_>::instance();
	}

}


#endif // __htlI2C__


