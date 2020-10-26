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
uint16_t ColorMath::RGB565_combineColor(
	uint16_t b,
	uint16_t f,
	uint8_t o) {

	uint8_t br = (b & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	uint8_t bg = (b & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	uint8_t bb = (b & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	uint8_t fr = (f & COLOR_RGB565_MASK_R) >> COLOR_RGB565_SHIFT_R;
	uint8_t fg = (f & COLOR_RGB565_MASK_G) >> COLOR_RGB565_SHIFT_G;
	uint8_t fb = (f & COLOR_RGB565_MASK_B) >> COLOR_RGB565_SHIFT_B;

	return (uint16_t)
		((((fr * o) + (br * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_R) |
		((((fg * o) + (bg * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_G) |
		((((fb * o) + (bb * (255u - o))) >> 8) << COLOR_RGB565_SHIFT_B);
}


