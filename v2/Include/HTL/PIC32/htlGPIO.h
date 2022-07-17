#ifndef __PIC32_htlGPIO__
#define __PIC32_htlGPIO__


// EOS includes
//
#include "eos.h"


namespace htl {

    enum class GPIOPort {
        #ifdef _PORTA
            portA,
        #endif
        #ifdef _PORTB
            portB,
        #endif
        #ifdef _PORTC
            portC,
        #endif
        #ifdef _PORTD
            portD,
        #endif
        #ifdef _PORTE
            portE,
        #endif
        #ifdef _PORTF
            portF,
        #endif
        #ifdef _PORTG
            portG,
        #endif
    };

    enum class GPIOPin {
        pin0,
        pin1,
        pin2,
        pin3,
        pin4,
        pin5,
        pin6,
        pin7,
        pin8,
        pin9,
        pin10,
        pin11,
        pin12,
        pin13,
        pin14,
        pin15,
    };

    enum class GPIOPull {
        none,
        up
    };

    enum class GPIODriver {
        pushPull,
        openDrain
    };

    enum class GPIOSpeed {
        low,
        medium,
        hight,
        fast
    };

    template <GPIOPort port_, GPIOPin pin_>
	struct GPIOInfo {
		static const uint32_t addr;
		static const uint32_t pn;
        static const uint32_t cn;
        static const uint32_t an;
	};

    struct __attribute__((packed , aligned(4))) GPIORegisters {
        volatile uint32_t TRISx;
        volatile uint32_t TRISxCLR;
        volatile uint32_t TRISxSET;
        volatile uint32_t TRISxINV;
        volatile uint32_t PORTx;
        volatile uint32_t PORTxCLR;
        volatile uint32_t PORTxSET;
        volatile uint32_t PORTxINV;
        volatile uint32_t LATx;
        volatile uint32_t LATxCLR;
        volatile uint32_t LATxSET;
        volatile uint32_t LATxINV;
        volatile uint32_t ODCx;
        volatile uint32_t ODCxCLR;
        volatile uint32_t ODCxSET;
        volatile uint32_t ODCxINV;
    };

    class GPIOAdapter {
        private:
            uint32_t _addr;
            uint32_t _mask;

        public:
            GPIOAdapter(uint32_t addr, uint32_t pn):
                _addr(addr),
                _mask(1 << pn) {
            }

            GPIOAdapter(const GPIOAdapter &other) :
                _addr(other._addr),
                _mask(other._mask) {
            }

            inline void set() const {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxSET = _mask;
            }

            inline void clear() const {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxCLR = _mask;
            }

            inline void toggle() const {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxINV = _mask;
            }

            inline bool read() const {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                return (regs->PORTx & _mask) != 0;
            }
    };

    template <GPIOPort port_, GPIOPin pin_>
    class GPIO_x {
        private:
            using Info = GPIOInfo<port_, pin_>;

        public:
            constexpr static const GPIOPort port = port_;
			constexpr static const GPIOPin pin = pin_;

        private:
            constexpr static const uint32_t _addr = Info::addr;
            constexpr static const uint32_t _pn = Info::pn;
            constexpr static const uint32_t _cn = Info::cn;
            constexpr static const uint32_t _an = Info::an;

        private:
			GPIO_x() = delete;
            GPIO_x(const GPIO_x &) = delete;
			GPIO_x(const GPIO_x &&) = delete;
            ~GPIO_x() = delete;

			GPIO_x & operator = (const GPIO_x &) = delete;
			GPIO_x & operator = (const GPIO_x &&) = delete;

        public:
            inline static void initInput(
                GPIOPull pull = GPIOPull::none) {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->TRISxSET = 1 << _pn;
                if constexpr (_cn != -1) {
                    if (pull == GPIOPull::up)
                        CNPUESET = 1 << _cn;
                    else
                        CNPUECLR = 1 << _cn;
                }
                if constexpr (_an != -1)
                    AD1PCFGSET = 1 <<_an;
            }

            inline static void initOutput(
                GPIODriver driver = GPIODriver::pushPull,
                GPIOSpeed speed = GPIOSpeed::medium) {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->TRISxCLR = 1 << _pn;
                if (driver == GPIODriver::openDrain)
                    regs->ODCxSET = 1 << _pn;
                else
                    regs->ODCxCLR = 1 << _pn;
            }

            inline static void deInit() {

            }

            inline static void set() {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxSET = 1 << _pn;
            }

            inline static void clear() {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxCLR = 1 << _pn;
            }

            inline static void toggle() {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxINV = 1 << _pn;
            }

            inline static bool read() {
                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                return (regs->PORTx & (1 << _pn)) != 0;
            }

            inline static void write(bool value) {
                if (value)
                    set();
                else
                    clear();
            }
    };

    template <typename gpio_>
    const GPIOAdapter& getAdapter() {
        using Info = GPIOInfo<gpio_::port, gpio_::pin>;
        static GPIOAdapter adapter(Info::addr, Info::pn);
        return adapter;
    }

    #ifdef _PORTA
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin0> GPIO_A0;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin1> GPIO_A1;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin2> GPIO_A2;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin3> GPIO_A3;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin4> GPIO_A4;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin5> GPIO_A5;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin6> GPIO_A6;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin7> GPIO_A7;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin8> GPIO_A8;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin9> GPIO_A9;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin10> GPIO_A10;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin11> GPIO_A11;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin12> GPIO_A12;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin13> GPIO_A13;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin14> GPIO_A14;
        typedef GPIO_x<GPIOPort::portA, GPIOPin::pin15> GPIO_A15;
    #endif

    #ifdef _PORTB
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin0> GPIO_B0;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin1> GPIO_B1;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin2> GPIO_B2;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin3> GPIO_B3;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin4> GPIO_B4;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin5> GPIO_B5;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin6> GPIO_B6;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin7> GPIO_B7;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin8> GPIO_B8;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin9> GPIO_B9;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin10> GPIO_B10;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin11> GPIO_B11;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin12> GPIO_B12;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin13> GPIO_B13;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin14> GPIO_B14;
        typedef GPIO_x<GPIOPort::portB, GPIOPin::pin15> GPIO_B15;
    #endif

    #ifdef _PORTC
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin0> GPIO_C0;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin1> GPIO_C1;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin2> GPIO_C2;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin3> GPIO_C3;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin4> GPIO_C4;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin5> GPIO_C5;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin6> GPIO_C6;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin7> GPIO_C7;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin8> GPIO_C8;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin9> GPIO_C9;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin10> GPIO_C10;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin11> GPIO_C11;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin12> GPIO_C12;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin13> GPIO_C13;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin14> GPIO_C14;
        typedef GPIO_x<GPIOPort::portC, GPIOPin::pin15> GPIO_C15;
    #endif

    #ifdef _PORTD
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin0> GPIO_D0;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin1> GPIO_D1;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin2> GPIO_D2;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin3> GPIO_D3;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin4> GPIO_D4;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin5> GPIO_D5;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin6> GPIO_D6;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin7> GPIO_D7;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin8> GPIO_D8;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin9> GPIO_D9;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin10> GPIO_D10;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin11> GPIO_D11;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin12> GPIO_D12;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin13> GPIO_D13;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin14> GPIO_D14;
        typedef GPIO_x<GPIOPort::portD, GPIOPin::pin15> GPIO_D15;
    #endif

    #ifdef _PORTE
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin0> GPIO_E0;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin1> GPIO_E1;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin2> GPIO_E2;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin3> GPIO_E3;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin4> GPIO_E4;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin5> GPIO_E5;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin6> GPIO_E6;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin7> GPIO_E7;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin8> GPIO_E8;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin9> GPIO_E9;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin10> GPIO_E10;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin11> GPIO_E11;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin12> GPIO_E12;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin13> GPIO_E13;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin14> GPIO_E14;
        typedef GPIO_x<GPIOPort::portE, GPIOPin::pin15> GPIO_E15;
    #endif

    #ifdef _PORTF
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin0> GPIO_F0;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin1> GPIO_F1;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin2> GPIO_F2;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin3> GPIO_F3;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin4> GPIO_F4;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin5> GPIO_F5;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin6> GPIO_F6;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin7> GPIO_F7;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin8> GPIO_F8;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin9> GPIO_F9;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin10> GPIO_F10;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin11> GPIO_F11;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin12> GPIO_F12;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin13> GPIO_F13;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin14> GPIO_F14;
        typedef GPIO_x<GPIOPort::portF, GPIOPin::pin15> GPIO_F15;
    #endif

    #ifdef _PORTG
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin0> GPIO_G0;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin1> GPIO_G1;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin2> GPIO_G2;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin3> GPIO_G3;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin4> GPIO_G4;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin5> GPIO_G5;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin6> GPIO_G6;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin7> GPIO_G7;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin8> GPIO_G8;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin9> GPIO_G9;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin10> GPIO_G10;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin11> GPIO_G11;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin12> GPIO_G12;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin13> GPIO_G13;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin14> GPIO_G14;
        typedef GPIO_x<GPIOPort::portG, GPIOPin::pin15> GPIO_G15;
    #endif


    // PORT A ------------------------------------------------------------
	template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin0> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 0;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin1> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 1;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin2> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 2;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin3> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 3;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin4> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 4;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin5> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 5;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin6> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 6;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin7> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 7;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin8> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 8;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin9> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 9;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin10> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 10;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin11> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 11;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin12> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 12;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin13> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 13;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin14> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 14;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portA, GPIOPin::pin15> {
		constexpr static const uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 15;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    // PORT B ------------------------------------------------------------
	template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin0> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 0;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin1> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 1;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin2> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 2;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin3> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 3;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin4> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 4;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin5> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 5;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin6> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 6;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin7> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 7;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin8> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 8;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin9> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 9;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin10> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 10;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin11> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 11;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin12> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 12;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin13> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 13;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin14> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 14;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    template <>
	struct GPIOInfo<GPIOPort::portB, GPIOPin::pin15> {
		constexpr static const uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 15;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    // PORT C ------------------------------------------------------------
	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin0> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 0;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin1> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 1;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin2> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 2;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin3> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 3;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin4> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 4;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin5> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 5;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin6> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 6;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin7> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 7;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin8> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 8;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin9> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 9;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin10> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 10;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin11> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 11;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin12> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 12;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin13> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 13;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin14> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 14;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portC, GPIOPin::pin15> {
		constexpr static const uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 15;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};


    // PORT D ------------------------------------------------------------
	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin0> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 0;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin1> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 1;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin2> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 2;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin3> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 3;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin4> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 4;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin5> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 5;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin6> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 6;
        constexpr static const uint32_t cn = 15;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin7> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 7;
        constexpr static const uint32_t cn = 16;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin8> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 8;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin9> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 9;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin10> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 10;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin11> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 11;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin12> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 12;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin13> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 13;
        constexpr static const uint32_t cn = 19;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin14> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 14;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portD, GPIOPin::pin15> {
		constexpr static const uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 15;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

    // PORT F ------------------------------------------------------------
	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin0> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 0;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin1> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 1;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin2> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 2;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin3> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 3;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin4> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 4;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin5> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 5;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin6> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 6;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin7> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 7;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin8> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 8;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin9> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 9;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin10> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 10;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin11> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 11;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin12> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 12;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin13> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 13;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin14> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 14;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};

	template <>
	struct GPIOInfo<GPIOPort::portF, GPIOPin::pin15> {
		constexpr static const uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pn = 15;
        constexpr static const uint32_t cn = -1;
        constexpr static const uint32_t an = -1;
	};
}


#endif // __PIC32_htlGPIO__
