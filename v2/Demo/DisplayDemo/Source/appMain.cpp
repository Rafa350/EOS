#include "eos.h"
#include "appApplication.h"


#include "System/Graphics/eosColor.h"
using namespace eos;

using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {


	ColorBase<ColorFormat::argb8888> rgb8888_A(0xFF, 0, 0, 0);
	ColorBase<ColorFormat::argb8888> rgb8888_R(0, 0xFF, 0, 0);
	ColorBase<ColorFormat::argb8888> rgb8888_G(0, 0, 0xFF, 0);
	ColorBase<ColorFormat::argb8888> rgb8888_B(0, 0, 0, 0xFF);
	ColorBase<ColorFormat::rgb565> rgb565_R(0, 0xFF, 0, 0);
	ColorBase<ColorFormat::rgb565> rgb565_G(0, 0, 0xFF, 0);
	ColorBase<ColorFormat::rgb565> rgb565_B(0, 0, 0, 0xFF);

	MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
