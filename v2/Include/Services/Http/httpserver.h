#ifndef __HTTPSERVER_H
#define __HTTPSERVER_H


#include "lwip/api.h"


#ifdef	__cplusplus
extern "C" {
#endif


void http_server_init(void);
void http_server_thread(void* args);
void http_server_serve(struct netconn *conn);


#ifdef	__cplusplus
}
#endif


#endif // __HTTPSERVER_H
