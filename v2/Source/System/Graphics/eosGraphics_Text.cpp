#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosText.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un text.
/// \param    position: Posicio.
/// \param    text: El text.
///
void Graphics::paintText(
	const Point& position,
	const Text& text) const {

	text.draw(this, position);
}
