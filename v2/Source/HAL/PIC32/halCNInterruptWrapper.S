#include <xc.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
	.set 	noreorder

	.extern isrCNHandler

	.global	isrCNWrapper

	.set	noreorder
	.set 	noat
		
/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _CHANGE_NOTICE_VECTOR
 *
 *       Funcio:
 *           isrCNWrapper
 *
 *************************************************************************/
	
	.ent	isrCNWrapper
isrCNWrapper:
	portSAVE_CONTEXT
	jal	isrCNHandler
	nop
	portRESTORE_CONTEXT
	.end	isrCNWrapper
