#include "eos.h"
#include "eosAssert.h"
#include "Services/eosGuiService.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/eosVisualUtils.h"
#include "Services/Gui/Visuals/eosTabControl.h"
#include "Services/Gui/Visuals/eosTabControlItem.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "Services/Gui/Visuals/eosBorder.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTextBox.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "appApplication.h"
#include "appLedService.h"


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
	createMainPanel();
	Application::onInitialize();
}


eos::Visual* MyApplication::createKeyboardPanel() {

	Border* border = new Border();
	border->setHorizontalAlignment(HorizontalAlignment::center);
	border->setVerticalAlignment(VerticalAlignment::center);
	border->setBackground(Brush(BrushStyle::solid, RGB(50, 0, 0)));
	border->setBorderBrush(Brush(BrushStyle::solid, Colors::white));
	border->setBorderThickness(1);

	StackPanel* sp = new StackPanel();
	sp->setBackground(Brush(BrushStyle::solid, RGB(0x3F, 0x3F, 0x3F)));
	sp->setMargin(Thickness(5));
	sp->setOrientation(Orientation::vertical);
	sp->setHorizontalAlignment(HorizontalAlignment::center);
	sp->setVerticalAlignment(VerticalAlignment::center);
	border->setChild(sp);

	TextBox* tb = new TextBox();
	tb->setId(1000);
	tb->setSize(Size(200, 30));
	tb->setTextAlign(TextAlign::left);
	tb->setMargin(Thickness(5, 5, 5, 5));
	tb->setHorizontalAlignment(HorizontalAlignment::center);
	tb->setVerticalAlignment(VerticalAlignment::center);
	sp->addChild(tb);

	VirtualKeyboard* kb = new VirtualKeyboard();
	kb->setBackground(Brush(BrushStyle::solid, Colors::blue));
	kb->setMargin(Thickness(5, 0, 5, 5));
	kb->setHorizontalAlignment(HorizontalAlignment::center);
	kb->setVerticalAlignment(VerticalAlignment::center);
	kb->setVirtualKeyboardEventCallback(&_virtualKeyboardEventCallback);
	sp->addChild(kb);

	return border;
}


void MyApplication::createMainPanel() {

	TabControl* tabControl = new TabControl();
	tabControl->setHorizontalAlignment(HorizontalAlignment::center);
	tabControl->setVerticalAlignment(VerticalAlignment::center);

	TextBlock* tab1 = new TextBlock();
	tab1->setText("TAB1");
	tab1->setMargin(Thickness(10, 5));
	Panel* panel1 = new Panel();
	panel1->setBackground(Brush(BrushStyle::solid, Colors::red));
	panel1->setMinSize(Size(100, 30));
	TabControlItem* tabItem1 = new TabControlItem(tab1, panel1);

	TextBlock* tab2 = new TextBlock();
	tab2->setText("TAB2");
	tab2->setMargin(Thickness(10, 5));
	Panel* panel2 = new Panel();
	panel2->setMinSize(Size(100, 30));
	panel2->setBackground(Brush(BrushStyle::solid, Colors::green));
	TabControlItem* tabItem2 = new TabControlItem(tab2, panel2);

	TextBlock* tab3 = new TextBlock();
	tab3->setText("TAB3");
	tab3->setMargin(Thickness(10, 5));
	Panel* panel3 = new Panel();
	panel3->setMinSize(Size(100, 30));
	panel3->setBackground(Brush(BrushStyle::solid, Colors::blue));
	TabControlItem* tabItem3 = new TabControlItem(tab3, panel3);

	tabControl->addItem(tabItem1);
	tabControl->addItem(tabItem2);
	tabControl->addItem(tabItem3);

	eos::Visual* keyboardPanel = createKeyboardPanel();

	eos::Screen* screen = _guiService->getScreen();
	screen->addChild(keyboardPanel);
	//screen->addChild(tabControl);

	eos::Visual* tb = VisualUtils::getVisual(screen,  1000);
	_guiService->setFocus(tb);
}


void MyApplication::buttonEventHandler(
	const ButtonEventArgs& args) {

	args.sender->setVisibility(Visibility::hidden);
}


void MyApplication::virtualKeyboardEventHandler(
	const eos::VirtualKeyboardEventArgs& args) {
}
