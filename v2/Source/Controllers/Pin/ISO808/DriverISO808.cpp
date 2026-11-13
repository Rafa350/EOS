export module Eos.Controllers.Pin.ISO808;

import Eos.Controllers.Pin;
import Eos.Hardware.GPIO;
import Eos.Hardware.SPI;
import Eos.Result;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


export namespace eos {

    class Device_ISO808;

    class PinDriver_ISO808 final: public PinDriver {
		private:
			Device_ISO808 * const _dev;
			UInt8 const _pinMask;

		public:
			PinDriver_ISO808(Device_ISO808 *dev, UInt8 pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };

    class Device_ISO808: private NonCopyableClass {
        private:
            UInt8 _oldState;
            UInt8 _newState;

        protected:
            Device_ISO808();

        protected:
            virtual void updateImpl(UInt8 state) = 0;
            virtual bool isOKImpl() = 0;

        public:
            ~Device_ISO808() = default;

            inline void set(UInt8 pinMask) {
                _newState |= pinMask;
            }

            inline void clear(UInt8 pinMask) {
                _newState &= ~pinMask;
            }

            inline void toggle(UInt8 pinMask) {
                _newState ^= pinMask;
            }

            inline void write(UInt8 pinMask) {
            	_newState = pinMask;
            }

            inline UInt8 read() const {
            	return _newState;
            }

            void update();
            bool isOK();
    };

    class Device_ISO808_Paralel final : public Device_ISO808 {
        public:
            struct CreateParams {
                PinDevice *pinSYNC;
                PinDevice *pinLOAD;
                PinDevice *pinIN1;
                PinDevice *pinIN2;
                PinDevice *pinIN3;
                PinDevice *pinIN4;
                PinDevice *pinIN5;
                PinDevice *pinIN6;
                PinDevice *pinIN7;
                PinDevice *pinIN8;
                PinDevice *pinOUTEN;
                PinDevice *pinFAULT;
            };

        private:
			PinDevice * const _pinSYNC;
			PinDevice * const _pinLOAD;
			PinDevice * const _pinIN1;
			PinDevice * const _pinIN2;
			PinDevice * const _pinIN3;
			PinDevice * const _pinIN4;
			PinDevice * const _pinIN5;
			PinDevice * const _pinIN6;
			PinDevice * const _pinIN7;
			PinDevice * const _pinIN8;
			PinDevice * const _pinOUTEN;
			PinDevice * const _pinFAULT;

        protected:
            void updateImpl(UInt8 state) override;
            bool isOKImpl() override;

        public:
            Device_ISO808_Paralel(PinDevice *pinSYNC, PinDevice *pinLOAD, PinDevice *pinIN1, PinDevice *pinIN2,
                PinDevice *pinIN3, PinDevice *pinIN4, PinDevice *pinIN5, PinDevice *pinIN6, PinDevice *pinIN7,
                PinDevice *pinIN8, PinDevice *pinOUTEN, PinDevice *pinFAULT);
            Device_ISO808_Paralel(const CreateParams *params);

			StdResult initialize();
            void deinitialize();

			inline void enable() const {
                _pinOUTEN->set();
            }
			inline void disable() const {
                _pinOUTEN->clear();
            }
	};

    class Device_ISO808_SPI final: public Device_ISO808 {
        private:
            SPIDevice * const _devSPI;
            PinDevice * const _pinSS;
			PinDevice * const _pinOUTEN;
			PinDevice * const _pinFAULT;
            PinDevice * const _pinPGOOD;

        protected:
            void updateImpl(UInt8 state) override;
            bool isOKImpl() override;

        public:
            Device_ISO808_SPI(SPIDevice *devSPI, PinDevice *pinSS,
                PinDevice *pinOUTEN, PinDevice *pinFAULT, PinDevice *pinPGOOD);
    };
}
