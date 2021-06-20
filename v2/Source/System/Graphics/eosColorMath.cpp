#include "eos.h"
#include "System/Graphics/eosColorMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Compbina dos pixels en format RGB565
/// \param    b: Pixel del fons.
/// \param    f: Pixel del primer pla.
/// \param    o: Opacitat.
/// \return   El valor del pixel combinat.
///
uint16_t ColorMath::combineColor_RGB565(
	uint16_t b,
	uint16_t f,
	uint8_t o) {

	typedef ColorInfo<ColorFormat::rgb565> CI;

	uint8_t br = (b & CI::maskR) >> CI::shiftR;
	uint8_t bg = (b & CI::maskG) >> CI::shiftG;
	uint8_t bb = (b & CI::maskB) >> CI::shiftB;

	uint8_t fr = (f & CI::maskR) >> CI::shiftR;
	uint8_t fg = (f & CI::maskG) >> CI::shiftG;
	uint8_t fb = (f & CI::maskB) >> CI::shiftB;

	return (uint16_t)
		((((fr * o) + (br * (255u - o))) >> 8) << CI::shiftR) |
		((((fg * o) + (bg * (255u - o))) >> 8) << CI::shiftG) |
		((((fb * o) + (bb * (255u - o))) >> 8) << CI::shiftB);
}


