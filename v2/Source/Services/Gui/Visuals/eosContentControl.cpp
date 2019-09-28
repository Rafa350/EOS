#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosContentControl.h"


using namespace eos;


/// ---------------------------------------------------------------------
/// \brief Constructor del objecte.
///
ContentControl::ContentControl() :
	padding(Thickness(0)),
	pContent(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief Assigna el contingut.
/// \param pNewContent: El contingut.
///
void ContentControl::setContent(
	Visual *pNewContent) {

	if (pContent != pNewContent) {

		if (pContent != nullptr)
			removeVisual(pContent);

		pContent = pNewContent;

		if (pContent != nullptr)
			addVisual(pContent);

		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief Assigna el marge interior.
/// \param padding: El marge interior.
///
void ContentControl::setPadding(
	const Thickness &padding) {

	if (this->padding != padding) {
		this->padding = padding;
		invalidate();
	}
}
