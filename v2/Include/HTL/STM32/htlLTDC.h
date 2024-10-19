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
		enum class PixelFormat {
			argb8888 = 0,
			rgb888 = 1,
			rgb565 = 2,
			argb1555 = 3,
			argb4444 = 4,
			l8 = 5,
			al44 = 6,
			al88 = 7
		};

		/// \brief Clock divider factor.
		///
		enum class ClockDivider {
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

		namespace internal {

			template <LayerID>
			struct LayerHardwareInfo;

			template<PinFunction, typename>
			struct PinFunctionInfo;
		}

		class LTDCDevice final {
			private:
				static LTDCDevice _instance;
			public:
				static constexpr LTDCDevice *pInst = &_instance;
                static constexpr LTDCDevice &rInst = _instance;
			private:
				LTDCDevice(const LTDCDevice &) = delete;
				LTDCDevice & operator = (const LTDCDevice &) = delete;
			private:
				LTDCDevice();
				void activate();
				void deactivate();
                void interruptService();
			public:
				void initialize(uint16_t width, uint16_t height, uint16_t hSync, uint16_t vSync, uint16_t hBP, uint16_t vBP, uint16_t hFP, uint16_t vFP);
				void deinitialize();
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinHSYNC() {
					auto af = internal::PinFunctionInfo<PinFunction::hsync, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_HSPOL;
					else if constexpr (polarity_ == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_HSPOL;
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinVSYNC() {
				    auto af = internal::PinFunctionInfo<PinFunction::vsync, pin_>::alt;
				    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_VSPOL;
					else if constexpr (polarity_ == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_VSPOL;
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinPC() {
				    auto af = internal::PinFunctionInfo<PinFunction::pc, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_PCPOL;
					else if constexpr (polarity_ == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_PCPOL;
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinDE() {
				    auto af = internal::PinFunctionInfo<PinFunction::de, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						LTDC->GCR |= LTDC_GCR_DEPOL;
					else if constexpr (polarity_ == PinPolarity::activeLow)
						LTDC->GCR &= ~LTDC_GCR_DEPOL;
				}
				template <typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initPinRX() {
					pinR2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r2, pinR2_>::alt);
					pinR3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r3, pinR3_>::alt);
					pinR4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r4, pinR4_>::alt);
					pinR5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r5, pinR5_>::alt);
					pinR6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r6, pinR6_>::alt);
					pinR7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r7, pinR7_>::alt);
				}
				template <typename pinR0_, typename pinR1_, typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initPinRX() {
				    pinR0_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r0, pinR0_>::alt);
				    pinR1_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r1, pinR1_>::alt);
				    pinR2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r2, pinR2_>::alt);
				    pinR3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r3, pinR3_>::alt);
				    pinR4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r4, pinR4_>::alt);
				    pinR5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r5, pinR5_>::alt);
				    pinR6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r6, pinR6_>::alt);
				    pinR7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::r7, pinR7_>::alt);
				}
				template <typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initPinGX() {
				    pinG2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g2, pinG2_>::alt);
				    pinG3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g3, pinG3_>::alt);
				    pinG4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g4, pinG4_>::alt);
				    pinG5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g5, pinG5_>::alt);
				    pinG6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g6, pinG6_>::alt);
				    pinG7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g7, pinG7_>::alt);
				}
				template <typename pinG0_, typename pinG1_, typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initPinGX() {
				    pinG0_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g0, pinG0_>::alt);
				    pinG1_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g1, pinG1_>::alt);
				    pinG2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g2, pinG2_>::alt);
				    pinG3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g3, pinG3_>::alt);
				    pinG4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g4, pinG4_>::alt);
				    pinG5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g5, pinG5_>::alt);
				    pinG6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g6, pinG6_>::alt);
				    pinG7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::g7, pinG7_>::alt);
				}
				template <typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initPinBX() {
				    pinB2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b2, pinB2_>::alt);
				    pinB3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b3, pinB3_>::alt);
				    pinB4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b4, pinB4_>::alt);
				    pinB5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b5, pinB5_>::alt);
				    pinB6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b6, pinB6_>::alt);
				    pinB7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b7, pinB7_>::alt);
				}
				template <typename pinB0_, typename pinB1_, typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initPinBX() {
				    pinB0_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b0, pinB0_>::alt);
				    pinB1_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b1, pinB1_>::alt);
				    pinB2_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b2, pinB2_>::alt);
				    pinB3_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b3, pinB3_>::alt);
				    pinB4_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b4, pinB4_>::alt);
				    pinB5_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b5, pinB5_>::alt);
				    pinB6_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b6, pinB6_>::alt);
				    pinB7_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, internal::PinFunctionInfo<PinFunction::b7, pinB7_>::alt);
				}
				inline void enable() {
					LTDC->GCR |= LTDC_GCR_LTDCEN;
				}
				inline void disable() {
					LTDC->GCR &= ~LTDC_GCR_LTDCEN;
				}
				void setBackgroundColor(uint32_t rgb);
				void reload();
                inline static void interruptHandler() {
                    _instance.interruptService();
                }
		};

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
				void setFrameFormat(PixelFormat format, int16_t width, int16_t pitch, int16_t lines);
				void setFrameBuffer(void *buffer);
				void setConstantAlpha(uint8_t a);
				void setDefaultColor(uint32_t argb);
				void setCLUTTable(uint32_t *rgb);
				void disableCLUTTable();
				void setKeyColor(uint32_t rgb);
				void disableKeyColor();
		};


		template <LayerID layerID_>
		class LTDCLayerDeviceX final: public LTDCLayerDevice {
			private:
				using HI = internal::LayerHardwareInfo<layerID_>;
			private:
				static constexpr uint32_t _layerAddr = HI::layerAddr;
				static LTDCLayerDeviceX _instance;
			public:
				static constexpr LTDCLayerDeviceX *pInst = &_instance;
				static constexpr LTDCLayerDeviceX &rInst = _instance;
			private:
				LTDCLayerDeviceX():
					LTDCLayerDevice(reinterpret_cast<LTDC_Layer_TypeDef*>(_layerAddr)) {
				}
		};
		template <LayerID layerID_>
		LTDCLayerDeviceX<layerID_> LTDCLayerDeviceX<layerID_>::_instance;

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
	}
}


#if defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlLTDC_AF.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlLTDC_AF.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlLTDC__
