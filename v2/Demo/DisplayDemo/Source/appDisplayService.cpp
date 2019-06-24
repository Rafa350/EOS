#include "eos.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosGraphics.h"
#if defined(DISPLAY_DRV_ILI9341LTDC)
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#elif defined(DISPLAY_DRV_ILI9341)
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

    graphics = new eos::Graphics(driver);

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

    graphics->setOrientation(DisplayOrientation(orientation++));
    if (orientation == 4)
    	orientation = 0;

    screenWidth = graphics->getWidth();
    screenHeight  = graphics->getHeight();

    // Points
    //
    drawBackground("50K Points");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawPoint(x, y);
    }
    pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    srand(seed);
    graphics->setColor(COLOR_Black);
    for (int i = 0; i < 50000; i++) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;
        rand();

        graphics->drawPoint(x, y);
    }
    //Task::delay(500);

    // Vertical lines
    //
    drawBackground("Vertical lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 500; i++) {
        int x = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int y2 = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawVLine(x, y1, y2);
    }
    verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 500; i++) {
        int x1 = rand() % screenWidth;
        int x2 = rand() % screenWidth;
        int y = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawHLine(x1, x2, y);
    }
    horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 500; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawLine(x1, y1, x2, y2);
    }
    linesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Rectangles
    //
    drawBackground("Rectangles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 250; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawRectangle(x1, y1, x2, y2);
    }
    rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 250; i++) {
        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = x1 + rand() % 100;
        int y2 = y1 + rand() % 100;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->fillRectangle(x1, y1, x2, y2);
    }
    filledRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Circles
    //
    drawBackground("Circles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 250; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 150;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawCircle(cx, cy, r);
    }
    circlesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled circles
    //
    drawBackground("Filled circles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 250; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 50;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->fillCircle(cx, cy, r);
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
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "V. lines      %d ms", verticalLinesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "H. lines      %d ms", horizontalLinesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Lines         %d ms", linesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Rectangles    %d ms", rectanglesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. rectangles %d ms", filledRectanglesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Circles       %d ms", circlesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. circles    %d ms", filledCirclesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;

    Task::delay(5000);
}


void DisplayService::drawBackground(
    const char* title) {

    graphics->resetClip();
    graphics->clear(COLOR_Black);
    graphics->setColor(COLOR_Red);
    graphics->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    graphics->drawLine(screenWidth - 1, 20, 0, 20);
    graphics->drawText(4, 16, title, 0, -1);
    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
}
