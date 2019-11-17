#include "eos.h"
#include "eosAssert.h"
#include "Services/eosGuiService.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosScreen.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosTextBox.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Graphics/eosBitmap.h"
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
	buttonEventCallback(this, &MyApplication::buttonEventHandler) {

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


Panel *MyApplication::createMainPanel() {

	StackPanel *sp = new StackPanel();
	sp->setOrientation(Orientation::vertical);
	sp->setHorizontalAlignment(HorizontalAlignment::center);
	sp->setVerticalAlignment(VerticalAlignment::center);

	TextBox *tb = new TextBox();
	tb->setSize(Size(200, 30));
	tb->setMargin(Thickness(5, 5, 5, 5));
	tb->setHorizontalAlignment(HorizontalAlignment::center);
	tb->setVerticalAlignment(VerticalAlignment::center);
	sp->addChild(tb);

	VirtualKeyboard *kb = new VirtualKeyboard();
	kb->setHorizontalAlignment(HorizontalAlignment::center);
	kb->setVerticalAlignment(VerticalAlignment::center);
	sp->addChild(kb);

	return sp;
}


void MyApplication::buttonEventHandler(
	const ButtonBase::EventArgs &args) {

	args.button->setVisibility(Visibility::hidden);
}
