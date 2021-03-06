#include "eos.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosBitmap.h"
#include "Controllers/TouchPad/eosTouchPad.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#include "appDisplayService.h"

#include <stdlib.h>
#include <stdio.h>


using namespace eos;
using namespace app;


static const char *title = "EOS v2.0: TouchPad Demo";


static Bitmap *createBitmap() {

	extern const unsigned char bitmapBmpMain[];

	const uint8_t *data = bitmapBmpMain;

	int width = (int) (data[0] | (data[1] << 8));
	int height = (int) (data[2] | (data[3] << 8));
	//int flags = (int) (data[4] | (data[5] << 8));

	return new Bitmap(width, height, PixelFormat::rgb565, &data[6]);
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param application: L'aplicacio.
///
DisplayService::DisplayService(
	Application *application):

    AppLoopService(application),
	bitmap(nullptr),
	display(nullptr),
	touch(nullptr) {

}


///-----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

	// Inicialitzacio del display
	//
	displayDriver = RGBDirectDriver::getInstance();
    displayDriver->initialize();
    displayDriver->setOrientation(DisplayOrientation::normal);
    displayDriver->displayOn();

    display = new Graphics(displayDriver);
    display->clear(COLOR_Black);

    //bitmap = new Bitmap(30, 30, PixelFormat::rgb565, Color(COLOR_Blue));
    bitmap = createBitmap();

    // Inicialitzacio del touch pad
    //
    touchDriver = FT5336Driver::getInstance();
    touch = new TouchPad(touchDriver);

    screenWidth = display->getWidth();
    screenHeight  = display->getHeight();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

	TouchPadState tps;

	x = 300;
	y = screenHeight / 2;

    drawBackground();
    while (true) {
    	if (touch->getState(tps)) {
    		int16_t newX = tps.x[0];
    		int16_t newY = tps.y[0];
    		if ((x != newX) || (y != newY)) {

    			clearDot();

    			x = newX;
    			y = newY;

    			drawDot();
    			drawInfo();
    		}
    	}
    	else
    		Task::delay(100);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa el fons de pantalla.
///
void DisplayService::drawBackground() {

    display->clear(COLOR_Black);
    display->resetClip();
    display->setColor(COLOR_Red);

    display->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    display->drawLine(screenWidth - 1, 20, 0, 20);
    display->drawText(4, 16, title, 0, -1);

    display->drawRectangle(7, 27, 130, screenHeight - 10);
    display->drawRectangle(137, 27, screenWidth - 10, screenHeight - 10);

    display->setColor(COLOR_Cyan);
	display->drawText(15, 50, "Position");
	display->drawText(35, 70, "X:");
	display->drawText(35, 90, "Y:");
	display->drawText(15, 120, "Size");
	display->drawText(35, 140, "W:");
	display->drawText(35, 160, "H:");

	drawDot();
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa el punt
///
void DisplayService::drawDot() {

    display->setClip(138, 28, screenWidth - 11, screenHeight - 11);

    int r1 = 30;
    int r2 = 25;
	display->setColor(COLOR_Red);
	display->fillEllipse(x - r1, y - r1, x + r1, y + r1);
	display->setColor(COLOR_Yellow);
	display->fillEllipse(x - r2, y - r2, x + r2, y + r2);

	display->drawBitmap(
		x - bitmap->getWidth() / 2,
		y - bitmap->getHeight() / 2,
		bitmap);

	display->resetClip();
}


/// ----------------------------------------------------------------------
/// \brief Borra el punt
///
void DisplayService::clearDot() {

    display->setClip(138, 28, screenWidth - 11, screenHeight - 11);

    display->setColor(COLOR_Black);
	display->fillRectangle(x - 32, y - 32, x + 32, y + 32);

	display->resetClip();
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa la informacio de posicio i tamany
///
void DisplayService::drawInfo() {

	static char buffer[20];

	display->setColor(COLOR_Black);
	display->fillRectangle(55, 55, 55 + 40, 55 + 15);
	display->fillRectangle(55, 75, 55 + 40, 75 + 15);

	display->setColor(COLOR_Yellow);

	sprintf(buffer, "%d", x);
	display->drawText(55, 70, buffer);

	sprintf(buffer, "%d", y);
	display->drawText(55, 90, buffer);
}
