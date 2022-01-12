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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o.d ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d ${OBJECTDIR}/_ext/2104168611/AppMain.o.d ${OBJECTDIR}/_ext/2104168611/appApplication.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halCN.o.d ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalMutex.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/618460187/heap_4.o.d ${OBJECTDIR}/_ext/152460360/port.o.d ${OBJECTDIR}/_ext/152460360/port_asm.o.d ${OBJECTDIR}/_ext/1745914046/list.o.d ${OBJECTDIR}/_ext/1745914046/queue.o.d ${OBJECTDIR}/_ext/1745914046/tasks.o.d ${OBJECTDIR}/_ext/1745914046/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o

# Source Files
SOURCEFILES=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c



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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2cda832d6aa109524e1f328708e5af3f376c862 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2346f0641f58cf2a7e63dbfc1336928b4678f443 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fd3c3059d03028723ee1739be282f27e2e1c7830 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c421e4031ac220aaa3a6e26d74d0a362697b5b31 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5336a3175a6327da407ab2ba111f61b825ff25a9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--gdwarf-2,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2fbae9e8d8a6d92b56ba1e1ee1cd0ea40d41cb04 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--gdwarf-2,-I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/700cb2104f42d19f784b215d3b015ff382840763 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/394c345447a24116f1dbe33e4621afb1fc810a43 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5a0cc0b804606c7d9da4151c18f61fad6fadab30 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7434754908b96d94e1df939d7d6ba9856226c6dc .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2078dc4b74a88e0871cd9631171bf318dfc32fa5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4d481f83c113c199f7111f140c85a8f17d7485d3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c710f67f2d38fcd45975536efb41284b0df0dd1b .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4628d7f1fae720229276961c33b44152bfa8b643 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/32a6fd30f2569db0cedd01006bfad286a527eb19 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7367f003e8f0882764a9766d362e5e84621a9aca .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/acc177e842444b785716f06352222666cd30b217 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ae53d38beef1f920933815154b7b28088e3e2eb4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8dce8b9d8d8632f622d3c5abcc628bfc6dff645d .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7ad6e33e3fab786d720317daa42bf0165a4df507 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/206e598d64371eb2cbb58ca173ef9d8cb42d23b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e27ee410f999b907c64b7a47c314c72df6ebad37 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/80e853500ee098526f21b53e214e7f023e946e0f .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c0d610df0de112483bcedccb97acb94668e15b6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f568f48365338baeabc3730a0cae84ca1a794cb9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7d1f137f77d76ed7b7507346440067513f132adf .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6176c110d7e085da816222dcfb1731582f17063c .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/998eb439d73914ae427b42b4ce41523057421d01 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8d8fa251f1425bca4de4b7c6c52fb97dd92de329 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/38f2a3e200ba9ee7679f7d887b86e13cbcdf8093 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dc0cd0cc1db3a980381a9759a35d1854025bca44 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2df8dfbcb78369aeb55068e212c8aca6e7bebb66 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/df9e9e243c24fff6ce9e8694098e00940b777f51 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fe7a953d35ba91c4723447d5927f9943509d8caa .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/427fdd2c0ffba70460c79d8be9f522e2ef4db219 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6f52cac68f1c696e595640eaa213513ff2a7cc6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c58f4017f6228c9e59bce7a4eda696105d67aec6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/663ebcf09823e07b939691cab28198e462396c80 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/110d2a6f6b8992045c313b630806bf47e717d014 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3d283f1e70a449115da5dc1ebc366643e72b65a6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/306df47f2887e6f19dc0ebcf41d6a1177828b880 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cd78a0ee11f825182904f714a143131c1d1c6f6e .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6e33a912dd1cf4f11b99c43e6e440fae803fa926 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cdd1ca848b8e21b68718f074f6c946280e41c26 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3c53dadbe9fdf6d948a4fe365a5847bab0212a27 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4b2256501c95df575da430cd5709ae8758a6a6cf .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f57cc6a921eabc4d8a1f0200794e6aa7a0725c6a .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/35d6f7b86aa221437e8e1a40edcb6615eb3c6e92 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f1e274b46f163624ead2bac06dff0b4c86b771f5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2d22dae4ce30565258d597aa6bc5e39e6eadc9e0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9b4c38385978b2a9b5617dbf9602d37999783e0f .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6cad8137e66218498556241c8142071f3ef3034b .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2d34616cb392ae4856e2e69ac6511b7eaa3237f6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d793b578bf0dd4d1ad9922b99efeb91602a77f6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1dc416e88629c75623d082bc2fc691b1a084752f .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/511fd59786d92f01798367daaf5d48f3641f8a95 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/59ff02a0d2a15c2e5db8e4c8820247d80ed3addc .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b3987617da598831442c08c9ed50426b9dc66fb7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d6ee049ae38327da39fc16ee884961a9580ea96e .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f5b5b2eebae018b95fefa9bede958cf38d7fbf8c .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fbfc6f7201723500366198f6917a5ef2c0d112b8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/31771f7f669bf24e6ea22ab7d246f3d420086f67 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/40bd7feb6961d30d5bb4b0f99b89929f2f5a197d .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4b9bac95631099f57edd399a78dbe7f98c29b856 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/eb697770ef9fb05ffaf599ad25f86a38a0906b05 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f746062f0db78d83cab4f5f9b0c4b6372cbcbeac .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8e3a9b9a1ca204c8036413cc30f6f5eaf33bd4ef .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1e388caff7ff8b0d8138cf92b4d74f8508e55359 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7f2f9958b9b4c3411c66c0170c5d7fc4a63a9204 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4108026cdecfef6143fcb5e1087991810e0a963e .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/85417a340d13d55177a5686f736d98e076999d7f .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ae0f9c33fcfbdd429f96eef88b2c97dbd75bcaba .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/69282ef205c08e92d3945393759dc34c82093c81 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b9419d0ebc7587dbe08c663870911573c4eba8c3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f38fc24debd200365572e31df96c993fbb06278b .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/68415da16a004adc1845e1bf2ee704dd609e8093 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/39fb322fd3efe72e2f5abdf696b81790da86b8ac .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/db24c00524452af8c9e0adf51163930602c9dc91 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/25947148d983ff646fd7053db5fd6efe914363c0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9874a8c2f14ce238cf2921706e2976c4baa67b76 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4720dbcf3bc3a7ad8b0a9b7de97d19d2f45ea270 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/195224ea52fd650ac527eb81f82a5933dc6e6e31 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7e908c067d2568e155905776597878e20b009856 .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1a5b1e3ef0d871f3d33ac74f88bea551d453fd2c .generated_files/flags/PIC32_USB_STARTER_KIT_I/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu++17 -mdfp="${DFP_DIR}"  
	
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
