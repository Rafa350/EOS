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
	{   5,   5,  35,  35, "1" },
	{  45,   5,  35,  35, "2" },
	{  85,   5,  35,  35, "3" },
	{   5,  45,  35,  35, "4" },
	{  45,  45,  35,  35, "5" },
	{  85,  45,  35,  35, "6" },
	{   5,  85,  35,  35, "7" },
	{  45,  85,  35,  35, "8" },
	{  85,  85,  35,  35, "9" },
	{   5, 125, 115,  35, "0" }
};


VirtualKeyboard::VirtualKeyboard() {

	initializePanel();
}


void VirtualKeyboard::initializePanel() {

	setColor(Color::fromRGB888(0xFF3A3A3A));
	for (int i = 0; i < 10; i++) {
		const KeyInfo *p = &calculatorKeys[i];
		PushButton *button = new PushButton();
		//button->setPosition(Point(p->x, p->y));
		button->setSize(Size(p->width, p->height));
		addChild(button);
	}
}
