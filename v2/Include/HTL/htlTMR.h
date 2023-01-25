#pragma once
#ifndef __htlTMR__
#define	__htlTMR__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlTMR.h"

#elif defined(EOS_PLATFORM_STM32F0) || \
	defined (EO_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htlTMR.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlTMR.h"

#endif


namespace htl {

	class ITMR {
		protected:
			virtual ~ITMR() = default;
		public:
			virtual void start() const = 0;
			virtual void stop() const = 0;
			virtual void setInterruptFunction(TMRInterruptFunction function, TMRInterruptParam param) const = 0;
			virtual void enableInterrupt(TMRInterrupt interrupt) const = 0;
			virtual bool disableInterrupt(TMRInterrupt interrupt) const = 0;
			virtual void disableInterrupts() const = 0;
			virtual bool getFlag(TMRFlag flag) const = 0;
			virtual void clearFlag(TMRFlag flag) const = 0;
			virtual void clearFlags() const = 0;
	};

	typedef ITMR *TMRHandler;

	template <typename timer_>
	class TMR final : public ITMR {
		private:
			TMR() = default;
			TMR(const TMR &) = delete;
			TMR(const TMR &&) = delete;

			TMR & operator = (const TMR &) = delete;
			TMR & operator = (const TMR &&) = delete;

		public:
			static TMRHandler instance() {
				static TMR<timer_> tmr;
				return &tmr;
			}

			void start() const override {
				timer_::start();
			}

			void stop() const override {
				timer_::stop();
			}

			void setInterruptFunction(TMRInterruptFunction function, TMRInterruptParam param) const {
				timer_::setInterruptFunction(function, param);
			}

			void enableInterrupt(TMRInterrupt interrupt) const override {

				timer_::enableInterrupt(interrupt);
			}

			bool disableInterrupt(TMRInterrupt interrupt) const override {

				return timer_::disableInterrupt(interrupt);
			}

			void disableInterrupts() const override {
				//TODO:: timer_::disableInterrupts();
			}

			bool getFlag(TMRFlag flag) const override {

				return timer_::getFlag(flag);
			}

			void clearFlag(TMRFlag flag) const override {

				timer_::clearFlag(flag);
			}

			void clearFlags() const override {
				// TODO: timer_::clearFlags();
			}
	};

	template <typename timer_>
	TMRHandler getTMR() {
		return TMR<timer_>::instance();
	}
}


#endif // __htlTMR__

