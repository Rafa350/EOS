#include <xc.h>
#include <sys/asm.h>
#include "ISR_Support.h"

	.set	nomips16
	.set 	noreorder

	.extern UART_1_InterruptHandler
	.extern UART_2_InterruptHandler
	.extern UART_3_InterruptHandler
	.extern UART_4_InterruptHandler
	.extern UART_5_InterruptHandler

	.global	UART_1_InterruptVector
	.global	UART_2_InterruptVector
	.global	UART_3_InterruptVector
	.global	UART_4_InterruptVector
	.global	UART_5_InterruptVector

	.set	noreorder
	.set 	noat

/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _UART_1_VECTOR
 *
 *       Funcio:
 *           UART_1_InterruptVector
 *
 *************************************************************************/

	.ent	UART_1_InterruptVector
UART_1_InterruptVector:
	portSAVE_CONTEXT
	jal	UART_1_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UART_1_InterruptVector


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _UART_2_VECTOR
 *
 *       Funcio:
 *           UART_2_InterruptVector
 *
 *************************************************************************/

#ifdef _UART2
	.ent	UART_2_InterruptVector
UART_2_InterruptVector:
	portSAVE_CONTEXT
	jal	UART_2_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UART_2_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _UART_3_VECTOR
 *
 *       Funcio:
 *           UART_3_InterruptVector
 *
 *************************************************************************/

#ifdef _UART3
	.ent	UART_3_InterruptVector
UART_3_InterruptVector:
	portSAVE_CONTEXT
	jal	UART_3_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UART_3_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _UART_4_VECTOR
 *
 *       Funcio:
 *           UART_4_InterruptVector
 *
 *************************************************************************/

#ifdef _UART4
	.ent	UART_4_InterruptVector
UART_4_InterruptVector:
	portSAVE_CONTEXT
	jal	UART_4_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UART_4_InterruptVector
#endif


/*************************************************************************
 *
 *       Punt d'entrada del del vector de interrupcio _I2C_5_VECTOR
 *
 *       Funcio:
 *           UART_5_InterruptVector
 *
 *************************************************************************/

#ifdef _UART5
	.ent	UART_5_InterruptVector
UART_5_InterruptVector:
	portSAVE_CONTEXT
	jal	UART_5_InterruptHandler
	nop
	portRESTORE_CONTEXT
	.end	UART_5_InterruptVector
#endif
