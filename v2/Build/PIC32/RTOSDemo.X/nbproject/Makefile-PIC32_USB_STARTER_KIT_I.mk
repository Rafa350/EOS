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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/RTOSDemo/PIC32/Main.c ../../../Demo/RTOSDemo/AppMain.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2146455232/Main.o ${OBJECTDIR}/_ext/1282550982/AppMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1199125522/heap_4.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2146455232/Main.o.d ${OBJECTDIR}/_ext/1282550982/AppMain.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/list.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2146455232/Main.o ${OBJECTDIR}/_ext/1282550982/AppMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1199125522/heap_4.o

# Source Files
SOURCEFILES=../../../Demo/RTOSDemo/PIC32/Main.c ../../../Demo/RTOSDemo/AppMain.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c


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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2146455232/Main.o: ../../../Demo/RTOSDemo/PIC32/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2146455232" 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146455232/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2146455232/Main.o.d" -o ${OBJECTDIR}/_ext/2146455232/Main.o ../../../Demo/RTOSDemo/PIC32/Main.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1282550982/AppMain.o: ../../../Demo/RTOSDemo/AppMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" -o ${OBJECTDIR}/_ext/1282550982/AppMain.o ../../../Demo/RTOSDemo/AppMain.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
else
${OBJECTDIR}/_ext/2146455232/Main.o: ../../../Demo/RTOSDemo/PIC32/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2146455232" 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146455232/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2146455232/Main.o.d" -o ${OBJECTDIR}/_ext/2146455232/Main.o ../../../Demo/RTOSDemo/PIC32/Main.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1282550982/AppMain.o: ../../../Demo/RTOSDemo/AppMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" -o ${OBJECTDIR}/_ext/1282550982/AppMain.o ../../../Demo/RTOSDemo/AppMain.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/Portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
