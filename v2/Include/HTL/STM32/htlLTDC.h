#pragma once
#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	/// \brief Control signals pin polarity.
	//
    enum class LTDCPolarity {
    	activeLow,
		activeHigh,
    	noChange
    };

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
    enum class LTDCPin {
    	HSYNC,
		VSYNC,
		DE,
		PC,
		R0, R1, R2, R3, R4, R5, R6, R7,
		G0, G1, G2, G3, G4, G5, G6, G7,
		B0, B1, B2, B3, B4, B5, B6, B7
    };

    using LTDCInterruptParam = void*;
    using LTDCInterruptFunction = void (*)(LTDCEvent, LTDCInterruptParam);

    template <typename gpio_, LTDCPin pin_>
    struct LTDCPinTrait {
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
				LTDCPolarity polarity = LTDCPolarity::noChange) {

		    	gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::HSYNC>::alt);
     			setHSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initVSYNCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::VSYNC>::alt);
     			setVSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initPCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::PC>::alt);
				setPCPolarity(polarity);
			}

			template <typename gpio_>
			static void initDEPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::DE>::alt);
				setDEPolarity(polarity);
			}

			template <typename gpioR0_, typename gpioR1_, typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR0_, LTDCPin::R0>::alt);
				gpioR1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR1_, LTDCPin::R1>::alt);
				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR2_, LTDCPin::R2>::alt);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR3_, LTDCPin::R3>::alt);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR4_, LTDCPin::R4>::alt);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR5_, LTDCPin::R5>::alt);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR6_, LTDCPin::R6>::alt);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR7_, LTDCPin::R7>::alt);
			}

			template <typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR2_, LTDCPin::R2>::alt);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR3_, LTDCPin::R3>::alt);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR4_, LTDCPin::R4>::alt);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR5_, LTDCPin::R5>::alt);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR6_, LTDCPin::R6>::alt);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR7_, LTDCPin::R7>::alt);
			}

			template <typename gpioG0_, typename gpioG1_, typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG0_, LTDCPin::G0>::alt);
				gpioG1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG1_, LTDCPin::G1>::alt);
				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG2_, LTDCPin::G2>::alt);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG3_, LTDCPin::G3>::alt);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG4_, LTDCPin::G4>::alt);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG5_, LTDCPin::G5>::alt);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG6_, LTDCPin::G6>::alt);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG7_, LTDCPin::G7>::alt);
			}

			template <typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG2_, LTDCPin::G2>::alt);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG3_, LTDCPin::G3>::alt);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG4_, LTDCPin::G4>::alt);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG5_, LTDCPin::G5>::alt);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG6_, LTDCPin::G6>::alt);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG7_, LTDCPin::G7>::alt);
			}

			template <typename gpioB0_, typename gpioB1_, typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB0_, LTDCPin::B0>::alt);
				gpioB1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB1_, LTDCPin::B1>::alt);
				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB2_, LTDCPin::B2>::alt);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB3_, LTDCPin::B3>::alt);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB4_, LTDCPin::B4>::alt);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB5_, LTDCPin::B5>::alt);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB6_, LTDCPin::B6>::alt);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB7_, LTDCPin::B7>::alt);
			}

			template <typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB2_, LTDCPin::B2>::alt);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB3_, LTDCPin::B3>::alt);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB4_, LTDCPin::B4>::alt);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB5_, LTDCPin::B5>::alt);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB6_, LTDCPin::B6>::alt);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB7_, LTDCPin::B7>::alt);
			}

			/// \brief Asigna la polaritat del pin HSYNC.
			/// \param polarity: Opcions de polaritat.
			///
			static constexpr void setHSYNCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_HSPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_HSPOL;
			}

			/// \brief Asigna la polaritat del pin VSYNC.
			/// \param polarity: Opcions de polaritat.
			///
			static constexpr void setVSYNCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_VSPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_VSPOL;
			}

			/// \brief Asigna la polaritat del pin DE.
			/// \param polarity: Opcions de polaritat.
			///
			static constexpr void setDEPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_DEPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_DEPOL;
			}

			/// \brief Asigna la polaritat del pin PC.
			/// \param polarity: Opcions de polaritat.
			///
			static constexpr void setPCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_PCPOL;
			    else if (polarity == LTDCPolarity::activeLow)
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
    struct LTDCPinTrait<GPIO_A1, LTDCPin::R2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A2, LTDCPin::R1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A3, LTDCPin::B5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A4, LTDCPin::VSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A5, LTDCPin::R4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A6, LTDCPin::G2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A8, LTDCPin::R6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A11, LTDCPin::R4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A12, LTDCPin::R5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B0, LTDCPin::R3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_9;
    };

    template <>
    struct LTDCPinTrait<GPIO_B1, LTDCPin::R6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_9;
    };

    template <>
    struct LTDCPinTrait<GPIO_B8, LTDCPin::B6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B9, LTDCPin::B7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B10, LTDCPin::G4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B11, LTDCPin::G5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C6, LTDCPin::HSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C7, LTDCPin::G6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C10, LTDCPin::R2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D3, LTDCPin::G7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D6, LTDCPin::B2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D10, LTDCPin::B3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E4, LTDCPin::B0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E5, LTDCPin::G0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E6, LTDCPin::G1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E11, LTDCPin::G3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E12, LTDCPin::B4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E13, LTDCPin::DE> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E14, LTDCPin::PC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E15, LTDCPin::R7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_F10, LTDCPin::DE> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G6, LTDCPin::R7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G7, LTDCPin::PC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G10, LTDCPin::B2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G10, LTDCPin::G3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_9;
    };

    template <>
    struct LTDCPinTrait<GPIO_G11, LTDCPin::B3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G12, LTDCPin::B1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G12, LTDCPin::B4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_9;
    };

    template <>
    struct LTDCPinTrait<GPIO_H2, LTDCPin::R0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H3, LTDCPin::R1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H8, LTDCPin::R2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H9, LTDCPin::R3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H10, LTDCPin::R4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H11, LTDCPin::R5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H12, LTDCPin::R6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H13, LTDCPin::G2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H14, LTDCPin::G3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H15, LTDCPin::G4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I0, LTDCPin::G5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I1, LTDCPin::G6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I2, LTDCPin::G7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I4, LTDCPin::B4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I5, LTDCPin::B5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I6, LTDCPin::B6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I7, LTDCPin::B7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I9, LTDCPin::VSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I10, LTDCPin::HSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I12, LTDCPin::HSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I13, LTDCPin::VSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I14, LTDCPin::PC> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I15, LTDCPin::R0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J0, LTDCPin::R1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J1, LTDCPin::R2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J2, LTDCPin::R3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J3, LTDCPin::R4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J4, LTDCPin::R5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J5, LTDCPin::R6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J6, LTDCPin::R7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J7, LTDCPin::G0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J8, LTDCPin::G1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J9, LTDCPin::G2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J10, LTDCPin::G3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J11, LTDCPin::G4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J12, LTDCPin::B0> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J13, LTDCPin::B1> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J14, LTDCPin::B2> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J15, LTDCPin::B3> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K0, LTDCPin::G5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K1, LTDCPin::G6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K2, LTDCPin::G7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K3, LTDCPin::B4> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K4, LTDCPin::B5> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K5, LTDCPin::B6> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K6, LTDCPin::B7> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K7, LTDCPin::DE> {
    	static constexpr GPIOAlt alt = GPIOAlt::_14;
    };
}


#endif // __STM32_htlLTDC__
