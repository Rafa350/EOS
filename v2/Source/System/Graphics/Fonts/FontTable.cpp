#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosFont.h"


using namespace eos;


#ifdef FONT_USE_Arial14pt
extern const unsigned char *fontArial14pt;
#endif
#ifdef FONT_USE_Arial18pt
extern const unsigned char *fontArial18pt;
#endif
#ifdef FONT_USE_Arial24pt
extern const unsigned char *fontArial24pt;
#endif
#ifdef FONT_USE_Consolas8pt
extern const unsigned char *fontConsolas8pt;
#endif
#ifdef FONT_USE_Consolas10pt
extern const unsigned char *fontConsolas10pt;
#endif
#ifdef FONT_USE_Consolas12pt
extern const unsigned char *fontConsolas12pt;
#endif
#ifdef FONT_USE_Consolas14pt
extern const unsigned char *fontConsolas14pt;
#endif
#ifdef FONT_USE_Consolas18pt
extern const unsigned char *fontConsolas18pt;
#endif
#ifdef FONT_USE_Consolas24pt
extern const unsigned char *fontConsolas24pt;
#endif
#ifdef FONT_USE_Tahoma10pt
extern const unsigned char *fontTahoma10pt;
#endif
#ifdef FONT_USE_Tahoma12pt
extern const unsigned char *fontTahoma12pt;
#endif


static const FontTableEntry fonts[] = {

	// Primer sempre el font per defecte
	{ eosGraphics_DefFontName, eosGraphics_DefFontHeight, eosGraphics_DefFontStyle, eosGraphics_DefFontResource },

#ifdef FONT_USE_Arial14pt
    { "Arial", 14, FontStyle::regular, fontArial14pt },
#endif

#ifdef FONT_USE_Arial18pt
    { "Arial", 18, FontStyle::regular, fontArial18pt },
#endif

#ifdef FONT_USE_Arial24pt
    { "Arial", 24, FontStyle::regular, fontArial24pt },
#endif

#ifdef FONT_USE_Consolas8pt
    { "Consolas", 8, FontStyle::regular, fontConsolas8pt },
#endif

#ifdef FONT_USE_Consolas10pt
    { "Consolas", 10, FontStyle::regular, fontConsolas10pt },
#endif

#ifdef FONT_USE_Consolas12pt
    { "Consolas", 12, FontStyle::regular, fontConsolas12pt },
#endif

#ifdef FONT_USE_Consolas14pt
    { "Consolas", 14, FontStyle::regular, fontConsolas14pt },
#endif

#ifdef FONT_USE_Consolas18pt
    { "Consolas", 18, FontStyle::regular, fontConsolas18pt },
#endif

#ifdef FONT_USE_Consolas24pt
    { "Consolas", 24, FontStyle::regular, fontConsolas24pt },
#endif

#ifdef FONT_USE_Tahoma10pt
    { "Tahoma", 10, FontStyle::regular, fontTahoma10pt },
#endif

#ifdef FONT_USE_Tahoma12pt
    { "Tahoma", 12, FontStyle::regular, fontTahoma12pt },
#endif

	// Marca de final de taula
	{ NULL, 0, FontStyle::regular, NULL }
};


const FontTableEntry *fontResourceTable = fonts;

