#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Controllers/TouchPad/eosTouchPad.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Controllers/Display/eosDisplay.h"
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
        void onRun();
};


class DisplayLoopService: public AppLoopService {
    private:
		ITouchPadDriver *touchDriver;
        TouchPad *touch;
		IDisplayDriver *displayDriver;
        Display *display;
        int16_t screenWidth;
        int16_t screenHeight;
        int loopCount;

    public:
        DisplayLoopService(Application *application):
            AppLoopService(application) {}

    protected:
        void onSetup();
        void onRun();

    private:
        void drawBackground(const char *title);
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

	ledService->initialize();
	displayService->initialize();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio de la tasca.
///
void LedLoopService::onSetup() {

	// Inicialitza el LED 1
	//
	halGPIOInitializePinOutput(LEDS_LD1_PORT, LEDS_LD1_PIN);
	halGPIOClearPin(LEDS_LD1_PORT, LEDS_LD1_PIN);

#ifdef LEDS_LD2_PORT

	// Inicialitza el LED 2
	//
	halGPIOInitializePinOutput(LEDS_LD2_PORT, LEDS_LD2_PIN);
	halGPIOSetPin(LEDS_LD2_PORT, LEDS_LD2_PIN);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedLoopService::onRun() {

	while (true) {

		halGPIOTogglePin(LEDS_LD1_PORT, LEDS_LD1_PIN);
#ifdef LEDS_LD2_PORT
		halGPIOTogglePin(LEDS_LD2_PORT, LEDS_LD2_PIN);
#endif

		Task::delay(500);
	}
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayLoopService::onSetup() {

	// Inicialitzacio del display
	//
	displayDriver = RGBDirect_Driver::getInstance();
    displayDriver->initialize();
    displayDriver->setOrientation(DisplayOrientation::rotate180);
    displayDriver->displayOn();
    display = new Display(displayDriver);
    display->clear(COLOR_Black);

    // Inicialitzacio del touch pad
    //
    touchDriver = FT5336_Driver::getInstance();
    touch = new TouchPad(touchDriver);

    screenWidth = displayDriver->getWidth();
    screenHeight  = displayDriver->getHeight();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayLoopService::onRun() {

    int ticks;

    int pointsTicks;
    int horizontalLinesTicks;
    int verticalLinesTicks;
    int linesTicks;
    int rectanglesTicks;
    int filledRectanglesTicks;
    int circlesTicks;
    int filledCirclesTicks;

    int seed = 0; //Task::getTickCount();

    // Points
    //
    drawBackground("Points");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int16_t x = rand() % screenWidth;
        int16_t y = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawPoint(x, y);
    }
    pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    srand(seed);
    display->setColor(COLOR_Black);
    for (int i = 0; i < 50000; i++) {
        int16_t x = rand() % screenWidth;
        int16_t y = rand() % screenHeight;
        rand();

        display->drawPoint(x, y);
    }
    Task::delay(500);

    // Vertical lines
    //
    drawBackground("Vertical lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = x1;
        int16_t y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = y1;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    linesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Rectangles
    //
    drawBackground("Rectangles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawRectangle(x1, y1, x2, y2);
    }
    rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = x1 + rand() % 100;
        int16_t y2 = y1 + rand() % 100;

        display->setColor(rand() & 0x00FFFFFF);
        display->fillRectangle(x1, y1, x2, y2);
    }
    filledRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Circles
    //
    drawBackground("Circles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int16_t cx = rand() % screenWidth;
        int16_t cy = rand() % screenHeight;
        int16_t r = rand() % 150;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawCircle(cx, cy, r);
    }
    circlesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Filled circles
    //
    drawBackground("Filled circles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int16_t cx = rand() % screenWidth;
        int16_t cy = rand() % screenHeight;
        int16_t r = rand() % 50;

        display->setColor(rand() & 0x00FFFFFF);
        display->fillCircle(cx, cy, r);
    }
    filledCirclesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Show results
    //
    drawBackground("Results");
    Task::delay(250);

    char lineBuffer[30];
    uint16_t y = 50;
    sprintf(lineBuffer, "Points        %d ms", pointsTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "V. lines      %d ms", verticalLinesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "H. lines      %d ms", horizontalLinesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Lines         %d ms", linesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Rectangles    %d ms", rectanglesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. rectangles %d ms", filledRectanglesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Circles       %d ms", circlesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. circles    %d ms", filledCirclesTicks * 2);
    display->drawText(10, y, lineBuffer, 0, -1); y += 20;

    Task::delay(10000);
}


void DisplayLoopService::drawBackground(
    const char* title) {

    display->clear(COLOR_Black);
    display->resetClip();
    display->setColor(COLOR_Red);
    display->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    display->drawLine(screenWidth - 1, 20, 0, 20);
    display->drawText(4, 16, title, 0, -1);
    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

    MyApplication *app = new MyApplication();
    app->execute();
    delete app;
}