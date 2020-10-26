#include "eos.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/eosString.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    visual: El control al que aplicar la plantilla.
///
VirtualKeyboardTemplate::VirtualKeyboardTemplate(
	VirtualKeyboard *visual):

	visual(visual) {

}

/// ----------------------------------------------------------------------
/// \brief    Aplica la plantilla al control.
///
void VirtualKeyboardTemplate::applyTemplate() {

	Size size(40, 40);

	// Panell principal
	//
	StackPanel* sp = new StackPanel();
	sp->setOrientation(Orientation::vertical);
	visual->addChild(sp);

	// Panell de la primera fila
	//
	StackPanel* sp1 = new StackPanel();
	sp1->setOrientation(Orientation::horizontal);
	sp->addChild(sp1);

	// Boto "7"
	//
	PushButton* pb11 = createPushButton("7", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key7));
	sp1->addChild(pb11);

	// Boto "8"
	//
	PushButton* pb12 = createPushButton("8", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key8));
	sp1->addChild(pb12);

	// Boto "9"
	//
	PushButton* pb13 = createPushButton("9", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key9));
	sp1->addChild(pb13);

	// Panell de la segona fila
	//
	StackPanel* sp2 = new StackPanel();
	sp2->setOrientation(Orientation::horizontal);
	sp->addChild(sp2);

	PushButton* pb21 = createPushButton("4", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key4));
	sp2->addChild(pb21);

	PushButton* pb22 = createPushButton("5", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key5));
	sp2->addChild(pb22);

	PushButton* pb23 = createPushButton("6", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key6));
	sp2->addChild(pb23);

	// Panell de la tercera fila
	//
	StackPanel* sp3 = new StackPanel();
	sp3->setOrientation(Orientation::horizontal);
	sp->addChild(sp3);

	PushButton* pb31 = createPushButton("1", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key1));
	sp3->addChild(pb31);

	PushButton* pb32 = createPushButton("2", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key2));
	sp3->addChild(pb32);

	PushButton* pb33 = createPushButton("3", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key3));
	sp3->addChild(pb33);

	// Panell de la quarta fila
	//
	StackPanel* sp4 = new StackPanel();
	sp4->setOrientation(Orientation::horizontal);
	sp->addChild(sp4);

	PushButton* pb41 = createPushButton("0", size);
	pb11->setId(unsigned(VirtualKeyboard::KeyCode::key0));
	sp4->addChild(pb41);
}


PushButton* VirtualKeyboardTemplate::createPushButton(
	const String& text,
	const Size& size) {

	Label* label = new Label();
	label->setText(text);

	PushButton* pb = new PushButton();
	pb->setMargin(Thickness(2, 2, 2, 2));
	pb->setSize(size);
	pb->setContent(label);
	pb->setEventCallback(visual->getButtonEventCallback());

	return pb;
}


