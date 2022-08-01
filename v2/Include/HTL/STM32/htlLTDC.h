#pragma once
#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "eos.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/Graphics/eosColor.h"


namespace htl {

	/// \brief Control signals pin polarity
	//
    enum class LTDCPolarity {
    	noChange,
    	activeLow,
		activeHigh
    };

    /// \brief Image format
    ///
    enum class LTDCPixelFormat {
    	argb8888,
		rgb888,
		rgb565,
		argb1555,
		argb4444,
		l8,
		al44,
		al88
    };

    enum class LTDCEvent {
    	line = 0,
		reload = 3,
		fifoError = 1,
		transferError = 2
    };

    /// \brief GPIO alternative pin identifiers
    ///
    enum class LTDCPin {
    	pinHSYNC,
		pinVSYNC,
		pinDE,
		pinPC,
		pinR0, pinR1, pinR2, pinR3, pinR4, pinR5, pinR6, pinR7,
		pinG0, pinG1, pinG2, pinG3, pinG4, pinG5, pinG6, pinG7,
		pinB0, pinB1, pinB2, pinB3, pinB4, pinB5, pinB6, pinB7
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

			inline static void activate() {

				RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
			    __DSB();
			}

			inline static void deactivate() {

				RCC->APB2ENR &= ~RCC_APB2ENR_LTDCEN;
			}

		public:
		    static void init(
		    	uint16_t width,
				uint16_t height,
		    	uint16_t hSync,
				uint16_t vSync,
				uint16_t hBP,
				uint16_t vBP,
				uint16_t hFP,
				uint16_t vFP) {

		    	uint32_t tmp;

		    	// Activa el rellotge del dispositiu
		    	//
		    	activate();

		    	// Desactiva el dispositiu
		    	//
		    	LTDC->GCR &= ~LTDC_GCR_LTDCEN;

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

		    static void deInit() {

		    	disable();
		    	deactivate();
		    }

		    static void enable() {

		    	LTDC->GCR |= LTDC_GCR_LTDCEN;
		    }

		    static void disable() {

		    	LTDC->GCR &= ~LTDC_GCR_LTDCEN;
		    }

		    template <typename gpio_>
			static void initHSYNCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

		    	gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::pinHSYNC>::alt);
     			setHSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initVSYNCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::pinVSYNC>::alt);
     			setVSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initPCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::pinPC>::alt);
				setPCPolarity(polarity);
			}

			template <typename gpio_>
			static void initDEPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpio_, LTDCPin::pinDE>::alt);
				setDEPolarity(polarity);
			}

			template <typename gpioR0_, typename gpioR1_, typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR0_, LTDCPin::pinR0>::alt);
				gpioR1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR1_, LTDCPin::pinR1>::alt);
				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR2_, LTDCPin::pinR2>::alt);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR3_, LTDCPin::pinR3>::alt);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR4_, LTDCPin::pinR4>::alt);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR5_, LTDCPin::pinR5>::alt);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR6_, LTDCPin::pinR6>::alt);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR7_, LTDCPin::pinR7>::alt);
			}

			template <typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR2_, LTDCPin::pinR2>::alt);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR3_, LTDCPin::pinR3>::alt);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR4_, LTDCPin::pinR4>::alt);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR5_, LTDCPin::pinR5>::alt);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR6_, LTDCPin::pinR6>::alt);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioR7_, LTDCPin::pinR7>::alt);
			}

			template <typename gpioG0_, typename gpioG1_, typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG0_, LTDCPin::pinG0>::alt);
				gpioG1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG1_, LTDCPin::pinG1>::alt);
				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG2_, LTDCPin::pinG2>::alt);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG3_, LTDCPin::pinG3>::alt);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG4_, LTDCPin::pinG4>::alt);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG5_, LTDCPin::pinG5>::alt);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG6_, LTDCPin::pinG6>::alt);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG7_, LTDCPin::pinG7>::alt);
			}

			template <typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG2_, LTDCPin::pinG2>::alt);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG3_, LTDCPin::pinG3>::alt);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG4_, LTDCPin::pinG4>::alt);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG5_, LTDCPin::pinG5>::alt);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG6_, LTDCPin::pinG6>::alt);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioG7_, LTDCPin::pinG7>::alt);
			}

			template <typename gpioB0_, typename gpioB1_, typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB0_, LTDCPin::pinB0>::alt);
				gpioB1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB1_, LTDCPin::pinB1>::alt);
				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB2_, LTDCPin::pinB2>::alt);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB3_, LTDCPin::pinB3>::alt);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB4_, LTDCPin::pinB4>::alt);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB5_, LTDCPin::pinB5>::alt);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB6_, LTDCPin::pinB6>::alt);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB7_, LTDCPin::pinB7>::alt);
			}

			template <typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB2_, LTDCPin::pinB2>::alt);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB3_, LTDCPin::pinB3>::alt);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB4_, LTDCPin::pinB4>::alt);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB5_, LTDCPin::pinB5>::alt);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB6_, LTDCPin::pinB6>::alt);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, LTDCPinTrait<gpioB7_, LTDCPin::pinB7>::alt);
			}

			static void setHSYNCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_HSPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_HSPOL;
			}

			static void setVSYNCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_VSPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_VSPOL;
			}

			static void setDEPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_DEPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_DEPOL;
			}

			static void setPCPolarity(
				LTDCPolarity polarity) {

				if (polarity == LTDCPolarity::activeHigh)
			    	LTDC->GCR |= LTDC_GCR_PCPOL;
			    else if (polarity == LTDCPolarity::activeLow)
				    LTDC->GCR &= ~LTDC_GCR_PCPOL;
			}

			static void setBackgroundColor(
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

			static void update() {

				if ((LTDC->GCR & LTDC_GCR_LTDCEN) == 0)
			    	LTDC->SRCR |= LTDC_SRCR_IMR;

			    // En cas contrari, fa l'actualitzacio durant la sincronitzacio
			    // vertical, i espera que finalitzi.
			    //
			    else {
			    	LTDC->SRCR |= LTDC_SRCR_VBR;
					while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
						continue;
					while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 1)
						continue;
			    }
			}

			static void enableInterrrupt(
				LTDCEvent event) {

				LTDC->IER |= 1 << uint32_t(event);
			}

			static void disableInterrupt(
				LTDCEvent event) {

				LTDC->IER &= ~(1 << uint32_t(event));
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

    	public:
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
			}

			static void setFrameFormat(
				LTDCPixelFormat format,
				int width,
				int pitch,
				int lines) {

				uint32_t tmp;
				LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

				tmp = regs->PFCR;
			    tmp &= ~(LTDC_LxPFCR_PF);
			    switch (format) {
					case LTDCPixelFormat::rgb888:
						tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
						break;

					case LTDCPixelFormat::rgb565:
			    		tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
			    		break;

			    	case LTDCPixelFormat::l8:
			    		tmp |= 0b101 << LTDC_LxPFCR_PF_Pos;
			    		break;

			    	default:
			    		break;
			    }
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
			}

			static void setFrameBuffer(
				void *buffer) {

				LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);

				if (buffer== nullptr)
				    regs->CR &= ~LTDC_LxCR_LEN;
				else {
					regs->CFBAR = (uint32_t)buffer;
					regs->CR |= LTDC_LxCR_LEN;
				}
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
			}

			static void setChroma(
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
			}

			static void disableChroma() {

				LTDC_Layer_TypeDef *regs = reinterpret_cast<LTDC_Layer_TypeDef*>(_addr);
			    regs->CR &= ~LTDC_LxCR_COLKEN;
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
    struct LTDCPinTrait<GPIO_A3, LTDCPin::pinB5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A4, LTDCPin::pinVSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A6, LTDCPin::pinG2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A8, LTDCPin::pinR6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A11, LTDCPin::pinR4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_A12, LTDCPin::pinR5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B8, LTDCPin::pinR6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B9, LTDCPin::pinB7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B10, LTDCPin::pinG4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_B11, LTDCPin::pinG5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C6, LTDCPin::pinHSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C7, LTDCPin::pinG6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_C10, LTDCPin::pinR2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D3, LTDCPin::pinG7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D6, LTDCPin::pinB2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_D10, LTDCPin::pinB3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E4, LTDCPin::pinB0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E5, LTDCPin::pinG0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E6, LTDCPin::pinG1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E11, LTDCPin::pinG3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E12, LTDCPin::pinB4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E13, LTDCPin::pinDE> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E14, LTDCPin::pinPC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_E15, LTDCPin::pinR7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_F10, LTDCPin::pinDE> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G6, LTDCPin::pinR7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G7, LTDCPin::pinPC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G10, LTDCPin::pinB2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G10, LTDCPin::pinG3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt9;
    };

    template <>
    struct LTDCPinTrait<GPIO_G11, LTDCPin::pinB3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G12, LTDCPin::pinB1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_G12, LTDCPin::pinB4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt9;
    };

    template <>
    struct LTDCPinTrait<GPIO_H2, LTDCPin::pinR0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H3, LTDCPin::pinR1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H8, LTDCPin::pinR2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H9, LTDCPin::pinR3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H10, LTDCPin::pinR4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H11, LTDCPin::pinR5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H12, LTDCPin::pinR6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H13, LTDCPin::pinG2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H14, LTDCPin::pinG3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_H15, LTDCPin::pinG4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I0, LTDCPin::pinG5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I1, LTDCPin::pinG6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I2, LTDCPin::pinG7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I4, LTDCPin::pinB4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I5, LTDCPin::pinB5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I6, LTDCPin::pinB6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I7, LTDCPin::pinB7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I9, LTDCPin::pinVSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I10, LTDCPin::pinHSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I12, LTDCPin::pinHSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I13, LTDCPin::pinVSYNC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I14, LTDCPin::pinPC> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_I15, LTDCPin::pinR0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J0, LTDCPin::pinR1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J1, LTDCPin::pinR2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J2, LTDCPin::pinR3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J3, LTDCPin::pinR4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J4, LTDCPin::pinR5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J5, LTDCPin::pinR6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J6, LTDCPin::pinR7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J7, LTDCPin::pinG0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J8, LTDCPin::pinG1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J9, LTDCPin::pinG2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J10, LTDCPin::pinG3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J11, LTDCPin::pinG4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J12, LTDCPin::pinB0> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J13, LTDCPin::pinB1> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J14, LTDCPin::pinB2> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_J15, LTDCPin::pinB3> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K0, LTDCPin::pinG5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K1, LTDCPin::pinG6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K2, LTDCPin::pinG7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K3, LTDCPin::pinB4> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K4, LTDCPin::pinB5> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K5, LTDCPin::pinB6> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K6, LTDCPin::pinB7> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    template <>
    struct LTDCPinTrait<GPIO_K7, LTDCPin::pinDE> {
    	static constexpr GPIOAlt alt = GPIOAlt::alt14;
    };

    // Valors que depenen del format de color
    //
	template <eos::ColorFormat format_>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::rgb888> {
		static const LTDCPixelFormat value = LTDCPixelFormat::rgb888;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::argb8888> {
		static const LTDCPixelFormat value = LTDCPixelFormat::argb8888;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::rgb565> {
		static const LTDCPixelFormat value = LTDCPixelFormat::rgb565;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::l8> {
		static const LTDCPixelFormat value = LTDCPixelFormat::l8;
	};

}


#endif // __STM32_htlLTDC__
