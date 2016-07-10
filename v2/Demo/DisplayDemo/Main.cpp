#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"


using namespace eos;


class MyAppLoopService: public AppLoopService {
    private:
        unsigned char r, g, b;
        Display *display;
        IDisplayDriver *driver;
    
    protected:
        void setup();
        void loop();
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
    
    service = new MyAppLoopService();
}


///-----------------------------------------------------------------------
/// \brief Process d'inicialitzacio. El sistema el crida nomes un cop.
///
void MyAppLoopService::setup() {
    
    driver = new ILI9341_DisplayDriver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);
    
    display = new Display(driver);
    display->clear(0x00000000);
    
    r = 12;
    g = 134;
    b = 97;
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {

    display->clear(0);
    int fontHeight = display->getTextHeight("M") + 2;
    for (int i = 0; i < 10; i++) {
        display->setColor(RGB(r, g, b));
        display->drawString(10, 30 + i * fontHeight, "0123456789 ABCD abcd", 0, -1);
        r += 5;
        g += 7;
        b += 9;
    }
    Task::delay(1000);
    
    display->clear(0);
    for (int i = 0; i < 1000; i++)
        display->putTTY('a');   
    Task::delay(1000);
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
