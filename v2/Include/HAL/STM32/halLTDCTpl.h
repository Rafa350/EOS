#ifndef __STM32_halLTDCTpl__
#define __STM32_halLTDCTpl__


// EOS includes
//
#include "HAL/STM32/halLTDC.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	enum class LtdcLayerNum: LTDCLayerNum {
		layer0 = HAL_LTDC_LAYER_0,
		layer1 = HAL_LTDC_LAYER_1
	};

    template <LtdcLayerNum layerNum>
    class LtdcLayer {

    	inline static void setWindow(int x, int y, int width, int height) {
    		halLTDCLayerSetWindow(
    			LTDCLayerNum(layerNum),
				x, y,
				width, height);
    	}

    	inline static void setFrameFormat(LTDCPixelFormat format, int width, int pitch, int lines) {
    		halLTDCLayerSetFrameFormat(
    			LTDCLayerNum(layerNum),
    			format,
				width,
    			pitch,
    			lines);
    	}

    	inline static void setFramBuffer(void* buffer) {
			halLTDCLayerSetFrameBuffer(
				LTDCLayerNum(layerNum),
				buffer);
    	}

    	inline static void update() {
    		halLTDCLayerUpdate(
    			LTDCLayerNum(layerNum));
    	}
    };

    // Valors que depenen del format de color
    //
	template <ColorFormat FORMAT>
	struct LTDCPixelFormatFor {
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb888> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::argb8888> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB888;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::rgb565> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_RGB565;
	};
	template<>
	struct LTDCPixelFormatFor<ColorFormat::l8> {
		constexpr static const LTDCPixelFormat value = HAL_LTDC_FORMAT_L8;
	};

}


#endif
