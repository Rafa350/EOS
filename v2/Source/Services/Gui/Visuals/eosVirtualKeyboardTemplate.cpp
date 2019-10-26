#include "eos.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosLabel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosStackPanel.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosSize.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    visual: El controlal que aplicar la plantilla.
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
	StackPanel *sp = new StackPanel();
	sp->setOrientation(Orientation::vertical);
	visual->addChild(sp);

	// Panell de la primera fila
	//
	StackPanel *sp1 = new StackPanel();
	sp1->setOrientation(Orientation::horizontal);
	sp->addChild(sp1);

	// Boto "7"
	//
	PushButton *pb11 = createPushButton("7", size);
	sp1->addChild(pb11);

	// Boto "8"
	//
	PushButton *pb12 = createPushButton("8", size);
	sp1->addChild(pb12);

	// Boto "9"
	//
	PushButton *pb13 = createPushButton("9", size);
	sp1->addChild(pb13);

	// Panell de la segona fila
	//
	StackPanel *sp2 = new StackPanel();
	sp2->setOrientation(Orientation::horizontal);
	sp->addChild(sp2);

	PushButton *pb21 = createPushButton("4", size);
	sp2->addChild(pb21);

	PushButton *pb22 = createPushButton("5", size);
	sp2->addChild(pb22);

	PushButton *pb23 = createPushButton("6", size);
	sp2->addChild(pb23);

	// Panell de la tercera fila
	//
	StackPanel *sp3 = new StackPanel();
	sp3->setOrientation(Orientation::horizontal);
	sp->addChild(sp3);

	PushButton *pb31 = createPushButton("1", size);
	sp3->addChild(pb31);

	PushButton *pb32 = createPushButton("2", size);
	sp3->addChild(pb32);

	PushButton *pb33 = createPushButton("3", size);
	sp3->addChild(pb33);

	// Panell de la quarta fila
	//
	StackPanel *sp4 = new StackPanel();
	sp4->setOrientation(Orientation::horizontal);
	sp->addChild(sp4);

	PushButton *pb41 = createPushButton("0", size);
	sp4->addChild(pb41);
}


PushButton *VirtualKeyboardTemplate::createPushButton(
	const String &text,
	const Size &size) {

	PushButton *pb = new PushButton();
	pb->setMargin(Thickness(2, 2, 2, 2));
	pb->setSize(size);

	Label *label = new Label();
	pb->setContent(label);
	label->setText(text);

	return pb;
}


