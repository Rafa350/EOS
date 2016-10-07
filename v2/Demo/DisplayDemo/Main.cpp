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
    display->clear(0x00000000);
    
    screenWidth = display->getDriver()->getWidth();
    screenHeight  = display->getDriver()->getHeight();    
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {
    
    // Random points
    //
    drawBackground("Random points");
    Task::delay(250);

    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);    
    srand(0);
    for (int i = 0; i < 50000; i++) {
        int16_t x = rand() % screenWidth;
        int16_t y = rand() % screenHeight;
        Color c = rand() & 0x00FFFFFF;
        
        display->setColor(c);
        display->drawPoint(x, y);
    }
    Task::delay(250);
    
    srand(0);
    display->setColor(0);
    for (int i = 0; i < 50000; i++) {
        int16_t x = rand() % screenWidth;
        int16_t y = rand() % screenHeight;
        rand();
       
        display->drawPoint(x, y);        
    }
    
    // Random vertical lines
    //
    drawBackground("Random vertical lines");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    for (int i = 0; i < 200; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = x1; 
        int16_t y2 = rand() % screenHeight;
        Color c = rand() & 0x00FFFFFF;
        
        display->setColor(c);
        display->drawLine(x1, y1, x2, y2);
    }    
    Task::delay(1500);
    
    // Random horizontal lines
    //
    drawBackground("Random horizontal lines");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    for (int i = 0; i < 200; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = y1;
        Color c = rand() & 0x00FFFFFF;
        
        display->setColor(c);
        display->drawLine(x1, y1, x2, y2);
    }
    Task::delay(1500);
    
    // Random lines
    //
    drawBackground("Random lines");
    Task::delay(250);
    
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);   
    display->setClip(6, 26, screenWidth - 7, screenHeight - 7);
    for (int i = 0; i < 500; i++) {
        int16_t x1 = rand() % screenWidth;
        int16_t y1 = rand() % screenHeight;
        int16_t x2 = rand() % screenWidth;
        int16_t y2 = rand() % screenHeight;
        Color c = rand() & 0x00FFFFFF;
        
        display->setColor(c);
        display->drawLine(x1, y1, x2, y2);
    }
    Task::delay(1500);
    
    /*

    display->clear(0);
    int fontHeight = display->getTextHeight("M") + 2;
    for (int i = 0; i < 10; i++) {
        display->setColor(RGB(r, g, b));
        display-> drawText(10, 30 + i * fontHeight, "0123456789 ABCD abcd", 0, -1);
        r += 5;
        g += 7;
        b += 9;
    }
    Task::delay(1000);
    
    display->clear(0);
    for (int i = 0; i < 1000; i++)
        display->putTTY('a');   
    Task::delay(1000);*/
}


void MyAppLoopService::drawBackground(
    const char* title) {
    
    display->clear(0);
    display->resetClip();
    display->setColor(0x00FF0000);
    display->drawRectangle(0, 0, screenWidth - 1, screenHeight - 1);
    display->drawLine(0, 20, screenWidth - 1, 20);
    display->drawText(4, 16, title, 0, -1);
    display->drawRectangle(5, 25, screenWidth - 6, screenHeight - 6);
}

/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
int main(void) {
    
    LATGbits.LATG6 = 0;
    TRISGbits.TRISG6 = 0;
    
    LATDbits.LATD1 = 1;
    TRISDbits.TRISD1 = 0;    
    
    MyApplication *app = new MyApplication();
    app->execute();
    delete app;

    return 0;
}
