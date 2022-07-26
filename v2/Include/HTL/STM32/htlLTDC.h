#pragma once
#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "eos.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/Graphics/eosColor.h"


namespace htl {

    enum class LTDCPolarity {
    	noChange,
    	activeLow,
		activeHigh
    };

    enum class LTDCPixelFormat {
    	rgb8888,
		rgb888,
		rgb565,
		l8
    };

    enum class LTDCEvent {
    	line = 0,
		reload = 3,
		fifoError = 1,
		transferError = 2
    };

    using LTDCInterruptParam = void*;
    using LTDCInterruptFunction = void (*)(LTDCEvent, LTDCInterruptParam);

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

		    	gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_HSYNC);
     			setHSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initVSYNCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_VSYNC);
     			setVSYNCPolarity(polarity);
			}

			template <typename gpio_>
			static void initPCPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_DOTCLK);
				setPCPolarity(polarity);
			}

			template <typename gpio_>
			static void initDEPin(
				LTDCPolarity polarity = LTDCPolarity::noChange) {

				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_DE);
				setDEPolarity(polarity);
			}

			template <typename gpioR0_, typename gpioR1_, typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR0_::GPIOAlt::ltdc_R0);
				gpioR1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR1_::GPIOAlt::ltdc_R1);
				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR2_::GPIOAlt::ltdc_R2);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR3_::GPIOAlt::ltdc_R3);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR4_::GPIOAlt::ltdc_R4);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR5_::GPIOAlt::ltdc_R5);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR6_::GPIOAlt::ltdc_R6);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR7_::GPIOAlt::ltdc_R7);
			}

			template <typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			static void initRPins() {

				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR2_::GPIOAlt::ltdc_R2);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR3_::GPIOAlt::ltdc_R3);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR4_::GPIOAlt::ltdc_R4);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR5_::GPIOAlt::ltdc_R5);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR6_::GPIOAlt::ltdc_R6);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR7_::GPIOAlt::ltdc_R7);
			}

			template <typename gpioG0_, typename gpioG1_, typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG0_::GPIOAlt::ltdc_G0);
				gpioG1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG1_::GPIOAlt::ltdc_G1);
				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG2_::GPIOAlt::ltdc_G2);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG3_::GPIOAlt::ltdc_G3);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG4_::GPIOAlt::ltdc_G4);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG5_::GPIOAlt::ltdc_G5);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG6_::GPIOAlt::ltdc_G6);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG7_::GPIOAlt::ltdc_G7);
			}

			template <typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			static void initGPins() {

				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG2_::GPIOAlt::ltdc_G2);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG3_::GPIOAlt::ltdc_G3);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG4_::GPIOAlt::ltdc_G4);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG5_::GPIOAlt::ltdc_G5);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG6_::GPIOAlt::ltdc_G6);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG7_::GPIOAlt::ltdc_G7);
			}

			template <typename gpioB0_, typename gpioB1_, typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB0_::GPIOAlt::ltdc_B0);
				gpioB1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB1_::GPIOAlt::ltdc_B1);
				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB2_::GPIOAlt::ltdc_B2);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB3_::GPIOAlt::ltdc_B3);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB4_::GPIOAlt::ltdc_B4);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB5_::GPIOAlt::ltdc_B5);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB6_::GPIOAlt::ltdc_B6);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB7_::GPIOAlt::ltdc_B7);
			}

			template <typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			static void initBPins() {

				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB2_::GPIOAlt::ltdc_B2);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB3_::GPIOAlt::ltdc_B3);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB4_::GPIOAlt::ltdc_B4);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB5_::GPIOAlt::ltdc_B5);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB6_::GPIOAlt::ltdc_B6);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB7_::GPIOAlt::ltdc_B7);
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
			    	case LTDCPixelFormat::rgb565:
			    		tmp |= 0b010 << LTDC_LxPFCR_PF_Pos;
			    		break;

			    	case LTDCPixelFormat::rgb888:
			    		tmp |= 0b001 << LTDC_LxPFCR_PF_Pos;
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
		static const uint32_t addr = LTDC_Layer1_BASE;
	};

    template <>
	struct LTDCLayerTrait<LTDCLayerNum::layer2> {
		static const uint32_t addr = LTDC_Layer2_BASE;
	};


    // Valors que depenen del format de color
    //
	template <eos::ColorFormat format_>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::rgb888> {
		static const LTDCPixelFormat value = LTDCPixelFormat::rgb8888;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::argb8888> {
		static const LTDCPixelFormat value = LTDCPixelFormat::rgb888;
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
