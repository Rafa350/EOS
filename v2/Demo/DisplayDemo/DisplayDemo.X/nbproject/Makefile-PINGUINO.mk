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

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Config.cpp ../Main.cpp ../rtos_hooks.c ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/eosFont.cpp ../../../Source/HAL/halSYS.c ../../../Source/Services/eosAppLoop.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Collections/eosQueue.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/771906982/Arial10pt.o ${OBJECTDIR}/_ext/771906982/Arial12pt.o ${OBJECTDIR}/_ext/771906982/Arial24pt.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/2094700795/eosFont.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1156436454/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1942712868/heap_4.o ${OBJECTDIR}/_ext/836116151/port.o ${OBJECTDIR}/_ext/836116151/port_asm.o ${OBJECTDIR}/_ext/1481326433/tasks.o ${OBJECTDIR}/_ext/1481326433/queue.o ${OBJECTDIR}/_ext/1481326433/list.o ${OBJECTDIR}/_ext/1481326433/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d ${OBJECTDIR}/_ext/771906982/Arial10pt.o.d ${OBJECTDIR}/_ext/771906982/Arial12pt.o.d ${OBJECTDIR}/_ext/771906982/Arial24pt.o.d ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d ${OBJECTDIR}/_ext/2094700795/eosFont.o.d ${OBJECTDIR}/_ext/55825582/halSYS.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d ${OBJECTDIR}/_ext/1156436454/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1942712868/heap_4.o.d ${OBJECTDIR}/_ext/836116151/port.o.d ${OBJECTDIR}/_ext/836116151/port_asm.o.d ${OBJECTDIR}/_ext/1481326433/tasks.o.d ${OBJECTDIR}/_ext/1481326433/queue.o.d ${OBJECTDIR}/_ext/1481326433/list.o.d ${OBJECTDIR}/_ext/1481326433/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/771906982/Arial10pt.o ${OBJECTDIR}/_ext/771906982/Arial12pt.o ${OBJECTDIR}/_ext/771906982/Arial24pt.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/2094700795/eosFont.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1156436454/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1942712868/heap_4.o ${OBJECTDIR}/_ext/836116151/port.o ${OBJECTDIR}/_ext/836116151/port_asm.o ${OBJECTDIR}/_ext/1481326433/tasks.o ${OBJECTDIR}/_ext/1481326433/queue.o ${OBJECTDIR}/_ext/1481326433/list.o ${OBJECTDIR}/_ext/1481326433/timers.o

# Source Files
SOURCEFILES=../Config.cpp ../Main.cpp ../rtos_hooks.c ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/eosFont.cpp ../../../Source/HAL/halSYS.c ../../../Source/Services/eosAppLoop.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Collections/eosQueue.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c


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

MP_PROCESSOR_OPTION=32MX440F256H
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port_asm.o.d" "${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO_MICRO -I"../" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port_asm.o.d"  -o ${OBJECTDIR}/_ext/836116151/port_asm.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/836116151/port_asm.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/836116151/port_asm.o.ok ${OBJECTDIR}/_ext/836116151/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port_asm.o.d" "${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO_MICRO -I"../" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/836116151/port_asm.o.d"  -o ${OBJECTDIR}/_ext/836116151/port_asm.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/836116151/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1942712868/heap_4.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1942712868" 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" -o ${OBJECTDIR}/_ext/1942712868/heap_4.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/836116151/port.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/836116151/port.o.d" -o ${OBJECTDIR}/_ext/836116151/port.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/tasks.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/tasks.o.d" -o ${OBJECTDIR}/_ext/1481326433/tasks.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/queue.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/queue.o.d" -o ${OBJECTDIR}/_ext/1481326433/queue.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/list.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/list.o.d" -o ${OBJECTDIR}/_ext/1481326433/list.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/timers.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/timers.o.d" -o ${OBJECTDIR}/_ext/1481326433/timers.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1942712868/heap_4.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1942712868" 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1942712868/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1942712868/heap_4.o.d" -o ${OBJECTDIR}/_ext/1942712868/heap_4.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/836116151/port.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/836116151" 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/836116151/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/836116151/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/836116151/port.o.d" -o ${OBJECTDIR}/_ext/836116151/port.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/tasks.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/tasks.o.d" -o ${OBJECTDIR}/_ext/1481326433/tasks.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/queue.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/queue.o.d" -o ${OBJECTDIR}/_ext/1481326433/queue.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/list.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/list.o.d" -o ${OBJECTDIR}/_ext/1481326433/list.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1481326433/timers.o: ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1481326433" 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1481326433/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481326433/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"C:/microchip/harmony/v1_06_01/framework" -MMD -MF "${OBJECTDIR}/_ext/1481326433/timers.o.d" -o ${OBJECTDIR}/_ext/1481326433/timers.o ../../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial10pt.o: ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial10pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial10pt.o ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial12pt.o: ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial12pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial12pt.o ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial24pt.o: ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial24pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial24pt.o ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosFont.o: ../../../Source/Controllers/Display/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosFont.o ../../../Source/Controllers/Display/eosFont.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosQueue.o: ../../../Source/System/Collections/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosQueue.o ../../../Source/System/Collections/eosQueue.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial10pt.o: ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial10pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial10pt.o ../../../Source/Controllers/Display/Fonts/Arial10pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial12pt.o: ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial12pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial12pt.o ../../../Source/Controllers/Display/Fonts/Arial12pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Arial24pt.o: ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Arial24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Arial24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/771906982/Arial24pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Arial24pt.o ../../../Source/Controllers/Display/Fonts/Arial24pt.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosFont.o: ../../../Source/Controllers/Display/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosFont.o ../../../Source/Controllers/Display/eosFont.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosQueue.o: ../../../Source/System/Collections/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosQueue.o ../../../Source/System/Collections/eosQueue.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO_MICRO -I"../" -I"../../../Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/harmony/v1_06_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\harmony\v1_06_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/harmony/v1_06_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\harmony\v1_06_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
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