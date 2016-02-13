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

    private:
        void setupDisplay();
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
    
    setupDisplay();
}


/*************************************************************************
 *
 *       Inicialitza la pantalla
 *
 *       Funcio:
 *           void MyApplication::setupDisplay() 
 *
 *************************************************************************/

void MyApplication::setupDisplay() {
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
       
    MyApplication *app = new MyApplication();
    app->execute();

    return 0;
}
