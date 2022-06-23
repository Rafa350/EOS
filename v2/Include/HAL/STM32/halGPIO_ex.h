/// \file      halGPIO_ex.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO module manager.
/// \addtogroup HAL Hardware Abstraction Layer
/// @{
/// \addtogroup HAL_STM32 STM32 Hardware Abstraction Layer
/// @{
/// \defgroup HAL_STM32_GPIO_ex GPIO++
/// @{

#ifndef __STM32_halGPIO_ex__
#define __STM32_halGPIO_ex__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halGPIO.h"


namespace eos {

	/// \brief GPIO port identifiers.
	enum class GPIOPort: halGPIOPort {
		portA = HAL_GPIO_PORT_A,            ///< Identificador del port A
		portB = HAL_GPIO_PORT_B,            ///< Identificador del port B
		portC = HAL_GPIO_PORT_C,            ///< Identificador del port C
		portD = HAL_GPIO_PORT_D,			///< Identificador del port D
		portE = HAL_GPIO_PORT_E,			///< Identificador del port E
		portF = HAL_GPIO_PORT_F,			///< Identificador del port F
		portG = HAL_GPIO_PORT_G,			///< Identificador del port G
		portH = HAL_GPIO_PORT_H,			///< Identificador del port H
		portI = HAL_GPIO_PORT_I,			///< Identificador del port I
		portJ = HAL_GPIO_PORT_J,			///< Identificador del port J
		portK = HAL_GPIO_PORT_K				///< Identificador del port K
	};

	/// \brief GPIO Pin identifiers.
	enum class GPIOPin: halGPIOPin {
		pin0 = HAL_GPIO_PIN_0,				///< Identificador del pin 0
		pin1 = HAL_GPIO_PIN_1,				///< Identificador del pin 1
		pin2 = HAL_GPIO_PIN_2,				///< Identificador del pin 2
		pin3 = HAL_GPIO_PIN_3,				///< Identificador del pin 3
		pin4 = HAL_GPIO_PIN_4,				///< Identificador del pin 4
		pin5 = HAL_GPIO_PIN_5,				///< Identificador del pin 5
		pin6 = HAL_GPIO_PIN_6,				///< Identificador del pin 6
		pin7 = HAL_GPIO_PIN_7,				///< Identificador del pin 7
		pin8 = HAL_GPIO_PIN_8,				///< Identificador del pin 8
		pin9 = HAL_GPIO_PIN_9,				///< Identificador del pin 9
		pin10 = HAL_GPIO_PIN_10,			///< Identificador del pin 10
		pin11 = HAL_GPIO_PIN_11,			///< Identificador del pin 11
		pin12 = HAL_GPIO_PIN_12,			///< Identificador del pin 12
		pin13 = HAL_GPIO_PIN_13,			///< Identificador del pin 13
		pin14 = HAL_GPIO_PIN_14,			///< Identificador del pin 14
		pin15 = HAL_GPIO_PIN_15				///< Identificador del pin 15
	};

	/// \brief GPIO Driver type identifiers.
	enum class GPIODriver {
		pushPull,
		openDrain
	};

	/// \brief GPIO Speed identifier.
	enum class GPIOSpeed: halGPIOOptions {
		low    = HAL_GPIO_SPEED_LOW,
		medium = HAL_GPIO_SPEED_MEDIUM,
		high   = HAL_GPIO_SPEED_HIGH,
		fast   = HAL_GPIO_SPEED_FAST
	};

	/// \brief GPIO Pull up/down mode identifier.
	enum class GPIOPull: halGPIOOptions {
		none = HAL_GPIO_PULL_NONE,
		up   = HAL_GPIO_PULL_UP,
		down = HAL_GPIO_PULL_DOWN
	};

	/// \brief GPIO Initial state identifier
	enum class GPIOState: halGPIOOptions {
		noChange = HAL_GPIO_INIT_NOCHANGE,
		set = HAL_GPIO_INIT_SET,
		clr = HAL_GPIO_INIT_CLR
	};

	template <GPIOPort port_, GPIOPin pin_>
	struct GPIOPinInfo {
		enum class GPIOAlt: halGPIOAlt {
		};
		static const uint32_t baseAddr;
		static const uint32_t pinNumber;
	};

	/// \class GPIOPinAdapter
	/// \brief Adapter class form pins
	///
	template <GPIOPort port_, GPIOPin pin_>
	class GPIOPinAdapter {
		public:
			using GPIOAlt = typename GPIOPinInfo<port_, pin_>::GPIOAlt;

		private:
			constexpr static const uint32_t _baseAddr = GPIOPinInfo<port_, pin_>::baseAddr;
			constexpr static const uint32_t _pinNumber = GPIOPinInfo<port_, pin_>::pinNumber;

		public:
			GPIOPinAdapter() = default;

			GPIOPinAdapter(const GPIOPinAdapter &) = delete;
			GPIOPinAdapter(const GPIOPinAdapter &&) = delete;

			inline static void initInput(GPIOSpeed speed, GPIOPull pull = GPIOPull::none) {
				halGPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					halGPIOOptions(speed) |
					halGPIOOptions(pull);
				halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, HAL_GPIO_AF_NONE);
			}

			inline static void initOutput(GPIOSpeed speed, GPIODriver driver, GPIOState state = GPIOState::noChange) {
				halGPIOOptions options =
					(driver == GPIODriver::pushPull ? HAL_GPIO_MODE_OUTPUT_PP : HAL_GPIO_MODE_OUTPUT_OD) |
					halGPIOOptions(speed) |
					halGPIOOptions(state);
				halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, HAL_GPIO_AF_NONE);
			}

			inline static void initAlt(GPIOSpeed speed, GPIODriver driver, GPIOAlt alt) {
				halGPIOOptions options =
					(driver == GPIODriver::pushPull ? HAL_GPIO_MODE_ALT_PP : HAL_GPIO_MODE_ALT_OD) |
					halGPIOOptions(speed);
				halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, halGPIOAlt(alt));
			}

			inline static void initialize(halGPIOOptions options) {
				halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, HAL_GPIO_AF_NONE);
			}

			inline static void initialize(halGPIOOptions options, halGPIOAlt alt) {
				halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, alt);
			}

			/// \brief Set pin to ON state.
			///
			inline static void set() {
				GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_baseAddr);
				regs->BSRR = 1 << _pinNumber;
			}

			/// \brief Set pin to OFF state.
			///
			inline static void clear() {
				GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_baseAddr);
				regs->BSRR = 1 << (_pinNumber + 16);
			}

			/// \brief Toggle pin state.
			///
			inline static void toggle() {
				GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_baseAddr);
				regs->ODR ^= 1 << _pinNumber;
			}

			/// \brief Read pin state
			/// \return Pin state.
			///
			inline static bool read() {
				GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_baseAddr);
				return regs->IDR & (1 << _pinNumber);
			}

			/// \brief Write pin state.
			/// \param b: State to write.
			///
			inline static void write(bool s) {
				GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_baseAddr);
				regs->BSRR = 1 << (_pinNumber + (s ? 0 : 16));
			}

			GPIOPinAdapter& operator = (const GPIOPinAdapter &) = delete;
			GPIOPinAdapter& operator = (const GPIOPinAdapter &&) = delete;

			/// \brief Operator '='. Assign a state to pin.
			/// \param b: State to assign.
			/// \return Reference to this.
			///
			inline GPIOPinAdapter& operator = (bool s) {
				write(s);
				return *this;
			}

			/// \brief Operador bool. Read pin state.
			/// \return Pin state.
			//
			inline operator bool () {
				return read();
			}
	};


	/// \class GPIOPortAdapter
	/// \brief Adapter class form ports
	///
	template <GPIOPort port_, uint16_t mask_>
	class GPIOPortAdapter {
		public:
			constexpr static const GPIOPort port = port_;
			constexpr static const uint32_t mask = mask_;
	};


#ifdef HAL_GPIO_PORT_A
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin0> GPIO_A0;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin1> GPIO_A1;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin2> GPIO_A2;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin3> GPIO_A3;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin4> GPIO_A4;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin5> GPIO_A5;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin6> GPIO_A6;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin7> GPIO_A7;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin8> GPIO_A8;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin9> GPIO_A9;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin10> GPIO_A10;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin11> GPIO_A11;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin12> GPIO_A12;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin13> GPIO_A13;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin14> GPIO_A14;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin15> GPIO_A15;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin0> GPIO_B0;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin1> GPIO_B1;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin2> GPIO_B2;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin3> GPIO_B3;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin4> GPIO_B4;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin5> GPIO_B5;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin6> GPIO_B6;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin7> GPIO_B7;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin8> GPIO_B8;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin9> GPIO_B9;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin10> GPIO_B10;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin11> GPIO_B11;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin12> GPIO_B12;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin13> GPIO_B13;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin14> GPIO_B14;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin15> GPIO_B15;
#endif

#ifdef HAL_GPIO_PORT_C
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin0> GPIO_C0;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin1> GPIO_C1;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin2> GPIO_C2;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin3> GPIO_C3;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin4> GPIO_C4;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin5> GPIO_C5;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin6> GPIO_C6;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin7> GPIO_C7;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin8> GPIO_C8;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin9> GPIO_C9;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin10> GPIO_C10;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin11> GPIO_C11;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin12> GPIO_C12;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin13> GPIO_C13;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin14> GPIO_C14;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin15> GPIO_C15;
#endif

#ifdef HAL_GPIO_PORT_D
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin0> GPIO_D0;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin1> GPIO_D1;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin2> GPIO_D2;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin3> GPIO_D3;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin4> GPIO_D4;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin5> GPIO_D5;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin6> GPIO_D6;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin7> GPIO_D7;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin8> GPIO_D8;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin9> GPIO_D9;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin10> GPIO_D10;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin11> GPIO_D11;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin12> GPIO_D12;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin13> GPIO_D13;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin14> GPIO_D14;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin15> GPIO_D15;
#endif

#ifdef HAL_GPIO_PORT_E
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin0> GPIO_E0;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin1> GPIO_E1;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin2> GPIO_E2;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin3> GPIO_E3;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin4> GPIO_E4;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin5> GPIO_E5;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin6> GPIO_E6;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin7> GPIO_E7;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin8> GPIO_E8;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin9> GPIO_E9;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin10> GPIO_E10;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin11> GPIO_E11;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin12> GPIO_E12;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin13> GPIO_E13;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin14> GPIO_E14;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin15> GPIO_E15;
#endif

#ifdef HAL_GPIO_PORT_F
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin0> GPIO_F0;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin1> GPIO_F1;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin2> GPIO_F2;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin3> GPIO_F3;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin4> GPIO_F4;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin5> GPIO_F5;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin6> GPIO_F6;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin7> GPIO_F7;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin8> GPIO_F8;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin9> GPIO_F9;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin10> GPIO_F10;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin11> GPIO_F11;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin12> GPIO_F12;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin13> GPIO_F13;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin14> GPIO_F14;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin15> GPIO_F15;
#endif

#ifdef HAL_GPIO_PORT_G
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin0> GPIO_G0;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin1> GPIO_G1;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin2> GPIO_G2;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin3> GPIO_G3;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin4> GPIO_G4;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin5> GPIO_G5;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin6> GPIO_G6;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin7> GPIO_G7;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin8> GPIO_G8;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin9> GPIO_G9;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin10> GPIO_G10;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin11> GPIO_G11;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin12> GPIO_G12;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin13> GPIO_G13;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin14> GPIO_G14;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin15> GPIO_G15;
#endif

#ifdef HAL_GPIO_PORT_H
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin0> GPIO_H0;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin1> GPIO_H1;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin2> GPIO_H2;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin3> GPIO_H3;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin4> GPIO_H4;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin5> GPIO_H5;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin6> GPIO_H6;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin7> GPIO_H7;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin8> GPIO_H8;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin9> GPIO_H9;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin10> GPIO_H10;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin11> GPIO_H11;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin12> GPIO_H12;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin13> GPIO_H13;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin14> GPIO_H14;
	typedef GPIOPinAdapter<GPIOPort::portH, GPIOPin::pin15> GPIO_H15;
#endif

#ifdef HAL_GPIO_PORT_I
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin0> GPIO_I0;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin1> GPIO_I1;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin2> GPIO_I2;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin3> GPIO_I3;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin4> GPIO_I4;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin5> GPIO_I5;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin6> GPIO_I6;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin7> GPIO_I7;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin8> GPIO_I8;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin9> GPIO_I9;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin10> GPIO_I10;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin11> GPIO_I11;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin12> GPIO_I12;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin13> GPIO_I13;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin14> GPIO_I14;
	typedef GPIOPinAdapter<GPIOPort::portI, GPIOPin::pin15> GPIO_I15;
#endif

#ifdef HAL_GPIO_PORT_J
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin0> GPIO_J0;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin1> GPIO_J1;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin2> GPIO_J2;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin3> GPIO_J3;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin4> GPIO_J4;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin5> GPIO_J5;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin6> GPIO_J6;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin7> GPIO_J7;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin8> GPIO_J8;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin9> GPIO_J9;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin10> GPIO_J10;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin11> GPIO_J11;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin12> GPIO_J12;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin13> GPIO_J13;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin14> GPIO_J14;
	typedef GPIOPinAdapter<GPIOPort::portJ, GPIOPin::pin15> GPIO_J15;
#endif

#ifdef HAL_GPIO_PORT_K
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin0> GPIO_K0;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin1> GPIO_K1;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin2> GPIO_K2;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin3> GPIO_K3;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin4> GPIO_K4;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin5> GPIO_K5;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin6> GPIO_K6;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin7> GPIO_K7;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin8> GPIO_K8;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin9> GPIO_K9;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin10> GPIO_K10;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin11> GPIO_K11;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin12> GPIO_K12;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin13> GPIO_K13;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin14> GPIO_K14;
	typedef GPIOPinAdapter<GPIOPort::portK, GPIOPin::pin15> GPIO_K15;
#endif


#ifdef HAL_GPIO_PORT_A
	typedef GPIOPortAdapter<GPIOPort::portA, 0x00FF> GPIO_ALo;
	typedef GPIOPortAdapter<GPIOPort::portA, 0xFF00> GPIO_AHi;
	typedef GPIOPortAdapter<GPIOPort::portA, 0xFFFF> GPIO_A;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GPIOPortAdapter<GPIOPort::portB, 0x00FF> GPIO_BLo;
	typedef GPIOPortAdapter<GPIOPort::portB, 0xFF00> GPIO_BHi;
	typedef GPIOPortAdapter<GPIOPort::portB, 0xFFFF> GPIO_B;
#endif


	// PORT A ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			eth_MII_CRS = HAL_GPIO_AF_11,
#ifdef EOS_STM32F7
			sai2_SD_B = HAL_GPIO_AF_10,
#endif
			tim2_CH1 = HAL_GPIO_AF_1,
			tim2_ETR = HAL_GPIO_AF_1,
			tim5_CH1 = HAL_GPIO_AF_2,
			tim8_ETR = HAL_GPIO_AF_3,
			usart2_CTS = HAL_GPIO_AF_7,
			uart4_TX = HAL_GPIO_AF_8,
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			eth_MII_RX_CLK = HAL_GPIO_AF_11,
#ifdef EOS_STM32F7
			sai2_MCK_B = HAL_GPIO_AF_10,
#endif
			tim2_CH2 = HAL_GPIO_AF_2,
			tim5_CH2 = HAL_GPIO_AF_3,
			usart2_RTS = HAL_GPIO_AF_7,
			uart4_RX = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_HSYNC = HAL_GPIO_AF_13,
			usart2_CK = HAL_GPIO_AF_7,
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			i2s1_CL = HAL_GPIO_AF_5,
			spi1_SCK = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_PIXCK = HAL_GPIO_AF_13,
			spi1_MISO = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			i2s1_SD = HAL_GPIO_AF_5,
			spi1_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOA_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};


	// PORT B ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			i2c1_SCL = HAL_GPIO_AF_4,
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOB_BASE;
		constexpr static const uint32_t pinNumber = 8;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			i2c1_SDA = HAL_GPIO_AF_4,
			ltdc_B7 = HAL_GPIO_AF_14,
			spi2_NSS = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOB_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			i2c2_SCL = HAL_GPIO_AF_4,
			ltdc_G4 = HAL_GPIO_AF_14,
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOB_BASE;
		constexpr static const uint32_t pinNumber = 10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			spi2_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOB_BASE;
		constexpr static const uint32_t pinNumber = 15;
	};


	// PORT C ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14,
			uart6_TX = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOC_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14,
			uart6_RX = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOC_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};


	// PORT D ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin3> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D5 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOD_BASE;
		constexpr static const uint32_t pinNumber = 3;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			spi3_SCK = HAL_GPIO_AF_5,
			i2s3_SD = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOD_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			fmc_NE1 = HAL_GPIO_AF_12,
			usart2_CK = HAL_GPIO_AF_7,
			spdifrx_IN0 = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOD_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};

	// PORT E ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portE, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B0 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOE_BASE;
		constexpr static const uint32_t pinNumber = 4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portE, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D6 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOE_BASE;
		constexpr static const uint32_t pinNumber = 5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portE, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D7 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOE_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	// PORT F ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			spi5_SCK = HAL_GPIO_AF_5,
			uart7_TX = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOF_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			spi5_MOSI = HAL_GPIO_AF_5,
#ifdef EOS_STM32F7
			uart7_TX = HAL_GPIO_AF_8
#endif
		};
		constexpr static const uint32_t baseAddr = GPIOF_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};


	// PORT G ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portG, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
		};
		constexpr static const uint32_t baseAddr = GPIOG_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portG, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_VSYNC = HAL_GPIO_AF_13,
			uart6_RX = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOG_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portG, GPIOPin::pin12> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14,
			ltdc_B4 = HAL_GPIO_AF_9,
			spi6_MISO = HAL_GPIO_AF_5,
			usart6_RTS = HAL_GPIO_AF_8
		};
		constexpr static const uint32_t baseAddr = GPIOG_BASE;
		constexpr static const uint32_t pinNumber = 12;
	};

	// PORT H ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			i2c3_SCL = HAL_GPIO_AF_4
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			i2c3_SDA = HAL_GPIO_AF_4,
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 8;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D0 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D1 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin11> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D2 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 11;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin12> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D3 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 12;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin14> {
		enum class GPIOAlt: halGPIOAlt {
			dcmi_D4 = HAL_GPIO_AF_13
		};
		constexpr static const uint32_t baseAddr = GPIOH_BASE;
		constexpr static const uint32_t pinNumber = 14;
	};


	// PORT I ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_VSYNC = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin12> {
		enum class GPIOAlt: halGPIOAlt {
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 12;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin14> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_DOTCLK = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 14;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R0 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOI_BASE;
		constexpr static const uint32_t pinNumber = 15;
	};


	// PORT J ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R1 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin2> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R3 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 2;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin3> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R4 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 3;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R5 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R6 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R7 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G0 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G1 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 8;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G2 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G3 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin11> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G4 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 11;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin13> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 13;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin14> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B2 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 14;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B3 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOJ_BASE;
		constexpr static const uint32_t pinNumber = 15;
	};


	// PORT K ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G5 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin2> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G7 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 2;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin3> {
		enum class GPIOAlt: halGPIOAlt {
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 3;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B5 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B7 = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_DE = HAL_GPIO_AF_14
		};
		constexpr static const uint32_t baseAddr = GPIOK_BASE;
		constexpr static const uint32_t pinNumber = 7;
	};
}


#endif // __STM32_halGPIO_ex__

/// @}
/// @}
/// @}

