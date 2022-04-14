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
		    inline static void initialize(const halLTDCSettings &settings) {
		    	halLTDCInitialize(&settings);
		    }

			template <typename pinAdapter_>
			inline static void initHSYNCPin() {
				pinAdapter_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapter_::GPIOAlt::ltdc_HSYNC);
			}

			template <typename pinAdapter_>
			inline static void initVSYNCPin() {
				pinAdapter_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapter_::GPIOAlt::ltdc_VSYNC);
			}

			template <typename pinAdapter_>
			inline static void initDOTCLKPin() {
				pinAdapter_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapter_::GPIOAlt::ltdc_DOTCLK);
			}

			template <typename pinAdapter_>
			inline static void initDEPin() {
				pinAdapter_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapter_::GPIOAlt::ltdc_DE);
			}

			template <typename pinAdapterR0_,
			          typename pinAdapterR1_,
					  typename pinAdapterR2_,
					  typename pinAdapterR3_,
					  typename pinAdapterR4_,
					  typename pinAdapterR5_,
					  typename pinAdapterR6_,
					  typename pinAdapterR7_>
			inline static void initRPins() {
				pinAdapterR0_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR0_::GPIOAlt::ltdc_R0);
				pinAdapterR1_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR1_::GPIOAlt::ltdc_R1);
				pinAdapterR2_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR2_::GPIOAlt::ltdc_R2);
				pinAdapterR3_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR3_::GPIOAlt::ltdc_R3);
				pinAdapterR4_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR4_::GPIOAlt::ltdc_R4);
				pinAdapterR5_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR5_::GPIOAlt::ltdc_R5);
				pinAdapterR6_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR6_::GPIOAlt::ltdc_R6);
				pinAdapterR7_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterR7_::GPIOAlt::ltdc_R7);
			}

			template <typename pinAdapterG0_,
                      typename pinAdapterG1_,
					  typename pinAdapterG2_,
					  typename pinAdapterG3_,
					  typename pinAdapterG4_,
					  typename pinAdapterG5_,
					  typename pinAdapterG6_,
					  typename pinAdapterG7_>
			inline static void initGPins() {
				pinAdapterG0_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG0_::GPIOAlt::ltdc_G0);
				pinAdapterG1_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG1_::GPIOAlt::ltdc_G1);
				pinAdapterG2_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG2_::GPIOAlt::ltdc_G2);
				pinAdapterG3_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG3_::GPIOAlt::ltdc_G3);
				pinAdapterG4_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG4_::GPIOAlt::ltdc_G4);
				pinAdapterG5_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG5_::GPIOAlt::ltdc_G5);
				pinAdapterG6_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG6_::GPIOAlt::ltdc_G6);
				pinAdapterG7_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterG7_::GPIOAlt::ltdc_G7);
			}

			template <typename pinAdapterB0_,
					  typename pinAdapterB1_,
					  typename pinAdapterB2_,
					  typename pinAdapterB3_,
					  typename pinAdapterB4_,
					  typename pinAdapterB5_,
					  typename pinAdapterB6_,
					  typename pinAdapterB7_>
			inline static void initBPins() {
				pinAdapterB0_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB0_::GPIOAlt::ltdc_B0);
				pinAdapterB1_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB1_::GPIOAlt::ltdc_B1);
				pinAdapterB2_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB2_::GPIOAlt::ltdc_B2);
				pinAdapterB3_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB3_::GPIOAlt::ltdc_B3);
				pinAdapterB4_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB4_::GPIOAlt::ltdc_B4);
				pinAdapterB5_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB5_::GPIOAlt::ltdc_B5);
				pinAdapterB6_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB6_::GPIOAlt::ltdc_B6);
				pinAdapterB7_::initAlt(
					GPIOSpeed::fast,
					GPIODriver::pushPull,
					pinAdapterB7_::GPIOAlt::ltdc_B7);
			}

			inline static void setBackgroundColor(Color color) {
				uint32_t c = (color.getR() << 16) | (color.getG() << 8) | color.getB();
				halLTDCSetBackgroundColor(c);
			}
	};

	typedef LTDCAdapter LTDC_1;


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

    	inline static void setFramBuffer(void *buffer) {
			halLTDCLayerSetFrameBuffer(
				halLTDCLayerNum(layerNum),
				buffer);
    	}

    	inline static void update() {
    		halLTDCLayerUpdate(
    			halLTDCLayerNum(layerNum));
    	}
    };

    typedef LTDCLayerAdapter<LTDCLayerNum::layer0> LTDCLayer_L0;
    typedef LTDCLayerAdapter<LTDCLayerNum::layer1> LTDCLayer_L1;


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
