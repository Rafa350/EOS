#include "eos.h"
#include "Services/Forms/eosControl.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosRect.h"


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    point: La posicio.
/// \param    size: El tamany.
///
eos::Control::Control(
    const Point &position,
    const Size &size):

	Visual {position, size},
	_backgroundColor {Colors::black},
	_borderColor {Colors::white},
	_propertyChangedEvent {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el control.
/// \param    graphics : L'objecte per dibuixar.
///
void eos::Control::onRender(
	Graphics *graphics) {

    graphics->paintRectangle(
   		Pen(_borderColor, 1),
   		Brush(_backgroundColor),
   		Rect(getPosition(), getSize())
	);

    Visual::onRender(graphics);
}


/// ---------------------------------------------------------------------
/// \brief    Metode que es crida quent canvia el valor d'una propietat.
/// \param    property : La propietat que ha canviat.
///
void eos::Control::onPropertyChanged(
    void *property) {

	if (_propertyChangedEvent != nullptr) {
		PropertyChangedEventArgs args = {
			.ptr {property}
		};
		_propertyChangedEvent->execute(this, &args);
	}

	if ((property == &_backgroundColor) || (property == &_borderColor))
		invalidate();

	Visual::onPropertyChanged(property);
}
