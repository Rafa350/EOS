#include "eos.h"
#include "eosAssert.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Controllers/TouchPad/eosTouchPad.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Controllers/Display/eosDisplay.h"
#include "Controllers/Display/eosBitmap.h"
#include "Controllers/Display/Drivers/eosRGBDirect.h"
#include "HAL/halSYS.h"
#include "HAL/halGPIO.h"

#include <stdlib.h>
#include <stdio.h>


using namespace eos;


class LedLoopService: public AppLoopService {
	public:
    	LedLoopService(Application *application):
        	AppLoopService(application) {}

    protected:
    	void onSetup();
        void onLoop();
};


class DisplayLoopService: public AppLoopService {
    private:
        Bitmap *bitmap;
		IDisplayDriver *displayDriver;
        Display *display;
		ITouchPadDriver *touchDriver;
        TouchPad *touch;
        int16_t screenWidth;
        int16_t screenHeight;
        int16_t x;
        int16_t y;
        int16_t w;
        int16_t h;

    public:
        DisplayLoopService(Application *application):
            AppLoopService(application),
			bitmap(nullptr),
			display(nullptr),
			touch(nullptr) {}

    protected:
        void onSetup();
        void onLoop();

    private:
        void drawBackground();
        void drawInfo();
        void drawDot();
        void clearDot();
};


class MyApplication: public Application {
	private:
		LedLoopService *ledService;
		DisplayLoopService *displayService;

    public :
        MyApplication();

    protected:
        void onInitialize();
};


static const char *title = "EOS v2.0: TouchPad Demo";


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication() {

	ledService = new LedLoopService(this);
    displayService = new DisplayLoopService(this);
}


/// ---------------------------------------------------------------------
/// \brief Processa la inicialitzacio de l'aplicacio
///
void MyApplication::onInitialize() {
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedLoopService::onSetup() {

	// Inicialitza el LED 1
	//
	halGPIOInitializePinOutput(LED_LED1_PORT, LED_LED1_PIN);
	halGPIOClearPin(LED_LED1_PORT, LED_LED1_PIN);

#ifdef LED_LED2_PORT

	// Inicialitza el LED 2
	//
	halGPIOInitializePinOutput(LED_LED2_PORT, LED_LED2_PIN);
	halGPIOSetPin(LED_LED2_PORT, LED_LED2_PIN);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedLoopService::onLoop() {

	while (true) {

		halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
#ifdef LED_LED2_PORT
		halGPIOTogglePin(LED_LED2_PORT, LED_LED2_PIN);
#endif

		Task::delay(500);
	}
}


///-----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void DisplayLoopService::onSetup() {

	// Inicialitzacio del display
	//
	displayDriver = RGBDirectDriver::getInstance();
    displayDriver->initialize();
    displayDriver->setOrientation(DisplayOrientation::rotate180);
    displayDriver->displayOn();
    display = new Display(displayDriver);
    display->clear(COLOR_Black);

    bitmap = new Bitmap(30, 30, COLOR_Blue);

    // Inicialitzacio del touch pad
    //
    touchDriver = FT5336Driver::getInstance();
    touch = new TouchPad(touchDriver);

    screenWidth = displayDriver->getWidth();
    screenHeight  = displayDriver->getHeight();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayLoopService::onLoop() {

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
    		Task::delay(250);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa el fons de pantalla.
///
void DisplayLoopService::drawBackground() {

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
void DisplayLoopService::drawDot() {

	display->setColor(COLOR_Red);
	display->fillCircle(x, y, 30);
	display->setColor(COLOR_Yellow);
	display->fillCircle(x, y, 25);

	display->drawBitmap(x, y, bitmap);
}

/// ----------------------------------------------------------------------
/// \brief Dibuixa la informacio de posicio i tamany
///
void DisplayLoopService::drawInfo() {

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


/// ----------------------------------------------------------------------
/// \brief Borra el punt
///
void DisplayLoopService::clearDot() {

	display->setColor(COLOR_Black);
	display->fillRectangle(x - 32, y - 32, x + 32, y + 32);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

    MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
