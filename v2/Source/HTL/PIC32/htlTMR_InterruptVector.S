#include <xc.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
	.set 	noreorder

	.extern TMR_1_InterruptHandler
	.extern TMR_2_InterruptHandler
	.extern TMR_3_InterruptHandler
	.extern TMR_4_InterruptHandler
	.extern TMR_5_InterruptHandler

	.global	TMR_1_InterruptVector
	.global	TMR_2_InterruptVector
	.global	TMR_3_InterruptVector
	.global	TMR_4_InterruptVector
	.global	TMR_5_InterruptVector

	.set	noreorder
	.set 	noat


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_1_VECTOR
 *
 *       Funcio:
 *           TMR_1_InterruptVector
 *
 *************************************************************************/

#ifdef _TMR1x
	.ent	TMR_1_InterruptVector
TMR_1_InterruptVector:
	portSAVE_CONTEXT
	jal	TMR_1_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	TMR_1_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_2_VECTOR
 *
 *       Funcio:
 *           TMR_2_InterruptVector
 *
 *************************************************************************/

#ifdef _TMR2
	.ent	TMR_2_InterruptVector
TMR_2_InterruptVector:
	portSAVE_CONTEXT
	jal	TMR_2_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	TMR_2_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_3_VECTOR
 *
 *       Funcio:
 *           TMR_3_InterruptVector
 *
 *************************************************************************/

#ifdef _TMR3
	.ent	TMR_3_InterruptVector
TMR_3_InterruptVector:
	portSAVE_CONTEXT
	jal	TMR_3_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	TMR_3_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_4_VECTOR
 *
 *       Funcio:
 *           TMR_4_InterruptVector
 *
 *************************************************************************/

#ifdef _TMR4
	.ent	TMR_4_InterruptVector
TMR_4_InterruptVector:
	portSAVE_CONTEXT
	jal	TMR_4_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	TMR_4_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_5_VECTOR
 *
 *       Funcio:
 *           TMR_5_InterruptVector
 *
 *************************************************************************/

#ifdef _TMR5
	.ent	TMR_5_InterruptVector
TMR_5_InterruptVector:
	portSAVE_CONTEXT
	jal	TMR_5_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	TMR_5_InterruptVector
#endif
