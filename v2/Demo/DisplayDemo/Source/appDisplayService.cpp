#include "eos.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosGraphics.h"
#if defined(DISPLAY_DRV_ILI9341LTDC)
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#elif defined(DISPLAY_DRV_ILI9341)
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341.h"
#elif defined(DISPLAY_DRV_RGBLTDC)
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#elif defined(DISPLAY_DRV_SSD1306)
#include "Controllers/Display/Drivers/SSD1306/eosDisplayDriver_SSD1306.h"
#else
#error No se especifico DISPLAY_DRV_XXXX
#endif
#include "appDisplayService.h"
#include "stdio.h"


using namespace eos;
using namespace app;


#define TEST_OPACITY
#define TEST_COLORS
#define TEST_POINTS
#define TEST_LINES
#define TEST_RECTANGLES
#define TEST_ELLIPSES
#define TEST_BITMAPS
#define SHOW_RESULTS

static int seed = 537;

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
	_orientation(0) {
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

	// Crea el driver de pantalla
	//
#if defined(DISPLAY_DRV_ILI9341LTDC)
	_driver = new DisplayDriver_ILI9341LTDC();
#elif defined(DISPLAY_DRV_ILI9341)
	_driver = new DisplayDriver_ILI9341();
#elif defined(DISPLAY_DRV_RGBLTDC)
	_driver = new DisplayDriver_RGBLTDC();
#elif defined(DISPLAY_DRV_SSD1306)
	_driver = new  DisplayDriver_SSD1306();
#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
    _driver->initialize();
    _driver->displayOn();

    // Crea el controlador de grafics
    //
    _graphics = new eos::Graphics(_driver);

    const uint8_t *pFontResource = Font::getFontResource("Consolas", 14, FontStyle::regular);
    Font font(pFontResource);
    _graphics->setFont(font);
    _graphics->setTextAlign(HorizontalTextAlign::left, VerticalTextAlign::top);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onLoop() {

    _pointsTicks = 0;
    _horizontalLinesTicks = 0;
    _verticalLinesTicks = 0;
    _linesTicks = 0;
    _rectanglesTicks = 0;
    _filledRectanglesTicks = 0;
    _ellipsesTicks = 0;
    _filledEllipsesTicks = 0;

    _driver->setOrientation(DisplayOrientation((_orientation++) & 0b11));

    _screenWidth = _graphics->getWidth();
    _screenHeight = _graphics->getHeight();

#ifdef TEST_COLORS
    testColors();
#endif
#ifdef TEST_OPACITY
    testOpacity();
#endif
#ifdef TEST_POINTS
    testPoints();
#endif
#ifdef TEST_LINES
    testLines();
#endif
#ifdef TEST_RECTANGLES
    testRectangles();
#endif
#ifdef TEST_ELLIPSES
    testEllipses();
#endif
#ifdef TEST_BITMAPS
    testBitmaps();
#endif

    // Show results
    //
    drawBackground("Results");
    Task::delay(250);

    char lineBuffer[30];
    int y = 50;

    sprintf(lineBuffer, "Points        %d ms", _pointsTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "V. lines      %d ms", _verticalLinesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "H. lines      %d ms", _horizontalLinesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Lines         %d ms", _linesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Rectangles    %d ms", _rectanglesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. rectangles %d ms", _filledRectanglesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "Ellipses      %d ms", _ellipsesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;
    sprintf(lineBuffer, "F. ellipses   %d ms", _filledEllipsesTicks * 2);
    _graphics->drawText(10, y, COLOR_Yellow, lineBuffer, 0, -1); y += 20;

    Task::delay(5000);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa els fons de pantalla.
///
void DisplayService::drawBackground(
    const char* title) {

	_graphics->resetClip();
    _graphics->clear(COLOR_Black);
    _graphics->drawRectangle(0, 0, _screenWidth - 1, _screenHeight - 1, COLOR_Red);
    _graphics->drawLine(_screenWidth - 1, 20, 0, 20, COLOR_Red);
    _graphics->drawText(4, 16, COLOR_Yellow, title, 0, -1);
    _graphics->drawRectangle(7, 27, _screenWidth - 10, _screenHeight - 10, COLOR_Red);
}


void DisplayService::testColors() {

	drawBackground("Colors");
	Task::delay(250);

	_graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);

	int barWidth = _screenWidth - 45;
	int barHeight = 45;

	int x = (_screenWidth - barWidth) / 2;
	int y = 40;
	int w = barWidth;
	int h = barHeight;

	_graphics->drawRectangle(x, y, x + w, y + h, Color(255, 0, 0));
	_graphics->drawRectangle(x, y + 50, x + w, y + 50 + h, Color(0, 255, 0));
	_graphics->drawRectangle(x, y + 100, x + w, y + 100 + h, Color(0, 0, 255));
	_graphics->drawRectangle(x, y + 150, x + w, y + 150 + h, Color(255, 255, 255));

	y = 41;
	h = barHeight - 2;
	int hh = h / 2;

	for (int i = 1; i < barWidth; i++) {

		int c = i * 256 / barWidth;

		_graphics->drawRectangle(x + i, y,             x + i,  y + hh,       Color(c, 0, 0));
		_graphics->drawRectangle(x + i, y + hh,        x + i,  y + h,        Color(255 - c, 0, 0));

		_graphics->drawRectangle(x + i, y + 50,        x + i,  y + 50 + hh,  Color(0, c, 0));
		_graphics->drawRectangle(x + i, y + hh + 50,   x + i,  y + 50 + h,   Color(0, 255 - c, 0));

		_graphics->drawRectangle(x + i, y + 100,       x + i,  y + 100 + hh, Color(0, 0, c));
		_graphics->drawRectangle(x + i, y + hh + 100,  x + i,  y + 100 + h,  Color(0, 0, 255 - c));

		_graphics->drawRectangle(x + i, y + 150,       x + i,  y + 150 + hh, Color(c, c, c));
		_graphics->drawRectangle(x + i, y + hh + 150,  x + i,  y + 150 + h,  Color(255 - c, 255 - c, 255 - c));
	}

	Task::delay(2500);
}

/// ----------------------------------------------------------------------
/// \brief    Test d'opacitat.
///
void DisplayService::testOpacity() {

	const int w = 75;

	drawBackground("Opacity");
	Task::delay(250);

	_graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
	_graphics->fillRectangle(Point(40, 40), Size(w, w), Color(128, 255, 0, 0));
	_graphics->fillRectangle(Point(80, 80), Size(w, w), Color(128, 0, 255, 0));
	_graphics->fillRectangle(Point(120, 120), Size(w, w), Color(128, 0, 0, 255));

	Task::delay(2500);
}


/// ----------------------------------------------------------------------
/// \brief    Test de punts aleatoris.
///
void DisplayService::testPoints() {

	int ticks;

	drawBackground("Random points");
	Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);

    __srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _screenWidth;
        int y = __rand() % _screenHeight;

        Color c(__rand() | 0xFF000000);
        _graphics->drawPoint(x, y, c);
    }
    _pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    __srand(seed);
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _screenWidth;
        int y = __rand() % _screenHeight;

        __rand(); // Mantre la sequencia de 3 rand's per cicle

        _graphics->drawPoint(x, y, COLOR_Black);
    }

    Task::delay(250);
}


/// ----------------------------------------------------------------------
/// \brief    Test de linies.
///
void DisplayService::testLines() {

	int ticks;

	// Vertical lines
    //
    drawBackground("Vertical lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x = __rand() % _screenWidth;
        int y1 = __rand() % _screenHeight;
        int y2 = __rand() % _screenHeight;

        Color c(__rand() | 0xFF000000);
        _graphics->drawVLine(x, y1, y2, c);
    }
    _verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _screenWidth;
        int x2 = __rand() % _screenWidth;
        int y = __rand() % _screenHeight;

        Color c(__rand() | 0xFF000000);
        _graphics->drawHLine(x1, x2, y, c);
    }
    _horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _screenWidth;
        int y1 = __rand() % _screenHeight;
        int x2 = __rand() % _screenWidth;
        int y2 = __rand() % _screenHeight;

        Color c(__rand() | 0xFF000000);
        _graphics->drawLine(x1, y1, x2, y2, c);
    }
    _linesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de rectangles.
///
void DisplayService::testRectangles() {

	int ticks;

	// Restangles buits
	//
	drawBackground("Rectangles");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = __rand() % _screenWidth;
        int y1 = __rand() % _screenHeight;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c(__rand() | 0xFF000000);
        _graphics->drawRectangle(x1, y1, x2, y2, c);
    }
    _rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Rectangles plens
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int x1 = __rand() % _screenWidth;
        int y1 = __rand() % _screenHeight;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c(__rand() | 0xFF000000);
        _graphics->fillRectangle(x1, y1, x2, y2, c);
    }
    _filledRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de rectangles.
///
void DisplayService::testEllipses() {

	int ticks;

    // El·lipses buides
    //
    drawBackground("Ellipses");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = __rand() % _screenWidth;
        int cy = __rand() % _screenHeight;
        int r = (__rand() % 60) + 3;

        Color c(__rand() | 0xFF000000);
        _graphics->drawEllipse(cx - r, cy - r, cx + r, cy + r, c);
    }
    _ellipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Elipses plenes
    //
    drawBackground("Filled ellipses");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 200; i++) {
        int cx = __rand() % _screenWidth;
        int cy = __rand() % _screenHeight;
        int r = (__rand() % 60) + 3;

        Color c(__rand() | 0xFF000000);
       	_graphics->fillEllipse(cx - r, cy - r, cx + r, cy + r, c);
    }
    _filledEllipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}


extern "C" const unsigned char bitmap1[];


/// ----------------------------------------------------------------------
/// \brief    Test de bitmaps
///
void DisplayService::testBitmaps() {

	int ticks;
	const uint8_t *data = bitmap1;

	int width = (int) (data[0] | (data[1] << 8));
	int height = (int) (data[2] | (data[3] << 8));
	//int flags = (int) (data[4] | (data[5] << 8));

	Bitmap* bitmap = new Bitmap(width, height, ColorFormat::rgb565, &data[6]);

	drawBackground("Bitmaps");
    Task::delay(250);

    _graphics->setClip(8, 28, _screenWidth - 11, _screenHeight - 11);

    ticks = Task::getTickCount();

    int x = _screenWidth / 2;
    int y = _screenHeight / 2;
	_graphics->drawBitmap(
		x - bitmap->getWidth() / 2,
		y - bitmap->getHeight() / 2,
		bitmap);

    delete bitmap;

    _bitmapTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}
