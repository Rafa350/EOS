#ifndef __eosColorDefinitions__
#define __eosColorDefinitions__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


// Basic colors
//
namespace eos {

	struct Colors {
		static constexpr Color transparent            = ARGB(0, 0, 0, 0);
		static constexpr Color black               	  = RGB(0, 0, 0);
		static constexpr Color white                  = RGB(255, 255, 255);
		static constexpr Color blue                   = RGB(0, 0, 255);
		static constexpr Color cyan                   = RGB(0, 255, 255);
		static constexpr Color magenta                = RGB(255, 0, 255);
		static constexpr Color silver                 = RGB(192, 192, 192);
		static constexpr Color gray                   = RGB(128, 128, 128);
		static constexpr Color maroon                 = RGB(128, 0, 0);
		static constexpr Color purple                 = RGB(128, 0, 128);
		static constexpr Color teal                   = RGB(0, 128, 128);
		static constexpr Color navy                   = RGB(0, 0, 128);

		// HTML red colors
		//
		static constexpr Color lightSalmon            = RGB(255, 160, 122);
		static constexpr Color salmon                 = RGB(250, 128, 114);
		static constexpr Color darkSalmon             = RGB(233, 150, 122);
		static constexpr Color lightCoral             = RGB(240, 128, 128);
		static constexpr Color indianRed              = RGB(205, 92, 92);
		static constexpr Color crimson                = RGB(220, 20, 60);
		static constexpr Color fireBrick              = RGB(178, 34, 34);
		static constexpr Color red                    = RGB(255, 0, 0);
		static constexpr Color darkRed                = RGB(139, 0, 0);

		// HTML orange colors
		//
		static constexpr Color coral                  = RGB(255, 127, 80);
		static constexpr Color tomato                 = RGB(255, 99, 71);
		static constexpr Color orangeRed              = RGB(255, 69, 0);
		static constexpr Color gold                   = RGB(255, 215, 0);
		static constexpr Color orange                 = RGB(255, 165, 0);
		static constexpr Color darkOrange             = RGB(255, 140, 0);

		// HTML yellow colors
		//
		static constexpr Color lightYellow            = RGB(255, 255, 224);
		static constexpr Color lemonChiffon           = RGB(255, 250, 205);
		static constexpr Color lightGoldenrodYellow   = RGB(250, 250, 210);
		static constexpr Color papayaWhip             = RGB(255, 239, 213);
		static constexpr Color moccasin               = RGB(225, 228, 181);
		static constexpr Color peachPuff              = RGB(255, 218, 185);
		static constexpr Color paleGoldenrod          = RGB(238, 232, 170);
		static constexpr Color khaki                  = RGB(240, 230, 140);
		static constexpr Color darkKhaki              = RGB(189, 183, 107);
		static constexpr Color yellow                 = RGB(255, 255, 0);

		// HTML green colors
		//
		static constexpr Color lawnGreen              = RGB(124, 252, 0);
		static constexpr Color chartreuse             = RGB(127, 255, 0);
		static constexpr Color limeGreen              = RGB(50, 205, 50);
		static constexpr Color lime                   = RGB(0, 255, 0);
		static constexpr Color forestGreen            = RGB(34, 139, 34);
		static constexpr Color green                  = RGB(0, 128, 0);
		static constexpr Color darkGreen              = RGB(0, 100, 0);
		static constexpr Color greenYellow            = RGB(173, 255, 47);
		static constexpr Color yellowGreen            = RGB(154, 205, 50);
		static constexpr Color springGreen            = RGB(0, 255, 127);
		static constexpr Color mediumSpreingGreen     = RGB(0, 250, 154);
		static constexpr Color lightGreen             = RGB(144, 238, 144);
		static constexpr Color paleGreen              = RGB(152, 251, 152);
		static constexpr Color darkSeaGreen           = RGB(143, 188, 143);
		static constexpr Color mediumSeaGreen         = RGB(60, 179, 113);
		static constexpr Color seaGreen               = RGB(46, 139, 87);
		static constexpr Color olive                  = RGB(128, 128, 0);
		static constexpr Color darkOliveGreen         = RGB(85, 107, 47);
		static constexpr Color oliveDrab              = RGB(107, 142, 35);

		// HTML cyan colors
		//
		static constexpr Color lightCyan              = RGB(224, 255, 255);
		static constexpr Color aqua                   = RGB(0, 255, 255);
		static constexpr Color Aquamarine             = RGB(127, 255, 212);
		static constexpr Color mediumAquamarine       = RGB(102, 205, 170);
		static constexpr Color paleTurquoise          = RGB(175, 238, 238);
		static constexpr Color turquoise              = RGB(64, 224, 208);
		static constexpr Color mediumTurquoise        = RGB(72, 209, 204);
		static constexpr Color darkTurquoise          = RGB(0, 206, 209);
		static constexpr Color lightSeaGreen          = RGB(32, 178, 170);
		static constexpr Color cadetBlue              = RGB(95, 158, 160);
		static constexpr Color darkCyan			      = RGB(0, 139, 139);

		// HTML blue colors
		//
		static constexpr Color powderBlue             = RGB(176, 224, 230);
		static constexpr Color lightBlue              = RGB(173, 216, 230);
		static constexpr Color lightSkyBlue           = RGB(135, 206, 250);
		static constexpr Color skyBlue                = RGB(135, 206, 235);
		static constexpr Color deepSkyBlue            = RGB(0, 191, 255);
		static constexpr Color lightSteelBlue         = RGB(176, 196, 222);
		static constexpr Color dodgerBlue             = RGB(30, 144, 255);
		static constexpr Color cornflowerBlue         = RGB(100, 149, 237);
		static constexpr Color steelBlue              = RGB(70, 130, 180);
		static constexpr Color royalBlue              = RGB(65, 105, 225);
		static constexpr Color mediumBlue             = RGB(0, 0, 205);
		static constexpr Color darkBlue               = RGB(0, 0, 139);
		static constexpr Color midnightBlue           = RGB(25, 25, 112);
		static constexpr Color mediumSlateBlue        = RGB(123, 104, 238);
		static constexpr Color slateBlue              = RGB(106, 90, 205);
		static constexpr Color darkSlateBlue          = RGB(72, 61, 139);

		// HTML gray colors
		//
		static constexpr Color darkGray               = RGB(169, 169, 169);
		static constexpr Color lightSlateGray         = RGB(119, 136, 153);
		static constexpr Color slateGray              = RGB(112, 128, 144);
		static constexpr Color darkSlateGray          = RGB(47, 79, 79);

		// Basic palete colors
		//
		static constexpr Color palBlack               = PAL(0);
		static constexpr Color palWhite               = PAL(255);
		static constexpr Color palBlue                = PAL(2);
		static constexpr Color palCyan                = PAL(3);
		static constexpr Color palMagenta             = PAL(4);
		static constexpr Color palSilver              = PAL(5);
		static constexpr Color palGray                = PAL(6);
		static constexpr Color palMaroon              = PAL(7);
		static constexpr Color palPurple              = PAL(8);
		static constexpr Color palTeal                = PAL(9);
		static constexpr Color palNavy                = PAL(10);
	};
}

#endif // __eosColorDefinitions__
