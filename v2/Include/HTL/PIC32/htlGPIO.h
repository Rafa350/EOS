#pragma once
#ifndef __PIC32_htlGPIO__
#define __PIC32_htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


namespace htlV2 {

    enum class GPIOPortID: uint8_t {
        A, B, C, D, E, F, G
    };
    
    enum class GPIOPinID: uint8_t {
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15
    };
    
    typedef uint16_t GPIOPinMask;
    
    enum class GPIOPull: uint8_t {
        noChange,
        none,
        up
    };

    enum class GPIODriver: uint8_t {
        noChange,
        pushPull,
        openDrain
    };

    enum class GPIOSpeed: uint8_t {
        noChange,
        low,
        medium,
        hight,
        fast
    };
    
    enum class GPIOInitPinState: uint8_t {
        noChange,
        clear,
        set
    };

    enum class GPIOPinState: uint8_t {
        clear,
        set
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
    

    class GPIOPort {
        private:
            GPIORegisters *_registers;

        protected:
            GPIOPort(GPIORegisters *registers);

        public:
            void activate();
            void deactivate();
            void reset();
            
            void initInput(GPIOPinMask mask);
            void initOutput(GPIOPinMask mask, GPIODriver driver = GPIODriver::pushPull, GPIOSpeed speed = GPIOSpeed::medium);

            inline void set(GPIOPinMask mask) { 
                _registers->LATxSET = mask; 
            }
            inline void set(GPIOPinID pinID) { 
                _registers->LATxSET = 1 << (int)pinID; 
            }
            
            inline void clear(GPIOPinMask mask) { 
                _registers->LATxCLR = mask; 
            }
            inline void clear(GPIOPinID pinID) { 
                _registers->LATxCLR = 1 << (int)pinID; 
            }
            
            inline void toggle(GPIOPinMask mask) { 
                _registers->LATxINV = mask; 
            }
            inline void toggle(GPIOPinID pinID) { 
                _registers->LATxINV = 1 << (int)pinID; 
            }
            
            inline GPIOPinMask read() { 
                return _registers->PORTx; 
            }
            inline GPIOPinState read(GPIOPinID pinID) {
                return (_registers->PORTx & (1 << (int)pinID)) ? GPIOPinState::set : GPIOPinState::clear;
            }
            
            inline void write(GPIOPinMask mask) { 
                _registers->LATx = mask; 
            }            
            inline void write(GPIOPinMask clearMask, GPIOPinMask setMask) {
                uint16_t r = _registers->PORTx;
                r &= ~clearMask;
                r |= setMask;
                _registers->LATx = r;
            }
            inline void write(GPIOPinID pinID, GPIOPinState state) {
                if (state == GPIOPinState::set)
                    _registers->LATxSET = 1 << (int) pinID;
                else
                    _registers->LATxCLR = 1 << (int) pinID;
            }
    };

    typedef GPIOPort *GPIOPortHandler;
        
    template <GPIOPortID>
    struct GPIOInfo {                
    };   

    template <GPIOPortID portID_>
    class GPIOPort_x final: public GPIOPort {
        private:
            using Info = GPIOInfo<portID_>;
        private:
            static constexpr uint32_t _regAddr = Info::regAddr;
        protected:
            GPIOPort_x(): 
                GPIOPort(reinterpret_cast<GPIORegisters*>(_regAddr)) {
            }
        public:
            static GPIOPortHandler getHandler() {
                static GPIOPort_x port;
                return &port;
            }
    };

    typedef GPIOPort_x<GPIOPortID::A> GPIO_A;
    typedef GPIOPort_x<GPIOPortID::B> GPIO_B;
    typedef GPIOPort_x<GPIOPortID::C> GPIO_C;
    typedef GPIOPort_x<GPIOPortID::D> GPIO_D;
    typedef GPIOPort_x<GPIOPortID::E> GPIO_E;
    typedef GPIOPort_x<GPIOPortID::F> GPIO_F;
    typedef GPIOPort_x<GPIOPortID::G> GPIO_G;

    
    class GPIOPin {
        private:
            GPIORegisters *_registers;
            GPIOPinMask _pinMask;
            
        protected:
            GPIOPin(GPIORegisters *registers, GPIOPinID pinID);
            
        public :
            void initInput();
            void initOutput(GPIODriver driver = GPIODriver::pushPull, GPIOSpeed speed = GPIOSpeed::medium, GPIOInitPinState state = GPIOInitPinState::noChange);

            inline void set() {
                _registers->LATxSET = _pinMask; 
            }
            
            inline void clear() {
                _registers->LATxCLR = _pinMask; 
            }
            
            inline void toggle() {
                _registers->LATxINV = _pinMask; 
            }
            
            inline GPIOPinState read() {
                return _registers->PORTx & _pinMask ? GPIOPinState::set : GPIOPinState::clear;
            }
            
            inline void write(GPIOPinState state) {
                if (state == GPIOPinState::set)
                    _registers->LATxSET = _pinMask;
                else
                    _registers->LATxCLR = _pinMask;
            }
    };
    
    typedef GPIOPin *GPIOPinHandler;
    
    template <GPIOPortID portID_, GPIOPinID pinID_>
    class GPIOPin_x: public GPIOPin {
        private:
            using Info = GPIOInfo<portID_>;
        private:
            static constexpr uint32_t _regAddr = Info::regAddr;
        protected:
            GPIOPin_x(): 
                GPIOPin(reinterpret_cast<GPIORegisters*>(_regAddr), pinID_) {
            }
        public:
            static GPIOPinHandler getHandler() {
                static GPIOPin_x pin;
                return &pin;
            }
    };
    
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_0> GPIO_A0;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_1> GPIO_A1;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_2> GPIO_A2;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_3> GPIO_A3;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_4> GPIO_A4;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_5> GPIO_A5;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_6> GPIO_A6;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_7> GPIO_A7;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_8> GPIO_A8;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_9> GPIO_A9;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_10> GPIO_A10;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_11> GPIO_A11;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_12> GPIO_A12;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_13> GPIO_A13;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_14> GPIO_A14;
    typedef GPIOPin_x<GPIOPortID::A, GPIOPinID::_15> GPIO_A15;
    
    template <>
    struct GPIOInfo<GPIOPortID::A> {
        static constexpr uint32_t regAddr = _PORTA_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::B> {
        static constexpr uint32_t regAddr = _PORTB_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::C> {
        static constexpr uint32_t regAddr = _PORTC_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::D> {
        static constexpr uint32_t regAddr = _PORTD_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::E> {
        static constexpr uint32_t regAddr = _PORTE_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::F> {
        static constexpr uint32_t regAddr = _PORTF_BASE_ADDRESS - 0x10;
    };
    template <>
    struct GPIOInfo<GPIOPortID::G> {
        static constexpr uint32_t regAddr = _PORTG_BASE_ADDRESS - 0x10;
    };
    
 }


namespace htl {

    enum class GPIOPort {
        #ifdef _PORTA
            A,
        #endif
        #ifdef _PORTB
            B,
        #endif
        #ifdef _PORTC
            C,
        #endif
        #ifdef _PORTD
            D,
        #endif
        #ifdef _PORTE
            E,
        #endif
        #ifdef _PORTF
            F,
        #endif
        #ifdef _PORTG
            G,
        #endif
    };

    enum class GPIOPin {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15
    };

    enum class GPIOPull {
        noChange,
        none,
        up
    };

    enum class GPIODriver {
        noChange,
        pushPull,
        openDrain
    };

    enum class GPIOSpeed {
        noChange,
        low,
        medium,
        hight,
        fast
    };

    enum class GPIOState {
        clear,
        set
    };

    template <GPIOPort>
    struct GPIOPortTrait {
    };

    template <GPIOPort, GPIOPin>
	struct GPIOPinTrait {
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

    template <GPIOPort port_, GPIOPin pin_>
    class GPIO_x {
        private:
            using PortTrait = GPIOPortTrait<port_>;
            using PinTrait = GPIOPinTrait<port_, pin_>;

        public:
            static constexpr GPIOPort port = port_;
			static constexpr GPIOPin pin = pin_;

        private:
            static constexpr uint32_t _addr = PortTrait::addr;
            static constexpr uint32_t _pn = PinTrait::pn;
            static constexpr uint32_t _cn = PinTrait::cn;
            static constexpr uint32_t _an = PinTrait::an;

        private:
			GPIO_x() = delete;
            GPIO_x(const GPIO_x &) = delete;
			GPIO_x(const GPIO_x &&) = delete;
            ~GPIO_x() = delete;

			GPIO_x & operator = (const GPIO_x &) = delete;
			GPIO_x & operator = (const GPIO_x &&) = delete;

        public:
            /// \brief Inicialitza un pin com entrada.
            /// \param pull: Les opcions pull.
            ///
            static void initInput(
                GPIOPull pull = GPIOPull::none) {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);

                regs->TRISxSET = 1 << _pn;

                if constexpr (_cn != -1) {
                    if (pull != GPIOPull::noChange) {
                        if (pull == GPIOPull::up)
                            CNPUESET = 1 << _cn;
                        else
                            CNPUECLR = 1 << _cn;
                    }
                }

                // Configura com a entrada digital, si s'escau
                //
                if constexpr (_an != -1)
                    AD1PCFGSET = 1 <<_an;
            }

            /// \brief Inicialitza un pin com sortida.
            /// \param driver: Les opcions del driver.
            /// \param speed: Les opcions de velocitat.
            ///
            static void initOutput(
                GPIODriver driver = GPIODriver::pushPull,
                GPIOSpeed speed = GPIOSpeed::medium) {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);

                regs->TRISxCLR = 1 << _pn;

                if (driver != GPIODriver::noChange) {
                    if (driver == GPIODriver::openDrain)
                        regs->ODCxSET = 1 << _pn;
                    else
                        regs->ODCxCLR = 1 << _pn;
                }
            }

            /// \bried Desinicialitza el pin.
            ///
            inline static void deinitialize() {

            }

            /// \brief Situa el pin a estat ON
            ///
            inline static void set() {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxSET = 1 << _pn;
            }

            /// \brief Situa el pin a estat OFF
            ///
            inline static void clear() {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxCLR = 1 << _pn;
            }

            /// \brief Canvia l'estat del pin
            ///
            inline static void toggle() {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                regs->LATxINV = 1 << _pn;
            }

            /// \brief  Llegeix l'estat del pin.
            /// \return L'estat del pin
            ///
            inline static GPIOState read() {

                GPIORegisters *regs = reinterpret_cast<GPIORegisters*>(_addr);
                return (regs->PORTx & (1 << _pn)) ? GPIOState::set : GPIOState::clear;
            }

            /// \brief Escriu l'estat del pin.
            /// \param state: EL nou estat.
            ///
            inline static void write(
                GPIOState value) {

                if (value == GPIOState::set)
                    set();
                else
                    clear();
            }
    };


    #ifdef _PORTA
        typedef GPIO_x<GPIOPort::A, GPIOPin::_0> GPIO_A0;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_1> GPIO_A1;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_2> GPIO_A2;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_3> GPIO_A3;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_4> GPIO_A4;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_5> GPIO_A5;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_6> GPIO_A6;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_7> GPIO_A7;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_8> GPIO_A8;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_9> GPIO_A9;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_10> GPIO_A10;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_11> GPIO_A11;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_12> GPIO_A12;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_13> GPIO_A13;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_14> GPIO_A14;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_15> GPIO_A15;
    #endif

    #ifdef _PORTB
        typedef GPIO_x<GPIOPort::B, GPIOPin::_0> GPIO_B0;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_1> GPIO_B1;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_2> GPIO_B2;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_3> GPIO_B3;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_4> GPIO_B4;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_5> GPIO_B5;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_6> GPIO_B6;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_7> GPIO_B7;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_8> GPIO_B8;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_9> GPIO_B9;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_10> GPIO_B10;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_11> GPIO_B11;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_12> GPIO_B12;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_13> GPIO_B13;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_14> GPIO_B14;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_15> GPIO_B15;
    #endif

    #ifdef _PORTC
        typedef GPIO_x<GPIOPort::C, GPIOPin::_0> GPIO_C0;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_1> GPIO_C1;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_2> GPIO_C2;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_3> GPIO_C3;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_4> GPIO_C4;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_5> GPIO_C5;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_6> GPIO_C6;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_7> GPIO_C7;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_8> GPIO_C8;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_9> GPIO_C9;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_10> GPIO_C10;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_11> GPIO_C11;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_12> GPIO_C12;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_13> GPIO_C13;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_14> GPIO_C14;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_15> GPIO_C15;
    #endif

    #ifdef _PORTD
        typedef GPIO_x<GPIOPort::D, GPIOPin::_0> GPIO_D0;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_1> GPIO_D1;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_2> GPIO_D2;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_3> GPIO_D3;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_4> GPIO_D4;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_5> GPIO_D5;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_6> GPIO_D6;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_7> GPIO_D7;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_8> GPIO_D8;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_9> GPIO_D9;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_10> GPIO_D10;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_11> GPIO_D11;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_12> GPIO_D12;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_13> GPIO_D13;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_14> GPIO_D14;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_15> GPIO_D15;
    #endif

    #ifdef _PORTE
        typedef GPIO_x<GPIOPort::E, GPIOPin::_0> GPIO_E0;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_1> GPIO_E1;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_2> GPIO_E2;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_3> GPIO_E3;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_4> GPIO_E4;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_5> GPIO_E5;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_6> GPIO_E6;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_7> GPIO_E7;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_8> GPIO_E8;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_9> GPIO_E9;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_10> GPIO_E10;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_11> GPIO_E11;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_12> GPIO_E12;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_13> GPIO_E13;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_14> GPIO_E14;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_15> GPIO_E15;
    #endif

    #ifdef _PORTF
        typedef GPIO_x<GPIOPort::F, GPIOPin::_0> GPIO_F0;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_1> GPIO_F1;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_2> GPIO_F2;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_3> GPIO_F3;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_4> GPIO_F4;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_5> GPIO_F5;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_6> GPIO_F6;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_7> GPIO_F7;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_8> GPIO_F8;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_9> GPIO_F9;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_10> GPIO_F10;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_11> GPIO_F11;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_12> GPIO_F12;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_13> GPIO_F13;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_14> GPIO_F14;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_15> GPIO_F15;
    #endif

    #ifdef _PORTG
        typedef GPIO_x<GPIOPort::G, GPIOPin::_0> GPIO_G0;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_1> GPIO_G1;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_2> GPIO_G2;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_3> GPIO_G3;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_4> GPIO_G4;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_5> GPIO_G5;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_6> GPIO_G6;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_7> GPIO_G7;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_8> GPIO_G8;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_9> GPIO_G9;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_10> GPIO_G10;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_11> GPIO_G11;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_12> GPIO_G12;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_13> GPIO_G13;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_14> GPIO_G14;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_15> GPIO_G15;
    #endif


    #ifdef _PORTA
        template<>
        struct GPIOPortTrait<GPIOPort::A> {
            static constexpr uint32_t addr = _PORTA_BASE_ADDRESS - 0x10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };
    #endif

    #ifdef _PORTB
        template<>
        struct GPIOPortTrait<GPIOPort::B> {
            static constexpr uint32_t addr = _PORTB_BASE_ADDRESS - 0x10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };
    #endif

    #ifdef _PORTC
        template<>
        struct GPIOPortTrait<GPIOPort::C> {
            static constexpr uint32_t addr = _PORTC_BASE_ADDRESS - 0x10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };
    #endif

    #ifdef _PORTD
        template<>
        struct GPIOPortTrait<GPIOPort::D> {
            static constexpr uint32_t addr = _PORTD_BASE_ADDRESS - 0x10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
            static constexpr uint32_t cn = -1;
            static const uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
            static constexpr uint32_t cn = 15;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
            static constexpr uint32_t cn = 16;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
            static constexpr uint32_t cn = 19;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };
    #endif

    #ifdef _PORTE
        template<>
        struct GPIOPortTrait<GPIOPort::E> {
            static constexpr uint32_t addr = _PORTE_BASE_ADDRESS - 0x10;
        };
    #endif

    #ifdef _PORTF
        template<>
        struct GPIOPortTrait<GPIOPort::F> {
            static constexpr uint32_t addr = _PORTF_BASE_ADDRESS - 0x10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
            static constexpr uint32_t cn = -1;
            static constexpr uint32_t an = -1;
        };
    #endif
}


#endif // __PIC32_htlGPIO__
