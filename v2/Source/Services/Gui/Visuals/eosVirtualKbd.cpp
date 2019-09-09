#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosRenderContext.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosVirtualKbd.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


struct KeyInfo {
	int x;
	int y;
	int width;
	int height;
	const char *text;
};

static const KeyInfo calculatorKeys[] = {
	{  5,  5, 25, 25, "1" },
	{ 35,  5, 25, 25, "2" },
	{ 65,  5, 25, 25, "3" },
	{  5, 35, 25, 25, "4" },
	{ 35, 35, 25, 25, "5" },
	{ 65, 35, 25, 25, "6" },
	{  5, 65, 25, 25, "7" },
	{ 35, 65, 25, 25, "8" },
	{ 65, 65, 25, 25, "9" },
	{  5, 95, 25, 90, "0" }
};


VirtualKeyboard::VirtualKeyboard() {

	initializePanel();
}


void VirtualKeyboard::initializePanel() {

	setColor(Color::fromRGB888(0xFF3A3A3A));
	for (int i = 0; i < 9; i++) {
		const KeyInfo *p = &calculatorKeys[i];
		PushButton *button = new PushButton();
		button->setPosition(Point(p->x, p->y));
		button->setSize(Size(p->width, p->height));
		addChild(button);
	}
}
