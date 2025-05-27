#pragma once
#ifndef __STM32_htlLTDC__
#define __STM32_htlLTDC__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {
	namespace ltdc {

		enum class DeviceID {
			ltdc
		};

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

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;
		}

		class LTDCDevice final {
			private:
				template <PinFunction pinFunction_, gpio::PortID portID_, gpio::PinID pinID_> using LTDCPins = internal::PinFunctionInfo<DeviceID::ltdc, pinFunction_, portID_, pinID_>;

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
					auto af = LTDCPins<PinFunction::hsync, pin_::portID, pin_::pinID>::value;
                    gpio::initAlternateOutput<pin_::portID, pin_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						bits::set(LTDC->GCR, LTDC_GCR_HSPOL);
					else if constexpr (polarity_ == PinPolarity::activeLow)
						bits::clear(LTDC->GCR, LTDC_GCR_HSPOL);
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinVSYNC() {
				    auto af = LTDCPins<PinFunction::vsync, pin_::portID, pin_::pinID>::value;
				    gpio::initAlternateOutput<pin_::portID, pin_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						bits::set(LTDC->GCR, LTDC_GCR_VSPOL);
					else if constexpr (polarity_ == PinPolarity::activeLow)
						bits::clear(LTDC->GCR, LTDC_GCR_VSPOL);
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinPC() {
				    auto af = LTDCPins<PinFunction::pc, pin_::portID, pin_::pinID>::value;
                    gpio::initAlternateOutput<pin_::portID, pin_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						bits::set(LTDC->GCR, LTDC_GCR_PCPOL);
					else if constexpr (polarity_ == PinPolarity::activeLow)
						bits::clear(LTDC->GCR, LTDC_GCR_PCPOL);
				}
				template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
				void initPinDE() {
				    auto af = LTDCPins<PinFunction::de, pin_::portID, pin_::pinID>::value;
                    gpio::initAlternateOutput<pin_::portID, pin_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
					if constexpr (polarity_ == PinPolarity::activeHigh)
						bits::set(LTDC->GCR, LTDC_GCR_DEPOL);
					else if constexpr (polarity_ == PinPolarity::activeLow)
						bits::clear(LTDC->GCR, LTDC_GCR_DEPOL);
				}
				template <typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initPinRX() {
					gpio::initAlternateOutput<pinR2_::portID, pinR2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r2, pinR2_::portID, pinR2_::pinID>::value);
					gpio::initAlternateOutput<pinR3_::portID, pinR3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r3, pinR3_::portID, pinR3_::pinID>::value);
					gpio::initAlternateOutput<pinR4_::portID, pinR4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r4, pinR4_::portID, pinR4_::pinID>::value);
					gpio::initAlternateOutput<pinR5_::portID, pinR5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r5, pinR5_::portID, pinR5_::pinID>::value);
					gpio::initAlternateOutput<pinR6_::portID, pinR6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r6, pinR6_::portID, pinR6_::pinID>::value);
					gpio::initAlternateOutput<pinR7_::portID, pinR7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r7, pinR7_::portID, pinR7_::pinID>::value);
				}
				template <typename pinR0_, typename pinR1_, typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
				void initPinRX() {
				    gpio::initAlternateOutput<pinR0_::portID, pinR0_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r0, pinR0_::portID, pinR0_::pinID>::value);
				    gpio::initAlternateOutput<pinR1_::portID, pinR1_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r1, pinR1_::portID, pinR1_::pinID>::value);
				    gpio::initAlternateOutput<pinR2_::portID, pinR2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r2, pinR2_::portID, pinR2_::pinID>::value);
				    gpio::initAlternateOutput<pinR3_::portID, pinR3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r3, pinR3_::portID, pinR3_::pinID>::value);
				    gpio::initAlternateOutput<pinR4_::portID, pinR4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r4, pinR4_::portID, pinR4_::pinID>::value);
				    gpio::initAlternateOutput<pinR5_::portID, pinR5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r5, pinR5_::portID, pinR5_::pinID>::value);
				    gpio::initAlternateOutput<pinR6_::portID, pinR6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r6, pinR6_::portID, pinR6_::pinID>::value);
				    gpio::initAlternateOutput<pinR7_::portID, pinR7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::r7, pinR7_::portID, pinR7_::pinID>::value);
				}
				template <typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initPinGX() {
				    gpio::initAlternateOutput<pinG2_::portID, pinG2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g2, pinG2_::portID, pinG2_::pinID>::value);
				    gpio::initAlternateOutput<pinG3_::portID, pinG3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g3, pinG3_::portID, pinG3_::pinID>::value);
				    gpio::initAlternateOutput<pinG4_::portID, pinG4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g4, pinG4_::portID, pinG4_::pinID>::value);
				    gpio::initAlternateOutput<pinG5_::portID, pinG5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g5, pinG5_::portID, pinG5_::pinID>::value);
				    gpio::initAlternateOutput<pinG6_::portID, pinG6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g6, pinG6_::portID, pinG6_::pinID>::value);
				    gpio::initAlternateOutput<pinG7_::portID, pinG7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g7, pinG7_::portID, pinG7_::pinID>::value);
				}
				template <typename pinG0_, typename pinG1_, typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
				void initPinGX() {
					gpio::initAlternateOutput<pinG0_::portID, pinG0_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g0, pinG0_::portID, pinG0_::pinID>::value);
					gpio::initAlternateOutput<pinG1_::portID, pinG1_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g1, pinG1_::portID, pinG1_::pinID>::value);
					gpio::initAlternateOutput<pinG2_::portID, pinG2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g2, pinG2_::portID, pinG2_::pinID>::value);
					gpio::initAlternateOutput<pinG3_::portID, pinG3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g3, pinG3_::portID, pinG3_::pinID>::value);
					gpio::initAlternateOutput<pinG4_::portID, pinG4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g4, pinG4_::portID, pinG4_::pinID>::value);
					gpio::initAlternateOutput<pinG5_::portID, pinG5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g5, pinG5_::portID, pinG5_::pinID>::value);
					gpio::initAlternateOutput<pinG6_::portID, pinG6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g6, pinG6_::portID, pinG6_::pinID>::value);
					gpio::initAlternateOutput<pinG7_::portID, pinG7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::g7, pinG7_::portID, pinG7_::pinID>::value);
				}
				template <typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initPinBX() {
					gpio::initAlternateOutput<pinB2_::portID, pinB2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b2, pinB2_::portID, pinB2_::pinID>::value);
					gpio::initAlternateOutput<pinB3_::portID, pinB3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b3, pinB3_::portID, pinB3_::pinID>::value);
					gpio::initAlternateOutput<pinB4_::portID, pinB4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b4, pinB4_::portID, pinB4_::pinID>::value);
					gpio::initAlternateOutput<pinB5_::portID, pinB5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b5, pinB5_::portID, pinB5_::pinID>::value);
					gpio::initAlternateOutput<pinB6_::portID, pinB6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b6, pinB6_::portID, pinB6_::pinID>::value);
					gpio::initAlternateOutput<pinB7_::portID, pinB7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b7, pinB7_::portID, pinB7_::pinID>::value);
				}
				template <typename pinB0_, typename pinB1_, typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
				void initPinBX() {
					gpio::initAlternateOutput<pinB0_::portID, pinB0_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b0, pinB0_::portID, pinB0_::pinID>::value);
					gpio::initAlternateOutput<pinB1_::portID, pinB1_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b1, pinB1_::portID, pinB1_::pinID>::value);
					gpio::initAlternateOutput<pinB2_::portID, pinB2_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b2, pinB2_::portID, pinB2_::pinID>::value);
					gpio::initAlternateOutput<pinB3_::portID, pinB3_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b3, pinB3_::portID, pinB3_::pinID>::value);
					gpio::initAlternateOutput<pinB4_::portID, pinB4_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b4, pinB4_::portID, pinB4_::pinID>::value);
					gpio::initAlternateOutput<pinB5_::portID, pinB5_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b5, pinB5_::portID, pinB5_::pinID>::value);
					gpio::initAlternateOutput<pinB6_::portID, pinB6_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b6, pinB6_::portID, pinB6_::pinID>::value);
					gpio::initAlternateOutput<pinB7_::portID, pinB7_::pinID>(gpio::OutputMode::pushPull, gpio::Speed::fast, LTDCPins<PinFunction::b7, pinB7_::portID, pinB7_::pinID>::value);
				}

				inline void enable() {
					bits::set(LTDC->GCR, LTDC_GCR_LTDCEN);
				}
				inline void disable() {
					bits::clear(LTDC->GCR, LTDC_GCR_LTDCEN);
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
					bits::set(_layer->CR, LTDC_LxCR_LEN);
				}
				inline void disable() {
					bits::clear(_layer->CR, LTDC_LxCR_LEN);
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


#if defined(EOS_PLATFORM_STM32F429)
    #include "htl/STM32/F4/F429/htlLTDC_Pins.h"

#elif defined(EOS_PLATFORM_STM32F746)
    #include "htl/STM32/F7/F746/htlLTDC_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlLTDC__
