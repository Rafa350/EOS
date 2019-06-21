#ifndef __eosWindow__
#define __eosWindow__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {


    class Window: public Visual {
    	private:
    		int x;
    		int y;
    		int width;
    		int height;

    	public:
            void setPosition(int x, int y);
            void setSize(int width, int height);

            inline int getX() const { return x; }
            inline int getY() const { return y; }
            inline int getWidth() const { return width; }
            inline int getHeight() const { return height; }
    };

}


#endif // __eosWindow__
