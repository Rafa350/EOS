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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../Main.cpp ../rtos_hooks.c ../Config.cpp ../../../Source/HAL/halSYS.c ../../../Source/Services/Usb/eosUsbClient.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c ../../../Source/Services/Usb/eosUsbHarmony.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/2129976512/tasks.o ${OBJECTDIR}/_ext/2129976512/queue.o ${OBJECTDIR}/_ext/2129976512/timers.o ${OBJECTDIR}/_ext/1298945782/port.o ${OBJECTDIR}/_ext/1298945782/port_asm.o ${OBJECTDIR}/_ext/696550819/heap_4.o ${OBJECTDIR}/_ext/2129976512/list.o ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/55825582/halSYS.o.d ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/2129976512/tasks.o.d ${OBJECTDIR}/_ext/2129976512/queue.o.d ${OBJECTDIR}/_ext/2129976512/timers.o.d ${OBJECTDIR}/_ext/1298945782/port.o.d ${OBJECTDIR}/_ext/1298945782/port_asm.o.d ${OBJECTDIR}/_ext/696550819/heap_4.o.d ${OBJECTDIR}/_ext/2129976512/list.o.d ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/2129976512/tasks.o ${OBJECTDIR}/_ext/2129976512/queue.o ${OBJECTDIR}/_ext/2129976512/timers.o ${OBJECTDIR}/_ext/1298945782/port.o ${OBJECTDIR}/_ext/1298945782/port_asm.o ${OBJECTDIR}/_ext/696550819/heap_4.o ${OBJECTDIR}/_ext/2129976512/list.o ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o

# Source Files
SOURCEFILES=../Main.cpp ../rtos_hooks.c ../Config.cpp ../../../Source/HAL/halSYS.c ../../../Source/Services/Usb/eosUsbClient.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c ../../../Source/Services/Usb/eosUsbHarmony.c


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
	${MAKE}  -f nbproject/Makefile-PINGUINO.mk dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1298945782/port_asm.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.ok ${OBJECTDIR}/_ext/1298945782/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port_asm.o.d" "${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1298945782/port_asm.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/1298945782/port_asm.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.ok ${OBJECTDIR}/_ext/1298945782/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port_asm.o.d" "${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1298945782/port_asm.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d",--gdwarf-2 -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/tasks.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/tasks.o.d" -o ${OBJECTDIR}/_ext/2129976512/tasks.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/queue.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/queue.o.d" -o ${OBJECTDIR}/_ext/2129976512/queue.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/timers.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/timers.o.d" -o ${OBJECTDIR}/_ext/2129976512/timers.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1298945782/port.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port.o.d" -o ${OBJECTDIR}/_ext/1298945782/port.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/696550819/heap_4.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/696550819" 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/696550819/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/696550819/heap_4.o.d" -o ${OBJECTDIR}/_ext/696550819/heap_4.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/list.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/list.o.d" -o ${OBJECTDIR}/_ext/2129976512/list.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o: ../../../Source/Services/Usb/eosUsbHarmony.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o ../../../Source/Services/Usb/eosUsbHarmony.c    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/tasks.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/tasks.o.d" -o ${OBJECTDIR}/_ext/2129976512/tasks.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/queue.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/queue.o.d" -o ${OBJECTDIR}/_ext/2129976512/queue.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/timers.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/timers.o.d" -o ${OBJECTDIR}/_ext/2129976512/timers.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1298945782/port.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port.o.d" -o ${OBJECTDIR}/_ext/1298945782/port.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/696550819/heap_4.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/696550819" 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/696550819/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/696550819/heap_4.o.d" -o ${OBJECTDIR}/_ext/696550819/heap_4.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/list.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/list.o.d" -o ${OBJECTDIR}/_ext/2129976512/list.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o: ../../../Source/Services/Usb/eosUsbHarmony.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbHarmony.o ../../../Source/Services/Usb/eosUsbHarmony.c    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbClient.o: ../../../Source/Services/Usb/eosUsbClient.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o ../../../Source/Services/Usb/eosUsbClient.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbClient.o: ../../../Source/Services/Usb/eosUsbClient.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbClient.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbClient.o ../../../Source/Services/Usb/eosUsbClient.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../" -I"../../" -I"../../../Include" -I"c:/microchip/harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/harmony/v1_07_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\harmony\v1_07_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/harmony/v1_07_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\harmony\v1_07_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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