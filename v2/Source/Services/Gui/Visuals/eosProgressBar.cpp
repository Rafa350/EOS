#include "eos.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosProgressBar.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosRect.h"

#include <cmath>


using namespace eos;


struct ProgressBarStyle {
	Color backgroundColor;
	Color borderColor;
	Color barColor;
};

static const ProgressBarStyle style = {
	.backgroundColor = Colors::black,
	.borderColor = Colors::red,
	.barColor = Colors::green
};

static const ProgressBarStyle *pStyle = &style;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
ProgressBar::ProgressBar():
	backgroundColor(pStyle->backgroundColor),
	borderColor(pStyle->borderColor),
	barColor(pStyle->barColor),
	minValue(0),
	maxValue(100),
    value(50) {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor de la propietat 'MaxValue'
/// \param    value: El no valor.
///
void ProgressBar::setMaxValue(
	int value) {

	if (maxValue != value) {
		maxValue = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor de la propietat 'MinValue'
/// \param    value: El no valor.
///
void ProgressBar::setMinValue(
	int value) {

	if (minValue != value) {
		minValue = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor de la propietat 'Value'
/// \param    value: El no valor.
///
void ProgressBar::setValue(
	int value) {

	if (this->value != value) {
		this->value = value;
		invalidate();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida desitjada del visual.
/// \param    availableSize: Tamany disponible.
///
Size ProgressBar::measureOverride(
	const Size &availableSize) const {

	return Size(200, 30);
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el control.
/// \param    context: El context de renderitzat.
///
void ProgressBar::onRender(
	RenderContext *context) {

	Graphics &g = context->beginRender(this);

	const Rect &r = getBounds();
	int width = r.getWidth();
	int height = r.getHeight();

	int w = value * width / (std::max(1, maxValue - minValue));

	g.fillRectangle(w, 0, width - 1, height - 1, backgroundColor);
	g.fillRectangle(0, 0, w, height - 1, barColor);
	g.drawRectangle(0, 0, width - 1, height - 1, borderColor);


	context->endRender();
}
