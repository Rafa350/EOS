#include <p32xxxx.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
 	.set 	noreorder
 	
 	.extern eosTickServiceISR
	.global eosTickServiceISRWrapper

	.set	noreorder
	.set 	noat
	.ent	eosTickServiceISRWrapper
	
eosTickServiceISRWrapper:
	portSAVE_CONTEXT
	jal	eosTickServiceISR
	nop
	portRESTORE_CONTEXT

	.end eosTickServiceISRWrapper



