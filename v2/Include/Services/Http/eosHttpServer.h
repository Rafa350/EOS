#ifndef __eosHttpServer__
#define __eosHttpServer__


#include "eos.h"
#include "lwip/api.h"


namespace eos {

    class HttpServer {
    	private:
    		typedef struct netconn* HConnection;
    	private:
    		void error(HConnection hConnection);
    		void processGET(HConnection hConnection, const char* data, unsigned dateLength);
    		void processData(HConnection hConnection, const char* data, unsigned dataLength);

        public:
            HttpServer();
            
            void initialize();
            void run();
    };
}


#endif // __httpServer__
