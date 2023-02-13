#pragma once
#ifndef __htlGPIO__
#define	__htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlGPIO.h"

#elif defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
	#include "HTL/STM32/htlGPIO.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlGPIO.h"

#endif


namespace htl {

    class IGPIO {
        protected:
            virtual ~IGPIO() = default;
        public:
            virtual void initInput(GPIOPull pull = GPIOPull::none) const = 0;
            virtual void initOutput(GPIODriver driver, GPIOSpeed speed = GPIOSpeed::medium) const = 0;
#if defined(EOS_PLATFORM_STM32)
            virtual void initAlt(GPIODriver driver, GPIOSpeed speed, GPIOAlt alt) const = 0;
#endif
            virtual void set() const = 0;
            virtual void clear() const = 0;
            virtual void toggle() const = 0;
            virtual GPIOState read() const = 0;
            virtual void write(GPIOState state) const = 0;
    };

    typedef IGPIO *GPIOHandler;

    template <typename gpio_>
    class GPIO final: public IGPIO {
        private:
            GPIO() = default;
            GPIO(const GPIO &) = delete;
            GPIO(const GPIO &&) = delete;

			GPIO & operator = (const GPIO &) = delete;
			GPIO & operator = (const GPIO &&) = delete;

        public:
            static GPIOHandler instance() {
                static GPIO<gpio_> gpio;
                return &gpio;
            }

            void initInput(GPIOPull pull = GPIOPull::none) const override {
            	gpio_::initInput(pull);
            }

            void initOutput(GPIODriver driver, GPIOSpeed speed = GPIOSpeed::medium) const override {
            	gpio_::initOutput(driver, speed);
            }

#if defined(EOS_PLATFORM_STM32)
            void initAlt(GPIODriver driver, GPIOSpeed speed, GPIOAlt alt) const override {
            	gpio_::initAlt(driver, speed, alt);
            }
#endif

            void set() const override {
                gpio_::set();
            }

            void clear() const override {
                gpio_::clear();
            }

            void toggle() const override {
                gpio_::toggle();
            };

            GPIOState read() const override {
                return gpio_::read();
            }

            void write(GPIOState state) const override {
                return gpio_::write(state);
            }
    };

    template <typename gpio_>
    inline GPIOHandler getGPIO() {
        return GPIO<gpio_>::instance();
    }
}


#endif // __htlGPIO__

