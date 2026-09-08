module;

#include "eos.h"
#include "eosAssert.h"


module Eos.System.Graphics.Canvas;



/// ----------------------------------------------------------------------
/// \brief    Dibuixa un text.
/// \param    position: Posicio del text
/// \param    text: El text.
///
void eos::Graphics::paintText(
	const Point &position,
	const Text &text) const {

	text.draw(this, position);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un text.
/// \param    box: La caixa que conte el text.
/// \param    text: El text.
///
void eos::Graphics::paintText(
	const Rect &box,
	const Text &text) const {

	text.draw(this, box);
}
