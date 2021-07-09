#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/STM32/halEXTI.h"
#include "Services/eosGuiService.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTextBox.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "appApplication.h"
#include "appLedService.h"


//extern "C" const unsigned char bitmapBmpMain[];

using namespace eos;
using namespace app;


///-----------------------------------------------------------------------
/// \brief    Contructor.
///
MyApplication::MyApplication():

	Application(),
	buttonEventCallback(this, &MyApplication::buttonEventHandler),
	virtualKeyboardEventCallback(this, &MyApplication::virtualKeyboardEventHandler) {

	ledService = new LedService(this);
	guiService = new GuiService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio de l'aplicacio.
///
void MyApplication::onInitialize() {

	// Carrega els recursos
	//
	//Bitmap *bitmap = new Bitmap(bitmapBmpMain);

	Visual *visual = createMainPanel();
	guiService->getScreen()->addChild(visual);

	Application::onInitialize();
}


Visual *MyApplication::createMainPanel() {

	Border* border = new Border();
	border->setHorizontalAlignment(HorizontalAlignment::center);
	border->setVerticalAlignment(VerticalAlignment::center);
	border->setBackground(Brush(BrushStyle::solid, RGB(50, 50, 50)));
	border->setBorderThickness(1);

	StackPanel* sp = new StackPanel();
	sp->setOrientation(Orientation::vertical);
	sp->setHorizontalAlignment(HorizontalAlignment::center);
	sp->setVerticalAlignment(VerticalAlignment::center);
	border->setChild(sp);

	TextBox* tb = new TextBox();
	tb->setId(1000);
	tb->setSize(Size(200, 30));
	tb->setMargin(Thickness(5, 5, 5, 5));
	tb->setHorizontalAlignment(HorizontalAlignment::center);
	tb->setVerticalAlignment(VerticalAlignment::center);
	sp->addChild(tb);

	VirtualKeyboard* kb = new VirtualKeyboard();
	kb->setHorizontalAlignment(HorizontalAlignment::center);
	kb->setVerticalAlignment(VerticalAlignment::center);
	kb->setEventCallback(&virtualKeyboardEventCallback);
	sp->addChild(kb);

	return border;
}


void MyApplication::buttonEventHandler(
	const ButtonBase::EventArgs& args) {

	args.button->setVisibility(Visibility::hidden);
}


void MyApplication::virtualKeyboardEventHandler(
	const eos::VirtualKeyboard::EventArgs& args) {

	unsigned key = unsigned(args.keyCode);

	String text;

	text = "caca de perro";
	text = "mierda";

	TextBox* tb = (TextBox*) VisualUtils::getVisual(guiService->getScreen(), 1000);
	unsigned id = tb->getId();
	tb->setText(text);
}
