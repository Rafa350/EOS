#include "eos.h"
#include "System/Graphics/eosColorMath.h"
#include "System/Graphics/eosColor.h"


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

	typedef ColorTrait<ColorFormat::rgb565> CI;

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


uint8_t ColorMath::grayAverage(
	uint8_t r,
	uint8_t g,
	uint8_t b) {

	uint32_t rr = r;
	uint32_t gg = g;
	uint32_t bb = b;

	return (rr + gg + bb) / 3;
}


uint8_t ColorMath::grayWeight(
	uint8_t r,
	uint8_t g,
	uint8_t b) {

	uint32_t rr = (unsigned)r * 612;   // 0.299 * 2048
	uint32_t gg = (unsigned)g * 1202;  // 0.587 * 2048
	uint32_t bb = (unsigned)b * 294;   // 0.144 * 2048

	return (rr + gg + bb) >> 11;       // Divideix per 2048

}


/// ----------------------------------------------------------------------
/// \brief    Combina dos pixels amb opacitat.
/// \param    fg: El pixel a combinar.
/// \param    bg: El pixel de fons.
/// \param    opascity: Opacitat del pixel fg.
/// \return   El pixel combinat.
///
Color::Pixel combinePixels(
	Color::Pixel fg,
	Color::Pixel bg,
	uint8_t opacity) {

	using CT = ColorTrait<Color::format>;

	uint32_t fgR = (fg & CT::maskR) >> CT::shiftR;
	uint32_t fgG = (fg & CT::maskG) >> CT::shiftG;
	uint32_t fgB = (fg & CT::maskB) >> CT::shiftB;

	uint32_t bgR = (bg & CT::maskR) >> CT::shiftR;
	uint32_t bgG = (bg & CT::maskG) >> CT::shiftG;
	uint32_t bgB = (bg & CT::maskB) >> CT::shiftB;

	Color::Pixel c =
		((((fgR * opacity) + (bgR * (255 - opacity))) >> 8) << CT::shiftR) |
		((((fgG * opacity) + (bgG * (255 - opacity))) >> 8) << CT::shiftG) |
		((((fgB * opacity) + (bgB * (255 - opacity))) >> 8) << CT::shiftB);

	if constexpr (CT::hasAlpha)
		c |= 0xFF << CT::shiftA;

	return c;
}
