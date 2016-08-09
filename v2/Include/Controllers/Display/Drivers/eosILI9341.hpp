#ifndef __EOS_CONTROLLERS_DISPLAY_DRIVERS_ILI9341_HPP
#define	__EOS_CONTROLLERS_DISPLAY_DRIVERS_ILI9341_HPP


#include "eos.hpp"
#include "Controllers/Display/eosDisplay.hpp"


namespace eos {
    
    class ILI9341_DisplayDriver: public IDisplayDriver {
        private:
            int xScreenSize;
            int yScreenSize;
            int xClipPos;
            int yClipPos;
            int xClipSize;
            int yClipSize;
            
        public:
            ILI9341_DisplayDriver();
            void initialize();
            void shutdown();
            void setOrientation(Orientation orientation);
            void setClip(int xPos, int yPos, int xSize, int ySize);
            int getXSize() const { return xScreenSize; }
            int getYSize() const { return yScreenSize; }
            void clear(Color color);
            void setPixel(int xPos, int yPos, Color color);
            void setHPixels(int xPos, int yPos, int size, Color color);
            void setVPixels(int xPos, int yPos, int size, Color color);
            void setPixels(int xPos, int yPos, int xSize, int ySize, Color color);
            void setPixels(int xPos, int yPos, int xSize, int ySize, const Color *colors);
    };
}



#endif	

