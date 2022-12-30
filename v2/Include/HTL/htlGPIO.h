#pragma once
#ifndef __htlGPIO__
#define	__htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlGPIO.h"

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htlGPIO.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlGPIO.h"

#endif


namespace htl {

    class IGPIO {
        protected:
            virtual ~IGPIO() = default;
        public:
            virtual void set() const = 0;
            virtual void clear() const = 0;
            virtual void toggle() const = 0;
            virtual bool read() const = 0;
            virtual void write(bool) const = 0;
    };

    typedef IGPIO *GPIOHandler;

    template <typename gpio_>
    class GPIO: public IGPIO {
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

            void set() const override {
                gpio_::set();
            }

            void clear() const override {
                gpio_::clear();
            }

            void toggle() const override {
                gpio_::toggle();
            };

            bool read() const override {
                return gpio_::read();
            }

            void write(bool s) const override {
                return gpio_::write(s);
            }
    };

    template <typename gpio_>
    inline GPIOHandler getGPIO() {
        return GPIO<gpio_>::instance();
    }
}


#endif // __htlGPIO__

