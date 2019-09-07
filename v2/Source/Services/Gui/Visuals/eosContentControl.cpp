#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/Visuals/eosContentControl.h"



using namespace eos;


/// ---------------------------------------------------------------------
/// \brief Constructor del objecte.
///
ContentControl::ContentControl() :
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
