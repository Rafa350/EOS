module;


#include "eos.h"


module Eos.Services.Forms;


import Eos.System.Graphics;
import Eos.System.Graphics.Rect;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Form::Form():

	Visual {Point(), Size()},

	_activeControl {nullptr},
	_dataContext {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    dataContext: Context de dades.
///
eos::Form::Form(
	void *dataContext):

	Visual {Point(), Size()},

	_dataContext {dataContext} {

}


/// ----------------------------------------------------------------------
/// \brief    Despatche un missatge
/// \param    message: El missatge.
///
void eos::Form::onMessage(
	FormMessage &message) {

	switch (message.id) {
		case FormMessageID::selector:
		case FormMessageID::keyboard:
			if (_activeControl != nullptr)
				_activeControl->message(message);
			break;
	}
}

