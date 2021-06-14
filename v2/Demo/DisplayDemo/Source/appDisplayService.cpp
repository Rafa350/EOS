#include "eos.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"
#if defined(DISPLAY_DRV_ILI9341LTDC)
#include "Controllers/Display/Drivers/eosILI9341LTDC.h"
#elif defined(DISPLAY_DRV_ILI9341)
#include "Controllers/Display/Drivers/eosILI9341.h"
#elif defined(DISPLAY_DRV_RGBLTDC)
#include "Controllers/Display/Drivers/eosRGBLTDC.h"
#elif defined(DISPLAY_DRV_SSD1306)
#include "Controllers/Display/Drivers/eosSSD1306.h"
#else
#error No se especifico DISPLAY_DRV_XXXX
#endif
#include "appDisplayService.h"
#include "stdio.h"


using namespace eos;
using namespace app;


#define TEST_POINTS
#define TEST_LINES
#define TEST_RECTANGLES
#define TEST_ELLIPSES
#define TEST_OPACITY
#define SHOW_RESULTS

#if defined(EOS_STM32F7) || defined(EOS_STM32F4)
static uint64_t rnd = 0L;


void __srand(uint32_t r) {

	rnd = r;
}

uint32_t __rand(void) {

	const uint64_t a = 1664523;
	const uint64_t c = 1013904223;

	rnd = (a * (rnd >> 11)) + c;
	return (uint32_t) rnd;

}
#elif defined(EOS_PIC32)
#define __srand(a)  srand(a)
#define __rand()    rand()
#endif


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
#if defined(EOS_STM32F7)
	//halRNGInitialize();
#endif

#if defined(DISPLAY_DRV_ILI9341LTDC)
	driver = ILI9341LTDCDriver::getInstance();
#elif defined(DISPLAY_DRV_ILI9341)
	driver = ILI9341Driver::getInstance();
#elif defined(DISPLAY_DRV_RGBLTDC)
	driver = new RGBDirectDriver();
#elif defined(DISPLAY_DRV_SSD1306)
	driver = SSD1306Driver::getInstance();
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

    int pointsTicks = 0;
    int horizontalLinesTicks = 0;
    int verticalLinesTicks = 0;
    int linesTicks = 0;
    int rectanglesTicks = 0;
    int filledRectanglesTicks = 0;
    int ellipsesTicks = 0;
    int filledEllipsesTicks = 0;

    int seed = 537; //Task::getTickCount();

    driver->setOrientation(DisplayOrientation(orientation++));
    if (orientation == 4)
    	orientation = 0;

    const uint8_t *pFontResource = Font::getFontResource("Consolas", 14, FontStyle::regular);
    Font font(pFontResource);
    graphics->setFont(font);
    graphics->setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::top);

    screenWidth = graphics->getWidth();
    screenHeight = graphics->getHeight();

    testOpacity();

    // Points
    //
#ifdef TEST_POINTS
    drawBackground("Random points");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);

    __srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % screenWidth;
        int y = __rand() % screenHeight;

        Color c(__rand() | 0xFF000000);
        graphics->drawPoint(x, y, c);
    }
    pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    __srand(seed);
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % screenWidth;
        int y = __rand() % screenHeight;

        __rand(); // Mantre la sequencia de 3 rand's per cicle

        graphics->drawPoint(x, y, COLOR_Black);
    }

    Task::delay(250);
#endif

    // Vertical lines
    //
#ifdef TEST_LINES
    drawBackground("Vertical lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x = __rand() % screenWidth;
        int y1 = __rand() % screenHeight;
        int y2 = __rand() % screenHeight;

        Color c(__rand() | 0xFF000000);
        graphics->drawVLine(x, y1, y2, c);
    }
    verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % screenWidth;
        int x2 = __rand() % screenWidth;
        int y = __rand() % screenHeight;

        Color c(__rand() | 0xFF000000);
        graphics->drawHLine(x1, x2, y, c);
    }
    horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % screenWidth;
        int y1 = __rand() % screenHeight;
        int x2 = __rand() % screenWidth;
        int y2 = __rand() % screenHeight;

        Color c(__rand() | 0xFF000000);
        graphics->drawLine(x1, y1, x2, y2, c);
    }
    linesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
#endif


    // Rectangles
    //
#ifdef TEST_RECTANGLES
    drawBackground("Rectangles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = __rand() % screenWidth;
        int y1 = __rand() % screenHeight;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c(__rand() | 0xFF000000);
        graphics->drawRectangle(x1, y1, x2, y2, c);
    }
    rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = __rand() % screenWidth;
        int y1 = __rand() % screenHeight;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c(__rand() | 0xFF000000);
        graphics->fillRectangle(x1, y1, x2, y2, c);
    }
    filledRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
#endif

    // El·lipses
    //
#ifdef TEST_ELLIPSES
    drawBackground("Ellipses");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = __rand() % screenWidth;
        int cy = __rand() % screenHeight;
        int r = (__rand() % 60) + 3;

        Color c(__rand() | 0xFF000000);
        graphics->drawEllipse(cx - r, cy - r, cx + r, cy + r, c);
    }
    ellipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Filled circles
    //
    drawBackground("Filled ellipses");
    Task::delay(250);

    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
    graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = __rand() % screenWidth;
        int cy = __rand() % screenHeight;
        int r = (__rand() % 60) + 3;

        Color c(__rand() | 0xFF000000);
       	graphics->fillEllipse(cx - r, cy - r, cx + r, cy + r, c);
    }
    filledEllipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
#endif


    // Show results
    //
    drawBackground("Results");
    Task::delay(250);

    char lineBuffer[30];
    int y = 50;

    sprintf(lineBuffer, "Points        %d ms", pointsTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "V. lines      %d ms", verticalLinesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "H. lines      %d ms", horizontalLinesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Lines         %d ms", linesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Rectangles    %d ms", rectanglesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. rectangles %d ms", filledRectanglesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Ellipses      %d ms", ellipsesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. ellipses   %d ms", filledEllipsesTicks * 2);
    graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;

    Task::delay(5000);
}


void DisplayService::drawBackground(
    const char* title) {

	graphics->resetClip();
    graphics->clear(COLOR_Black);
    graphics->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1, COLOR_Red);
    graphics->drawLine(screenWidth - 1, 20, 0, 20, COLOR_Red);
    graphics->drawText(4, 16, COLOR_Yellow, title, 0, -1);
    graphics->drawRectangle(7, 27, screenWidth - 10, screenHeight - 10, COLOR_Red);
}


/// ----------------------------------------------------------------------
/// \brief test d'opacitat.
///
void DisplayService::testOpacity() {

	const int w = 75;

	drawBackground("Opacity");

	graphics->setClip(8, 28, screenWidth - 11, screenHeight - 11);
	graphics->fillRectangle(Point(40, 40), Size(w, w), Color(128, 255, 0, 0));
	graphics->fillRectangle(Point(80, 80), Size(w, w), Color(128, 0, 255, 0));
	graphics->fillRectangle(Point(120, 120), Size(w, w), Color(128, 0, 0, 255));

	Task::delay(5000);
}
