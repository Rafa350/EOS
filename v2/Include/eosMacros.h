#ifndef __EOS_MACROS_H
#define __EOS_MACROS_H


#define __concat2(a, b)      a ## b
#define __concat3(a, b, c)   a ## b ## c
#define concat2(a, b)        __concat2(a, b)
#define concat3(a, b, c)     __concat3(a, b, c)

#ifndef min
#define min(a, b)            (a) < (b) ? (a) : (b)
#endif

#ifndef max
#define max(a, b)            (a) > (b) ? (a) : (b)
#endif


#endif