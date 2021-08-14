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
	_buttonEventCallback(this, &MyApplication::buttonEventHandler),
	_virtualKeyboardEventCallback(this, &MyApplication::virtualKeyboardEventHandler) {

	_ledService = new LedService(this);
	_guiService = new GuiService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio de l'aplicacio.
///
void MyApplication::onInitialize() {

	// Carrega els recursos
	//
	//Bitmap *bitmap = new Bitmap(bitmapBmpMain);

	createMainPanel();
	Application::onInitialize();
}


void MyApplication::createMainPanel() {

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
	kb->setMargin(Thickness(5, 0, 5, 5));
	kb->setHorizontalAlignment(HorizontalAlignment::center);
	kb->setVerticalAlignment(VerticalAlignment::center);
	kb->setEventCallback(&_virtualKeyboardEventCallback);
	sp->addChild(kb);

	_guiService->getScreen()->addChild(border);
	_guiService->setFocus(tb);
}


void MyApplication::buttonEventHandler(
	const ButtonBase::EventArgs& args) {

	args.button->setVisibility(Visibility::hidden);
}


void MyApplication::virtualKeyboardEventHandler(
	const eos::VirtualKeyboard::EventArgs& args) {
}
