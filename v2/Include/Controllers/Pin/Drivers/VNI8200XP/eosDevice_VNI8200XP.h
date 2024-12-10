#pragma once
#ifndef __eosDevice_VNI8200XP__
#define __eosDevice_VNI8200XP__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "System/eosResults.h"


namespace eos {

	/// \brief Clase que implementa del driver del chip VNI8200XP
	///
    class Device_VNI8200XP {
		public:
			enum class State {
				reset,
				ready,
				updating
			};

        private:
            Device_VNI8200XP(const Device_VNI8200XP &) = delete;
            Device_VNI8200XP & operator = (const Device_VNI8200XP &) = delete;

        protected:
            Device_VNI8200XP() = default;

        public:
    		virtual ~Device_VNI8200XP() = default;

    		virtual Result initialize() = 0;
    		virtual void deinitialize() = 0;

            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual uint8_t read() const = 0;

            virtual void enable() const = 0;
			virtual void disable() const = 0;
            virtual Result update() = 0;
    };


	/// \brief Clase que implementa del driver del chip VNI8200XP
    ///        amb interficie SPI
	///
    class Device_VNI8200XP_SPI final: public Device_VNI8200XP {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;
            struct CreateParams {
                DevSPI *devSPI;
                Pin *pinSS;
                Pin *pinOUTEN;
            };

    	private:
    		State _state;
    		uint8_t _curPinState;
            uint8_t _oldPinState;
    		DevSPI *_devSPI;
    		Pin const * const _pinSS;
    		Pin const * const _pinOUTEN;

    	public:
    		Device_VNI8200XP_SPI(DevSPI *devSPI, Pin *pinSS, Pin *pinOUTEN = nullptr);
            Device_VNI8200XP_SPI(const CreateParams *params);

            Result initialize() override;
            void deinitialize() override;

            void set(uint8_t pinMask) override;
			void clear(uint8_t pinMask) override;
			void toggle(uint8_t pinMask) override;
			void write(uint8_t pinMask, bool pinState) override;
			uint8_t read() const override;

            void enable() const override;
			void disable() const override;
            Result update() override;

            inline State getState() const { return _state; }
            inline bool isReady() const { return _state == State::ready; }
    };

}


#endif // __eosDevice_VNI8200XP__
