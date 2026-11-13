export module App.Services.Display;

import App.Hardware;
import Eos.Controllers.Display.Drivers.ILI9341LTDC;
import Eos.Controllers.Display.Buffers.ColorDMA2D;
import Eos.Hardware.GPIO;
import Eos.Hardware.SPI;
import Eos.Hardware.LTDC;
import Eos.Services.Service;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


#define DISPLAY_DRV_ILI9341LTDC

using namespace eos;


export namespace app {

	class DisplayService: public Service {
	    private:
			static constexpr UInt32 _displayWidth = 240;
			static constexpr UInt32 _displayHeight = 320;
			static constexpr UInt32 _displayBuffer = 0xD0000000;

			DisplayDriver *_driver;
	        Graphics *_graphics;
	        Text _text;
	        int _maxX;
	        int _maxY;
	        int _orientation;
	        int _loopCount;

	        Ticks _pointsTicks;
	        Ticks _horizontalLinesTicks;
	        Ticks _verticalLinesTicks;
	        Ticks _linesTicks;
	        Ticks _rectanglesTicks;
	        Ticks _filledRectanglesTicks;
	        Ticks _ellipsesTicks;
	        Ticks _filledEllipsesTicks;
	        Ticks _polygonsTicks;
	        Ticks _filledPolygonsTicks;
	        Ticks _bitmapTicks;

	    public:
	        DisplayService();

	    protected:
	        void onExecute() override;

	    private:
	        void drawBackground(const char *title);
	        void testColors();
	        void testOpacity();
	        void testPoints();
	        void testLines();
	        void testThickLines();
	        void testRectangles();
	        void testEllipses();
	        void testPolygons();
	        void testBitmaps();
	};
}


using namespace app;
using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::ltdc;
using namespace eos::hardware::spi;


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


#if defined(DISPLAY_DRV_ILI9341LTDC)

// Parametres d'inicialitzacio per interficie LTDC
//
static const UInt8 initCommands[] = {

	// Reset
	__SOFTWARE_RESET,
	OP_DELAY, 250,
	OP_DELAY, 250,

	// Inicialitzacio del chip
	//
	__PUMP_RATIO_CONTROL(0x20),
	__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x62),
	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
	__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
	__POWER_CONTROL_1(0x23),
	__POWER_CONTROL_2(0x10),
	__FRAME_RATE_CONTROL_1(0x00, 0x18),
	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
	__VCOM_CONTROL_1(0x3E, 0x28),
	__VCOM_CONTROL_2(0x86),

	// Interficie i format de pixels
	//
	__PIXEL_FORMAT_SET(0x55),
	__MEMORY_ACCESS_CONTROL(MAC_MY_ON | MAC_MX_ON | MAC_MV_OFF | 0x08),
	__RGB_INTERFACE_SIGNAL_CONTROL(0xC2),
	__DISPLAY_FUNCTION_CONTROL(0x0A, 0xA7, 0x27, 0x04),
	__INTERFACE_CONTROL(0x01, 0x00, 0x06),

	// Senyal TEAR-OFF
	//
	__TEARING_EFFECT_LINE_ON(0),

	// Correccio GAMMA
	//
	__ENABLE_3G(0x00),
	__GAMMA_SET(0x01),
	__POSITIVE_GAMMA_CORRECTION( 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
			0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
			0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
	OP_END
};

#elif defined(DISPLAY_DRV_ILI9341)

// Parametres d'inicialitzacio per interficie SPI
//
static const UInt8 initCommands[] = {

	__SOFTWARE_RESET,
	OP_DELAY, 250,
	OP_DELAY, 250,
	__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x62),
	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
	__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
	__PUMP_RATIO_CONTROL(0x20),
	__POWER_CONTROL_1(0x23),
	__POWER_CONTROL_2(0x10),
	__VCOM_CONTROL_1(0x3E, 0x28),
	__VCOM_CONTROL_2(0x86),
	__PIXEL_FORMAT_SET(0x55),
	__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF),
	__FRAME_RATE_CONTROL_1(0x00, 0x18),
	__DISPLAY_FUNCTION_CONTROL(0x08, 0x82, 0x27, 0x00),
	__ENABLE_3G(0x00),
	__GAMMA_SET(0x01),
	__POSITIVE_GAMMA_CORRECTION( 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
			0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
			0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
	OP_END
};
#endif



static inline Color __getRandomColor() {

	UInt32 c = __rand();
	return RGB((c & 0x00FF0000) >> 16, (c & 0x0000FF00) >> 8, c & 0x000000FF);
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param application: Aplicacio al que pertany el servei.
///
DisplayService::DisplayService():
	_text(Font("Consolas", 14, FontStyle::regular), Text::HorizontalAlign::left),
	_orientation(0) {

	_text.setForeground(Brush(Colors::yellow));
}


///-----------------------------------------------------------------------
/// \brief Executa les tasques del servei
///
void DisplayService::onExecute() {

    // Inicialitza el pin CS
    //
    pinCS->initOutput(OutputType::pushPull, PullUpDown::none, Speed::fast, true);

    // Inicialitza el pin RS
    //
    pinRS->initOutput(OutputType::pushPull, PullUpDown::none, Speed::fast, false);

    // Inicialitza el dispositiu SPI
    //
    devSPI->initPinSCK<DISPLAY_SCK_Pin>();
    devSPI->initPinMOSI<DISPLAY_MOSI_Pin>();
    devSPI->initMaster(spi::ClkPolarity::high, spi::ClkPhase::edge1, spi::WordSize::ws8, spi::FirstBit::msb, spi::ClockDivider::div8);

	// Inicialitza el dispositiu ILI9341
	//
    auto devILI9341 = new Device_ILI9341_SPI(pinCS, pinRS, nullptr, devSPI);
    devILI9341->initialize(initCommands, sizeof(initCommands) / sizeof(initCommands[0]));

	constexpr int frameBufferLineBytes = (_displayWidth * Color::bytes + 63) & 0xFFFFFFC0;
	constexpr int frameBufferPitch = frameBufferLineBytes / Color::bytes;

    // Inicialitza el buffer del display
    //
	auto *frameBuffer = new DisplayBuffer_ColorDMA2D(
		_displayWidth,
		_displayHeight,
		frameBufferPitch,
		DisplayBuffer::Orientation::normal,
		reinterpret_cast<void*>(_displayBuffer));

    // Inicialitza el dispositiu LTDC
    //
    devLTDC->initPinDE<PinDE, pinDEPolarity>();
    devLTDC->initPinHSYNC<PinHSYNC, pinHSYNCPolartity>();
    devLTDC->initPinVSYNC<PinVSYNC, pinVSYNCPolarity>();
    devLTDC->initPinPC<pinDC, pinDCPolarity>();
    devLTDC->initPinRX<PinR2, PinR3, PinR4, PinR5, PinR6, PinR7>();
    devLTDC->initPinGX<PinG2, PinG3, PinG4, PinG5, PinG6, PinG7>();
    devLTDC->initPinBX<PinB2, PinB3, PinB4, PinB5, PinB6, PinB7>();
    devLTDC->initialize(_displayWidth, _displayHeight, DISPLAY_HSYNC, DISPLAY_VSYNC, DISPLAY_HBP, DISPLAY_VBP, DISPLAY_HFP, DISPLAY_VFP);
    devLTDC->setBackgroundColor(RGB(0, 0, 255));

	constexpr ltdc::PixelFormat pixelFormat =
		Color::format == ColorFormat::argb8888 ? ltdc::PixelFormat::argb8888 :
		Color::format == ColorFormat::argb4444 ? ltdc::PixelFormat::argb4444 :
		Color::format == ColorFormat::argb1555 ? ltdc::PixelFormat::argb1555 :
		Color::format == ColorFormat::rgb888 ? ltdc::PixelFormat::rgb888 :
		Color::format == ColorFormat::al88 ? ltdc::PixelFormat::al88 :
		Color::format == ColorFormat::al44 ? ltdc::PixelFormat::al44 :
		Color::format == ColorFormat::l8 ? ltdc::PixelFormat::l8 :
        ltdc::PixelFormat::rgb565;
	devLTDCLayer->setWindow(0, 0, _displayWidth, _displayHeight);
	devLTDCLayer->setFrameFormat(
		pixelFormat,
		_displayWidth * Color::bytes,
		((_displayWidth * Color::bytes) + 63) & 0xFFFFFFC0,
		_displayHeight);
    devLTDCLayer->setFrameBuffer(reinterpret_cast<void*>(frameBuffer->getBuffer()));
	devLTDCLayer->enable();

	devLTDC->reload();

    // Inicialitza el driver de pantalla
    //
	_driver = new DisplayDriver_ILI9341LTDC(devILI9341, devLTDC, devLTDCLayer, frameBuffer);
	_driver->initialize();
	_driver->enable();

    // Inicialitza el controlador de grafics
    //
    _graphics = new Graphics(_driver);

    _pointsTicks = Ticks::zero();
    _horizontalLinesTicks = Ticks::zero();
    _verticalLinesTicks = Ticks::zero();
    _linesTicks = Ticks::zero();
    _rectanglesTicks = Ticks::zero();
    _filledRectanglesTicks = Ticks::zero();
    _ellipsesTicks = Ticks::zero();
    _filledEllipsesTicks = Ticks::zero();

    while (!stopSignal()) {

		#ifdef TEST_ORIENTATION
		_frameBuffer->setOrientation(DisplayBuffer::Orientation((_orientation++) & 0b11));
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
		Task::delay(Ticks::fromMiliseconds(250));

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

		Task::delay(Ticks::fromMiliseconds(5000));
		#endif
    }
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

    _text.setText(title, -1);
    _graphics->paintText(Point(4, 0), _text);

    _graphics->drawRectangle(7, 27, _maxX - 10, _maxY - 10, Colors::red);
}


void DisplayService::testColors() {

	drawBackground("Colors");
	rtos::Task::delay(eos::Time::fromMiliseconds(250));

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

	delayMS(2500);
}

/// ----------------------------------------------------------------------
/// \brief    Test d'opacitat.
///
void DisplayService::testOpacity() {

	constexpr int w = 74;
	constexpr int dd = w / 2;

	drawBackground("Opacity");
	delayMS(250);

	UInt8 opacity = 128;

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

	delayMS(2500);
}


/// ----------------------------------------------------------------------
/// \brief    Test de punts aleatoris.
///
void DisplayService::testPoints() {

	Ticks ticks;

	drawBackground("Random points");
	Task::delay(Ticks::fromMiliseconds(250));

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    __srand(seed);
    ticks = Ticks::now();
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _maxX;
        int y = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawPoint(x, y, c);
    }
    _pointsTicks = Ticks::now() - ticks;
    Task::delay(Ticks::fromMiliseconds(250));

    __srand(seed);
    for (int i = 0; i < 50000; i++) {
        int x = __rand() % _maxX;
        int y = __rand() % _maxY;

        __rand(); // Mantre la sequencia de 3 rand's per cicle

        _graphics->drawPoint(x, y, Colors::black);
    }

    Task::delay(Ticks::fromMiliseconds(250));
}


/// ----------------------------------------------------------------------
/// \brief    Test de linies.
///
void DisplayService::testLines() {

	int ticks;

	// Vertical lines
    //
    drawBackground("Vertical lines");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int y2 = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawVLine(x, y1, y2, c);
    }
    _verticalLinesTicks = getTickCount() - ticks;
    delayMS(1000);

    // Horizontal lines
    //
    drawBackground("Horizontal lines");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _maxX;
        int x2 = __rand() % _maxY;
        int y = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawHLine(x1, x2, y, c);
    }
    _horizontalLinesTicks = getTickCount() - ticks;
    delayMS(1000);

    // Lines
    //
    drawBackground("Random lines");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 5000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = __rand() % _maxX;
        int y2 = __rand() % _maxY;

        Color c = __getRandomColor();
        _graphics->drawLine(x1, y1, x2, y2, c);
    }
    _linesTicks = getTickCount() - ticks;
    delayMS(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de linies amples.
///
void DisplayService::testThickLines() {

	// Thick lines
    //
    drawBackground("Thick lines");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    _graphics->drawLine(10, 10, 200, 376, 5, Colors::white);

    delayMS(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de rectangles.
///
void DisplayService::testRectangles() {

	int ticks;

	// Restangles buits
	//
	drawBackground("Rectangles");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c = __getRandomColor();
        _graphics->drawRectangle(x1, y1, x2, y2, c);
    }
    _rectanglesTicks = getTickCount() - ticks;
    delayMS(1000);

    // Rectangles plens
    //
    drawBackground("Filled rectangles");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1000; i++) {
        int x1 = __rand() % _maxX;
        int y1 = __rand() % _maxY;
        int x2 = x1 + __rand() % 150;
        int y2 = y1 + __rand() % 150;

        Color c = __getRandomColor();
        _graphics->fillRectangle(x1, y1, x2, y2, c);
    }
    _filledRectanglesTicks = getTickCount() - ticks;
    delayMS(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Test de rectangles.
///
void DisplayService::testEllipses() {

	int ticks;

    // El·lipses buides
    //
    drawBackground("Ellipses");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1000; i++) {
        int cx = __rand() % _maxX;
        int cy = __rand() % _maxY;
        int rx = (__rand() % 60) + 3;
        int ry = (__rand() % 60) + 3;

        Color c = __getRandomColor();
        _graphics->drawEllipse(cx - rx, cy - ry, cx + rx, cy + ry, c);
    }
    _ellipsesTicks = getTickCount() - ticks;
    delayMS(1000);

    // Elipses plenes
    //
    drawBackground("Filled ellipses");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1000; i++) {
        int cx = __rand() % _maxX;
        int cy = __rand() % _maxY;
        int rx = (__rand() % 60) + 3;
        int ry = (__rand() % 60) + 3;

        Color c = __getRandomColor();
       	_graphics->fillEllipse(cx - rx, cy - ry, cx + rx, cy + ry, c);
    }
    _filledEllipsesTicks = getTickCount() - ticks;
    delayMS(1000);
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
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1; i++) {

        Color c = __getRandomColor();
    	_graphics->drawPolygon(__points, 6, c);
    }
    _polygonsTicks = getTickCount() - ticks;
    delayMS(1000);

    // Elipses plenes
    //
    drawBackground("Filled polygons");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);
    ticks = getTickCount();
    for (int i = 0; i < 1; i++) {

    	Color c = __getRandomColor();
    	_graphics->fillPolygon(__points, 6, c);
    }
    _filledPolygonsTicks = getTickCount() - ticks;
    delayMS(1000);
}


extern "C" const unsigned char bitmap1[];


/// ----------------------------------------------------------------------
/// \brief    Test de bitmaps
///
void DisplayService::testBitmaps() {

	int ticks;
	const UInt8 *data = bitmap1;

	int width = (int) (data[0] | (data[1] << 8));
	int height = (int) (data[2] | (data[3] << 8));
	//int flags = (int) (data[4] | (data[5] << 8));

	Bitmap bitmap(width, height, ColorFormat::rgb565, &data[6]);

	drawBackground("Bitmaps");
    delayMS(250);

    _graphics->setClip(8, 28, _maxX - 11, _maxY - 11);

    ticks = getTickCount();

    int x = (_maxX + 1) / 2;
    int y = (_maxY + 1) / 2;
	_graphics->drawBitmap(
		x - bitmap.getWidth() / 2,
		y - bitmap.getHeight() / 2,
		bitmap);

    _bitmapTicks = getTickCount() - ticks;
    delayMS(1000);
}
