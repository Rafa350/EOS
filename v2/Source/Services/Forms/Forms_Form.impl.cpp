module Eos.Services.Forms;

import Eos.System.Graphics;
import Eos.System.Graphics.Rect;


using namespace eos;


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
///
Form::Form():

	Visual {Point(), Size()},

	_activeControl {nullptr},
	_childPropertyChangedEvent {*this, &Form::childPropertyChangedEventHandler},
	_dataContext {nullptr} {

}


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
/// \param    dataContext: Context de dades.
///
Form::Form(
	void *dataContext):

	Visual {Point(), Size()},
	_activeControl {nullptr},
	_childPropertyChangedEvent {*this, &Form::childPropertyChangedEventHandler},
	_dataContext {dataContext} {

}


/// ---------------------------------------------------------------------------
/// @brief   Processa l'event 'ChildPropertyChanged'
/// @param   sender: El remitent del event.
/// @param   args: Parametres del event.
///
void Form::childPropertyChangedEventHandler(
	PropertyObserver *sender,
	PropertyObserver::PropertyChangedEventArgs *args) {

	onChildPropertyChanged(reinterpret_cast<Visual*>(sender), args->property);
}


/// ---------------------------------------------------------------------------
/// @brief    Es crida al afeigit un fill al form.
/// @param    child : El fill.
///
void Form::onAddChild(
	Visual *child) {

	child->setPropertyChangedEvent(_childPropertyChangedEvent);
}


/// ---------------------------------------------------------------------------
/// @brief    Es crida quant ha canviat una propietat d'un fill.
/// @param 	  child: El fill.
/// @param    property: La propietat.
///
void Form::onChildPropertyChanged(
	Visual *child,
	void *property) {

}


/// ---------------------------------------------------------------------------
/// \brief    Despatche un missatge
/// \param    message: El missatge.
///
void Form::onMessage(
	FormMessage &message) {

	switch (message.id) {
		case FormMessageID::selector:
		case FormMessageID::keyboard:
			if (_activeControl != nullptr)
				_activeControl->message(message);
			break;
	}
}
