#include <xc.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
	.set 	noreorder

	.extern CN_1_InterruptHandler

	.global	CN_1_InterruptVector

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

	.ent	CN_1_InterruptVector
CN_1_InterruptVector:
	portSAVE_CONTEXT
	jal	CN_1_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	CN_1_InterruptVector
