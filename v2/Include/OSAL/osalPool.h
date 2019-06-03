#ifndef __osalPool__
#define __osalPool__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct POOL *HPool;


HPool osalPoolCreate(unsigned blockSize, unsigned maxBlocks, void *pBlock);
void osalPoolDestroy(HPool hPool);
void *osalPoolAlloc(HPool hPool);
void osalPoolFree(void *pBlock);


#ifdef	__cplusplus
}
#endif


#endif // __osalPool__
