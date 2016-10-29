#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"


using namespace eos;


class MyAppLoopService: public AppLoopService {
    private:
        Display *display;
        IDisplayDriver *driver;
        int16_t screenWidth;
        int16_t screenHeight;
        
    public:
        MyAppLoopService(Application *application):
            AppLoopService(application) {}
    
    protected:
        void setup();
        void loop();
        
    private:
        void drawBackground(const char *title);
};


class MyApplication: public Application {
    private:
        MyAppLoopService *service;
        
    public :
        MyApplication();
};


///-----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {
    
    service = new MyAppLoopService(this);
}


///-----------------------------------------------------------------------
/// \brief Process d'inicialitzacio. El sistema el crida nomes un cop.
///
void MyAppLoopService::setup() {
    
    driver = new ILI9341_Driver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);
    display = new Display(driver);
    display->clear(COLOR_Black);
    
    screenWidth = display->getDriver()->getWidth();
    screenHeight  = display->getDriver()->getHeight();    
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {
    
    int ticks;

    int pointsTicks;
    int horizontalLinesTicks;
    int verticalLinesTicks;
    int linesTicks;
    int fillRectanglesTicks;

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
    for (int i = 0; i < 200; i++) {
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
    for (int i = 0; i < 200; i++) {
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
    for (int i = 0; i < 500; i++) {
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
    for (int i = 0; i < 200; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;
        
        display->setColor(rand() & 0x00FFFFFF);
        display->drawRectangle(x1, y1, x2, y2);
    }
    Task::delay(1000);
    
    // Filled rectangles
    //
    drawBackground("Filled rectangles");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    ticks = Task::getTickCount();
    for (int i = 0; i < 1000; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = x1 + rand() % 100;
        int16_t y2 = y1 + rand() % 100;
        
        display->setColor(rand() & 0x00FFFFFF);
        display->fillRectangle(x1, y1, x2, y2);
    }
    fillRectanglesTicks = Task::getTickCount() - ticks;
    Task::delay(500);
    
    // Circles
    //
    drawBackground("Circles");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    for (int i = 0; i < 200; i++) {
        int16_t cx = rand() % screenWidth;
        int16_t cy = rand() % screenHeight;
        int16_t r = rand() % 150;
        
        display->setColor(rand() & 0x00FFFFFF);
        display->drawCircle(cx, cy, r);
    }
    Task::delay(1000);
    
    // Fillet circles
    //
    drawBackground("Filled circles");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    for (int i = 0; i < 200; i++) {
        int16_t cx = rand() % screenWidth;
        int16_t cy = rand() % screenHeight;
        int16_t r = rand() % 50;
        
        display->setColor(rand() & 0x00FFFFFF);
        display->fillCircle(cx, cy, r);
    }
    Task::delay(500);
    
    // Show results
    //
    drawBackground("Results");
    Task::delay(250);
    
    char lineBuffer[30];
    sprintf(lineBuffer, "Points        %d ms", pointsTicks);
    display->drawText(10, 50, lineBuffer, 0, -1);
    sprintf(lineBuffer, "V. lines      %d ms", verticalLinesTicks);
    display->drawText(10, 70, lineBuffer, 0, -1);
    sprintf(lineBuffer, "H. lines      %d ms", horizontalLinesTicks);
    display->drawText(10, 90, lineBuffer, 0, -1);
    sprintf(lineBuffer, "Lines         %d ms", linesTicks);
    display->drawText(10, 110, lineBuffer, 0, -1);
    sprintf(lineBuffer, "F. rectangles %d ms", fillRectanglesTicks);
    display->drawText(10, 130, lineBuffer, 0, -1);
    
    Task::delay(10000);
}


void MyAppLoopService::drawBackground(
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
