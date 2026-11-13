module;

#include "hardware.h"


export module Eos.Hardware.EXTI;

import Eos.Bits;
import Eos.Events;
import Eos.Hardware.GPIO;
import Eos.Types;


using namespace eos::hardware::gpio;


export namespace eos::hardware::exti {

    enum class LineID {
        pinX0,   // GPIO pin Px0
        pinX1,   // GPIO pin Px1
        pinX2,   // GPIO pin Px2
        pinX3,   // GPIO pin Px3
        pinX4,   // GPIO pin Px4
        pinX5,   // GPIO pin Px5
        pinX6,   // GPIO pin Px6
        pinX7,   // GPIO pin Px7
        pinX8,   // GPIO pin Px8
        pinX9,   // GPIO pin Px9
        pinX10,  // GPIO pin Px10
        pinX11,  // GPIO pin Px11
        pinX12,  // GPIO pin Px12
        pinX13,  // GPIO pin Px13
        pinX14,  // GPIO pin Px14
        pinX15,  // GPIO pin Px15
        pvd,
        comp1,
        comp2,
        rtc,
        comp3,
        tamp,
        i2c2,
        i2c1,
        uart3,
        uart1,
        uart2,
        cec,
        lpuart1,
        lptim1,
        lptim2,
        lsecss,
        ucpd1,
        ucpd2,
        vdd,
        lpuart2
    };

    class EXTIDevice final: private NonCopyableClass {
        public:
            enum class Mode {
                none,
                interrupt,
                event,
                all
            };

            enum class Edge {
                rissing,
                falling,
                all
            };

        public:
            enum class NotificationID {
                pinEdge
            };
            struct NotificationEventArgs {
                NotificationID const id;
                bool const irq;
                union {
                    struct {
                        UInt16 const falling;
                        UInt16 const rissing;
                    } pinEdge;
                };
            };
            using NotificationEventRaiser = EventRaiser<EXTIDevice, NotificationEventArgs>;
            using INotificationEvent = NotificationEventRaiser::IEvent;
            template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

        private:
            EXTI_TypeDef * const _exti;
            static EXTIDevice _instance;

        public:
            static constexpr EXTIDevice *pInst = &_instance;
            static constexpr EXTIDevice &rInst = _instance;

        private:
            NotificationEventRaiser _erNotification;

        private:
            EXTIDevice();

            void setPort(LineID lineID, PortID portID);
            void setMode(LineID lineID, Mode mode);
            void setEdge(LineID lineID, Edge edge);

            void interruptService();

        public:
            void initGPIO(PortID portID, PinID pinID, Mode mode, Edge edge);
            void deinitialize();

            inline void enableNotificationEvent(INotificationEvent &event) {
                _erNotification.enable(event);
            }
            inline void disableNotificationEvent() {
                _erNotification.disable();
            }

            inline static void interruptHandler() {
                _instance.interruptService();
            }
    };
}


using namespace eos;
using namespace eos::hardware::exti;
using namespace eos::hardware::gpio;


EXTIDevice EXTIDevice::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
EXTIDevice::EXTIDevice() :
    _exti {reinterpret_cast<EXTI_TypeDef*>(EXTI_BASE)} {

	_exti->FTSR1 = 0;
	_exti->FTSR2 = 0;
	_exti->RTSR1 = 0;
	_exti->RTSR2 = 0;
	_exti->FPR1 = 0;
	_exti->FPR2 = 0;
	_exti->RPR1 = 0;
	_exti->RPR2 = 0;
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza una linia d'interrupcio asignada al GPIO
/// @param    portID: Identificador del port GPIO.
/// @param    pinID: Identificador del pin GPIO.
/// @param    mode: El modus.
/// @param    edge: El flanc.
///
void EXTIDevice::initGPIO(
	gpio::PortID portID,
	gpio::PinID pinID,
	Mode mode,
	Edge edge) {

	LineID lineID = (LineID) pinID;

	setPort(lineID, portID);
	setMode(lineID, mode);
	setEdge(lineID, edge);
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitza el dispositiu.
///
void EXTIDevice::deinitialize() {

	_exti->FTSR1 = 0;
	_exti->FTSR2 = 0;
	_exti->RTSR1 = 0;
	_exti->RTSR2 = 0;
	_exti->FPR1 = 0;
	_exti->FPR2 = 0;
	_exti->RPR1 = 0;
	_exti->RPR2 = 0;
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna un port a una linia d'interrupcio externa
///
void EXTIDevice::setPort(
	LineID lineID,
	PortID portID) {

#if defined(EOS_PLATFORM_STM32G0)

	UInt32 lineNum = (UInt32) lineID;

	/// Asigna el port GPIO a la linia EXTI
	//
	UInt32 tmp = _exti->EXTICR[lineNum >> 2];
	tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03)));
	tmp |= ((UInt32)portID << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03)));
	_exti->EXTICR[lineNum >> 2] = tmp;

#else
	#error "Unknown platform"
#endif
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna modus a una linia d'interrupcio externa
/// @param    lineID: Idenfificador de la linia.
/// @param    mode: El modus.
///
void EXTIDevice::setMode(
	LineID lineID,
	Mode mode) {

	UInt32 mask = 1 << ((UInt32) lineID);

#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == Mode::interrupt) || (mode == Mode::all))
		Bits::set(_exti->IMR1, mask);
	else
		Bits::clear(_exti->IMR1, mask);

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == Mode::event) || (mode == Mode::all))
		Bits::set(_exti->EMR1, mask);
	else
		Bits::clear(_exti->EMR1, mask);

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
		_exti->IMR |= 1 << UInt32(line_);
	else
		_exti->IMR &= ~(1 << UInt32(line_));

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
		_exti->EMR |= 1 << UInt32(line_);
	else
		_exti->EMR &= ~(1 << UInt32(line_));

#else
	#error "Unknown platform"
#endif
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el flanc a una linia d'interrupcio externa
/// @param    lineID: Idenfificador de la linia.
/// @param    edge: El flanc.
///
void EXTIDevice::setEdge(
	LineID lineID,
	Edge edge) {

	UInt32 mask = 1 << ((UInt32) lineID);

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rissing) || (edge == Edge::all))
		Bits::set(_exti->RTSR1, mask);
	else
		Bits::clear(_exti->RTSR1, mask);
	Bits::clear(_exti->RPR1, mask);

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		Bits::set(_exti->FTSR1, mask);
	else
		Bits::clear(_exti->FTSR1, mask);
	Bits::clear(_exti->FPR1, mask);

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
		_exti->RTSR |= 1 << UInt32(line_);
	else
		_exti->RTSR &= ~(1 << UInt32(line_));

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
		_exti->FTSR |= 1 << UInt32(line_);
	else
		_exti->FTSR &= ~(1 << UInt32(line_));

#else
	#error "Unknown platform"
#endif
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les interrupcions.
///
void EXTIDevice::interruptService() {

	// Gestiona els events dels pins GPIO
	//
	auto fmask = _exti->FPR1 & 0x0000FFFF;
	auto rmask = _exti->RPR1 & 0x0000FFFF;
	if ((fmask | rmask) != 0) {

		_exti->FPR1 = fmask; // Borra els flags
		_exti->RPR1 = rmask; // Borra els flags

		if (_erNotification.isEnabled()) {

			NotificationEventArgs args = {
				.id {NotificationID::pinEdge},
				.irq {true},
				.pinEdge {
					.falling {(UInt16)fmask},
					.rissing {(UInt16)rmask}
				}
			};

			_erNotification(this, &args);
		}
	}
}
