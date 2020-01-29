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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Source/StartUp/PIC32/main.cpp ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp ../../../Demo/FsmDemo/Source/appApplication.cpp ../../../Demo/FsmDemo/Source/appMain.cpp ../../../Demo/FsmDemo/Source/appStateMachine.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosFsmService.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c ../../../Demo/FsmDemo/Machine/fsmState.cpp ../../../Demo/FsmDemo/Machine/fsmContext.cpp ../../../Source/Services/Fsm/eosFsmContextBase.cpp ../../../Source/Services/Fsm/eosFsmStateBase.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1439849346/appInitialize.o ${OBJECTDIR}/_ext/304469756/appApplication.o ${OBJECTDIR}/_ext/304469756/appMain.o ${OBJECTDIR}/_ext/304469756/appStateMachine.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosFsmService.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o ${OBJECTDIR}/_ext/1998561406/fsmState.o ${OBJECTDIR}/_ext/1998561406/fsmContext.o ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1439849346/appInitialize.o.d ${OBJECTDIR}/_ext/304469756/appApplication.o.d ${OBJECTDIR}/_ext/304469756/appMain.o.d ${OBJECTDIR}/_ext/304469756/appStateMachine.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halCN.o.d ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d ${OBJECTDIR}/_ext/863068963/eosFsmService.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/618460187/heap_4.o.d ${OBJECTDIR}/_ext/152460360/port.o.d ${OBJECTDIR}/_ext/152460360/port_asm.o.d ${OBJECTDIR}/_ext/1745914046/list.o.d ${OBJECTDIR}/_ext/1745914046/queue.o.d ${OBJECTDIR}/_ext/1745914046/tasks.o.d ${OBJECTDIR}/_ext/1745914046/timers.o.d ${OBJECTDIR}/_ext/1998561406/fsmState.o.d ${OBJECTDIR}/_ext/1998561406/fsmContext.o.d ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1439849346/appInitialize.o ${OBJECTDIR}/_ext/304469756/appApplication.o ${OBJECTDIR}/_ext/304469756/appMain.o ${OBJECTDIR}/_ext/304469756/appStateMachine.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosFsmService.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o ${OBJECTDIR}/_ext/1998561406/fsmState.o ${OBJECTDIR}/_ext/1998561406/fsmContext.o ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o

# Source Files
SOURCEFILES=../../../Source/StartUp/PIC32/main.cpp ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp ../../../Demo/FsmDemo/Source/appApplication.cpp ../../../Demo/FsmDemo/Source/appMain.cpp ../../../Demo/FsmDemo/Source/appStateMachine.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosFsmService.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c ../../../Demo/FsmDemo/Machine/fsmState.cpp ../../../Demo/FsmDemo/Machine/fsmContext.cpp ../../../Source/Services/Fsm/eosFsmContextBase.cpp ../../../Source/Services/Fsm/eosFsmStateBase.cpp



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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/618460187/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/618460187/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1745914046/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1439849346/appInitialize.o: ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1439849346" 
	@${RM} ${OBJECTDIR}/_ext/1439849346/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1439849346/appInitialize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1439849346/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1439849346/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1439849346/appInitialize.o ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appApplication.o: ../../../Demo/FsmDemo/Source/appApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appApplication.o.d" -o ${OBJECTDIR}/_ext/304469756/appApplication.o ../../../Demo/FsmDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appMain.o: ../../../Demo/FsmDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appMain.o.d" -o ${OBJECTDIR}/_ext/304469756/appMain.o ../../../Demo/FsmDemo/Source/appMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appStateMachine.o: ../../../Demo/FsmDemo/Source/appStateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appStateMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appStateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appStateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appStateMachine.o.d" -o ${OBJECTDIR}/_ext/304469756/appStateMachine.o ../../../Demo/FsmDemo/Source/appStateMachine.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosFsmService.o: ../../../Source/Services/eosFsmService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosFsmService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosFsmService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosFsmService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosFsmService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosFsmService.o ../../../Source/Services/eosFsmService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1998561406/fsmState.o: ../../../Demo/FsmDemo/Machine/fsmState.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1998561406" 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmState.o.d 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmState.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1998561406/fsmState.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1998561406/fsmState.o.d" -o ${OBJECTDIR}/_ext/1998561406/fsmState.o ../../../Demo/FsmDemo/Machine/fsmState.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1998561406/fsmContext.o: ../../../Demo/FsmDemo/Machine/fsmContext.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1998561406" 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmContext.o.d 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmContext.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1998561406/fsmContext.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1998561406/fsmContext.o.d" -o ${OBJECTDIR}/_ext/1998561406/fsmContext.o ../../../Demo/FsmDemo/Machine/fsmContext.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o: ../../../Source/Services/Fsm/eosFsmContextBase.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012509132" 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d" -o ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o ../../../Source/Services/Fsm/eosFsmContextBase.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o: ../../../Source/Services/Fsm/eosFsmStateBase.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012509132" 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d" -o ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o ../../../Source/Services/Fsm/eosFsmStateBase.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1439849346/appInitialize.o: ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1439849346" 
	@${RM} ${OBJECTDIR}/_ext/1439849346/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1439849346/appInitialize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1439849346/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1439849346/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1439849346/appInitialize.o ../../../Demo/FsmDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appApplication.o: ../../../Demo/FsmDemo/Source/appApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appApplication.o.d" -o ${OBJECTDIR}/_ext/304469756/appApplication.o ../../../Demo/FsmDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appMain.o: ../../../Demo/FsmDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appMain.o.d" -o ${OBJECTDIR}/_ext/304469756/appMain.o ../../../Demo/FsmDemo/Source/appMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/304469756/appStateMachine.o: ../../../Demo/FsmDemo/Source/appStateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/304469756" 
	@${RM} ${OBJECTDIR}/_ext/304469756/appStateMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/304469756/appStateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/304469756/appStateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/304469756/appStateMachine.o.d" -o ${OBJECTDIR}/_ext/304469756/appStateMachine.o ../../../Demo/FsmDemo/Source/appStateMachine.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/863068963/eosFsmService.o: ../../../Source/Services/eosFsmService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosFsmService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosFsmService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosFsmService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosFsmService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosFsmService.o ../../../Source/Services/eosFsmService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1998561406/fsmState.o: ../../../Demo/FsmDemo/Machine/fsmState.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1998561406" 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmState.o.d 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmState.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1998561406/fsmState.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1998561406/fsmState.o.d" -o ${OBJECTDIR}/_ext/1998561406/fsmState.o ../../../Demo/FsmDemo/Machine/fsmState.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/1998561406/fsmContext.o: ../../../Demo/FsmDemo/Machine/fsmContext.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1998561406" 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmContext.o.d 
	@${RM} ${OBJECTDIR}/_ext/1998561406/fsmContext.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1998561406/fsmContext.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1998561406/fsmContext.o.d" -o ${OBJECTDIR}/_ext/1998561406/fsmContext.o ../../../Demo/FsmDemo/Machine/fsmContext.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o: ../../../Source/Services/Fsm/eosFsmContextBase.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012509132" 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o.d" -o ${OBJECTDIR}/_ext/2012509132/eosFsmContextBase.o ../../../Source/Services/Fsm/eosFsmContextBase.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o: ../../../Source/Services/Fsm/eosFsmStateBase.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012509132" 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/FsmDemo/Include" -I"../../../Demo/FsmDemo/Include/PIC32" -I"../../../Demo/FsmDemo/Machine" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o.d" -o ${OBJECTDIR}/_ext/2012509132/eosFsmStateBase.o ../../../Source/Services/Fsm/eosFsmStateBase.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp=${DFP_DIR}
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp=${DFP_DIR}
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FsmServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_USB_STARTER_KIT_I
	${RM} -r dist/PIC32_USB_STARTER_KIT_I

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
