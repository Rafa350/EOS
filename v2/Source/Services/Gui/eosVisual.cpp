#include "eos.h"
#include "eosAssert.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosVisual.h"
#include "System/eosMath.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
///
Visual::Visual():
	_parent(nullptr),
	_needRender(false),
	_visibility(Visibility::visible),
	_size(0, 0),
	_minSize(0, 0),
	_maxSize(INT32_MAX, INT32_MAX),
	_bounds(0, 0, 0, 0),
	_margin(0),
	_horizontalAlignment(HorizontalAlignment::stretch),
	_verticalAlignment(VerticalAlignment::stretch),
	_id(0) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor del objecte.
///
Visual::~Visual() {

	if (_parent != nullptr)
		_parent->removeVisual(this);

	while (!_childs.isEmpty())
		delete _childs.peekBack();
}


/// ----------------------------------------------------------------------
/// \brief    Marca el visual per ser renderizat.
///
void Visual::invalidate() {

	_needRender = true;
}


/// ----------------------------------------------------------------------
/// \brief    Marca el visual per reposicionar.
///
void Visual::invalidateLayout() {

}


/// ----------------------------------------------------------------------
/// \brief    Comprova si cal renderitzar el visual o algun dels seus fills.
/// \return   True si cal renderitzar.
///
bool Visual::isRenderizable() const {

	if (_needRender)
		return true;

	else {
		for (auto child: _childs) {
			if (child->isRenderizable())
				return true;
		}
		return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el visual es visible.
/// \return   True si es visible.
///
bool Visual::isVisible() const {

	if (_visibility == Visibility::visible) {
		if (_parent != nullptr)
			return _parent->isVisible();
		else
			return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el visual.
/// \param    context: El context de renderitzat.
/// \return   True s'ha redibuixat el visual.
///
bool Visual::render(
	RenderContext* context) {

	// TODO: revisar aixo

	bool renderized = false;
	_needRender = false;

	if (isVisible())
		onRender(context);
	renderized = true;

	// Continua amb els fills.
	//
	for (auto child: _childs) {
		if (child->render(context))
			renderized = true;
	}

	return renderized;
}


/// ----------------------------------------------------------------------
/// \brief    Despatcha un missatge.
/// \param    msg: El missatge a despatchar.
///
void Visual::dispatch(
	const Message &msg) {

	onDispatch(msg);
}


/// ---------------------------------------------------------------------
/// \brief    Envia un missatge a la cua de missatges.
/// \param    msg: El missatge a enviar.
///
void Visual::send(
	const Message& msg) {

	MsgQueue* msgQueue = MsgQueue::getInstance();
	msgQueue->send(msg);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un visual.
/// \param    visual: L'objecte Visual a afeigir.
///
void Visual::addVisual(
	Visual* visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->_parent == nullptr);

	_childs.pushBack(visual);
	visual->_parent = this;

	invalidateLayout();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un visual.
/// \param    visual: L'objecte Visual a eliminar.
///
void Visual::removeVisual(
	Visual* visual) {

	eosAssert(visual != nullptr);
	eosAssert(visual->_parent != nullptr);

	visual->_parent = nullptr;
	_childs.removeAt(_childs.indexOf(visual));

	invalidateLayout();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina els visuals de la llista.
///
void Visual::removeVisuals() {

	while (!_childs.isEmpty())
        removeVisual(_childs.peekBack());
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual. Primera par del layout.
/// \param    availableSize: Indica el tamany disponible.
///
void Visual::measure(
	const Size& availableSize) {

	if (isVisible()) {

		Size measuredSize = measureOverride(_margin.deflate(availableSize));
		int declaredWidth = _size.getWidth();
		int declaredHeight = _size.getHeight();
		int width = declaredWidth != 0 ? declaredWidth : measuredSize.getWidth();
		int height = declaredHeight != 0 ? declaredHeight : measuredSize.getHeight();

		// Ajusta l'amplada als limits
		//
		width = Math::max(_minSize.getWidth(), width);
		width = Math::min(_maxSize.getWidth(), width);

		// Ajusta l'alçada als limits
		//
		height = Math::max(_minSize.getHeight(), height);
		height = Math::min(_maxSize.getHeight(), height);

		_desiredSize = _margin.inflate(Size(width, height));
	}

	else
		_desiredSize = Size();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la mida i la posicio del visual. Segon pas i final del layout.
/// \param    finalSize: Tamany final per asignar al visual.
///
void Visual::arrange(
	const Rect& finalRect) {

	if (isVisible()) {

		// Ajusta el marge
		//
		Rect deflatedFinalRect = _margin.deflate(finalRect);
		int deflatedFinalWidth = deflatedFinalRect.getWidth();
		int deflatedFinalHeight = deflatedFinalRect.getHeight();

		int availableWidth = deflatedFinalWidth;
        if (_horizontalAlignment != HorizontalAlignment::stretch)
            availableWidth = Math::max(0, Math::min(availableWidth, _desiredSize.getWidth() - _margin.getLeft() - _margin.getRight()));

		int availableHeight = deflatedFinalHeight;
        if (_verticalAlignment != VerticalAlignment::stretch)
            availableHeight = Math::max(0, Math::min(availableHeight, _desiredSize.getHeight() - _margin.getTop() - _margin.getBottom()));

        // Obte el tamany definitiu
		//
		Size arrangedSize = arrangeOverride(Size(availableWidth, availableHeight));

		int x = deflatedFinalRect.getX();
		int y = deflatedFinalRect.getY();
		int width = _horizontalAlignment == HorizontalAlignment::stretch ? deflatedFinalWidth : arrangedSize.getWidth();
		int height = _verticalAlignment == VerticalAlignment::stretch ? deflatedFinalHeight : arrangedSize.getHeight();

		switch (_horizontalAlignment) {
			case HorizontalAlignment::left:
				break;

			case HorizontalAlignment::center:
			case HorizontalAlignment::stretch:
				x += (deflatedFinalWidth - width) / 2;
				break;

			case HorizontalAlignment::right:
				x += deflatedFinalWidth - width;
				break;
		}

		switch (_verticalAlignment) {
			case VerticalAlignment::top:
				break;

			case VerticalAlignment::center:
			case VerticalAlignment::stretch:
				y += (deflatedFinalHeight - height) / 2;
				break;

			case VerticalAlignment::bottom:
				y += deflatedFinalHeight - height;
				break;
		}

		Rect bounds(x, y, width, height);
		if (bounds != _bounds) {
			_bounds = bounds;
			invalidate();
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la mida del visual i dels seus fills.
/// \param    availableSize: Indica el tamany disponible.
/// \return   El tamany requerit.
/// \remarks  Per defecte, calcula el tamany necesari per encabir tots
///           els fills. Si no te fills, el tamany es zero.
///
Size Visual::measureOverride(
	const Size& availableSize) const {

	int width = 0;
	int height = 0;

	for (auto it = _childs.begin(); it != _childs.end(); it++) {
		Visual* child = *it;
		eosAssert(child != nullptr);

		if (child->isVisible()) {

			child->measure(availableSize);
			const Size& childDesiredSize = child->getDesiredSize();

			width = Math::max(width, childDesiredSize.getWidth());
			height = Math::max(height, childDesiredSize.getHeight());
		}
	}

	return Size(width, height);
}


/// ----------------------------------------------------------------------
/// \brief    Ajusta el tamany del visual i els seus fills.
/// \param    finalSize: El tamany final a asignar.
/// \return   El tamany final obtingut.
///
Size Visual::arrangeOverride(
	const Size& finalSize) const {

	for (auto child: _childs)
		if (child->isVisible())
			child->arrange(Rect(finalSize));

	return finalSize;
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat de visibilitat.
/// \param    newVisibility: La nova visibilitat.
///
void Visual::setVisibility(
	Visibility value) {

	if (_visibility != value) {
		_visibility = value;
		invalidateLayout();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany.
/// \param    value: El nou tamany.
///
void Visual::setSize(
	const Size &value) {

    if (_size != value) {
    	_size = value;
		invalidateLayout();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el tamany minim.
/// \param    value: El nou tamany.
///
void Visual::setMinSize(
	const Size &value) {

	if (_minSize != value) {
		_minSize = value;
		invalidateLayout();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el marge.
/// \param    value: El nou marge.
///
void Visual::setMargin(
	const Thickness &value) {

	if (_margin != value) {
		_margin = value;
		invalidateLayout();
	}
}


/// ----------------------------------------------------------------------
/// \brief     Asigna l'aliniacio horizontal.
/// \param     value: El nou valor de l'aliniacio.
///
void Visual::setHorizontalAlignment(
	HorizontalAlignment value) {

	if (_horizontalAlignment != value) {
		_horizontalAlignment = value;
		invalidateLayout();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'aliniacio vertical
/// \param    value: El nou valor de l'aliniacio.
///
void Visual::setVerticalAlignment(
	VerticalAlignment value) {

	if (_verticalAlignment != value) {
		_verticalAlignment = value;
		invalidateLayout();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant hi ha que despatxar un missatge.
/// \param    msg: El missatge a despatxar.
///
void Visual::onDispatch(
	const Message& msg) {

	switch (msg.msgId) {
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
		case MsgId::keyboardEvent:
			onDispatchKeyboardEvent(msg.keyboard);
			break;
#endif
#if eosGuiService_TouchPadEnabled
		case MsgId::touchPadEvent:
			onDispatchTouchPadEvent(msg.touchPad);
			break;
#endif
		default:
			// Si no el procesa, pasa al pare.
			if (_parent != nullptr)
				_parent->onDispatch(msg);
			break;
	}

}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant s'ha de renderitzar el visual.
/// \param    context: Context de renderitzat.
///
void Visual::onRender(
	RenderContext* context) {

}


/// ----------------------------------------------------------------------
/// \brief    Es crida al activar el visual.
/// \param    visual: El visual desactivat al activar aquest.
///
void Visual::onActivate(
	Visual* visual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Es crida al desactivar el visual.
/// \param    visual: El visual activat al desactivar aquest.
///
void Visual::onDeactivate(
	Visual* visual) {

	invalidate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events del teclat.
/// \param    msg: L'event a procesat.
///
#if eosGuiService_KeyboardEnablked || eosGuiService_VirtualKeyboardEnabled
void Visual::onDispatchKeyboardEvent(
	const MsgKeyboard& msg) {

	char ch = 0;
	if ((msg.keyCode >= KeyCode::key0) && (msg.keyCode <= KeyCode::key9))
		ch = 0x30 + char(msg.keyCode) - char(KeyCode::key0);
	else if ((msg.keyCode >= KeyCode::keyA) && (msg.keyCode <= KeyCode::keyZ))
		ch = 0x41 + char(msg.keyCode) - char(KeyCode::keyA);

	switch (msg.event) {
		case MsgKeyboardEvent::press:
			onKeyboardPress(msg.keyCode, msg.keyFlags, ch);
			break;

		case MsgKeyboardEvent::release:
			onKeyboardRelease(msg.keyCode, msg.keyFlags, ch);
			break;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'press' del teclat
/// \param    keyCode: Codi de la tecla
/// \param    flags: Indicadors de la trecla: shift, control, etc.
/// \param    ch: Caracter de la tecla, 0 si no correspon a cap.
///
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
void Visual::onKeyboardPress(
	KeyCode keyCode,
	KeyFlags flags,
	char ch) {

	if (_parent != nullptr)
		_parent->onKeyboardPress(keyCode, flags, ch);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'release' del teclat
/// \param    keyCode: Codi de la tecla
/// \param    flags: Indicadors de la trecla: shift, control, etc.
/// \param    ch: Caracter de la tecla, 0 si no correspon a cap.
///
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
void Visual::onKeyboardRelease(
	KeyCode keyCode,
	KeyFlags flags,
	char ch) {

	if (_parent != nullptr)
		_parent->onKeyboardRelease(keyCode, flags, ch);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa els events del touchpad
/// \param    msg: L'event a procesar.
///
#if eosGuiService_TouchPadEnabled
void Visual::onDispatchTouchPadEvent(
	const MsgTouchPad& msg) {

	switch (msg.event) {
		case MsgTouchPadEvent::enter:
			onTouchPadEnter();
			break;

		case MsgTouchPadEvent::leave:
			onTouchPadLeave();
			break;

		case MsgTouchPadEvent::move:
			onTouchPadMove(Point(msg.x, msg.y));
			break;

		case MsgTouchPadEvent::press:
			onTouchPadPress(Point(msg.x, msg.y));
			break;

		case MsgTouchPadEvent::release:
			onTouchPadRelease();
			break;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa l'event 'enter' del touchpad
///
#if eosGuiService_TouchPadEnabled
void Visual::onTouchPadEnter() {

	if (_parent != nullptr)
		_parent->onTouchPadEnter();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'leave' del touchpad
///
#if eosGuiService_TouchPadEnabled
void Visual::onTouchPadLeave() {

	if (_parent != nullptr)
		_parent->onTouchPadLeave();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'press' del touchpad.
///
#if eosGuiService_TouchPadEnabled
void Visual::onTouchPadPress(
	const Point &position) {

	if (_parent != nullptr)
		_parent->onTouchPadPress(position);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'release' del touchpad.
//
#if eosGuiService_TouchPadEnabled
void Visual::onTouchPadRelease() {

	if (_parent != nullptr)
		_parent->onTouchPadRelease();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el event 'move' del touchpad.
/// \param    position: Posicio del punter.
///
#if eosGuiService_TouchPadEnabled
void Visual::onTouchPadMove(
	const Point& position) {

	if (_parent != nullptr)
		_parent->onTouchPadMove(position);
}
#endif
