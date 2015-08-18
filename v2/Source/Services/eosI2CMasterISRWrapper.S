#include <p32xxxx.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
	.set 	noreorder

	.extern isrI2C1Handler
	.extern isrI2C2Handler
	.extern isrI2C3Handler
	.extern isrI2C4Handler
	.extern isrI2C5Handler

	.global	isrI2C1Wrapper
	.global	isrI2C2Wrapper
	.global	isrI2C3Wrapper
	.global	isrI2C4Wrapper
	.global	isrI2C5Wrapper

	.set	noreorder
	.set 	noat
		
	.ent	isrI2C1Wrapper
isrI2C1Wrapper:
	portSAVE_CONTEXT
	jal	isrI2C1Handler
	nop
	portRESTORE_CONTEXT
	.end	isrI2C1Wrapper
	
	.ent	isrI2C2Wrapper
isrI2C2Wrapper:
	portSAVE_CONTEXT
	jal	isrI2C2Handler
	nop
	portRESTORE_CONTEXT
	.end	isrI2C2Wrapper	
	
	.ent	isrI2C3Wrapper
isrI2C3Wrapper:
	portSAVE_CONTEXT
	jal	isrI2C3Handler
	nop
	portRESTORE_CONTEXT
	.end	isrI2C3Wrapper
		
	.ent	isrI2C4Wrapper
isrI2C4Wrapper:
	portSAVE_CONTEXT
	jal	isrI2C4Handler
	nop
	portRESTORE_CONTEXT
	.end	isrI2C4Wrapper
	
	.ent	isrI2C5Wrapper
isrI2C5Wrapper:
	portSAVE_CONTEXT
	jal	isrI2C5Handler
	nop
	portRESTORE_CONTEXT
	.end	isrI2C5Wrapper
	
	
	
