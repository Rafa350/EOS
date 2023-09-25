#pragma once
#ifndef __eosPinDriver_ISO808__
#define	__eosPinDriver_ISO808__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class Driver_ISO808 final {
		private:
			using PinSYNC = ISO808_SYNC_Pin;
			using PinLOAD = ISO808_LOAD_Pin;
			using PinIN1 = ISO808_IN1_Pin;
			using PinIN2 = ISO808_IN2_Pin;
			using PinIN3 = ISO808_IN3_Pin;
			using PinIN4 = ISO808_IN4_Pin;
			using PinIN5 = ISO808_IN5_Pin;
			using PinIN6 = ISO808_IN6_Pin;
			using PinIN7 = ISO808_IN7_Pin;
			using PinIN8 = ISO808_IN8_Pin;
			using PinOUTEN = ISO808_OUTEN_Pin;
			using PinFAULT = ISO808_FAULT_Pin;

		private:
			const htl::gpio::PinHandler _pinSYNC = PinSYNC::getHandler();
			const htl::gpio::PinHandler _pinLOAD = PinLOAD::getHandler();
			const htl::gpio::PinHandler _pinIN1 = PinIN1::getHandler();
			const htl::gpio::PinHandler _pinIN2 = PinIN2::getHandler();
			const htl::gpio::PinHandler _pinIN3 = PinIN3::getHandler();
			const htl::gpio::PinHandler _pinIN4 = PinIN4::getHandler();
			const htl::gpio::PinHandler _pinIN5 = PinIN5::getHandler();
			const htl::gpio::PinHandler _pinIN6 = PinIN6::getHandler();
			const htl::gpio::PinHandler _pinIN7 = PinIN7::getHandler();
			const htl::gpio::PinHandler _pinIN8 = PinIN8::getHandler();
			const htl::gpio::PinHandler _pinOUTEN = PinOUTEN::getHandler();
			const htl::gpio::PinHandler _pinFAULT = PinFAULT::getHandler();
			uint8_t _pinState;

		public:
			Driver_ISO808();
			void initialize();
			void set(uint8_t pinNumber);
			void clear(uint8_t pinNumber);
			void toggle(uint8_t pinNumber);
			void refresh();
			void outputEnable();
			void outputDisable();

	};

	class PinDriver_ISO808 final: public PinDriver {
		private:
			Driver_ISO808 *_driver;
			uint8_t _pinNumber;
		public:
			PinDriver_ISO808(Driver_ISO808 *driver, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool state) override;
			bool read() const override;
	};
}

#endif // __eosPinDriver__ISO808__
