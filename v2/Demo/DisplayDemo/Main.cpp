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
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {

    for (int i = 0; i < 10; i++) {
        display->setColor(RGB(r, g, b));
        display->drawString(10, 30 + i * 30, "0123456789");
        r += 131;
        g += 97;
        b += 39;
    }

    Task::delay(250);
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
