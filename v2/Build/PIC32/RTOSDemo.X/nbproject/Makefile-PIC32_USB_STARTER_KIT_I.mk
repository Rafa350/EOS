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
SOURCEFILES_QUOTED_IF_SPACED=../../../Source/OSAL/osalThread.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c ../../../Demo/RTOSDemo/rtos_hooks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c ../../../Demo/RTOSDemo/AppMain.c ../../../Demo/RTOSDemo/PIC32/Main.c ../../../Source/HAL/PIC32/halSYS.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1730818612/osalThread.o ${OBJECTDIR}/_ext/1545219271/tasks.o ${OBJECTDIR}/_ext/1683326351/port.o ${OBJECTDIR}/_ext/1683326351/port_asm.o ${OBJECTDIR}/_ext/1204364548/heap_4.o ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o ${OBJECTDIR}/_ext/1545219271/list.o ${OBJECTDIR}/_ext/1545219271/queue.o ${OBJECTDIR}/_ext/1282550982/AppMain.o ${OBJECTDIR}/_ext/2146455232/Main.o ${OBJECTDIR}/_ext/346134360/halSYS.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1730818612/osalThread.o.d ${OBJECTDIR}/_ext/1545219271/tasks.o.d ${OBJECTDIR}/_ext/1683326351/port.o.d ${OBJECTDIR}/_ext/1683326351/port_asm.o.d ${OBJECTDIR}/_ext/1204364548/heap_4.o.d ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d ${OBJECTDIR}/_ext/1545219271/list.o.d ${OBJECTDIR}/_ext/1545219271/queue.o.d ${OBJECTDIR}/_ext/1282550982/AppMain.o.d ${OBJECTDIR}/_ext/2146455232/Main.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1730818612/osalThread.o ${OBJECTDIR}/_ext/1545219271/tasks.o ${OBJECTDIR}/_ext/1683326351/port.o ${OBJECTDIR}/_ext/1683326351/port_asm.o ${OBJECTDIR}/_ext/1204364548/heap_4.o ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o ${OBJECTDIR}/_ext/1545219271/list.o ${OBJECTDIR}/_ext/1545219271/queue.o ${OBJECTDIR}/_ext/1282550982/AppMain.o ${OBJECTDIR}/_ext/2146455232/Main.o ${OBJECTDIR}/_ext/346134360/halSYS.o

# Source Files
SOURCEFILES=../../../Source/OSAL/osalThread.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c ../../../Demo/RTOSDemo/rtos_hooks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c ../../../Demo/RTOSDemo/AppMain.c ../../../Demo/RTOSDemo/PIC32/Main.c ../../../Source/HAL/PIC32/halSYS.c


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
${OBJECTDIR}/_ext/1683326351/port_asm.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.ok ${OBJECTDIR}/_ext/1683326351/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port_asm.o.d" "${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -DSKDEPIC32PlatformTool=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"../../../Demo/RTOSDemo/PIC32" -MMD -MF "${OBJECTDIR}/_ext/1683326351/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1683326351/port_asm.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=SKDEPIC32PlatformTool=1
	
else
${OBJECTDIR}/_ext/1683326351/port_asm.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.ok ${OBJECTDIR}/_ext/1683326351/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port_asm.o.d" "${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"../../../Demo/RTOSDemo/PIC32" -MMD -MF "${OBJECTDIR}/_ext/1683326351/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1683326351/port_asm.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1730818612/osalThread.o: ../../../Source/OSAL/osalThread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalThread.o ../../../Source/OSAL/osalThread.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/tasks.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/tasks.o.d" -o ${OBJECTDIR}/_ext/1545219271/tasks.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1683326351/port.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1683326351/port.o.d" -o ${OBJECTDIR}/_ext/1683326351/port.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1204364548/heap_4.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1204364548" 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" -o ${OBJECTDIR}/_ext/1204364548/heap_4.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1282550982/rtos_hooks.o: ../../../Demo/RTOSDemo/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o ../../../Demo/RTOSDemo/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/list.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/list.o.d" -o ${OBJECTDIR}/_ext/1545219271/list.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/queue.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/queue.o.d" -o ${OBJECTDIR}/_ext/1545219271/queue.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1282550982/AppMain.o: ../../../Demo/RTOSDemo/AppMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" -o ${OBJECTDIR}/_ext/1282550982/AppMain.o ../../../Demo/RTOSDemo/AppMain.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2146455232/Main.o: ../../../Demo/RTOSDemo/PIC32/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2146455232" 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146455232/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/2146455232/Main.o.d" -o ${OBJECTDIR}/_ext/2146455232/Main.o ../../../Demo/RTOSDemo/PIC32/Main.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1730818612/osalThread.o: ../../../Source/OSAL/osalThread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalThread.o ../../../Source/OSAL/osalThread.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/tasks.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/tasks.o.d" -o ${OBJECTDIR}/_ext/1545219271/tasks.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1683326351/port.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1683326351/port.o.d" -o ${OBJECTDIR}/_ext/1683326351/port.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1204364548/heap_4.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1204364548" 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" -o ${OBJECTDIR}/_ext/1204364548/heap_4.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1282550982/rtos_hooks.o: ../../../Demo/RTOSDemo/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1282550982/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1282550982/rtos_hooks.o ../../../Demo/RTOSDemo/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/list.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/list.o.d" -o ${OBJECTDIR}/_ext/1545219271/list.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/queue.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1545219271/queue.o.d" -o ${OBJECTDIR}/_ext/1545219271/queue.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1282550982/AppMain.o: ../../../Demo/RTOSDemo/AppMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1282550982" 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282550982/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/1282550982/AppMain.o.d" -o ${OBJECTDIR}/_ext/1282550982/AppMain.o ../../../Demo/RTOSDemo/AppMain.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2146455232/Main.o: ../../../Demo/RTOSDemo/PIC32/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2146455232" 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2146455232/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146455232/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/2146455232/Main.o.d" -o ${OBJECTDIR}/_ext/2146455232/Main.o ../../../Demo/RTOSDemo/PIC32/Main.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -I"../../../Demo/RTOSDemo" -I"../../../Demo/RTOSDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"C:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -I"C:/Library/Microchip/Harmony/v1.9/framework" -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../Library/Microchip/Harmony/v1.9/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSKDEPIC32PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\Library\Microchip\Harmony\v1.9\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=SKDEPIC32PlatformTool=1,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../Library/Microchip/Harmony/v1.9/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\Library\Microchip\Harmony\v1.9\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
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
