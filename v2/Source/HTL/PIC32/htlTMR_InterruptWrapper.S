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

	.global	isrTMR1Wrapper
	.global	isrTMR2Wrapper
	.global	isrTMR3Wrapper
	.global	isrTMR4Wrapper
	.global	isrTMR5Wrapper

	.set	noreorder
	.set 	noat


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_1_VECTOR
 *
 *       Funcio:
 *           isrTMR1Wrapper
 *
 *************************************************************************/

	.ent	isrTMR1Wrapper
isrTMR1Wrapper:
	portSAVE_CONTEXT
	jal	TMR_1_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	isrTMR1Wrapper


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_2_VECTOR
 *
 *       Funcio:
 *           isrTMR2Wrapper
 *
 *************************************************************************/

#ifdef _TMR2
	.ent	isrTMR2Wrapper
isrTMR2Wrapper:
	portSAVE_CONTEXT
	jal	TMR_2_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	isrTMR2Wrapper
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_3_VECTOR
 *
 *       Funcio:
 *           isrTMR3Wrapper
 *
 *************************************************************************/

#ifdef _TMR3
	.ent	isrTMR3Wrapper
isrTMR3Wrapper:
	portSAVE_CONTEXT
	jal	TMR_3_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	isrTMR3Wrapper
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_4_VECTOR
 *
 *       Funcio:
 *           isrTMR4Wrapper
 *
 *************************************************************************/

#ifdef _TMR4
	.ent	isrTMR4Wrapper
isrTMR4Wrapper:
	portSAVE_CONTEXT
	jal	TMR_4_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	isrTMR4Wrapper
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _TIMER_5_VECTOR
 *
 *       Funcio:
 *           isrTMR5Wrapper
 *
 *************************************************************************/

#ifdef _TMR5
	.ent	isrTMR5Wrapper
isrTMR5Wrapper:
	portSAVE_CONTEXT
	jal	TMR_5_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	isrTMR5Wrapper
#endif
