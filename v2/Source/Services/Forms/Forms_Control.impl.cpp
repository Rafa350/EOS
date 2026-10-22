module Eos.Services.Forms;

import Eos.System.Graphics.Brush;
import Eos.System.Graphics.Canvas;
import Eos.System.Graphics.ColorDefinitions;
import Eos.System.Graphics.Pen;
import Eos.System.Graphics.Rect;


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    point: La posicio.
/// \param    size: El tamany.
///
Control::Control(
    const Point &position,
    const Size &size):

	Visual {position, size},
	_backgroundColor {Colors::black},
	_borderColor {Colors::white} {
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el control.
/// \param    graphics : L'objecte per dibuixar.
///
void Control::onRender(
	Graphics *graphics) {

    graphics->paintRectangle(
   		Pen(_borderColor, 1),
   		Brush(_backgroundColor),
   		Rect(getPosition(), getSize())
	);

    Visual::onRender(graphics);
}


/// ---------------------------------------------------------------------
/// \brief    Metode que es crida quant canvia el valor d'una propietat.
/// \param    property : La propietat que ha canviat.
///
void Control::onPropertyChanged(
    void *property) {

	if ((property == &_backgroundColor) || (property == &_borderColor))
		invalidate();

	else
		Visual::onPropertyChanged(property);
}
