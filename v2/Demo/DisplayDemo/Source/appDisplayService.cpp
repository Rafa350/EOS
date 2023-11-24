#include "eos.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosBitmap.h"
#include "System/Graphics/eosText.h"
#include "System/Graphics/eosGraphics.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#if defined(DISPLAY_DRV_ILI9341LTDC)
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341LTDC.h"
#elif defined(DISPLAY_DRV_ILI9341)
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341.h"
#elif defined(DISPLAY_DRV_RGBLTDC)
#include "Controllers/Display/Drivers/RGB/eosDisplayDriver_RGBLTDC.h"
#else
#error No se especifico DISPLAY_DRV_XXXX
#endif
#include "appDisplayService.h"
#include "stdio.h"


using namespace eos;
using namespace htl;
using namespace app;


#define TEST_ORIENTATION
#define TEST_OPACITY
#define TEST_COLORS
#define TEST_POINTS
#define TEST_LINES
//#define TEST_THICKLINES
#define TEST_RECTANGLES
#define TEST_ELLIPSES
#define TEST_POLYGONS
#define TEST_BITMAPS
#define SHOW_RESULTS

static int seed = 537;

#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32F4)
static uint64_t rnd = 0L;

static void __srand(uint32_t r) {

	rnd = r;
}

static uint32_t __rand(void) {

	const uint64_t a = 1664523;
	const uint64_t c = 1013904223;

	rnd = (a * (rnd >> 11)) + c;
	return (uint32_t) rnd;

}
#elif defined(EOS_PLATFORM_PIC32)
#define __srand(a)  srand(a)
#define __rand()    rand()
#endif


static inline Color __getRandomColor() {

	uint32_t c = __rand();
	return RGB((c & 0x00FF0000) >> 16, (c & 0x0000FF00) >> 8, c & 0x000000FF);
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param application: Aplicacio al que pertany el servei.
///
DisplayService::DisplayService():
	_text(Font("Consolas", 14, FontStyle::regular), TextAlign::left),
	_orientation(0) {

	_text.setForeground(Brush(Colors::yellow));
}


///-----------------------------------------------------------------------
/// \brief Process la inicialitzacio de la tasca.
///
void DisplayService::onInitialize() {

	// Inicialitza el generador de nombres aleatoris.
	//
#if defined(EOS_PLATFORM_STM32F7)
	//halRNGInitialize();
#endif

	// Crea el driver de pantalla
	//
#if defined(DISPLAY_DRV_ILI9341LTDC)

	constexpr int frameBufferLineBytes = (_displayWidth * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferLineBytes / Color::bytes;

	FrameBuffer *frameBuffer = new ColorFrameBuffer_DMA2D(
		_displayWidth,
		_displayHeight,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(_displayBuffer));

    auto pinCS = DISPLAY_CS_Pin::pInst;
    pinCS->initOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, true);

    auto pinRS = DISPLAY_RS_Pin::pInst;
    pinRS->initOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, false);

    auto devSPI = DISPLAY_SPI_Device::pInst;
    devSPI->initPinSCK<DISPLAY_SCK_Pin>();
    devSPI->initPinMOSI<DISPLAY_MOSI_Pin>();
    devSPI->initialize(spi::SPIMode::master, spi::ClkPolarity::high, spi::ClkPhase::edge1, spi::WordSize::_8, spi::FirstBit::msb, spi::ClockDivider::_8);
    devSPI->enable();

    auto device = eos::DeviceX_ILI9341_SPI<1>::pInst;
    device->initialize(pinCS, pinRS, devSPI);

	_driver = new DisplayDriver_ILI9341LTDC(device, frameBuffer);

#elif defined(DISPLAY_DRV_ILI9341)

	auto pinCS = DISPLAY_CS_Pin::pInst;
    pinCS->initOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, true);

	auto pinRS = DISPLAY_RS_Pin::pInst;
    pinRS->initOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, false);

	auto devSPI = DISPLAY_SPI_Device::pInst;
    devSPI->initPinSCK<DISPLAY_SCK_Pin>();
    devSPI->initPinMOSI<DISPLAY_MOSI_Pin>();
    devSPI->initialize(spi::SPIMode::master, spi::ClkPolarity::high, spi::ClkPhase::edge1, spi::WordSize::_8, spi::FirstBit::msb, spi::ClockDivider::_8);
    devSPI->enable();

	auto device = eos::DeviceX_ILI9341_SPI<1>::pInst;
	device->initialize(pinCS, pinRS, devSPI);

	_driver = new DisplayDriver_ILI9341(device);

#elif defined(DISPLAY_DRV_RGBLTDC)

	constexpr int frameBufferLineBytes = (_displayWidth * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferLineBytes / Color::bytes;

	FrameBuffer *frameBuffer = new ColorFrameBuffer_DMA2D(
		_displayWidth,
		_displayHeight,
		frameBufferPitch,
		DisplayOrientation::normal,
		reinterpret_cast<void*>(_displayBuffer));

	_driver = new DisplayDriver_RGBLTDC(frameBuffer);

#else
	#error No se especifico DISPLAY_DRV_XXXX
#endif
    _driver->initialize();
	_driver->enable();

    // Crea el controlador de grafics
    //
    _graphics = new eos::Graphics(_driver);
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio de la tasca.
///
void DisplayService::onTask() {

    _pointsTicks = 0;
    _horizontalLinesTicks = 0;
    _verticalLinesTicks = 0;
    _linesTicks = 0;
    _rectanglesTicks = 0;
    _filledRectanglesTicks = 0;
    _ellipsesTicks = 0;
    _filledEllipsesTicks = 0;

	#ifdef TEST_ORIENTATION
    	_driver->setOrientation(DisplayOrientation((_orientation++) & 0b11));
	#endif

    _maxX = _graphics->getMaxX();
    _maxY = _graphics->getMaxY();

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
	#ifdef TEST_THICKLINES
		testThickLines();
	#endif
	#ifdef TEST_RECTANGLES
		testRectangles();
	#endif
	#ifdef TEST_ELLIPSES
		testEllipses();
	#endif
	#ifdef TEST_POLYGONS
		testPolygons();
	#endif
	#ifdef TEST_BITMAPS
		testBitmaps();
	#endif

	#ifdef SHOW_RESULTS
		// Show results
		//
		drawBackground("Results");
		Task::delay(250);

		char lineBuffer[30];
		int y = 35;

		sprintf(lineBuffer, "Points        %d ms", _pointsTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "V. lines      %d ms", _verticalLinesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "H. lines      %d ms", _horizontalLinesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "Lines         %d ms", _linesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "Rectangles    %d ms", _rectanglesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "F. rectangles %d ms", _filledRectanglesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "Ellipses      %d ms", _ellipsesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		sprintf(lineBuffer, "F. ellipses   %d ms", _filledEllipsesTicks * 2);
		_text.setText(lineBuffer);
		_graphics->paintText(Point(10, y), _text); y += 20;

		Task::delay(5000);
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa els fons de pantalla.
///
void DisplayService::drawBackground(
    const char* title) {

	_graphics->resetClip();
    _graphics->clear(Colors::black);
    _graphics->drawRectangle(0, 0, _maxX, _maxY, Colors::red);
    _graphics->drawLine(_maxX, 20, 0, 20, Colors::red);

    _text.setText(title);
    _graphics->paintText(Point(4, 0), _text);

    _graphics->drawRectangle(7, 27, _maxX - 10, _maxY - 10, Colors::red);
}


void DisplayService::testColors() {

	drawBackground("Colors");
	Task::delay(250);

	_graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

	int barWidth = _maxX - 45;
	int barHeight = 45;

	int x = ((_maxX + 1) - barWidth) / 2;
	int y = 40;
	int w = barWidth;
	int h = barHeight;

	_graphics->drawRectangle(x, y, x + w, y + h, RGB(255, 0, 0));
	_graphics->drawRectangle(x, y + 50, x + w, y + 50 + h, RGB(0, 255, 0));
	_graphics->drawRectangle(x, y + 100, x + w, y + 100 + h, RGB(0, 0, 255));
	_graphics->drawRectangle(x, y + 150, x + w, y + 150 + h, RGB(255, 255, 255));

	y = 41;
	h = barHeight - 2;
	int hh = h / 2;

	for (int i = 1; i < barWidth; i++) {

		int c = i * 256 / barWidth;

		_graphics->fillRectangle(x + i, y,             x + i,  y + hh,       RGB(c, 0, 0));
		_graphics->fillRectangle(x + i, y + hh,        x + i,  y + h,        RGB(255 - c, 0, 0));

		_graphics->fillRectangle(x + i, y + 50,        x + i,  y + 50 + hh,  RGB(0, c, 0));
		_graphics->fillRectangle(x + i, y + hh + 50,   x + i,  y + 50 + h,   RGB(0, 255 - c, 0));

		_graphics->fillRectangle(x + i, y + 100,       x + i,  y + 100 + hh, RGB(0, 0, c));
		_graphics->fillRectangle(x + i, y + hh + 100,  x + i,  y + 100 + h,  RGB(0, 0, 255 - c));

		_graphics->fillRectangle(x + i, y + 150,       x + i,  y + 150 + hh, RGB(c, c, c));
		_graphics->fillRectangle(x + i, y + hh + 150,  x + i,  y + 150 + h,  RGB(255 - c, 255 - c, 255 - c));
	}

	Task::delay(2500);
}

/// ----------------------------------------------------------------------
/// \brief    Test d'opacitat.
///
void DisplayService::testOpacity() {

	constexpr int w = 74;
	constexpr int dd = w / 2;

	drawBackground("Opacity");
	Task::delay(250);

	uint8_t opacity = 128;

	Color colors[3];
	colors[0] = ARGB(opacity, 255, 0, 0);
	colors[1] = ARGB(opacity, 0, 255, 0);
	colors[2] = ARGB(opacity, 0, 0, 255);

	_graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

	int x = 40;
	int y = 40;

	_graphics->fillRectangle(Point(x, y), Size(w + (dd * 2), w + (dd * 2)), Colors::white);

	for (int i = 0; i < 3; i++) {
		_graphics->fillRectangle(Point(x, y), Size(w, w), colors[i]);
		x += dd;
		y += dd;
	}

	Task::delay(2500);
}


/// ----------------------------------------------------------------------
/// \brief    Test de punts aleatoris.
///
void DisplayService::testPoints() {

	int ticks;

	drawBackground("Random points");
	Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    __srand(seed);
    ticks = Task::getTickCount();
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _maxX;
        int y = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawPoint(x, y, c);
    }
    _pointsTicks = Task::getTickCount() - ticks;
    Task::delay(250);

    __srand(seed);
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _maxX;
        int y = __rand() % _maxY;

        __rand(); // Mantre la sequencia de 3 rand's per cicle

        _graphics->drawPoint(x, y, Colors::black);
    }

    Task::delay(250);

    ticks = Task::getTickCount();
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

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int y2 = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawVLine(x, y1, y2, c);
    }
    _verticalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _maxX;
        int x2 = __rand() % _maxY;
        int y = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawHLine(x1, x2, y, c);
    }
    _horizontalLinesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Lines
    //
    drawBackground("Random lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = __rand() % _maxX;
        int y2 = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawLine(x1, y1, x2, y2, c);
    }
    _linesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de linies amples.
///
void DisplayService::testThickLines() {

	// Thick lines
    //
    drawBackground("Thick lines");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    _graphics->drawLine(10, 10, 200, 376, 5, Colors::white);

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

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c = __getRandomColor();
        _graphics->drawRectangle(x1, y1, x2, y2, c);
    }
    _rectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Rectangles plens
    //
    drawBackground("Filled rectangles");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c = __getRandomColor();
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

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1000; i++) {
        int cx = __rand() % _maxX;
        int cy = __rand() % _maxY;
        int rx = (__rand() % 60) + 3;
        int ry = (__rand() % 60) + 3;

        Color c = __getRandomColor();
        _graphics->drawEllipse(cx - rx, cy - ry, cx + rx, cy + ry, c);
    }
    _ellipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Elipses plenes
    //
    drawBackground("Filled ellipses");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1000; i++) {
        int cx = __rand() % _maxX;
        int cy = __rand() % _maxY;
        int rx = (__rand() % 60) + 3;
        int ry = (__rand() % 60) + 3;

        Color c = __getRandomColor();
       	_graphics->fillEllipse(cx - rx, cy - ry, cx + rx, cy + ry, c);
    }
    _filledEllipsesTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de poligons.
///
void DisplayService::testPolygons() {

	int ticks;
	static Point __points[8] = {
		{100, 100},
		{100, 160},
		{160, 200},
		{280, 100},
		{280, 160},
		{220, 100},
	};

    // Poligons buides
    //
    drawBackground("Polygons");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1; i++) {

        Color c = __getRandomColor();
    	_graphics->drawPolygon(__points, 6, c);
    }
    _polygonsTicks = Task::getTickCount() - ticks;
    Task::delay(1000);

    // Elipses plenes
    //
    drawBackground("Filled polygons");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1; i++) {

    	Color c = __getRandomColor();
    	_graphics->fillPolygon(__points, 6, c);
    }
    _filledPolygonsTicks = Task::getTickCount() - ticks;
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

	Bitmap bitmap(width, height, ColorFormat::rgb565, &data[6]);

	drawBackground("Bitmaps");
    Task::delay(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    ticks = Task::getTickCount();

    int x = (_maxX + 1) / 2;
    int y = (_maxY + 1) / 2;
	_graphics->drawBitmap(
		x - bitmap.getWidth() / 2,
		y - bitmap.getHeight() / 2,
		bitmap);

    _bitmapTicks = Task::getTickCount() - ticks;
    Task::delay(1000);
}
