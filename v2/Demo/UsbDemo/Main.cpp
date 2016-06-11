#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"


using namespace eos;


class MyAppLoopService: public AppLoopService {
   
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
    
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {
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
