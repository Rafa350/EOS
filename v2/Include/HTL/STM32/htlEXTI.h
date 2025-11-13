#pragma once
#ifndef __STM32_htlEXTI__
#define __STM32_htlEXTI__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	namespace exti {

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

		class EXTIDevice final {
			public:
        		enum class NotificationID {
        			pinEdge
        		};
        		struct NotificationEventArgs {
        			NotificationID const id;
        			bool const irq;
        			union {
        				struct {
        					uint16_t const falling;
        					uint16_t const rissing;
        				} pinEdge;
        			};
        		};
        		using NotificationEventRaiser = eos::EventRaiser<EXTIDevice, NotificationEventArgs>;
        		using INotificationEvent = NotificationEventRaiser::IEvent;
                template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

			private:
				static EXTIDevice _instance;

            public:
                static constexpr EXTIDevice *pInst = &_instance;
                static constexpr EXTIDevice &rInst = _instance;

            private:
                NotificationEventRaiser _erNotification;

            private:
                EXTIDevice();

                static void setPort(LineID lineID, htl::gpio::PortID portID);
                static void setMode(LineID lineID, Mode mode);
                static void setEdge(LineID lineID, Edge edge);

                void interruptService();

			public:
				void initGPIO(gpio::PortID portID, gpio::PinID pinID, Mode mode, Edge edge);
				void deinitialize();

				eos::Result setNotificationEvent(INotificationEvent &event, bool enabled = true);

				/// Habilita l'event de notificacio.
				///
				inline void enableNotificationEvent() {
					_erNotification.enable();
				}

				/// Deshabilita l'event de notificacio.
				///
				inline void disableNotificationEvent() {
					_erNotification.disable();
				}

				inline static void interruptHandler() {
                    _instance.interruptService();
                }
		};
	}
}


#endif // __STM32_htlEXT__
