#ifndef __STM32_halLTDCTpl__
#define __STM32_halLTDCTpl__


// EOS includes
//
#include "HAL/STM32/halLTDC.h"
#include "HAL/STM32/halGPIOTpl.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	enum class LTDCLayerNum: halLTDCLayerNum {
		layer0 = HAL_LTDC_LAYER_0,
		layer1 = HAL_LTDC_LAYER_1
	};

	class LTDCAdapter {
		public:
		    inline static void initialize(const halLTDCSettings& settings) {
		    	halLTDCInitialize(&settings);
		    }

			template <GPIOPort port, GPIOPin pin>
			inline static void setHSYNCPin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_HSYNC);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setVSYNCPin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_VSYNC);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setDOTCLKPin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_DOTCLK);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setDEPin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_DE);
			}

			template <GPIOPort port0, GPIOPin pin0,
			          GPIOPort port1, GPIOPin pin1,
			          GPIOPort port2, GPIOPin pin2,
			          GPIOPort port3, GPIOPin pin3,
			          GPIOPort port4, GPIOPin pin4,
			          GPIOPort port5, GPIOPin pin5,
			          GPIOPort port6, GPIOPin pin6,
			          GPIOPort port7, GPIOPin pin7>
			inline static void setRPins(
					GPIOPinAdapter<port0, pin0> pinR0Adapter,
					GPIOPinAdapter<port1, pin1> pinR1Adapter,
					GPIOPinAdapter<port2, pin2> pinR2Adapter,
					GPIOPinAdapter<port3, pin3> pinR3Adapter,
					GPIOPinAdapter<port4, pin4> pinR4Adapter,
					GPIOPinAdapter<port5, pin5> pinR5Adapter,
					GPIOPinAdapter<port6, pin6> pinR6Adapter,
					GPIOPinAdapter<port7, pin7> pinR7Adapter) {
				pinR0Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port0, pin0>::GPIOAlt::ltdc_R0);
				pinR1Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port1, pin1>::GPIOAlt::ltdc_R1);
				pinR2Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port2, pin2>::GPIOAlt::ltdc_R2);
				pinR3Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port3, pin3>::GPIOAlt::ltdc_R3);
				pinR4Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port4, pin4>::GPIOAlt::ltdc_R4);
				pinR5Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port5, pin5>::GPIOAlt::ltdc_R5);
				pinR6Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port6, pin6>::GPIOAlt::ltdc_R6);
				pinR7Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port7, pin7>::GPIOAlt::ltdc_R7);
			}

			template <GPIOPort port0, GPIOPin pin0,
			          GPIOPort port1, GPIOPin pin1,
			          GPIOPort port2, GPIOPin pin2,
			          GPIOPort port3, GPIOPin pin3,
			          GPIOPort port4, GPIOPin pin4,
			          GPIOPort port5, GPIOPin pin5,
			          GPIOPort port6, GPIOPin pin6,
			          GPIOPort port7, GPIOPin pin7>
			inline static void setGPins(
					GPIOPinAdapter<port0, pin0> pinG0Adapter,
					GPIOPinAdapter<port1, pin1> pinG1Adapter,
					GPIOPinAdapter<port2, pin2> pinG2Adapter,
					GPIOPinAdapter<port3, pin3> pinG3Adapter,
					GPIOPinAdapter<port4, pin4> pinG4Adapter,
					GPIOPinAdapter<port5, pin5> pinG5Adapter,
					GPIOPinAdapter<port6, pin6> pinG6Adapter,
					GPIOPinAdapter<port7, pin7> pinG7Adapter) {
				pinG0Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port0, pin0>::GPIOAlt::ltdc_G0);
				pinG1Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port1, pin1>::GPIOAlt::ltdc_G1);
				pinG2Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port2, pin2>::GPIOAlt::ltdc_G2);
				pinG3Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port3, pin3>::GPIOAlt::ltdc_G3);
				pinG4Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port4, pin4>::GPIOAlt::ltdc_G4);
				pinG5Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port5, pin5>::GPIOAlt::ltdc_G5);
				pinG6Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port6, pin6>::GPIOAlt::ltdc_G6);
				pinG7Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port7, pin7>::GPIOAlt::ltdc_G7);
			}

			template <GPIOPort port0, GPIOPin pin0,
			          GPIOPort port1, GPIOPin pin1,
			          GPIOPort port2, GPIOPin pin2,
			          GPIOPort port3, GPIOPin pin3,
			          GPIOPort port4, GPIOPin pin4,
			          GPIOPort port5, GPIOPin pin5,
			          GPIOPort port6, GPIOPin pin6,
			          GPIOPort port7, GPIOPin pin7>
			inline static void setBPins(
					GPIOPinAdapter<port0, pin0> pinB0Adapter,
					GPIOPinAdapter<port1, pin1> pinB1Adapter,
					GPIOPinAdapter<port2, pin2> pinB2Adapter,
					GPIOPinAdapter<port3, pin3> pinB3Adapter,
					GPIOPinAdapter<port4, pin4> pinB4Adapter,
					GPIOPinAdapter<port5, pin5> pinB5Adapter,
					GPIOPinAdapter<port6, pin6> pinB6Adapter,
					GPIOPinAdapter<port7, pin7> pinB7Adapter) {
				pinB0Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port0, pin0>::GPIOAlt::ltdc_B0);
				pinB1Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port1, pin1>::GPIOAlt::ltdc_B1);
				pinB2Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port2, pin2>::GPIOAlt::ltdc_B2);
				pinB3Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port3, pin3>::GPIOAlt::ltdc_B3);
				pinB4Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port4, pin4>::GPIOAlt::ltdc_B4);
				pinB5Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port5, pin5>::GPIOAlt::ltdc_B5);
				pinB6Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port6, pin6>::GPIOAlt::ltdc_B6);
				pinB7Adapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port7, pin7>::GPIOAlt::ltdc_B7);
			}

			inline static void setBackgroundColor(Color color) {
				uint32_t c = (color.getR() << 16) | (color.getG() << 8) | color.getB();
				halLTDCSetBackgroundColor(c);
			}
	};

    template <LTDCLayerNum layerNum>
    class LTDCLayerAdapter {

    	inline static void setWindow(int x, int y, int width, int height) {
    		halLTDCLayerSetWindow(
    			halLTDCLayerNum(layerNum),
				x, y,
				width, height);
    	}

    	inline static void setFrameFormat(halLTDCPixelFormat format, int width, int pitch, int lines) {
    		halLTDCLayerSetFrameFormat(
    			halLTDCLayerNum(layerNum),
    			format,
				width,
    			pitch,
    			lines);
    	}

    	inline static void setFramBuffer(void* buffer) {
			halLTDCLayerSetFrameBuffer(
				halLTDCLayerNum(layerNum),
				buffer);
    	}

    	inline static void update() {
    		halLTDCLayerUpdate(
    			halLTDCLayerNum(layerNum));
    	}
    };

    // Valors que depenen del format de color
    //
	template <ColorFormat FORMAT>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb888> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::argb8888> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb565> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_RGB565;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::l8> {
		constexpr static const halLTDCPixelFormat value = HAL_LTDC_FORMAT_L8;
	};

}


#endif
