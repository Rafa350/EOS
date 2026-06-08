#include "eos.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "appDROForm.h"


using namespace eos;
using namespace app;


DROPanel::DROPanel() {

	initialize();
}


void DROPanel::initialize() {

	Border* border = new Border();
	border->setHorizontalAlignment(HorizontalAlignment::center);
	border->setVerticalAlignment(VerticalAlignment::center);
	border->setBackground(Brush(RGB(50, 0, 0)));
	border->setBorderBrush(Brush(Colors::white));
	border->setBorderThickness(1);

	StackPanel *vStack = new StackPanel();
	vStack->setOrientation(Orientation::vertical);

	StackPanel *hStack1 = new StackPanel();
	hStack1->setOrientation(Orientation::horizontal);

	StackPanel *hStack2 = new StackPanel();
	hStack2->setOrientation(Orientation::horizontal);

	StackPanel *hStack3 = new StackPanel();
	hStack3->setOrientation(Orientation::horizontal);

	TextBlock *text1 = new TextBlock();
	text1->setText("X");

	TextBlock *text2 = new TextBlock();
	text2->setText("Y");

	TextBlock *text3 = new TextBlock();
	text3->setText("Z");

	addChild(border);
	border->setChild(vStack);
	vStack->addChild(hStack1);
	vStack->addChild(hStack2);
	vStack->addChild(hStack3);
	hStack1->addChild(text1);
	hStack2->addChild(text2);
	hStack3->addChild(text3);
}
