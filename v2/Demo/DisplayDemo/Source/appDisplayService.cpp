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
#include "HAl/STM32/halRNG.h"
#include "appDisplayService.h"
#include "stdio.h"


using namespace eos;
using namespace app;



static uint32_t rnd = 0L;

void srand(uint32_t r) {

	rnd = r;
}


uint32_t rand() {

	const uint32_t a = 1664525;
	const uint32_t c = 1013904223;

	rnd = ((a * rnd) + c);
	return rnd;
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param application: Aplicacio al que pertany el servei.
///
DisplayService::DisplayService(
	Application *application):

	AppLoopService(application),
	orientation(0) {
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onSetup() {

	// Inicialitza el generador de nombres aleatoris.
	//
	halRNGInitialize();

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
    int ellipsesTicks;
    int filledEllipsesTicks;

    int seed = 7; //Task::getTickCount();

    driver->setOrientation(DisplayOrientation(orientation++));
    if (orientation == 4)
    	orientation = 0;

    screenWidth = graphics->getWidth();
    screenHeight = graphics->getHeight();

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

    Task::delay(250);

    // Vertical lines
    //
    drawBackground("Vertical lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 250; i++) {
        int x = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int y2 = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawLine(x, y1, x, y2);
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
    for (int i = 0; i < 250; i++) {
        int x1 = rand() % screenWidth;
        int x2 = rand() % screenWidth;
        int y = rand() % screenHeight;

        graphics->setColor(rand() & 0x00FFFFFF);
        graphics->drawLine(x1, y, x2, y);
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
    for (int i = 0; i < 250; i++) {
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
    for (int i = 0; i < 200; i++) {
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
    for (int i = 0; i < 200; i++) {
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
    drawBackground("Ellipses");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 150;

        graphics->setColor(rand() & 0x00FFFFFF);

        if (r > 1) 
            graphics->drawEllipse(cx - r, cy - r, cx + r, cy + r);
    }
    ellipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled circles
    //
    drawBackground("Filled ellipses");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = rand() % screenWidth;
        int cy = rand() % screenHeight;
        int r = rand() % 50;

        graphics->setColor(rand() & 0x00FFFFFF);
        if (r > 1)
        	graphics->fillEllipse(cx - r, cy - r, cx + r, cy + r);
    }
    filledEllipsesTicks = Task::getTickCount() - ticks;
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
    sprintf(lineBuffer, "Ellipses      %d ms", ellipsesTicks * 2);
    graphics->drawText(10, y, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. ellipses   %d ms", filledEllipsesTicks * 2);
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
