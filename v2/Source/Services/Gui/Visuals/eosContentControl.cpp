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


/// ----------------------------------------------------------------------
/// \brief Calcula la mida del visual i dels seus fills.
/// \param availableSize: Indica el tamany disponible.
/// \return El tamany requerit.
///
Size ContentControl::measureOverride(
	const Size &availableSize) const {

	if ((pContent != nullptr)) {
		pContent->measure(availableSize);
		return pContent->getDesiredSize();
	}
	else
		return Size(0, 0);
}


/// ----------------------------------------------------------------------
/// \brief Ajusta el tamany del panell i dels seus fills.
/// \param finalSize: El tamany final a asignar.
/// \return El tamany final obtingut.
///
Size ContentControl::arrangeOverride(
	const Size &finalSize) const {

	if (pContent != nullptr) {

		Rect r(Point(0, 0), finalSize);
		pContent->arrange(r);
	}

	return finalSize;
}

