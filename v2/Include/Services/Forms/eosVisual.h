#pragma once
#ifndef __eosVisual__
#define __eosVisual__


#include "eos.h"
#include "Services/Forms/eosPropertyObserver.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


namespace eos {

	class Graphics;
	class FormMessage;

	class Visual;
    using VisualList = eos::IntrusiveForwardList<Visual, 0>;
    using VisualListNode = eos::IntrusiveForwardListNode<Visual, 0>;

    class Visual: public VisualListNode, public PropertyObserver {
    	private:
    		Point _position;
    		Size _size;
    		Visual *_parent;
    		VisualList _childs;
            bool _renderPending;

    	protected:
            virtual void onMessage(FormMessage &message);
            virtual void onRender(Graphics *graphics);
            virtual void onPropertyChanged(void *property);

    	public:
    		Visual(const Point &position, const Size &size);

    		inline void setPosition(const Point &value) { setProperty(_position, value); }
    		inline void setSize(const Size &value) { setProperty(_size, value); }

    		inline Visual* getParent() const { return _parent; }
    		Visual *getRoot();
    		inline const Point& getPosition() const { return _position; }
    		inline const Size& getSize() const { return _size; }

            bool isRenderPending() const;

    		void addChild(Visual *visual);

            void invalidate();
            void message(FormMessage &message);
    		void render(Graphics *graphics);
    };

}


#endif // __eosVisual__
