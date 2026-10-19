module Eos.Services.Forms;

import Eos.Controllers.Display.Drivers;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.Queue;
import Eos.System.Core.Ticks;
import Eos.System.Graphics.Canvas;
import Eos.System.Graphics.Color;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
FormsService::FormsService(
	DisplayDriver *drvDisplay):

	_drvDisplay {drvDisplay},
	_activeForm {nullptr},
	_messageQueue {10} {

}


/// ---------------------------------------------------------------------------
/// @brief    Afgeig un form
/// @param 	  form : El form a afeigir.
///
void FormsService::addForm(
	Form *form) {

	_forms.pushFront(form);
}


/// ---------------------------------------------------------------------------
/// @brief    Envia un missatge de forma directe.
/// @param    message: El missatge.
///
void FormsService::sendMessage(
	FormMessage &message) {

	if (message.target != nullptr)
		message.target->message(message);
}


/// ---------------------------------------------------------------------------
/// @brief    Envia un missatge de forma diferida a traves de la cua
/// @param    message: El missatge.
/// @param    blockTime: Temps maxim de bloqueig-
/// \return   True si tot es correcte, false en cas d'error o timeout.
///
bool FormsService::postMessage(
	FormMessage &message,
	Ticks blockTime) {

	return _messageQueue.push(message, blockTime);
}


bool FormsService::postInitializeMessage(
	Ticks blockTime) {

	FormMessage message = {
		.id { FormMessageID::initialize},
		.target {nullptr}
	};

	return postMessage(message, blockTime);
}


bool FormsService::postKeyboardMessage(
	KeyboardMessageID id,
	Ticks blockTime) {

	FormMessage message = {
		.id { FormMessageID::keyboard},
		.target {_activeForm},
		.keyboard {
			.id {id}
		}
	};

	return postMessage(message, blockTime);
}


bool FormsService::postSelectorMessage(
	SelectorMessageID id,
	Ticks blockTime) {

	FormMessage message = {
		.id { FormMessageID::selector},
		.target {_activeForm},
		.selector {
			.id {id}
		}
	};

	return postMessage(message, blockTime);
}


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el form actiu.
/// @param    form: El form a activat. nullptr si no activa cap.
///
void FormsService::setActiveForm(
	Form *form) {

	// Notifica que es desactivara el form
	//
	if (_activeForm != nullptr) {
		FormMessage message = {
			.id {FormMessageID::deactivated},
			.target {_activeForm}
		};
		sendMessage(message);
	}

	// Selecciona el form actiu
	//
	_activeForm = form;

	// Notifica que s'ha activat el form
	//
	if (_activeForm != nullptr) {
		FormMessage message = {
			.id {FormMessageID::activated},
			.target {_activeForm}
		};
		sendMessage(message);
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza els parametres del servei.
/// \params   params: El parametres per inicialitzar.
///
void FormsService::onInitialize(
	ServiceParams &params) {

	params.name = _serviceName;
	params.priority = _servicePriority;
	params.stackDepth = _serviceStackDepth;
}


/// ---------------------------------------------------------------------------
/// @brief    Executa les tasques del servei
///
void FormsService::onExecute() {

	postInitializeMessage(Ticks::infinite());

    auto graphics = new Graphics(_drvDisplay);

    while (!stopSignal()) {

    	FormMessage message;
    	while (_messageQueue.pop(message, Ticks::infinite())) {
    		sendMessage(message);

    		// Quant s'ha procesat l'ultim missatge, renderitza el form,
    		// si cal.
    		//
			if ((_messageQueue.getCount() == 0) &&
				(_activeForm != nullptr) &&
				_activeForm->isRenderPending()) {

				_activeForm->render(graphics);

				CriticalSection::enter();
				auto driver = graphics->getDriver();
				driver->refresh();
				CriticalSection::exit();
			}
    	}
    }
}
