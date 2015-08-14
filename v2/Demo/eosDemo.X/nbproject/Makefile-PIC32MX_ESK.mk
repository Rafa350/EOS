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
ifeq "$(wildcard nbproject/Makefile-local-PIC32MX_ESK.mk)" "nbproject/Makefile-local-PIC32MX_ESK.mk"
include nbproject/Makefile-local-PIC32MX_ESK.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32MX_ESK
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../Source/System/eosKernel.c ../../Source/System/eosStart.c ../Main.c ../Config.c C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c ../rtos_hooks.c ../../Source/System/eosTask.c ../../Source/System/eosHeap.c ../../Source/Services/eosDigOutput.c ../../Source/Services/eosTick.c ../../Source/Services/eosTickISRWrapper.S

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1479454979/eosKernel.o ${OBJECTDIR}/_ext/1479454979/eosStart.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/746221417/sys_devcon.o ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o ${OBJECTDIR}/_ext/1208317312/port.o ${OBJECTDIR}/_ext/1208317312/port_asm.o ${OBJECTDIR}/_ext/1501210797/heap_4.o ${OBJECTDIR}/_ext/565814006/croutine.o ${OBJECTDIR}/_ext/565814006/event_groups.o ${OBJECTDIR}/_ext/565814006/list.o ${OBJECTDIR}/_ext/565814006/queue.o ${OBJECTDIR}/_ext/565814006/tasks.o ${OBJECTDIR}/_ext/565814006/timers.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1479454979/eosTask.o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosTick.o ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1479454979/eosKernel.o.d ${OBJECTDIR}/_ext/1479454979/eosStart.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/746221417/sys_devcon.o.d ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d ${OBJECTDIR}/_ext/1208317312/port.o.d ${OBJECTDIR}/_ext/1208317312/port_asm.o.d ${OBJECTDIR}/_ext/1501210797/heap_4.o.d ${OBJECTDIR}/_ext/565814006/croutine.o.d ${OBJECTDIR}/_ext/565814006/event_groups.o.d ${OBJECTDIR}/_ext/565814006/list.o.d ${OBJECTDIR}/_ext/565814006/queue.o.d ${OBJECTDIR}/_ext/565814006/tasks.o.d ${OBJECTDIR}/_ext/565814006/timers.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/1479454979/eosTask.o.d ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d ${OBJECTDIR}/_ext/474813902/eosTick.o.d ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1479454979/eosKernel.o ${OBJECTDIR}/_ext/1479454979/eosStart.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/746221417/sys_devcon.o ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o ${OBJECTDIR}/_ext/1208317312/port.o ${OBJECTDIR}/_ext/1208317312/port_asm.o ${OBJECTDIR}/_ext/1501210797/heap_4.o ${OBJECTDIR}/_ext/565814006/croutine.o ${OBJECTDIR}/_ext/565814006/event_groups.o ${OBJECTDIR}/_ext/565814006/list.o ${OBJECTDIR}/_ext/565814006/queue.o ${OBJECTDIR}/_ext/565814006/tasks.o ${OBJECTDIR}/_ext/565814006/timers.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1479454979/eosTask.o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosTick.o ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o

# Source Files
SOURCEFILES=../../Source/System/eosKernel.c ../../Source/System/eosStart.c ../Main.c ../Config.c C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c ../rtos_hooks.c ../../Source/System/eosTask.c ../../Source/System/eosHeap.c ../../Source/Services/eosDigOutput.c ../../Source/Services/eosTick.c ../../Source/Services/eosTickISRWrapper.S


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
	${MAKE}  -f nbproject/Makefile-PIC32MX_ESK.mk dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1208317312/port_asm.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.ok ${OBJECTDIR}/_ext/1208317312/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port_asm.o.d" "${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1208317312/port_asm.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o: ../../Source/Services/eosTickISRWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.ok ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d" "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d"  -o ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o ../../Source/Services/eosTickISRWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/1208317312/port_asm.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.ok ${OBJECTDIR}/_ext/1208317312/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port_asm.o.d" "${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1208317312/port_asm.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d",--gdwarf-2,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o: ../../Source/Services/eosTickISRWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.ok ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d" "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.d"  -o ${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o ../../Source/Services/eosTickISRWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/474813902/eosTickISRWrapper.o.asm.d",--gdwarf-2,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1479454979/eosKernel.o: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ../../Source/System/eosKernel.c   
	
${OBJECTDIR}/_ext/1479454979/eosStart.o: ../../Source/System/eosStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosStart.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosStart.o ../../Source/System/eosStart.c   
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c   
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/746221417/sys_devcon.o: C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/746221417" 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/746221417/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/746221417/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/746221417/sys_devcon.o C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c   
	
${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o: C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/746221417" 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c   
	
${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o: C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1817942673" 
	@${RM} ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/1208317312/port.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port.o.d" -o ${OBJECTDIR}/_ext/1208317312/port.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1501210797/heap_4.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1501210797" 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" -o ${OBJECTDIR}/_ext/1501210797/heap_4.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/565814006/croutine.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/croutine.o.d" -o ${OBJECTDIR}/_ext/565814006/croutine.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/_ext/565814006/event_groups.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/event_groups.o.d" -o ${OBJECTDIR}/_ext/565814006/event_groups.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c   
	
${OBJECTDIR}/_ext/565814006/list.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/list.o.d" -o ${OBJECTDIR}/_ext/565814006/list.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/565814006/queue.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/queue.o.d" -o ${OBJECTDIR}/_ext/565814006/queue.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/565814006/tasks.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/tasks.o.d" -o ${OBJECTDIR}/_ext/565814006/tasks.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/565814006/timers.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/timers.o.d" -o ${OBJECTDIR}/_ext/565814006/timers.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1479454979/eosTask.o: ../../Source/System/eosTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosTask.o ../../Source/System/eosTask.c   
	
${OBJECTDIR}/_ext/1479454979/eosHeap.o: ../../Source/System/eosHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ../../Source/System/eosHeap.c   
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.c   
	
${OBJECTDIR}/_ext/474813902/eosTick.o: ../../Source/Services/eosTick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTick.o.d" -o ${OBJECTDIR}/_ext/474813902/eosTick.o ../../Source/Services/eosTick.c   
	
else
${OBJECTDIR}/_ext/1479454979/eosKernel.o: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ../../Source/System/eosKernel.c   
	
${OBJECTDIR}/_ext/1479454979/eosStart.o: ../../Source/System/eosStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosStart.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosStart.o ../../Source/System/eosStart.c   
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c   
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/746221417/sys_devcon.o: C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/746221417" 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/746221417/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/746221417/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/746221417/sys_devcon.o C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon.c   
	
${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o: C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/746221417" 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/746221417/sys_devcon_pic32mx.o C:/microchip/harmony/v1_05/framework/system/devcon/src/sys_devcon_pic32mx.c   
	
${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o: C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1817942673" 
	@${RM} ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1817942673/sys_int_pic32.o C:/microchip/harmony/v1_05/framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/1208317312/port.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port.o.d" -o ${OBJECTDIR}/_ext/1208317312/port.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1501210797/heap_4.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1501210797" 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" -o ${OBJECTDIR}/_ext/1501210797/heap_4.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/565814006/croutine.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/croutine.o.d" -o ${OBJECTDIR}/_ext/565814006/croutine.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/_ext/565814006/event_groups.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/event_groups.o.d" -o ${OBJECTDIR}/_ext/565814006/event_groups.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/event_groups.c   
	
${OBJECTDIR}/_ext/565814006/list.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/list.o.d" -o ${OBJECTDIR}/_ext/565814006/list.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/565814006/queue.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/queue.o.d" -o ${OBJECTDIR}/_ext/565814006/queue.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/565814006/tasks.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/tasks.o.d" -o ${OBJECTDIR}/_ext/565814006/tasks.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/565814006/timers.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/timers.o.d" -o ${OBJECTDIR}/_ext/565814006/timers.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1479454979/eosTask.o: ../../Source/System/eosTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosTask.o ../../Source/System/eosTask.c   
	
${OBJECTDIR}/_ext/1479454979/eosHeap.o: ../../Source/System/eosHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ../../Source/System/eosHeap.c   
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.c   
	
${OBJECTDIR}/_ext/474813902/eosTick.o: ../../Source/Services/eosTick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTick.o.d" -o ${OBJECTDIR}/_ext/474813902/eosTick.o ../../Source/Services/eosTick.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:/microchip/harmony/v1_05/bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v1_05\bin\framework\peripheral\PIC32MX795F512L_peripherals.a          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:/microchip/harmony/v1_05/bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v1_05\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32MX_ESK
	${RM} -r dist/PIC32MX_ESK

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
