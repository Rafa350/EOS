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
ifeq "$(wildcard nbproject/Makefile-local-PINGUINO.mk)" "nbproject/Makefile-local-PINGUINO.mk"
include nbproject/Makefile-local-PINGUINO.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PINGUINO
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Config.cpp ../Main.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../rtos_hooks.c ../../../Source/HAL/halSYS.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1481326433/tasks.o ${OBJECTDIR}/_ext/1481326433/queue.o ${OBJECTDIR}/_ext/1481326433/list.o ${OBJECTDIR}/_ext/1481326433/timers.o ${OBJECTDIR}/_ext/836116151/port.o ${OBJECTDIR}/_ext/836116151/port_asm.o ${OBJECTDIR}/_ext/1942712868/heap_4.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/55825582/halSYS.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1481326433/tasks.o.d ${OBJECTDIR}/_ext/1481326433/queue.o.d ${OBJECTDIR}/_ext/1481326433/list.o.d ${OBJECTDIR}/_ext/1481326433/timers.o.d ${OBJECTDIR}/_ext/836116151/port.o.d ${OBJECTDIR}/_ext/836116151/port_asm.o.d ${OBJECTDIR}/_ext/1942712868/heap_4.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/55825582/halSYS.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1481326433/tasks.o ${OBJECTDIR}/_ext/1481326433/queue.o ${OBJECTDIR}/_ext/1481326433/list.o ${OBJECTDIR}/_ext/1481326433/timers.o ${OBJECTDIR}/_ext/836116151/port.o ${OBJECTDIR}/_ext/836116151/port_asm.o ${OBJECTDIR}/_ext/1942712868/heap_4.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/55825582/halSYS.o

# Source Files
SOURCEFILES=../Config.cpp ../Main.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../rtos_hooks.c ../../../Source/HAL/halSYS.c


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
	${MAKE}  -f nbproject/Makefile-PINGUINO.mk dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/836116151/port_asm.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.ok ${OBJECTDIR}/_ext/836116151/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port_asm.o.d" "${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port_asm.o.d"  -o ${OBJECTDIR}/_ext/836116151/port_asm.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1
	
else
${OBJECTDIR}/_ext/836116151/port_asm.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.ok ${OBJECTDIR}/_ext/836116151/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port_asm.o.d" "${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port_asm.o.d"  -o ${OBJECTDIR}/_ext/836116151/port_asm.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1481326433/tasks.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/tasks.o.d" -o ${OBJECTDIR}/_ext/1481326433/tasks.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/1481326433/queue.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/queue.o.d" -o ${OBJECTDIR}/_ext/1481326433/queue.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/1481326433/list.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/list.o.d" -o ${OBJECTDIR}/_ext/1481326433/list.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/1481326433/timers.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/timers.o.d" -o ${OBJECTDIR}/_ext/1481326433/timers.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/836116151/port.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port.o.d" -o ${OBJECTDIR}/_ext/836116151/port.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1942712868/heap_4.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1942712868" 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" -o ${OBJECTDIR}/_ext/1942712868/heap_4.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c   
	
else
${OBJECTDIR}/_ext/1481326433/tasks.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/tasks.o.d" -o ${OBJECTDIR}/_ext/1481326433/tasks.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/1481326433/queue.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/queue.o.d" -o ${OBJECTDIR}/_ext/1481326433/queue.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/1481326433/list.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/list.o.d" -o ${OBJECTDIR}/_ext/1481326433/list.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/1481326433/timers.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1481326433/timers.o.d" -o ${OBJECTDIR}/_ext/1481326433/timers.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/836116151/port.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port.o.d" -o ${OBJECTDIR}/_ext/836116151/port.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1942712868/heap_4.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1942712868" 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" -o ${OBJECTDIR}/_ext/1942712868/heap_4.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp  
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp  
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp  
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  
	
else
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp  
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp  
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp  
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=32000,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=32000,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PINGUINO
	${RM} -r dist/PINGUINO

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
