#include "eos.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosDisplay.h"
#if defined(DISPLAY_DRV_ILI9341LTDC)
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#elif defined(_DISPLAY_DRV_ILI9341)
#include "Controllers/Display/Drivers/eosILI9341.h"
#elif defined(DISPLAY_DRV_RGBLTDC)
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#else
#error No se especifico DISPLAY_DRV_XXXX
#endif
#include "appDisplayService.h"
#include "stdlib.h"
#include "stdio.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param application: Aplicacio al que pertany el servei.
///
DisplayService::DisplayService(
	Application *application):

	AppLoopService(application) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

#if defined(DISPLAY_DRV_ILI9341LTDC)
	driver = ILI9341LTDCDriver::getInstance();
#elif defined(DISPLAY_DRV_ILI9341)
	driver = ILI9341Driver::getInstance();
#elif defined(DISPLAY_DRV_RGBLTDC)
	driver = RGBDirectDriver::getInstance();
#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
    driver->initialize();
    driver->displayOn();

    display = new eos::Display(driver);
    display->clear(COLOR_Black);

    orientation = 0;
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

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

    display->setOrientation(DisplayOrientation(orientation++));
    if (orientation == 4)
    	orientation = 0;

    screenWidth = display->getWidth();
    screenHeight  = display->getHeight();

    // Points
    //
    drawBackground("50K Points");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawPoint(x, y);
    }
    pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    srand(seed);
    display->setColor(COLOR_Black);
    for (int i = 0; i < 50000; i++) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;
        rand();

        display->drawPoint(x, y);
    }
    //Task::delay(500);

    // Vertical lines
    //
    drawBackground("Vertical lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = x1;
        int y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = y1;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 300; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawLine(x1, y1, x2, y2);
    }
    linesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Rectangles
    //
    drawBackground("Rectangles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = rand() % screenHeight;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawRectangle(x1, y1, x2, y2);
    }
    rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = x1 + rand() % 100;
        int y2 = y1 + rand() % 100;

        display->setColor(rand() & 0x00FFFFFF);
        display->fillRectangle(x1, y1, x2, y2);
    }
    filledRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Circles
    //
    drawBackground("Circles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 150;

        display->setColor(rand() & 0x00FFFFFF);
        display->drawCircle(cx, cy, r);
    }
    circlesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled circles
    //
    drawBackground("Filled circles");
    Task::delay(250);

    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    display->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 50;

        display->setColor(rand() & 0x00FFFFFF);
        display->fillCircle(cx, cy, r);
    }
    filledCirclesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Show results
    //
    drawBackground("Results");
    Task::delay(250);

    char lineBuffer[30];
    int y = 50;
    sprintf(lineBuffer, "50K Points    %d ms", pointsTicks * 2);
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

    Task::delay(5000);
}


void DisplayService::drawBackground(
    const char* title) {

    display->clear(COLOR_Black);
    display->resetClip();
    display->setColor(COLOR_Red);
    display->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    display->drawLine(screenWidth - 1, 20, 0, 20);
    display->drawText(4, 16, title, 0, -1);
    display->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
}
