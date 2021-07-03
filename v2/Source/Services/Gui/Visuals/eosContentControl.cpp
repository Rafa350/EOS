#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosContentControl.h"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
ContentControl::ContentControl() :
	_padding(Thickness(0)),
	_content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Assigna el contingut.
/// \param    value: El contingut.
///
void ContentControl::setContent(
	Visual* value) {

	if (_content != value) {

		if (_content != nullptr)
			removeVisual(_content);

		_content = value;

		if (_content != nullptr)
			addVisual(_content);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Assigna el marge interior.
/// \param    value: El marge interior.
///
void ContentControl::setPadding(
	const Thickness &value) {

	if (_padding != value) {
		_padding = value;
		invalidateLayout();
	}
}
