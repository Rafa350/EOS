#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk)" "nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk"
include nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_USB_STARTER_KIT_I
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp ../../../Source/HTL/PIC32/htlCN_InterruptVector.S ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o.d ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d ${OBJECTDIR}/_ext/2104168611/AppMain.o.d ${OBJECTDIR}/_ext/2104168611/appApplication.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o.d ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o.d ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalMutex.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/618460187/heap_4.o.d ${OBJECTDIR}/_ext/152460360/port.o.d ${OBJECTDIR}/_ext/152460360/port_asm.o.d ${OBJECTDIR}/_ext/1745914046/list.o.d ${OBJECTDIR}/_ext/1745914046/queue.o.d ${OBJECTDIR}/_ext/1745914046/tasks.o.d ${OBJECTDIR}/_ext/1745914046/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o

# Source Files
SOURCEFILES=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp ../../../Source/HTL/PIC32/htlCN_InterruptVector.S ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk ${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o: ../../../Source/HTL/PIC32/htlCN_InterruptVector.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/81a83a28945504a11664c526d00aa9bfea40e82d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.ok ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d"  -o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o ../../../Source/HTL/PIC32/htlCN_InterruptVector.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d" "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o: ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f3bb860388771be2044736188248c6408f016d87 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.ok ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d"  -o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d" "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fd3c3059d03028723ee1739be282f27e2e1c7830 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o: ../../../Source/HTL/PIC32/htlCN_InterruptVector.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cc5a5eeeb7aa3917591244f34be5ba7fdebdfc7a .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.ok ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d"  -o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o ../../../Source/HTL/PIC32/htlCN_InterruptVector.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.asm.d",-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.d" "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptVector.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o: ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/23fafa08666bb3b2c2a1187d311206cf21faf3f8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.ok ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d"  -o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o ../../../Source/HTL/PIC32/htlTMR_InterruptVector.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.asm.d",-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.d" "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptVector.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/381b133e5a47fc37e838f95085fa7173c330ba47 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/394c345447a24116f1dbe33e4621afb1fc810a43 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2078dc4b74a88e0871cd9631171bf318dfc32fa5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4d481f83c113c199f7111f140c85a8f17d7485d3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c710f67f2d38fcd45975536efb41284b0df0dd1b .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4628d7f1fae720229276961c33b44152bfa8b643 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/32a6fd30f2569db0cedd01006bfad286a527eb19 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7367f003e8f0882764a9766d362e5e84621a9aca .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/acc177e842444b785716f06352222666cd30b217 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ae53d38beef1f920933815154b7b28088e3e2eb4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8dce8b9d8d8632f622d3c5abcc628bfc6dff645d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7ad6e33e3fab786d720317daa42bf0165a4df507 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/206e598d64371eb2cbb58ca173ef9d8cb42d23b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e27ee410f999b907c64b7a47c314c72df6ebad37 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/80e853500ee098526f21b53e214e7f023e946e0f .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c0d610df0de112483bcedccb97acb94668e15b6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f568f48365338baeabc3730a0cae84ca1a794cb9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6176c110d7e085da816222dcfb1731582f17063c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/38f2a3e200ba9ee7679f7d887b86e13cbcdf8093 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dc0cd0cc1db3a980381a9759a35d1854025bca44 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2df8dfbcb78369aeb55068e212c8aca6e7bebb66 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/df9e9e243c24fff6ce9e8694098e00940b777f51 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fe7a953d35ba91c4723447d5927f9943509d8caa .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/427fdd2c0ffba70460c79d8be9f522e2ef4db219 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6f52cac68f1c696e595640eaa213513ff2a7cc6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c58f4017f6228c9e59bce7a4eda696105d67aec6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/663ebcf09823e07b939691cab28198e462396c80 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/110d2a6f6b8992045c313b630806bf47e717d014 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3d283f1e70a449115da5dc1ebc366643e72b65a6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/306df47f2887e6f19dc0ebcf41d6a1177828b880 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cd78a0ee11f825182904f714a143131c1d1c6f6e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6e33a912dd1cf4f11b99c43e6e440fae803fa926 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cdd1ca848b8e21b68718f074f6c946280e41c26 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/646d0ba17a179b14ce5cbe258f41d56338fd3ea4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f0813b87390936084586ae796035b1f2a6d56d35 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/511f3fa470c4b477f2511a3f8f180bb7f25fd326 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3ea3bfb23581eb7c4e404259bd8263c48bc5d12d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o: ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7a042a2474f830487655d972943378c675fd9553 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o.d" -o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o: ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9580f8a853c8b96a50d7a4605d7b0214646de6b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o.d" -o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fa04cd4714e66787fbf1ad17aa589643535b0843 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/62dc1e3f4422980fae3ff25ef24f462764d3c882 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/afaed34a741a7a9b27f2181e5af89b615c4e0c45 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f0add1e247041b58c416f0c070f867f7b77e6739 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ee9f223b0e792805e9cc0bd573d150cece12fe32 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6fedc41191ef5637782d3369af4bf9ad8a57abdb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/61b1f78867ecb6a594d11189c56adf6b77fec31d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/caa643d11c8dfdb2ad1aebfc9c3e908f10806d39 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/240ea7fcbed2e4ede9d0b8d0c65b6dab1b7395be .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1155463caea76bbd6f9aca06a5e5237f054d89ef .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/21a404b553d902132a30edbb6dd1f1d97a1740bc .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8409d589b48734ea68838f426c17653efc32114c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3a2964cc7f9894c73bcaf064cdbc4d3802aa133 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/de5e1d9488d7ba8bfbf4eba2109d73b30b59a315 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fcb20af2992353108fbaffeac823c679160b4277 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5f591c9f889fa5cc81c9caaba451a205669a5ef5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/83a7c5025ae30afee0b8e66166d5143210daa9f5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dc00b52e64eefa91617ad460b113fc9b2c038357 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1f883325f54b5459039629a601343d2295f90cb5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e1919dd98c061a4d0208271d93436df02fdc0741 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o: ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dcc4f5a97c6edc5c19ca0f50d495b8e7b47055de .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o.d" -o ${OBJECTDIR}/_ext/1592476363/htlCN_InterruptHandler.o ../../../Source/HTL/PIC32/htlCN_InterruptHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o: ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7ca2c9c9d89608bb30db6793877e0d210bf236e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1592476363" 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o.d" -o ${OBJECTDIR}/_ext/1592476363/htlTMR_InterruptHandler.o ../../../Source/HTL/PIC32/htlTMR_InterruptHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/eae89644e9fc5f0f0097263b672bbe8defc49835 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/30d54f7241648ba6e6fa87ae6d2e7f7fb9f2e45d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a5de2ebddd160cb61c4834a3a1aa5e8d7520190b .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6ef5c00151c732f986fee8319b88339950276f84 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6421f0342d2e755f215613a7a55445e00d935ce4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9b4b2a805a316d5ce61133c5eadcb3cddd111966 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2c38a4ddfdcd59e8993551b90546222729fe4fd .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7a10ffb57575fe50e53964043c0bdc19b89bae4f .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cc2c9e34de409adf2d49c2d7083b874122fce7b8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/db1145b64aa2e2f955db473be0345dc6db8fcc99 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b0afe975bfd063e880b4d56c34aca1a205c873c3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/37d89b4e894a80fb8c6500a08b7c7fe9bde728f8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/62ff148bd2b08573e36dca326219d7485d0bc83c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9b223640ca61d282b37d0d9430f055e664b2ae66 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9d3fce9c2f0dd53d6f2276d072067561b31a3b59 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c70d882642dfb85b6218fbb52da0551e3b0e4cfc .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/DigIOServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
