#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"


using namespace eos;


class MyApplication: public Application {
    private:
        Display *display;
        IDisplayDriver *driver;
        
    public :
        MyApplication();

    protected:
        void onInitialize();
};


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           MyApplication::MyApplication()
 *
 *************************************************************************/

MyApplication::MyApplication() {
    
}


/*************************************************************************
 *
 *       Inicialitza l'aplicacio
 *
 *       Funcio:
 *           void MyApplication::onInitialize() 
 *
 *************************************************************************/

void MyApplication::onInitialize() {
    
    driver = new ILI9341_DisplayDriver();
    driver->initialize();
    driver->setOrientation(Orientation::rotate180);
    
    display = new Display(driver);
 
    display->clear(0x00000000);
    display->setColor(RGB(0, 255, 255));
    for (int i = 0; i < 10; i++)
        display->drawString(10, 10 + i * 30, "0123456789");
 }


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           int main(void)
 *
 *************************************************************************/

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
