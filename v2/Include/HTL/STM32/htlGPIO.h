#pragma once
/// \file      halGPIO_ex.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO module manager.
/// \addtogroup HTL HAL Template Library
/// @{
/// \addtogroup HTL_STM32 STM32
/// @{
/// \defgroup HTL_STM32_GPIO GPIO
/// @{
#ifndef __STM32_htlGPIO__
#define __STM32_htlGPIO__


// EOS includes
//
#include "eos.h"


namespace htl {

    /// \brief GPIO port identifiers.
    enum class GPIOPort {
        #ifdef GPIOA_BASE
            portA,
        #endif
        #ifdef GPIOB_BASE
            portB,
        #endif
        #ifdef GPIOC_BASE
            portC,
        #endif
        #ifdef GPIOD_BASE
            portD,
        #endif
        #ifdef GPIOE_BASE
            portE,
        #endif
        #ifdef GPIOF_BASE
            portF,
        #endif
        #ifdef GPIOG_BASE
            portG,
        #endif
        #ifdef GPIOH_BASE
            portH,
        #endif
        #ifdef GPIOI_BASE
            portI,
        #endif
        #ifdef GPIOJ_BASE
            portJ,
        #endif
        #ifdef GPIOK_BASE
            portK,
        #endif
    };

    /// \brief GPIO Pin identifiers.
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
        pin15
    };

    /// \brief GPIO Pull up/down mode identifier.
    enum class GPIOPull {
    	noChange,
        none,
        up,
        down
    };

    /// \brief GPIO Driver type identifiers.
    enum class GPIODriver {
    	noChange,
        pushPull,
        openDrain
    };

    /// \brief GPIO Speed identifier.
    enum class GPIOSpeed {
    	noChange,
        low,
        medium,
        high,
        fast
    };

    void GPIO_initInput(GPIO_TypeDef*, uint32_t, GPIOPull);
    void GPIO_initOutput(GPIO_TypeDef*, uint32_t, GPIODriver, GPIOSpeed);
    void GPIO_initAlt(GPIO_TypeDef*, uint32_t, GPIODriver, GPIOSpeed, unsigned);
    void GPIO_deInit(GPIO_TypeDef*, uint32_t);

    template <GPIOPort>
    struct GPIOPortTrait {
    };

    template <GPIOPort port_, GPIOPin pin_>
    struct GPIOPinTrait {
    };

    /// \class GPIO_x
    /// \brief Adapter class for gpio pins
    ///
    template <GPIOPort port_, GPIOPin pin_>
    class GPIO_x {
        public:
            using GPIOAlt = typename GPIOPinTrait<port_, pin_>::GPIOAlt;

        private:
            using PortTrait = GPIOPortTrait<port_>;
            using PinTrait = GPIOPinTrait<port_, pin_>;
            constexpr static const uint32_t _addr = PortTrait::addr;
            constexpr static const uint32_t _pn = PinTrait::pn;

        public:
            constexpr static const GPIOPort port = port_;
            constexpr static const GPIOPin pin = pin_;

        private:
            GPIO_x() = delete;
            GPIO_x(const GPIO_x &) = delete;
            GPIO_x(const GPIO_x &&) = delete;
            ~GPIO_x() = delete;

            GPIO_x & operator = (const GPIO_x &) = delete;
            GPIO_x & operator = (const GPIO_x &&) = delete;

        public:
            static void initInput(
            	GPIOPull pull = GPIOPull::none) {

                GPIO_initInput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr), 
                    _pn,
                    pull);
            }

            static void initOutput(
            	GPIODriver driver,
				GPIOSpeed speed = GPIOSpeed::medium) {

            	GPIO_initOutput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn,
                    driver,
                    speed);
            }

            static void initAlt(
            	GPIODriver driver,
				GPIOSpeed speed,
				GPIOAlt alt) {
                
            	GPIO_initAlt(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn,
                    driver,
                    speed,
                    unsigned(alt));
            }

            inline static void deInit() {
            	GPIO_deInit(
            		reinterpret_cast<GPIO_TypeDef*>(_addr),
					_pn);
            }

            /// \brief Set pin to ON state.
            ///
            inline static void set() {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << _pn;
            }

            /// \brief Set pin to OFF state.
            ///
            inline static void clear() {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << (_pn + 16);
            }

            /// \brief Toggle pin state.
            ///
            inline static void toggle() {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->ODR ^= 1 << _pn;
            }

            /// \brief Read pin state
            /// \return Pin state.
            ///
            inline static bool read() {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                return regs->IDR & (1 << _pn);
            }

            /// \brief Write pin state.
            /// \param b: State to write.
            ///
            inline static void write(bool s) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << (_pn + (s ? 0 : 16));
            }
    };


    #ifdef GPIOA_BASE
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

    #ifdef GPIOB_BASE
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

    #ifdef GPIOC_BASE
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

    #ifdef GPIOD_BASE
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

    #ifdef GPIOE_BASE
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

    #ifdef GPIOF_BASE
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

    #ifdef GPIOG_BASE
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

    #ifdef GPIOH_BASE
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin0> GPIO_H0;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin1> GPIO_H1;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin2> GPIO_H2;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin3> GPIO_H3;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin4> GPIO_H4;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin5> GPIO_H5;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin6> GPIO_H6;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin7> GPIO_H7;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin8> GPIO_H8;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin9> GPIO_H9;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin10> GPIO_H10;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin11> GPIO_H11;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin12> GPIO_H12;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin13> GPIO_H13;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin14> GPIO_H14;
        typedef GPIO_x<GPIOPort::portH, GPIOPin::pin15> GPIO_H15;
    #endif

    #ifdef GPIOI_BASE
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin0> GPIO_I0;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin1> GPIO_I1;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin2> GPIO_I2;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin3> GPIO_I3;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin4> GPIO_I4;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin5> GPIO_I5;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin6> GPIO_I6;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin7> GPIO_I7;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin8> GPIO_I8;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin9> GPIO_I9;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin10> GPIO_I10;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin11> GPIO_I11;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin12> GPIO_I12;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin13> GPIO_I13;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin14> GPIO_I14;
        typedef GPIO_x<GPIOPort::portI, GPIOPin::pin15> GPIO_I15;
    #endif

    #ifdef GPIOJ_BASE
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin0> GPIO_J0;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin1> GPIO_J1;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin2> GPIO_J2;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin3> GPIO_J3;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin4> GPIO_J4;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin5> GPIO_J5;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin6> GPIO_J6;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin7> GPIO_J7;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin8> GPIO_J8;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin9> GPIO_J9;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin10> GPIO_J10;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin11> GPIO_J11;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin12> GPIO_J12;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin13> GPIO_J13;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin14> GPIO_J14;
        typedef GPIO_x<GPIOPort::portJ, GPIOPin::pin15> GPIO_J15;
    #endif

    #ifdef GPIOK_BASE
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin0> GPIO_K0;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin1> GPIO_K1;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin2> GPIO_K2;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin3> GPIO_K3;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin4> GPIO_K4;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin5> GPIO_K5;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin6> GPIO_K6;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin7> GPIO_K7;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin8> GPIO_K8;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin9> GPIO_K9;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin10> GPIO_K10;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin11> GPIO_K11;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin12> GPIO_K12;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin13> GPIO_K13;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin14> GPIO_K14;
        typedef GPIO_x<GPIOPort::portK, GPIOPin::pin15> GPIO_K15;
    #endif


    #ifdef GPIOA_BASE
        template<>
        struct GPIOPortTrait<GPIOPort::portA> {
            static const uint32_t addr = GPIOA_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin0> {
            enum class GPIOAlt {
                eth_MII_CRS = 11,
                #ifdef EOS_STM32F7
                    sai2_SD_B = 10,
                #endif
                tim2_CH1 = 1,
                tim2_ETR = 1,
                tim5_CH1 = 2,
                tim8_ETR = 3,
                usart2_CTS = 7,
                uart4_TX = 8,
            };
            static const uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin1> {
            enum class GPIOAlt {
                eth_MII_RX_CLK = 11,
                #ifdef EOS_STM32F7
                    sai2_MCK_B = 10,
                #endif
                tim2_CH2 = 2,
                tim5_CH2 = 3,
                usart2_RTS = 7,
                uart4_RX = 8
            };
            static const uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin3> {
            enum class GPIOAlt {
            	ltdc_B5 = 14
            };
            static const uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin4> {
            enum class GPIOAlt {
                dcmi_HSYNC = 13,
                ltdc_VSYNC = 14,
                usart2_CK = 7,
            };
            static const uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin5> {
            enum class GPIOAlt {
                i2s1_CL = 5,
                spi1_SCK = 5
            };
            static const uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin6> {
            enum class GPIOAlt {
                dcmi_PIXCK = 13,
   				ltdc_G2 = 14,
                spi1_MISO = 5
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin7> {
            enum class GPIOAlt {
                i2s1_SD = 5,
                spi1_MOSI = 5
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin11> {
            enum class GPIOAlt {
            	ltdc_R4 = 14
            };
            static const uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portA, GPIOPin::pin12> {
            enum class GPIOAlt {
            	ltdc_R5 = 14
            };
            static const uint32_t pn = 12;
        };
    #endif

    #ifdef GPIOB_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portB> {
            static const uint32_t addr = GPIOB_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin0> {
            enum class GPIOAlt {
                ltdc_R3 = 9
            };
            static const uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin1> {
            enum class GPIOAlt {
                ltdc_R6 = 9
            };
            static const uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin8> {
            enum class GPIOAlt {
                i2c1_SCL = 4,
                ltdc_B6 = 14
            };
            static const uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin9> {
            enum class GPIOAlt {
                i2c1_SDA = 4,
                ltdc_B7 = 14,
                spi2_NSS = 5
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin10> {
            enum class GPIOAlt {
                i2c2_SCL = 4,
                ltdc_G4 = 14,
                spi2_SCK = 5
            };
            static const uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin11> {
            enum class GPIOAlt {
            	ltdc_G5 = 14
            };
            static const uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin14> {
            enum class GPIOAlt {
                spi2_MISO = 5
            };
            static const uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portB, GPIOPin::pin15> {
            enum class GPIOAlt {
                spi2_MOSI = 5
            };
            static const uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOC_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portC> {
            static const uint32_t addr = GPIOC_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portC, GPIOPin::pin2> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portC, GPIOPin::pin6> {
            enum class GPIOAlt {
                ltdc_HSYNC = 14,
                uart6_TX = 8
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portC, GPIOPin::pin7> {
            enum class GPIOAlt {
                ltdc_G6 = 14,
                uart6_RX = 8
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portC, GPIOPin::pin10> {
            enum class GPIOAlt {
                ltdc_R2 = 14,
            };
            static const uint32_t pn = 10;
        };
    #endif

    #ifdef GPIOD_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portD> {
            static const uint32_t addr = GPIOD_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portD, GPIOPin::pin3> {
            enum class GPIOAlt {
                dcmi_D5 = 13,
                ltdc_G7 = 14
            };
            static const uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portD, GPIOPin::pin6> {
            enum class GPIOAlt {
            	ltdc_B2 = 14,
                spi3_SCK = 5,
                i2s3_SD = 5
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portD, GPIOPin::pin7> {
            enum class GPIOAlt {
                fmc_NE1 = 12,
                usart2_CK = 7,
                spdifrx_IN0 = 8
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portD, GPIOPin::pin13> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 13;
        };
    #endif

    #ifdef GPIOE_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portE> {
            static const uint32_t addr = GPIOE_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portE, GPIOPin::pin4> {
            enum class GPIOAlt {
                ltdc_B0 = 14
            };
            static const uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portE, GPIOPin::pin5> {
            enum class GPIOAlt {
                dcmi_D6 = 13
            };
            static const uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portE, GPIOPin::pin6> {
            enum class GPIOAlt {
                dcmi_D7 = 13
            };
            static const uint32_t pn = 6;
        };
    #endif

    #ifdef GPIOF_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portF> {
            static const uint32_t addr = GPIOF_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portF, GPIOPin::pin7> {
            enum class GPIOAlt {
                spi5_SCK = 5,
                uart7_TX = 8
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portF, GPIOPin::pin9> {
            enum class GPIOAlt {
                spi5_MOSI = 5,
                #ifdef EOS_STM32F7
                    uart7_TX = 8
                #endif
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portF, GPIOPin::pin10> {
            enum class GPIOAlt {
            	ltdc_DE = 14
            };
            static const uint32_t pn = 10;
        };
    #endif

    #ifdef GPIOG_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portG> {
            static const uint32_t addr = GPIOG_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin6> {
            enum class GPIOAlt {
            	ltdc_R7 = 14
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin7> {
            enum class GPIOAlt {
            	ltdc_DOTCLK = 14
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin9> {
            enum class GPIOAlt {
                dcmi_VSYNC = 13,
                uart6_RX = 8
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin10> {
            enum class GPIOAlt {
            	ltdc_G3 = 9
            };
            static const uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin11> {
            enum class GPIOAlt {
            	ltdc_B3 = 14
            };
            static const uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin12> {
            enum class GPIOAlt {
                ltdc_B1 = 14,
                ltdc_B4 = 9,
                spi6_MISO = 5,
                usart6_RTS = 8
            };
            static const uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin13> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portG, GPIOPin::pin14> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 14;
        };
    #endif

    #ifdef GPIOH_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portH> {
            static const uint32_t addr = GPIOH_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin7> {
            enum class GPIOAlt {
                i2c3_SCL = 4
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin8> {
            enum class GPIOAlt {
                i2c3_SDA = 4,
                ltdc_R2 = 14
            };
            static const uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin9> {
            enum class GPIOAlt {
                dcmi_D0 = 13
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin10> {
            enum class GPIOAlt {
                dcmi_D1 = 13
            };
            static const uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin11> {
            enum class GPIOAlt {
                dcmi_D2 = 13
            };
            static const uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin12> {
            enum class GPIOAlt {
                dcmi_D3 = 13
            };
            static const uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portH, GPIOPin::pin14> {
            enum class GPIOAlt {
                dcmi_D4 = 13
            };
            static const uint32_t pn = 14;
        };
    #endif

    #ifdef GPIOI_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portI> {
            static const uint32_t addr = GPIOI_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin1> {
            enum class GPIOAlt {
                spi2_SCK = 5
            };
            static const uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin9> {
            enum class GPIOAlt {
                ltdc_VSYNC = 14
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin10> {
            enum class GPIOAlt {
                ltdc_HSYNC = 14
            };
            static const uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin12> {
            enum class GPIOAlt {
            	ltdc_LCDE = 14
            };
            static const uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin13> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin14> {
            enum class GPIOAlt {
                ltdc_DOTCLK = 14
            };
            static const uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portI, GPIOPin::pin15> {
            enum class GPIOAlt {
                ltdc_R0 = 14
            };
            static const uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOJ_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portJ> {
            static const uint32_t addr = GPIOJ_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin0> {
            enum class GPIOAlt {
                ltdc_R1 = 14
            };
            static const uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin1> {
            enum class GPIOAlt {
                ltdc_R2 = 14
            };
            static const uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin2> {
            enum class GPIOAlt {
                ltdc_R3 = 14
            };
            static const uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin3> {
            enum class GPIOAlt {
                ltdc_R4 = 14
            };
            static const uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin4> {
            enum class GPIOAlt {
                ltdc_R5 = 14
            };
            static const uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin5> {
            enum class GPIOAlt {
                ltdc_R6 = 14
            };
            static const uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin6> {
            enum class GPIOAlt {
                ltdc_R7 = 14
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin7> {
            enum class GPIOAlt {
                ltdc_G0 = 14
            };
            static const uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin8> {
            enum class GPIOAlt {
                ltdc_G1 = 14
            };
            static const uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin9> {
            enum class GPIOAlt {
                ltdc_G2 = 14
            };
            static const uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin10> {
            enum class GPIOAlt {
                ltdc_G3 = 14
            };
            static const uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin11> {
            enum class GPIOAlt {
                ltdc_G4 = 14
            };
            static const uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin13> {
            enum class GPIOAlt {
                ltdc_B1 = 14
            };
            static const uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin14> {
            enum class GPIOAlt {
                ltdc_B2 = 14
            };
            static const uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portJ, GPIOPin::pin15> {
            enum class GPIOAlt {
                ltdc_B3 = 14
            };
            static const uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOK_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::portK> {
            static const uint32_t addr = GPIOK_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin0> {
            enum class GPIOAlt {
                ltdc_G5 = 14
            };
            static const uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin1> {
            enum class GPIOAlt {
                ltdc_G6 = 14
            };
            static const uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin2> {
            enum class GPIOAlt {
                ltdc_G7 = 14
            };
            static const uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin3> {
            enum class GPIOAlt {
            };
            static const uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin4> {
            enum class GPIOAlt {
                ltdc_B5 = 14
            };
            static const uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin5> {
            enum class GPIOAlt {
                ltdc_B6 = 14
            };
            static const uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin6> {
            enum class GPIOAlt {
                ltdc_B7 = 14
            };
            static const uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::portK, GPIOPin::pin7> {
            enum class GPIOAlt {
                ltdc_DE = 14
            };
            static const uint32_t pn = 7;
        };
    #endif

}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

