#include "Services/Messenger/eosDigInputServicePublisher.h"
#include "Services/Messenger/eosMessengerService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei a publicar.
///
DigInputServiceNotificationEventPublisher::DigInputServiceNotificationEventPublisher(
	DigInputService *service):

	_notificationEvent {*this, &DigInputServiceNotificationEventPublisher::NotificationEventHandler} {

	service->setNotificationEvent(_notificationEvent,  true);
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'event
/// \param    server: El remitent del event.
/// \param    args: Els parametres del event.
///
void DigInputServiceNotificationEventPublisher::NotificationEventHandler(
	eos::DigInputService * const sender,
	eos::DigInputService::NotificationEventArgs * const args) {

	//Publisher<unsigned> publisher(nullptr);
	//unsigned message = 12324;
	//publisher.publish(message, 0);
}
