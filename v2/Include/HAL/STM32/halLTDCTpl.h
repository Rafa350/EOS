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

			template <GPIOPort port, GPIOPin pin>
			inline static void setR0Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R0);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR1Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R1);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR2Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R2);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR3Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R3);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR4Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R4);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR5Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R5);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR6Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R6);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setR7Pin(GPIOPinAdapter<port, pin> pinAdapter) {
				pinAdapter.initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					GPIOPinAdapter<port, pin>::GPIOAlt::ltdc_R7);
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
