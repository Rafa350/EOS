module;

#include "hardware.h"


export module Eos.Hardware.LTDC;

export import Eos.Hardware.LTDC._Types;

import Eos.Bits;
import Eos.Hardware.GPIO;
import Eos.Hardware.LTDC._LayerTraits;
import Eos.Hardware.LTDC._PinTraits;
import Eos.Types;


using namespace eos::hardware::gpio;


export namespace eos::hardware::ltdc {

    /// @brief Image format.
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

    /// @brief Clock divider factor.
    ///
    enum class ClockDivider {
        _2 = 0,
        _4 = 1,
        _8 = 2,
        _16 = 3
    };

    /// @brief Control signals pin polarity.
    //
    enum class PinPolarity {
        activeLow,
        activeHigh,
        noChange
    };

    class LTDCDevice final: private NonCopyableClass {
        private:
            template <internal::PinFunction pinFunction_, PortID portID_, PinID pinID_> using PinTraits = internal::PinTraits<LTDCDeviceID::ltdc, pinFunction_, portID_, pinID_>;

        private:
            LTDC_TypeDef * const _ltdc;
            static LTDCDevice _instance;

        public:
            static constexpr LTDCDevice *pInst = &_instance;
            static constexpr LTDCDevice &rInst = _instance;

        private:
            LTDCDevice();
            void activate();
            void deactivate();
            void interruptService();

        public:
            void initialize(UInt32 width, UInt32 height, UInt32 hSync, UInt32 vSync, UInt32 hBP, UInt32 vBP, UInt32 hFP, UInt32 vFP);
            void deinitialize();

            template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
            void initPinHSYNC();

            template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
            void initPinVSYNC();

            template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
            void initPinPC();

            template <typename pin_, PinPolarity polarity_ = PinPolarity::noChange>
            void initPinDE();

            template <typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
            void initPinRX();

            template <typename pinR0_, typename pinR1_, typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
            void initPinRX();

            template <typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
            void initPinGX();

            template <typename pinG0_, typename pinG1_, typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
            void initPinGX();

            template <typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
            void initPinBX();

            template <typename pinB0_, typename pinB1_, typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
            void initPinBX();

            void enable() const{
                Bits::set(_ltdc->GCR, LTDC_GCR_LTDCEN);
            }
            void disable() const {
                Bits::clear(_ltdc->GCR, LTDC_GCR_LTDCEN);
            }

            void setBackgroundColor(UInt32 rgb);
            void reload();

            inline static void interruptHandler() {
                _instance.interruptService();
            }
    };

    class LTDCLayerDevice: private NonCopyableClass {
        private:
            LTDC_Layer_TypeDef * const _layer;

        protected:
            LTDCLayerDevice(UInt32 layerAddr);

        public:
            inline void enable() {
                Bits::set(_layer->CR, LTDC_LxCR_LEN);
            }
            inline void disable() {
                Bits::clear(_layer->CR, LTDC_LxCR_LEN);
            }

            void setWindow(Int16 x, Int16 y, Int16 width, Int16 height);
            void setFrameFormat(PixelFormat format, Int16 width, Int16 pitch, Int16 lines);
            void setFrameBuffer(void *buffer);
            void setConstantAlpha(uint8_t a);
            void setDefaultColor(UInt32 argb);
            void setCLUTTable(UInt32 *rgb);
            void disableCLUTTable();
            void setKeyColor(UInt32 rgb);
            void disableKeyColor();
    };


    template <LTDCLayerID layerID_>
    class LTDCLayerDeviceX final: public LTDCLayerDevice {
        private:
            using LayerTraits = internal::LayerTraits<layerID_>;

        private:
            static constexpr UInt32 _layerAddr = LayerTraits::layerAddr;
            static LTDCLayerDeviceX _instance;

        public:
            static constexpr LTDCLayerDeviceX *pInst = &_instance;
            static constexpr LTDCLayerDeviceX &rInst = _instance;

        private:
            LTDCLayerDeviceX():
                LTDCLayerDevice(_layerAddr) {
            }
    };
    template <LTDCLayerID layerID_>
    LTDCLayerDeviceX<layerID_> LTDCLayerDeviceX<layerID_>::_instance;

    typedef LTDCLayerDeviceX<LTDCLayerID::layer1> LTDCLayerDevice1;
    typedef LTDCLayerDeviceX<LTDCLayerID::layer2> LTDCLayerDevice2;
}


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::ltdc;


LTDCDevice LTDCDevice::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
LTDCDevice::LTDCDevice():
    _ltdc {reinterpret_cast<LTDC_TypeDef*>(LTDC_BASE)} {
}


/// ---------------------------------------------------------------------------
/// @brief    Configura el pin HSYNC
/// @tparam   pin_: El pin.
/// @tparam   polarity_: La polaritat.
///
template <typename pin_, PinPolarity polarity_>
void LTDCDevice::initPinHSYNC() {

    auto value = PinTraits<internal::PinFunction::hsync, pin_::portID, pin_::pinID>::value;
    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, value);

    if constexpr (polarity_ == PinPolarity::activeHigh)
        Bits::set(_ltdc->GCR, LTDC_GCR_HSPOL);
    else if constexpr (polarity_ == PinPolarity::activeLow)
        Bits::clear(_ltdc->GCR, LTDC_GCR_HSPOL);
}


/// ---------------------------------------------------------------------------
/// @brief    Configura el pin VSYNC
/// @tparam   pin_: El pin.
/// @tparam   polarity_: La polaritat.
///
template <typename pin_, PinPolarity polarity_>
void LTDCDevice::initPinVSYNC() {

    auto value = PinTraits<internal::PinFunction::vsync, pin_::portID, pin_::pinID>::value;
    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, value);

    if constexpr (polarity_ == PinPolarity::activeHigh)
        Bits::set(_ltdc->GCR, LTDC_GCR_VSPOL);
    else if constexpr (polarity_ == PinPolarity::activeLow)
        Bits::clear(_ltdc->GCR, LTDC_GCR_VSPOL);
}


/// ---------------------------------------------------------------------------
/// @brief    Configura el pin PC
/// @tparam   pin_: El pin.
/// @tparam   polarity_: La polaritat.
///
template <typename pin_, PinPolarity polarity_>
void LTDCDevice::initPinPC() {

    auto value = PinTraits<internal::PinFunction::pc, pin_::portID, pin_::pinID>::value;
    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, value);

    if constexpr (polarity_ == PinPolarity::activeHigh)
        Bits::set(_ltdc->GCR, LTDC_GCR_PCPOL);
    else if constexpr (polarity_ == PinPolarity::activeLow)
        Bits::clear(_ltdc->GCR, LTDC_GCR_PCPOL);
}


/// ---------------------------------------------------------------------------
/// @brief    Configura el pin DE
/// @tparam   pin_: El pin.
/// @tparam   polarity_: La polaritat.
///
template <typename pin_, PinPolarity polarity_>
void LTDCDevice::initPinDE() {

    auto value = PinTraits<internal::PinFunction::de, pin_::portID, pin_::pinID>::value;
    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, value);

    if constexpr (polarity_ == PinPolarity::activeHigh)
        Bits::set(_ltdc->GCR, LTDC_GCR_DEPOL);
    else if constexpr (polarity_ == PinPolarity::activeLow)
        Bits::clear(_ltdc->GCR, LTDC_GCR_DEPOL);
}


template <typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
void LTDCDevice::initPinRX() {

    GPIOPin<pinR2_::portID, pinR2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r2, pinR2_::portID, pinR2_::pinID>::value);
    GPIOPin<pinR3_::portID, pinR3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r3, pinR3_::portID, pinR3_::pinID>::value);
    GPIOPin<pinR4_::portID, pinR4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r4, pinR4_::portID, pinR4_::pinID>::value);
    GPIOPin<pinR5_::portID, pinR5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r5, pinR5_::portID, pinR5_::pinID>::value);
    GPIOPin<pinR6_::portID, pinR6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r6, pinR6_::portID, pinR6_::pinID>::value);
    GPIOPin<pinR7_::portID, pinR7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r7, pinR7_::portID, pinR7_::pinID>::value);
}


template <typename pinR0_, typename pinR1_, typename pinR2_, typename pinR3_, typename pinR4_, typename pinR5_, typename pinR6_, typename pinR7_>
void LTDCDevice::initPinRX() {

    GPIOPin<pinR0_::portID, pinR0_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r0, pinR0_::portID, pinR0_::pinID>::value);
    GPIOPin<pinR1_::portID, pinR1_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r1, pinR1_::portID, pinR1_::pinID>::value);
    GPIOPin<pinR2_::portID, pinR2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r2, pinR2_::portID, pinR2_::pinID>::value);
    GPIOPin<pinR3_::portID, pinR3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r3, pinR3_::portID, pinR3_::pinID>::value);
    GPIOPin<pinR4_::portID, pinR4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r4, pinR4_::portID, pinR4_::pinID>::value);
    GPIOPin<pinR5_::portID, pinR5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r5, pinR5_::portID, pinR5_::pinID>::value);
    GPIOPin<pinR6_::portID, pinR6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r6, pinR6_::portID, pinR6_::pinID>::value);
    GPIOPin<pinR7_::portID, pinR7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::r7, pinR7_::portID, pinR7_::pinID>::value);
}


template <typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
void LTDCDevice::initPinGX() {

    GPIOPin<pinG2_::portID, pinG2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g2, pinG2_::portID, pinG2_::pinID>::value);
    GPIOPin<pinG3_::portID, pinG3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g3, pinG3_::portID, pinG3_::pinID>::value);
    GPIOPin<pinG4_::portID, pinG4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g4, pinG4_::portID, pinG4_::pinID>::value);
    GPIOPin<pinG5_::portID, pinG5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g5, pinG5_::portID, pinG5_::pinID>::value);
    GPIOPin<pinG6_::portID, pinG6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g6, pinG6_::portID, pinG6_::pinID>::value);
    GPIOPin<pinG7_::portID, pinG7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g7, pinG7_::portID, pinG7_::pinID>::value);
}


template <typename pinG0_, typename pinG1_, typename pinG2_, typename pinG3_, typename pinG4_, typename pinG5_, typename pinG6_, typename pinG7_>
void LTDCDevice::initPinGX() {

    GPIOPin<pinG0_::portID, pinG0_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g0, pinG0_::portID, pinG0_::pinID>::value);
    GPIOPin<pinG1_::portID, pinG1_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g1, pinG1_::portID, pinG1_::pinID>::value);
    GPIOPin<pinG2_::portID, pinG2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g2, pinG2_::portID, pinG2_::pinID>::value);
    GPIOPin<pinG3_::portID, pinG3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g3, pinG3_::portID, pinG3_::pinID>::value);
    GPIOPin<pinG4_::portID, pinG4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g4, pinG4_::portID, pinG4_::pinID>::value);
    GPIOPin<pinG5_::portID, pinG5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g5, pinG5_::portID, pinG5_::pinID>::value);
    GPIOPin<pinG6_::portID, pinG6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g6, pinG6_::portID, pinG6_::pinID>::value);
    GPIOPin<pinG7_::portID, pinG7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::g7, pinG7_::portID, pinG7_::pinID>::value);
}


template <typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
void LTDCDevice::initPinBX() {

    GPIOPin<pinB2_::portID, pinB2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b2, pinB2_::portID, pinB2_::pinID>::value);
    GPIOPin<pinB3_::portID, pinB3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b3, pinB3_::portID, pinB3_::pinID>::value);
    GPIOPin<pinB4_::portID, pinB4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b4, pinB4_::portID, pinB4_::pinID>::value);
    GPIOPin<pinB5_::portID, pinB5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b5, pinB5_::portID, pinB5_::pinID>::value);
    GPIOPin<pinB6_::portID, pinB6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b6, pinB6_::portID, pinB6_::pinID>::value);
    GPIOPin<pinB7_::portID, pinB7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b7, pinB7_::portID, pinB7_::pinID>::value);
}


template <typename pinB0_, typename pinB1_, typename pinB2_, typename pinB3_, typename pinB4_, typename pinB5_, typename pinB6_, typename pinB7_>
void LTDCDevice::initPinBX() {

    GPIOPin<pinB0_::portID, pinB0_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b0, pinB0_::portID, pinB0_::pinID>::value);
    GPIOPin<pinB1_::portID, pinB1_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b1, pinB1_::portID, pinB1_::pinID>::value);
    GPIOPin<pinB2_::portID, pinB2_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b2, pinB2_::portID, pinB2_::pinID>::value);
    GPIOPin<pinB3_::portID, pinB3_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b3, pinB3_::portID, pinB3_::pinID>::value);
    GPIOPin<pinB4_::portID, pinB4_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b4, pinB4_::portID, pinB4_::pinID>::value);
    GPIOPin<pinB5_::portID, pinB5_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b5, pinB5_::portID, pinB5_::pinID>::value);
    GPIOPin<pinB6_::portID, pinB6_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b6, pinB6_::portID, pinB6_::pinID>::value);
    GPIOPin<pinB7_::portID, pinB7_::pinID>::initAlternate(OutputType::pushPull, PullUpDown::none, Speed::fast, PinTraits<internal::PinFunction::b7, pinB7_::portID, pinB7_::pinID>::value);
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
///
void LTDCDevice::activate() {

	Bits::set(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
	__DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
///
void LTDCDevice::deactivate() {

	Bits::clear(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el dispositiu.
///
void LTDCDevice::initialize(
	UInt32 width,
	UInt32 height,
	UInt32 hSync,
	UInt32 vSync,
	UInt32 hBP,
	UInt32 vBP,
	UInt32 hFP,
	UInt32 vFP) {

	activate();
	disable();

	// Configura el registre SSCR (Sinchronization Size Configuration Register)
	//
	UInt32 SSCR = _ltdc->SSCR;
	SSCR &= ~(LTDC_SSCR_HSW | LTDC_SSCR_VSH);
	SSCR |= ((hSync - 1) << LTDC_SSCR_HSW_Pos) & LTDC_SSCR_HSW;
	SSCR |= ((vSync - 1) << LTDC_SSCR_VSH_Pos) & LTDC_SSCR_VSH;
	_ltdc->SSCR = SSCR;

	// Configura el registre BPCR (Back Porch Configuration Register)
	//
	UInt32 BPCR = _ltdc->BPCR;
	BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
	BPCR |= ((hSync + hBP - 1) << LTDC_BPCR_AHBP_Pos) & LTDC_BPCR_AHBP;
	BPCR |= ((vSync + vBP - 1) << LTDC_BPCR_AVBP_Pos) & LTDC_BPCR_AVBP;
	_ltdc->BPCR = BPCR;

	// Configura el registre AWCR (Active Width Configuration Register)
	// -AAW = HSYNC + HBP + WIDTH - 1
	// -AAH = VSYNC + VBP + HEIGHT - 1
	//
	UInt32 AWCR = _ltdc->AWCR;
	AWCR &= ~(LTDC_AWCR_AAW | LTDC_AWCR_AAH);
	AWCR |= ((hSync + hBP + width - 1) << LTDC_AWCR_AAW_Pos) & LTDC_AWCR_AAW;
	AWCR |= ((vSync + vBP + height - 1) << LTDC_AWCR_AAH_Pos) & LTDC_AWCR_AAH;
	_ltdc->AWCR = AWCR;

	// Configura el registre TWCR (Total Width Configuration Register)
	// -TOTALW = HSYNC + HBP + WIDTH + HFP - 1
	// -TOTALH = VSYNC + VBP + HEIGHT + VFP - 1
	//
	UInt32 TWCR = _ltdc->TWCR;
	TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
	TWCR |= ((hSync + hBP + width + hFP - 1) << LTDC_TWCR_TOTALW_Pos) & LTDC_TWCR_TOTALW;
	TWCR |= ((vSync + vBP + height + vFP - 1) << LTDC_TWCR_TOTALH_Pos) & LTDC_TWCR_TOTALH;
	_ltdc->TWCR = TWCR;
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el dispositiu.
///
void LTDCDevice::deinitialize() {

	disable();
	deactivate();
}


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el color sde fons.
/// @param    rgb: El color en formar RGB888
///
void LTDCDevice::setBackgroundColor(
	UInt32 rgb) {

	// Configura el registre BCCR (Back Color Configuration Register)
	//
	UInt32 BCCR = _ltdc->BCCR;
	BCCR &= ~(LTDC_BCCR_BCRED | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCBLUE);
	BCCR |= ((rgb & 0x00FF0000) >> 16) << LTDC_BCCR_BCRED_Pos;
	BCCR |= ((rgb & 0x0000FF00) >> 8) << LTDC_BCCR_BCGREEN_Pos;
	BCCR |= (rgb & 0x000000FF) << LTDC_BCCR_BCBLUE_Pos;
	_ltdc->BCCR = BCCR;
}


/// ---------------------------------------------------------------------------
/// @brief    Refresca la pantalla
///
void LTDCDevice::reload() {

	// Si el LTDC no esta actiu, fa una actualitzacio immediata
	//
	if ((_ltdc->GCR & LTDC_GCR_LTDCEN) == 0)
		Bits::set(_ltdc->SRCR, LTDC_SRCR_IMR);

	// En cas contrari, fa l'actualitzacio durant la sincronitzacio
	// vertical, i espera que finalitzi.
	//
	else {
		Bits::set(_ltdc->SRCR, LTDC_SRCR_VBR);
		while ((_ltdc->CDSR & LTDC_CDSR_VSYNCS) != 0)
			continue;
		while ((_ltdc->CDSR & LTDC_CDSR_VSYNCS) == 0)
			continue;
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void LTDCDevice::interruptService() {

}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    layerAddr: L'adresa dels registres de hardware.
///
LTDCLayerDevice::LTDCLayerDevice(
	UInt32 layerAddr):

	_layer {reinterpret_cast<LTDC_Layer_TypeDef*>(layerAddr)} {

}


void LTDCLayerDevice::setWindow(
	Int16 x,
	Int16 y,
	Int16 width,
	Int16 height) {

    LTDC_TypeDef *_ltdc = reinterpret_cast<LTDC_TypeDef*>(LTDC_BASE);

	// Configura Lx_WHPCR (Window Horizontal Position Configuration Register)
	// -Tamany horitzontal de la finestra
	//
	UInt32 ahbp = (_ltdc->BPCR & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos;
	UInt32 whpcr = _layer->WHPCR;
	whpcr &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
	whpcr |= ((ahbp + x + 1) << LTDC_LxWHPCR_WHSTPOS_Pos) & LTDC_LxWHPCR_WHSTPOS;
	whpcr |= ((ahbp + width - x) << LTDC_LxWHPCR_WHSPPOS_Pos) & LTDC_LxWHPCR_WHSPPOS;
	_layer->WHPCR = whpcr;

	// Configura Lx_WHPCR (Window Vertical Position Configuration Register)
	// -Tamany vertical de la finestra
	//
	UInt32 avbp = (_ltdc->BPCR & LTDC_BPCR_AVBP) >> LTDC_BPCR_AVBP_Pos;
	UInt32 wvpcr = _layer->WVPCR;
	wvpcr &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
	wvpcr |= ((avbp + y + 1) << LTDC_LxWVPCR_WVSTPOS_Pos) & LTDC_LxWVPCR_WVSTPOS;
	wvpcr |= ((avbp + height - y) << LTDC_LxWVPCR_WVSPPOS_Pos) & LTDC_LxWVPCR_WVSPPOS;
	_layer->WVPCR = wvpcr;
}


void LTDCLayerDevice::setFrameFormat(
	PixelFormat format,
	Int16 width,
	Int16 pitch,
	Int16 lines) {

	// Configura Lx_PFCR (Pixel Format Configuration Register)
	// -Format de color del buffer d'imatge.
	//
	UInt32 pfcr = _layer->PFCR;
	pfcr &= ~(0b111 << LTDC_LxPFCR_PF_Pos);
	pfcr |= (UInt32(format) & 0b111) << LTDC_LxPFCR_PF_Pos;
	_layer->PFCR = pfcr;

	// Configura Lx_CFBLR (Color Frame Buffer Length Register)
	// -Longitut de la linia en bytes.
	//
	UInt32 cfblr = _layer->CFBLR;
	cfblr &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
	cfblr |= (pitch & 0x1FFF) << LTDC_LxCFBLR_CFBP_Pos;
	cfblr |= ((width + 3) & 0x1FFF) << LTDC_LxCFBLR_CFBLL_Pos;
	_layer->CFBLR = cfblr;

	// Configura Lx_CFBLNR (Color Frame Buffer Line Number Register)
	//
	UInt32 cfblnr = _layer->CFBLNR;
	cfblnr  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	cfblnr |= lines & LTDC_LxCFBLNR_CFBLNBR;
	_layer->CFBLNR = cfblnr;
}


/// ---------------------------------------------------------------------------
/// @brief Asigna el buffer de la capa.
/// @param buffer: El buffer. Si es null, es desactiva la capa.
///
void LTDCLayerDevice::setFrameBuffer(
	void *buffer) {

	if (buffer == nullptr)
		disable();
	else
		_layer->CFBAR = (UInt32)buffer;
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna i activa la taula de colors (Valid per L8, AL44 i AL88)
/// @param    table: La taula de colors en format RGB888. Si es null,
///                  es desactiva.
///
void LTDCLayerDevice::setCLUTTable(
	UInt32 *rgb) {

    LTDC_TypeDef *_ltdc = reinterpret_cast<LTDC_TypeDef*>(LTDC_BASE);

    if ((_layer->CR & LTDC_LxCR_LEN) == 0) {
		if (rgb == nullptr)
			Bits::clear(_layer->CR, LTDC_LxCR_CLUTEN);
		else {
			for (UInt32 i = 0; i < 256; i++)
				_layer->CLUTWR = (i << LTDC_LxCLUTWR_CLUTADD_Pos) | (*rgb++ & 0x00FFFFFF);
			Bits::set(_layer->CR, LTDC_LxCR_CLUTEN);
		}

		Bits::set(_ltdc->SRCR, LTDC_SRCR_IMR);
	}
}


/// ---------------------------------------------------------------------------
/// @brief Desactiva la taula de colors.
///
void LTDCLayerDevice::disableCLUTTable() {

	Bits::clear(_layer->CR, LTDC_LxCR_CLUTEN);
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el color per defecte.
/// @param    argb: El color en format ARGB8888
///
void LTDCLayerDevice::setDefaultColor(
	UInt32 argb) {

	// Configura Lx_DCCR (Default Color Configuration Register)
	// -Color per defecte
	//
	UInt32 dccr = _layer->DCCR;
	dccr &= ~(LTDC_LxDCCR_DCALPHA | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCBLUE);
	dccr |= ((argb & 0xFF000000) >> 24) << LTDC_LxDCCR_DCALPHA_Pos;
	dccr |= ((argb & 0x00FF0000) >> 16) << LTDC_LxDCCR_DCRED_Pos;
	dccr |= ((argb & 0x0000FF00) >> 8) << LTDC_LxDCCR_DCGREEN_Pos;
	dccr |= (argb & 0x000000FF) << LTDC_LxDCCR_DCBLUE_Pos;
	_layer->DCCR = dccr;
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el valor ALPHA.
/// @param    a: El valor.
///
void LTDCLayerDevice::setConstantAlpha(
	uint8_t a) {

	_layer->CACR = a;
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el color croma i l'activa.
/// @param    rgb: El color en format RGB888
///
void LTDCLayerDevice::setKeyColor(
	UInt32 rgb) {

	// Configura Lx_CKCR (Color Key Configuration Register)
	// -Color clau per croma e
	//
	UInt32 ckcr = _layer->CKCR;
	ckcr &= ~(LTDC_LxCKCR_CKRED | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKBLUE);
	ckcr |= ((rgb & 0x00FF0000) >> 16) << LTDC_LxCKCR_CKRED_Pos;
	ckcr |= ((rgb & 0x0000FF00) >> 8) << LTDC_LxCKCR_CKGREEN_Pos;
	ckcr |= (rgb & 0x000000FF) << LTDC_LxCKCR_CKBLUE_Pos;
	_layer->CKCR = ckcr;

	// Activa el color croma
	//
	_layer->CR |= LTDC_LxCR_COLKEN;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el color croma.
///
void LTDCLayerDevice::disableKeyColor() {

	_layer->CR &= ~LTDC_LxCR_COLKEN;
}
