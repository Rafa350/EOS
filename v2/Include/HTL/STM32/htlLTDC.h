#pragma once
#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	namespace ltdc {

		/// \brief Image format.
		///
		enum class LTDCPixelFormat {
			argb8888 = 0,
			rgb888 = 1,
			rgb565 = 2,
			argb1555 = 3,
			argb4444 = 4,
			l8 = 5,
			al44 = 6,
			al88 = 7
		};

		/// \brief Interrupt events.
		///
		enum class LTDCEvent {
			line = 0,
			reload = 3,
			fifoError = 1,
			transferError = 2
		};

		/// \brief Clock divider factor.
		///
		enum class LTDCClockDivider {
			_2 = 0,
			_4 = 1,
			_8 = 2,
			_16 = 3
		};

		/// \brief GPIO alternative pin identifiers
		///
		enum class PinFunction {
			hsync,
			vsync,
			de,
			pc,
			r0, r1, r2, r3, r4, r5, r6, r7,
			g0, g1, g2, g3, g4, g5, g6, g7,
			b0, b1, b2, b3, b4, b5, b6, b7
		};

		/// \brief Control signals pin polarity.
		//
		enum class PinPolarity {
			activeLow,
			activeHigh,
			noChange
		};

		enum class LayerID {
			_1,
			_2
		};

		using LTDCInterruptParam = void*;
		using LTDCInterruptFunction = void (*)(LTDCEvent, LTDCInterruptParam);

		namespace internal {

			template <LayerID>
			struct LayerHardwareInfo;

			template<PinFunction, typename>
			struct LTDCAltFunction;
		}

		class LTDCDevice final {
			private:
				LTDC_TypeDef * const _ltdc;
				static LTDCDevice _device;
			private:
				LTDCDevice(const LTDCDevice &) = delete;
				LTDCDevice & operator = (const LTDCDevice &) = delete;
			private:
				LTDCDevice();
			public:
				void activate();
				void deactivate();
				void reset();
				void initialize(uint16_t width, uint16_t height, uint16_t hSync, uint16_t vSync, uint16_t hBP, uint16_t vBP, uint16_t hFP, uint16_t vFP);
				void deinitialize();
				template <typename pin_>
				void initHSYNCPin(PinPolarity polarity = PinPolarity::noChange) {
					gpio::GPIOAlt alt = internal::LTDCAltFunction<PinFunction::hsync, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
					if (polarity == PinPolarity::activeHigh)
						_ltdc->GCR |= LTDC_GCR_HSPOL;
					else if (polarity == PinPolarity::activeLow)
						_ltdc->GCR &= ~LTDC_GCR_HSPOL;
				}
				template <typename pin_>
				void initVSYNCPin(PinPolarity polarity = PinPolarity::noChange) {
					gpio::GPIOAlt alt = internal::LTDCAltFunction<PinFunction::vsync, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
					if (polarity == PinPolarity::activeHigh)
						_ltdc->GCR |= LTDC_GCR_VSPOL;
					else if (polarity == PinPolarity::activeLow)
						_ltdc->GCR &= ~LTDC_GCR_VSPOL;
				}
				template <typename pin_>
				void initPCPin(PinPolarity polarity = PinPolarity::noChange) {
					gpio::GPIOAlt alt = internal::LTDCAltFunction<PinFunction::pc, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
					if (polarity == PinPolarity::activeHigh)
						_ltdc->GCR |= LTDC_GCR_PCPOL;
					else if (polarity == PinPolarity::activeLow)
						_ltdc->GCR &= ~LTDC_GCR_PCPOL;
				}
				template <typename pin_>
				void initDEPin(PinPolarity polarity = PinPolarity::noChange) {
					gpio::GPIOAlt alt = internal::LTDCAltFunction<PinFunction::de, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
					if (polarity == PinPolarity::activeHigh)
						_ltdc->GCR |= LTDC_GCR_DEPOL;
					else if (polarity == PinPolarity::activeLow)
						_ltdc->GCR &= ~LTDC_GCR_DEPOL;
				}
				template <typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initRPins() {
					pinR2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r2, pinR2_>::alt);
					pinR3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r3, pinR3_>::alt);
					pinR4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r4, pinR4_>::alt);
					pinR5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r5, pinR5_>::alt);
					pinR6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r6, pinR6_>::alt);
					pinR7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r7, pinR7_>::alt);
				}
				template <typename pinR0_, typename pinR1_, typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initRPins() {
					pinR0_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r0, pinR0_>::alt);
					pinR1_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r1, pinR1_>::alt);
					pinR2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r2, pinR2_>::alt);
					pinR3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r3, pinR3_>::alt);
					pinR4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r4, pinR4_>::alt);
					pinR5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r5, pinR5_>::alt);
					pinR6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r6, pinR6_>::alt);
					pinR7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::r7, pinR7_>::alt);
				}
				template <typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initGPins() {
					pinG2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g2, pinG2_>::alt);
					pinG3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g3, pinG3_>::alt);
					pinG4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g4, pinG4_>::alt);
					pinG5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g5, pinG5_>::alt);
					pinG6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g6, pinG6_>::alt);
					pinG7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g7, pinG7_>::alt);
				}
				template <typename pinG0_, typename pinG1_, typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initGPins() {
					pinG0_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g0, pinG0_>::alt);
					pinG1_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g1, pinG1_>::alt);
					pinG2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g2, pinG2_>::alt);
					pinG3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g3, pinG3_>::alt);
					pinG4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g4, pinG4_>::alt);
					pinG5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g5, pinG5_>::alt);
					pinG6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g6, pinG6_>::alt);
					pinG7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::g7, pinG7_>::alt);
				}
				template <typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initBPins() {
					pinB2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b2, pinB2_>::alt);
					pinB3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b3, pinB3_>::alt);
					pinB4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b4, pinB4_>::alt);
					pinB5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b5, pinB5_>::alt);
					pinB6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b6, pinB6_>::alt);
					pinB7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b7, pinB7_>::alt);
				}
				template <typename pinB0_, typename pinB1_, typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initBPins() {
					pinB0_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b0, pinB0_>::alt);
					pinB1_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b1, pinB1_>::alt);
					pinB2_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b2, pinB2_>::alt);
					pinB3_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b3, pinB3_>::alt);
					pinB4_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b4, pinB4_>::alt);
					pinB5_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b5, pinB5_>::alt);
					pinB6_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b6, pinB6_>::alt);
					pinB7_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, internal::LTDCAltFunction<PinFunction::b7, pinB7_>::alt);
				}
				inline void enable() {
					_ltdc->GCR |= LTDC_GCR_LTDCEN;
				}
				inline void disable() {
					_ltdc->GCR &= ~LTDC_GCR_LTDCEN;
				}
				void setBackgroundColor(uint32_t rgb);
				void reload();
				void interruptService();
				void interruptERService();
				static LTDCDevice * getHandler() {
					return &_device;
				}
		};

		typedef LTDCDevice * LTDCDeviceHandler;


		class LTDCLayerDevice {
			private:
				LTDC_Layer_TypeDef * const _layer;
			private:
				LTDCLayerDevice(const LTDCLayerDevice &) = delete;
				LTDCLayerDevice & operator = (const LTDCLayerDevice &) = delete;
			protected:
				LTDCLayerDevice(LTDC_Layer_TypeDef *layer);
			public:
				inline void enable() {
					_layer->CR |= LTDC_LxCR_LEN;
				}
				inline void disable() {
					_layer->CR &= ~LTDC_LxCR_LEN;
				}
				void setWindow(int16_t x, int16_t y, int16_t width, int16_t height);
				void setFrameFormat(LTDCPixelFormat format, int16_t width, int16_t pitch, int16_t lines);
				void setFrameBuffer(void *buffer);
				void setConstantAlpha(uint8_t a);
				void setDefaultColor(uint32_t argb);
				void setCLUTTable(uint32_t *rgb);
				void disableCLUTTable();
				void setKeyColor(uint32_t rgb);
				void disableKeyColor();
		};

		typedef LTDCLayerDevice * LTDCLayerDeviceHandler;


		template <LayerID layerID_>
		class LTDCLayerDeviceX final: public LTDCLayerDevice {
			private:
				using HI = internal::LayerHardwareInfo<layerID_>;
			private:
				static constexpr uint32_t _layerAddr = HI::layerAddr;
				static LTDCLayerDeviceX _device;
			private:
				LTDCLayerDeviceX():
					LTDCLayerDevice(reinterpret_cast<LTDC_Layer_TypeDef*>(_layerAddr)) {
				}
			public:
				static LTDCLayerDeviceX * getHandler() {
					return &_device;
				}
		};
		template <LayerID layerID_>
		LTDCLayerDeviceX<layerID_> LTDCLayerDeviceX<layerID_>::_device;

		typedef LTDCLayerDeviceX<LayerID::_1> LTDCLayerDevice1;
		typedef LTDCLayerDeviceX<LayerID::_2> LTDCLayerDevice2;


		namespace internal {

			template <>
			struct LayerHardwareInfo<LayerID::_1> {
				static constexpr uint32_t layerAddr = LTDC_Layer1_BASE;
			};
			template <>
			struct LayerHardwareInfo<LayerID::_2> {
				static constexpr uint32_t layerAddr = LTDC_Layer2_BASE;
			};
		}
/*
		template <typename gpio_, PinFunction pin_>
		struct PinFunctionTrait {
		};

		template <int dummy_>
		class LTDC_x final {
			private:
				static LTDCInterruptFunction _isrFunction;
				static LTDCInterruptParam _isrParam;

				LTDC_x() = delete;
				LTDC_x(const LTDC_x &) = delete;
				LTDC_x(const LTDC_x &&) = delete;
				~LTDC_x() = delete;

				LTDC_x & operator = (const LTDC_x &) = delete;
				LTDC_x & operator = (const LTDC_x &&) = delete;

				/// \brief Habilita el rellotje del modul LTDC.
				///
				inline static void activate() {

					RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
					__DSB();
				}

				/// \brief Desabilita el rellotge del modul LTDC.
				///
				inline static void deactivate() {

					RCC->APB2ENR &= ~RCC_APB2ENR_LTDCEN;
				}

			public:
				/// \brief Inicialitza el modul.
				/// \param width: Amplada de la pantalla en pixels.
				/// \param height: Alçada de la pantalla en pixels.
				///
				static void initialize(
					uint16_t width,
					uint16_t height,
					uint16_t hSync,
					uint16_t vSync,
					uint16_t hBP,
					uint16_t vBP,
					uint16_t hFP,
					uint16_t vFP) {

					uint32_t tmp;

					activate();
					disable();

					// Configura el registre SSCR (Sinchronization Size Configuration Register)
					//
					tmp = LTDC->SSCR;
					tmp &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
					tmp |= ((hSync - 1) << LTDC_SSCR_HSW_Pos) & LTDC_SSCR_HSW;
					tmp |= ((vSync - 1) << LTDC_SSCR_VSH_Pos) & LTDC_SSCR_VSH;
					LTDC->SSCR = tmp;

					// Configura el registre BPCR (Back Porch Configuration Register)
					//
					tmp = LTDC->BPCR;
					tmp &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
					tmp |= ((hSync + hBP - 1) << LTDC_BPCR_AHBP_Pos) & LTDC_BPCR_AHBP;
					tmp |= ((vSync + vBP - 1) << LTDC_BPCR_AVBP_Pos) & LTDC_BPCR_AVBP;
					LTDC->BPCR = tmp;

					// Configura el registre AWCR (Active Width Configuration Register)
					// -AAW = HSYNC + HBP + WIDTH - 1
					// -AAH = VSYNC + VBP + HEIGHT - 1
					//
					tmp = LTDC->AWCR;
					tmp &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
					tmp |= ((hSync + hBP + width - 1) << LTDC_AWCR_AAW_Pos) & LTDC_AWCR_AAW;
					tmp |= ((vSync + vBP + height - 1) << LTDC_AWCR_AAH_Pos) & LTDC_AWCR_AAH;
					LTDC->AWCR = tmp;

					// Configura el registre TWCR (Total Width Configuration Register)
					// -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
					// -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
					//
					tmp = LTDC->TWCR;
					tmp &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
					tmp |= ((hSync + hBP + width + hFP - 1) << LTDC_TWCR_TOTALW_Pos) & LTDC_TWCR_TOTALW;
					tmp |= ((vSync + vBP + height + vFP - 1) << LTDC_TWCR_TOTALH_Pos) & LTDC_TWCR_TOTALH;
					LTDC->TWCR = tmp;
				}

				/// \brief Desinicialitza el modul
				///
				static void deinitialize() {

					disable();
					deactivate();
				}

				/// \brief Reseteja el modul.
				///
				static void reset() {

					RCC->APB2RSTR |= RCC_APB2RSTR_LTDCRST;
					RCC->APB2RSTR &= ~RCC_APB2RSTR_LTDCRST;
				}

				/// \brief Habilita el modul.
				///
				static void enable() {

					LTDC->GCR |= LTDC_GCR_LTDCEN;
				}

				/// \brief Desabilita el modul.
				///
				static void disable() {

					LTDC->GCR &= ~LTDC_GCR_LTDCEN;
				}

				/// ----------------------------------------------------------
				/// \brief Inicialitza el rellotge del modul LTDC
				/// \param pllMul: Multiplicador d'entrada del PLL
				/// \param pllDiv: Divisor de sortida del PLL.
				/// \param clkDiv: Divisor de la senyal LTDC_PC.
				/// \remarks: El PLL SAI es compartit amb altres periferics,
				///           pllMUL i pllDiv poden entrar amb conflicte amb SAI2
				///
				/// TODO: Revisar aixo
				static void initClock(
					uint32_t pllMul,
					uint32_t pllDiv,
					LTDCClockDivider clkDiv) {

					//eosAssert((pllMul >= 50) && (pllMul <= 432));
					//eosAssert((pllDiv >= 2) && (pllDiv <= 7));

					uint32_t tmp;

					RCC->CR &= ~RCC_CR_PLLSAION;
					while ((RCC->CR & RCC_CR_PLLSAIRDY) != 0)
						continue;

					#ifdef EOS_PLATFORM_STM32F7
						tmp = RCC->DCKCFGR1;
						tmp &= ~RCC_DCKCFGR1_PLLSAIDIVR_Msk;
						tmp |= (uint32_t(clkDiv) << RCC_DCKCFGR1_PLLSAIDIVR_Pos) & RCC_DCKCFGR1_PLLSAIDIVR_Msk;
						RCC->DCKCFGR1 = tmp;
					#endif

					tmp = RCC->PLLSAICFGR;
					tmp &= ~RCC_PLLSAICFGR_PLLSAIN_Msk;
					tmp |= (pllMul << RCC_PLLSAICFGR_PLLSAIN_Pos) & RCC_PLLSAICFGR_PLLSAIN_Msk;
					tmp &= ~RCC_PLLSAICFGR_PLLSAIR_Msk;
					tmp |= (pllDiv << RCC_PLLSAICFGR_PLLSAIR_Pos) & RCC_PLLSAICFGR_PLLSAIR_Msk;
					RCC->PLLSAICFGR = tmp;

					RCC->CR |= RCC_CR_PLLSAION;
					while ((RCC->CR & RCC_CR_PLLSAIRDY) == 0)
						continue;
				}

				/// ----------------------------------------------------------
				/// \brief Inicialitza el rellotge del modul LTDC
				/// \param clkDiv: Divisor de la senyal LTDC_PC.
				///
				static void initClock(
					LTDCClockDivider clkDiv) {

					#ifdef EOS_PLATFORM_STM32F7
						uint32_t tmp = RCC->DCKCFGR1;
						tmp &= ~RCC_DCKCFGR1_PLLSAIDIVR_Msk;
						tmp |= (uint32_t(clkDiv) << RCC_DCKCFGR1_PLLSAIDIVR_Pos) & RCC_DCKCFGR1_PLLSAIDIVR_Msk;
						RCC->DCKCFGR1 = tmp;
					#endif
				}

				template <typename gpio_>
				static void initHSYNCPin(
					PinPolarity polarity = PinPolarity::noChange) {

					gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpio_, PinFunction::HSYNC>::alt);
					setHSYNCPolarity(polarity);
				}

				template <typename gpio_>
				static void initVSYNCPin(
					PinPolarity polarity = PinPolarity::noChange) {

					gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpio_, PinFunction::VSYNC>::alt);
					setVSYNCPolarity(polarity);
				}

				template <typename gpio_>
				static void initPCPin(
					PinPolarity polarity = PinPolarity::noChange) {

					gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpio_, PinFunction::PC>::alt);
					setPCPolarity(polarity);
				}

				template <typename gpio_>
				static void initDEPin(
					PinPolarity polarity = PinPolarity::noChange) {

					gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpio_, PinFunction::DE>::alt);
					setDEPolarity(polarity);
				}

				template <typename gpioR0_, typename gpioR1_, typename gpioR2_, typename gpioR3_,
						  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
				static void initRPins() {

					gpioR0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR0_, PinFunction::R0>::alt);
					gpioR1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR1_, PinFunction::R1>::alt);
					gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR2_, PinFunction::R2>::alt);
					gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR3_, PinFunction::R3>::alt);
					gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR4_, PinFunction::R4>::alt);
					gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR5_, PinFunction::R5>::alt);
					gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR6_, PinFunction::R6>::alt);
					gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR7_, PinFunction::R7>::alt);
				}

				template <typename gpioR2_, typename gpioR3_,
						  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
				static void initRPins() {

					gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR2_, PinFunction::R2>::alt);
					gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR3_, PinFunction::R3>::alt);
					gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR4_, PinFunction::R4>::alt);
					gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR5_, PinFunction::R5>::alt);
					gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR6_, PinFunction::R6>::alt);
					gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioR7_, PinFunction::R7>::alt);
				}

				template <typename gpioG0_, typename gpioG1_, typename gpioG2_, typename gpioG3_,
						  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
				static void initGPins() {

					gpioG0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG0_, PinFunction::G0>::alt);
					gpioG1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG1_, PinFunction::G1>::alt);
					gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG2_, PinFunction::G2>::alt);
					gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG3_, PinFunction::G3>::alt);
					gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG4_, PinFunction::G4>::alt);
					gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG5_, PinFunction::G5>::alt);
					gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG6_, PinFunction::G6>::alt);
					gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG7_, PinFunction::G7>::alt);
				}

				template <typename gpioG2_, typename gpioG3_,
						  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
				static void initGPins() {

					gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG2_, PinFunction::G2>::alt);
					gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG3_, PinFunction::G3>::alt);
					gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG4_, PinFunction::G4>::alt);
					gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG5_, PinFunction::G5>::alt);
					gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG6_, PinFunction::G6>::alt);
					gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioG7_, PinFunction::G7>::alt);
				}

				template <typename gpioB0_, typename gpioB1_, typename gpioB2_, typename gpioB3_,
						  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
				static void initBPins() {

					gpioB0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB0_, PinFunction::B0>::alt);
					gpioB1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB1_, PinFunction::B1>::alt);
					gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB2_, PinFunction::B2>::alt);
					gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB3_, PinFunction::B3>::alt);
					gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB4_, PinFunction::B4>::alt);
					gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB5_, PinFunction::B5>::alt);
					gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB6_, PinFunction::B6>::alt);
					gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB7_, PinFunction::B7>::alt);
				}

				template <typename gpioB2_, typename gpioB3_,
						  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
				static void initBPins() {

					gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB2_, PinFunction::B2>::alt);
					gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB3_, PinFunction::B3>::alt);
					gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB4_, PinFunction::B4>::alt);
					gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB5_, PinFunction::B5>::alt);
					gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB6_, PinFunction::B6>::alt);
					gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, PinFunctionTrait<gpioB7_, PinFunction::B7>::alt);
				}

				/// \brief Asigna la polaritat del pin HSYNC.
				/// \param polarity: Opcions de polaritat.
				///
				static constexpr void setHSYNCPolarity(
					PinPolarity polarity) {

					if (polarity == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_HSPOL;
					else if (polarity == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_HSPOL;
				}

				/// \brief Asigna la polaritat del pin VSYNC.
				/// \param polarity: Opcions de polaritat.
				///
				static constexpr void setVSYNCPolarity(
					PinPolarity polarity) {

					if (polarity == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_VSPOL;
					else if (polarity == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_VSPOL;
				}

				/// \brief Asigna la polaritat del pin DE.
				/// \param polarity: Opcions de polaritat.
				///
				static constexpr void setDEPolarity(
					PinPolarity polarity) {

					if (polarity == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_DEPOL;
					else if (polarity == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_DEPOL;
				}

				/// \brief Asigna la polaritat del pin PC.
				/// \param polarity: Opcions de polaritat.
				///
				static constexpr void setPCPolarity(
					PinPolarity polarity) {

					if (polarity == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_PCPOL;
					else if (polarity == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_PCPOL;
				}

				/// \brief Asigna el color de fons de la pantalla.
				/// \param rgb: El color en formar RGB888.
				///
				static constexpr void setBackgroundColor(
					uint32_t rgb) {

					// Configura el registre BCCR (Back Color Configuration Register)
					//
					uint32_t tmp = LTDC->BCCR;
					tmp &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
					tmp |= ((rgb & 0x00FF0000) >> 16) << LTDC_BCCR_BCRED_Pos;
					tmp |= ((rgb & 0x0000FF00) >> 8) << LTDC_BCCR_BCGREEN_Pos;
					tmp |= (rgb & 0x000000FF) << LTDC_BCCR_BCBLUE_Pos;
					LTDC->BCCR = tmp;
				}

				static void waitSync() {

					while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) != 0)
						continue;
					while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
						continue;
				}

				/// \brief Habilita les interrupcions.
				/// \param event: El event.
				///
				static void enableInterrrupt(
					LTDCEvent event) {

					LTDC->IER |= 1 << uint32_t(event);
				}

				/// \brief Desabilita les interrupcions.
				/// \param event: El event.
				///
				static bool disableInterrupt(
					LTDCEvent event) {

					bool state = (LTDC->IER & (1 << uint32_t(event))) != 0;
					LTDC->IER &= ~(1 << uint32_t(event));
					return state;
				}

				static bool getInterruptFlag(
					LTDCEvent event) {

					return (LTDC->ISR & (1 << uint32_t(event))) != 0;
				}

				static void clearInterruptFlag(
					LTDCEvent event) {

					LTDC->ICR |= 1 << uint32_t(event);
				}

				static void setInterruptFunction(
					LTDCInterruptFunction function,
					LTDCInterruptParam param = nullptr) {

					_isrFunction = function;
					_isrParam = param;
				}

				inline static void interruptHandler(
					LTDCEvent event) {

					if (_isrFunction != nullptr)
						_isrFunction(event, _isrParam);
				}
		};

		template<int dummy_> LTDCInterruptFunction LTDC_x<dummy_>::_isrFunction = nullptr;
		template<int dummy_> LTDCInterruptParam LTDC_x<dummy_>::_isrParam = nullptr;

		using LTDC_1 = LTDC_x<1>;


		enum class LTDCLayerNum {
			layer1,
			layer2
		};

		template <LTDCLayerNum>
		struct LTDCLayerTrait {
		};

		template <LTDCLayerNum layerNum_>
		class LTDCLayer_x final {
			private:
				using Trait = LTDCLayerTrait<layerNum_>;

				static constexpr uint32_t _addr = Trait::addr;

				LTDCLayer_x() = delete;
				LTDCLayer_x(const LTDCLayer_x &) = delete;
				LTDCLayer_x(const LTDCLayer_x &&) = delete;
				~LTDCLayer_x() = delete;

				LTDCLayer_x & operator = (const LTDCLayer_x &) = delete;
				LTDCLayer_x & operator = (const LTDCLayer_x &&) = delete;

				/// \brief Carrega els registres modificats
				///
				static void reload() {

					// Si el LTDC no esta actiu, fa una actualitzacio immediata
					//
					if ((LTDC->GCR & LTDC_GCR_LTDCEN) == 0)
						LTDC->SRCR |= LTDC_SRCR_IMR;

					// En cas contrari, fa l'actualitzacio durant la sincronitzacio
					// vertical, i espera que finalitzi.
					//
					else {
						LTDC->SRCR |= LTDC_SRCR_VBR;
						while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) != 0)
							continue;
						while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
							continue;
					}
				}

			public:
				static void enable() {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					regs->CR |= LTDC_LxCR_LEN;

					reload();
				}

				static void disable() {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					regs->CR &= ~LTDC_LxCR_LEN;

					reload();
				}

				static void setWindow(
					int x,
					int y,
					int width,
					int height) {

					uint32_t tmp;
					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

					// Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
					// -Tamany horitzontal de la finestra
					//
					uint32_t ahbp = (LTDC->BPCR & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos;
					tmp = regs->WHPCR;
					tmp &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
					tmp |= ((ahbp + x + 1) << LTDC_LxWHPCR_WHSTPOS_Pos) & LTDC_LxWHPCR_WHSTPOS;
					tmp |= ((ahbp + width - x) << LTDC_LxWHPCR_WHSPPOS_Pos) & LTDC_LxWHPCR_WHSPPOS;
					regs->WHPCR = tmp;

					// Configura Lx_WHPCR (Window Vertical Position Configuration Register)
					// -Tamany vertical de la finestra
					//
					uint32_t avbp = (LTDC->BPCR & LTDC_BPCR_AVBP) >> LTDC_BPCR_AVBP_Pos;
					tmp = regs->WVPCR;
					tmp &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
					tmp |= ((avbp + y + 1) << LTDC_LxWVPCR_WVSTPOS_Pos) & LTDC_LxWVPCR_WVSTPOS;
					tmp |= ((avbp + height - y) << LTDC_LxWVPCR_WVSPPOS_Pos) & LTDC_LxWVPCR_WVSPPOS;
					regs->WVPCR = tmp;

					reload();
				}

				static void setFrameFormat(
					LTDCPixelFormat format,
					int width,
					int pitch,
					int lines) {

					uint32_t tmp;
					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

					// Configura Lx_PFCR (Pixel Format Configuration Register)
					// -Format de color del buffer d'imatge.
					//
					tmp = regs->PFCR;
					tmp &= ~(0b111 << LTDC_LxPFCR_PF_Pos);
					tmp |= (uint32_t(format) & 0b111) << LTDC_LxPFCR_PF_Pos;
					regs->PFCR = tmp;

					// Configura Lx_CFBLR (Color Frame Buffer Length Register)
					// -Longitut de la linia en bytes.
					//
					tmp = regs->CFBLR;
					tmp &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
					tmp |= (pitch & 0x1FFF) << LTDC_LxCFBLR_CFBP_Pos;
					tmp |= ((width + 3) & 0x1FFF) << LTDC_LxCFBLR_CFBLL_Pos;
					regs->CFBLR = tmp;

					// Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
					//
					tmp = regs->CFBLNR;
					tmp  &= ~(LTDC_LxCFBLNR_CFBLNBR);
					tmp |= lines & LTDC_LxCFBLNR_CFBLNBR;
					regs->CFBLNR = tmp;

					reload();
				}

				/// \brief Asigna el buffer de la capa.
				/// \param buffer: El buffer. Si es null, es desactiva la capa.
				///
				static void setFrameBuffer(
					void *buffer) {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					if (buffer == nullptr)
						regs->CR &= ~LTDC_LxCR_LEN;
					else
						regs->CFBAR = (uint32_t)buffer;

					reload();
				}

				/// \brief Asigna i activa la taula de colors (Valid per L8, AL44 i AL88)
				/// \param table: La taula de colors en format RGB888. Si es null,
				///               es desactiva.
				///
				static void setCLUTTable(
					uint32_t *rgb) {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					if ((regs->CR & LTDC_LxCR_LEN) == 0) {
						if (rgb == nullptr)
							regs->CR &= ~LTDC_LxCR_CLUTEN;
						else {
							for (uint32_t i = 0; i < 256; i++)
								regs->CLUTWR = (i << LTDC_LxCLUTWR_CLUTADD_Pos) | (*rgb++ & 0x00FFFFFF);
							regs->CR |= LTDC_LxCR_CLUTEN;
						}

						LTDC->SRCR |= LTDC_SRCR_IMR;
					}
				}

				/// \brief Desactiva la taula de colors.
				///
				static void disableCLUTTable() {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					regs->CR &= ~LTDC_LxCR_CLUTEN;

					reload();
				}

				static void setDefaultColor(
					uint32_t argb) {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

					// Configura Lx_DCCR (Default Color Configuration Register)
					// -Color per defecte
					//
					uint32_t tmp = regs->DCCR;
					tmp &= ~(LTDC_LxDCCR_DCALPHA | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCBLUE);
					tmp |= ((argb & 0xFF000000) >> 24) << LTDC_LxDCCR_DCALPHA_Pos;
					tmp |= ((argb & 0x00FF0000) >> 16) << LTDC_LxDCCR_DCRED_Pos;
					tmp |= ((argb & 0x0000FF00) >> 8) << LTDC_LxDCCR_DCGREEN_Pos;
					tmp |= (argb & 0x000000FF) << LTDC_LxDCCR_DCBLUE_Pos;
					regs->DCCR = tmp;

					reload();
				}

				static void setConstantAlpha(
					uint8_t a) {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					regs->CACR = a;

					reload();
				}

				static void setKeyColor(
					uint32_t rgb) {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

					// Configura Lx_CKCR (Color Key Configuration Register)
					// -Color clau per croma e
					//
					uint32_t tmp = regs->CKCR;
					tmp &= ~(LTDC_LxCKCR_CKRED | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKBLUE);
					tmp |= ((rgb & 0x00FF0000) >> 16) << LTDC_LxCKCR_CKRED_Pos;
					tmp |= ((rgb & 0x0000FF00) >> 8) << LTDC_LxCKCR_CKGREEN_Pos;
					tmp |= (rgb & 0x000000FF) << LTDC_LxCKCR_CKBLUE_Pos;
					regs->CKCR = tmp;

					// Activa el color croma
					//
					regs->CR |= LTDC_LxCR_COLKEN;

					reload();
				}

				static void disableKeyColor() {

					LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
					regs->CR &= ~LTDC_LxCR_COLKEN;

					reload();
				}
		};

		using LTDCLayer_1 = LTDCLayer_x<LTDCLayerNum::layer1>;
		using LTDCLayer_2 = LTDCLayer_x<LTDCLayerNum::layer2>;

		template <>
		struct LTDCLayerTrait<LTDCLayerNum::layer1> {
			static constexpr uint32_t addr = LTDC_Layer1_BASE;
		};

		template <>
		struct LTDCLayerTrait<LTDCLayerNum::layer2> {
			static constexpr uint32_t addr = LTDC_Layer2_BASE;
		};


		template <>
		struct PinFunctionTrait<GPIO_A1, PinFunction::R2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A2, PinFunction::R1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A3, PinFunction::B5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A4, PinFunction::VSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A5, PinFunction::R4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A6, PinFunction::G2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A8, PinFunction::R6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A11, PinFunction::R4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_A12, PinFunction::R5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_B0, PinFunction::R3> {
			static constexpr GPIOAlt alt = GPIOAlt::_9;
		};

		template <>
		struct PinFunctionTrait<GPIO_B1, PinFunction::R6> {
			static constexpr GPIOAlt alt = GPIOAlt::_9;
		};

		template <>
		struct PinFunctionTrait<GPIO_B8, PinFunction::B6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_B9, PinFunction::B7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_B10, PinFunction::G4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_B11, PinFunction::G5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_C6, PinFunction::HSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_C7, PinFunction::G6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_C10, PinFunction::R2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_D3, PinFunction::G7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_D6, PinFunction::B2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_D10, PinFunction::B3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E4, PinFunction::B0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E5, PinFunction::G0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E6, PinFunction::G1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E11, PinFunction::G3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E12, PinFunction::B4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E13, PinFunction::DE> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E14, PinFunction::PC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_E15, PinFunction::R7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_F10, PinFunction::DE> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G6, PinFunction::R7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G7, PinFunction::PC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G10, PinFunction::B2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G10, PinFunction::G3> {
			static constexpr GPIOAlt alt = GPIOAlt::_9;
		};

		template <>
		struct PinFunctionTrait<GPIO_G11, PinFunction::B3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G12, PinFunction::B1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_G12, PinFunction::B4> {
			static constexpr GPIOAlt alt = GPIOAlt::_9;
		};

		template <>
		struct PinFunctionTrait<GPIO_H2, PinFunction::R0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H3, PinFunction::R1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H8, PinFunction::R2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H9, PinFunction::R3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H10, PinFunction::R4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H11, PinFunction::R5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H12, PinFunction::R6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H13, PinFunction::G2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H14, PinFunction::G3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_H15, PinFunction::G4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I0, PinFunction::G5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I1, PinFunction::G6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I2, PinFunction::G7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I4, PinFunction::B4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I5, PinFunction::B5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I6, PinFunction::B6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I7, PinFunction::B7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I9, PinFunction::VSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I10, PinFunction::HSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I12, PinFunction::HSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I13, PinFunction::VSYNC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I14, PinFunction::PC> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_I15, PinFunction::R0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J0, PinFunction::R1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J1, PinFunction::R2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J2, PinFunction::R3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J3, PinFunction::R4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J4, PinFunction::R5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J5, PinFunction::R6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J6, PinFunction::R7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J7, PinFunction::G0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J8, PinFunction::G1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J9, PinFunction::G2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J10, PinFunction::G3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J11, PinFunction::G4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J12, PinFunction::B0> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J13, PinFunction::B1> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J14, PinFunction::B2> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_J15, PinFunction::B3> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K0, PinFunction::G5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K1, PinFunction::G6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K2, PinFunction::G7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K3, PinFunction::B4> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K4, PinFunction::B5> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K5, PinFunction::B6> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K6, PinFunction::B7> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};

		template <>
		struct PinFunctionTrait<GPIO_K7, PinFunction::DE> {
			static constexpr GPIOAlt alt = GPIOAlt::_14;
		};*/
	}
}


#if defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlLTDC_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlLTDC_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlLTDC__
