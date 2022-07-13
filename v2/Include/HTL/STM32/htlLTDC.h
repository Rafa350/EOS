#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halLTDC.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/Graphics/eosColor.h"


namespace htl {

	enum class LTDCLayerNum: halLTDCLayerNum {
		layer0 = HAL_LTDC_LAYER_0,
		layer1 = HAL_LTDC_LAYER_1
	};

    template <LTDCLayerNum layerNum_>
    class LTDCLayer_x {
    	public:
			inline static void setWindow(int x, int y, int width, int height) {
				halLTDCLayerSetWindow(
					halLTDCLayerNum(layerNum_),
					x, y,
					width, height);
			}

			inline static void setFrameFormat(halLTDCPixelFormat format, int width, int pitch, int lines) {
				halLTDCLayerSetFrameFormat(
					halLTDCLayerNum(layerNum_),
					format,
					width,
					pitch,
					lines);
			}

			inline static void setFramBuffer(void *buffer) {
				halLTDCLayerSetFrameBuffer(
					halLTDCLayerNum(layerNum_),
					buffer);
			}

			inline static void update() {
				halLTDCLayerUpdate(
					halLTDCLayerNum(layerNum_));
			}
    };

    using LTDCLayer_0 = LTDCLayer_x<LTDCLayerNum::layer0>;
    using LTDCLayer_1 = LTDCLayer_x<LTDCLayerNum::layer1>;


    class LTDC_x {
		public:
			static const LTDCLayer_0 layer0;
			static const LTDCLayer_1 layer1;

		public:
		    inline static void initialize(const halLTDCSettings &settings) {
		    	halLTDCInitialize(&settings);
		    }

		    inline static void enable() {
		    	halLTDCEnable();
		    }

		    inline static void disable() {
		    	halLTDCDisable();
		    }

		    template <typename gpio_>
			inline static void initHSYNCPin() {
				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_HSYNC);
			}

			template <typename gpio_>
			inline static void initVSYNCPin() {
				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_VSYNC);
			}

			template <typename gpio_>
			inline static void initDOTCLKPin() {
				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_DOTCLK);
			}

			template <typename gpio_>
			inline static void initDEPin() {
				gpio_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpio_::GPIOAlt::ltdc_DE);
			}

			template <typename gpioR0_, typename gpioR1_, typename gpioR2_, typename gpioR3_,
					  typename gpioR4_, typename gpioR5_, typename gpioR6_, typename gpioR7_>
			inline static void initRPins() {
				gpioR0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR0_::GPIOAlt::ltdc_R0);
				gpioR1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR1_::GPIOAlt::ltdc_R1);
				gpioR2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR2_::GPIOAlt::ltdc_R2);
				gpioR3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR3_::GPIOAlt::ltdc_R3);
				gpioR4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR4_::GPIOAlt::ltdc_R4);
				gpioR5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR5_::GPIOAlt::ltdc_R5);
				gpioR6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR6_::GPIOAlt::ltdc_R6);
				gpioR7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioR7_::GPIOAlt::ltdc_R7);
			}

			template <typename gpioG0_, typename gpioG1_, typename gpioG2_, typename gpioG3_,
					  typename gpioG4_, typename gpioG5_, typename gpioG6_, typename gpioG7_>
			inline static void initGPins() {
				gpioG0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG0_::GPIOAlt::ltdc_G0);
				gpioG1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG1_::GPIOAlt::ltdc_G1);
				gpioG2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG2_::GPIOAlt::ltdc_G2);
				gpioG3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG3_::GPIOAlt::ltdc_G3);
				gpioG4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG4_::GPIOAlt::ltdc_G4);
				gpioG5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG5_::GPIOAlt::ltdc_G5);
				gpioG6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG6_::GPIOAlt::ltdc_G6);
				gpioG7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioG7_::GPIOAlt::ltdc_G7);
			}

			template <typename gpioB0_, typename gpioB1_, typename gpioB2_, typename gpioB3_,
					  typename gpioB4_, typename gpioB5_, typename gpioB6_, typename gpioB7_>
			inline static void initBPins() {
				gpioB0_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB0_::GPIOAlt::ltdc_B0);
				gpioB1_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB1_::GPIOAlt::ltdc_B1);
				gpioB2_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB2_::GPIOAlt::ltdc_B2);
				gpioB3_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB3_::GPIOAlt::ltdc_B3);
				gpioB4_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB4_::GPIOAlt::ltdc_B4);
				gpioB5_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB5_::GPIOAlt::ltdc_B5);
				gpioB6_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB6_::GPIOAlt::ltdc_B6);
				gpioB7_::initAlt(GPIODriver::pushPull, GPIOSpeed::fast, gpioB7_::GPIOAlt::ltdc_B7);
			}

			inline static void setBackgroundColor(eos::Color color) {
				uint32_t c = (color.getR() << 16) | (color.getG() << 8) | color.getB();
				halLTDCSetBackgroundColor(c);
			}
	};

	using LTDC_1 = LTDC_x;


	// Valors que depenen del format de color
    //
	template <eos::ColorFormat format_>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::rgb888> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::argb8888> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::rgb565> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB565;
	};
	template<>
	struct LTDCPixelFormatFor<eos::ColorFormat::l8> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_L8;
	};

}


#endif // __STM32_htlLTDC__
