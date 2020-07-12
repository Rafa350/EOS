#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosContentControl.h"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
ContentControl::ContentControl() :
	padding(Thickness(0)),
	content(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Assigna el contingut.
/// \param    value: El contingut.
///
void ContentControl::setContent(
	Visual* value) {

	if (content != value) {

		if (content != nullptr)
			removeVisual(content);

		content = value;

		if (content != nullptr)
			addVisual(content);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Assigna el marge interior.
/// \param    value: El marge interior.
///
void ContentControl::setPadding(
	const Thickness& value) {

	if (padding != value) {
		padding = value;
		invalidateLayout();
	}
}
