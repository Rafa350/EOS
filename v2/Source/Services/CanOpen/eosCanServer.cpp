module;


#include "eosTime.h"
#include "HTL/STM32/htlCAN.h"


export module Eos.Services.CanOpen.CanServer;



export namespace eos {

    class CanServer final {
        private:
			htl::can::CANDevice * const _devCAN;
			htl::can::CANDevice::NotificationEvent<CanServer> _devCAN_notificationEvent;

        private:
            void devCAN_notificationEventHandler(htl::can::CANDevice *sender, htl::can::CANDevice::NotificationEventArgs *args);

        public:
            CanServer(htl::can::CANDevice * devCAN);
            ~CanServer();

            void sendFrame();
            bool receiveFrame();

    };
}


eos::CanServer::CanServer(
    htl::can::CANDevice *devCAN):

    _devCAN {devCAN},
    _devCAN_notificationEvent {*this, &CanServer::devCAN_notificationEventHandler} {

    _devCAN->enableNotificationEvent(_devCAN_notificationEvent);
}


void eos::CanServer::devCAN_notificationEventHandler(
    htl::can::CANDevice *sender,
    htl::can::CANDevice::NotificationEventArgs *args) {

}
