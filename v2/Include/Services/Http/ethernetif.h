#ifndef __ETHERNETIF_H
#define __ETHERNETIF_H


#include "lwip/err.h"
#include "lwip/netif.h"


#ifdef	__cplusplus
extern "C" {
#endif


err_t ethernetif_init(struct netif *netif);


#ifdef	__cplusplus
}
#endif


#endif // __ETHERNETIF_H
