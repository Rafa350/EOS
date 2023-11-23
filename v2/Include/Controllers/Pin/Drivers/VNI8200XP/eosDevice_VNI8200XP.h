#pragma once
#ifndef __eosDevice_VNI8200XP__
#define __eosDevice_VNI8200XP__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


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
			enum class Result {
				ok,
				error
			};

        private:
            Device_VNI8200XP(const DeviceX_VNI8200XP&) = delete;
            Device_VNI8200XP & operator = (const DeviceX_VNI8200XP&) = delete;

        public:
    		virtual ~Device_VNI8200XP() = default;
            
            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual uint8_t read() const = 0;
			
            virtual void enable() const = 0;
			virtual void disable() const = 0;
            virtual void update() = 0;
    };


	/// \brief Clase que implementa del driver del chip VNI8200XP
    ///        amb interficie SPI
	///
    class Device_VNI8200XP_SPI: public Device_VNI8200XP {
    	private:
    		State _state;
    		uint8_t _curPinState;
            uint8_t _oldPinState;
    		htl::spi::SPIDevice *_spi;
    		htl::gpio::Pin *_pinSS;
    		htl::gpio::Pin *_pinOUTEN;

    	protected:
    		Device_VNI8200XP_SPI();

    	public:
            Result initialize(htl::spi::SPIDevice *spi, htl::gpio::Pin *pinSS, htl::gpio::Pin *pinOUTEN = nullptr);
        	
            void set(uint8_t pinMask) override;
			void clear(uint8_t pinMask) override;
			void toggle(uint8_t pinMask) override;
			void write(uint8_t pinMask, bool pinState) override;
			uint8_t read() const override;
			
            void enable() const override;
			void disable() const override;
            void update() override;
    };
    

    template <uint8_t id_>
    class DeviceX_VNI8200XP_SPI final: public Device_VNI8200XP_SPI {
        private:
            static DeviceX_VNI8200XP_SPI _instance;

        public:
            static constexpr uint8_t id = id_;
            static constexpr DeviceX_VNI8200XP_SPI *pInst = &_instance;
            static constexpr DeviceX_VNI8200XP_SPI &rInst = _instance;

        private:
            DeviceX_VNI8200XP_SPI():
            	Device_VNI8200XP_SPI() {
            }
    };

    template <uint8_t id_>
	DeviceX_VNI8200XP_SPI<id_> DeviceX_VNI8200XP_SPI<id_>::_instance;

}


#endif // __eosDevice_VNI8200XP__
