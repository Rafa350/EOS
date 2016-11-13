#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "Hal/halGPIO.h"

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
		IDisplayDriver *driver;
        Display *display;
        int16_t screenWidth;
        int16_t screenHeight;

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

	halGPIOInitializePin(LEDS_LD1_PORT, LEDS_LD1_PIN, GPIO_DIRECTION_OUTPUT);
	halGPIOInitializePin(LEDS_LD2_PORT, LEDS_LD2_PIN, GPIO_DIRECTION_OUTPUT);

	halGPIOClearPin(LEDS_LD1_PORT, LEDS_LD1_PIN);
	halGPIOSetPin(LEDS_LD2_PORT, LEDS_LD2_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void LedLoopService::onRun() {

	while (true) {

		halGPIOTogglePin(LEDS_LD1_PORT, LEDS_LD1_PIN);
		halGPIOTogglePin(LEDS_LD2_PORT, LEDS_LD2_PIN);

		Task::delay(500);
	}
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayLoopService::onSetup() {

	driver = new ILI9341_Driver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);

    display = new Display(driver);
    display->clear(COLOR_Black);

    screenWidth = display->getDriver()->getWidth();
    screenHeight  = display->getDriver()->getHeight();
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

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
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
    display->setColor(Color(0));
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

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
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
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
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
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;

        display->setColor( rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    linesTicks = Task::getTickCount() - ticks;
    Task::delay(500);

    // Rectangles
    //
    drawBackground("Rectangles");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawRectangle(x1, y1, x2, y2);
    }
    rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
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

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int16_t cx = rand() % screenWidth;
        int16_t cy = rand() % screenHeight;
        int16_t r = rand() % 150;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawCircle(cx, cy, r);
    }
    circlesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled circles
    //
    drawBackground("Filled circles");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
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

    display->clear(0);
    display->resetClip();
    display->setColor(0x00FF0000);
    display->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    display->drawLine(screenWidth - 1, 20, 0, 20);
    display->drawText(4, 16, title, 0, -1);
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

    MyApplication *app = new MyApplication();
    app->execute();
    delete app;
}
