module;

#include "hardware.h"


export module Eos.Hardware.DMA;


import Eos.Events;
import Eos.Hardware.DMA._PlatformTraits;
import Eos.Platform;
import Eos.System.Core.Ticks;
import Eos.Result;
import Eos.Types;


export namespace eos::hardware::dma {

    using DMADeviceID = internal::PlatformTraits::DeviceID;

    class DMADevice: private NonCopyableClass {
        public:
            enum class NotificationID {
                null,
                half,
                completed,
                error
            };
            struct NotificationEventArgs {
                NotificationID id;
                bool irq;
            };
            using NotificationEventRaiser = EventRaiser<DMADevice, NotificationEventArgs>;
            using INotificationEvent = NotificationEventRaiser::IEvent;
            template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

        private:
            NotificationEventRaiser _notificationEventRaiser;

        protected:
            DMADevice(UInt32 dmaAddr, UInt32 dmaChannelAddr, UInt32 muxChannelStatusAddr, UInt32 muxChannelAddr);

            void interruptService();

            virtual void activateImpl() const = 0;
            virtual void deactivateImpl() const = 0;

        public:
            StdResult start(const UInt8 *src, UInt8 *dst, UInt32 size);
            StdResult waitForFinish(Ticks blockTime);

            void enableNotificationEvent(INotificationEvent &event) {
                _notificationEventRaiser.enable(event);
            }
            void disableNotificationEvent() {
                _notificationEventRaiser.disable();
            }
    };

    template <DMADeviceID deviceId_>
    class DMADeviceX: public DMADevice {

    };
}
