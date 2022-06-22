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
FINAL_IMAGE=${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp ../../../Demo/MonoDisplayDemo/Source/appMain.cpp ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosFontCache.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/437380671/appInitialize.o ${OBJECTDIR}/_ext/1484845179/appApplication.o ${OBJECTDIR}/_ext/1484845179/appMain.o ${OBJECTDIR}/_ext/1484845179/appLedService.o ${OBJECTDIR}/_ext/1484845179/appDisplayService.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/212539067/FontTable.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosFontCache.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/437380671/appInitialize.o.d ${OBJECTDIR}/_ext/1484845179/appApplication.o.d ${OBJECTDIR}/_ext/1484845179/appMain.o.d ${OBJECTDIR}/_ext/1484845179/appLedService.o.d ${OBJECTDIR}/_ext/1484845179/appDisplayService.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/212539067/FontTable.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d ${OBJECTDIR}/_ext/1486223398/eosRect.o.d ${OBJECTDIR}/_ext/1486223398/eosSize.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d ${OBJECTDIR}/_ext/1486223398/eosColor.o.d ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d ${OBJECTDIR}/_ext/1486223398/eosFont.o.d ${OBJECTDIR}/_ext/1486223398/eosFontCache.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/list.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/437380671/appInitialize.o ${OBJECTDIR}/_ext/1484845179/appApplication.o ${OBJECTDIR}/_ext/1484845179/appMain.o ${OBJECTDIR}/_ext/1484845179/appLedService.o ${OBJECTDIR}/_ext/1484845179/appDisplayService.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/212539067/FontTable.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosFontCache.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o

# Source Files
SOURCEFILES=../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp ../../../Demo/MonoDisplayDemo/Source/appMain.cpp ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosFontCache.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp



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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk ${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ddab79acbf53a55bc71aa38d062b16fa0f8a40a7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/577b44a0e7f60c78d090ea54c6af8ab73ccaa5fc .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--gdwarf-2,-I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7da0472c8aeab2cdb59b8f226988f3db34bb8368 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ce84edd63a13365e014c2e0ad46e873e14b50697 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9f765f448ecf939d3763353b0657e663b9f37cc1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3656fef46042eb6835c27ea9433cfadd78ab2e37 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/26bb0daeeaeb3da870cd51f14438c80a16def5cc .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/414a55b549d87d9cd97951db38f9789c0c1a2052 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9e35fd3d201c1a78f0eb17348fd6f0564ec9c13 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f9661a161f8410350687a52cc872aa3a963a75f3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6b596cec54cdf4a761f0dacc55e10823187c8a5a .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cb393376b47de27fb0e27a8348defbeff36f6275 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1642c91414bc5f04a3335debb1a003a326a250eb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1d478184f576c11537c6c35fe7258a1daf7f915d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/613d3d8b1ca7929b8d83093fa3a7177430040de1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9852dbb20b73284dad6a9af61b9496ad21efc3b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/30e64f0c6cfe47c31cebc7d51794ecd0d5f8fb4e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b9302312636199a9f9f15e51e07407185b95d29c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/82388d0905fc87cca2c0aebed6c7f41956ce154e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6bc0162d6422092c2ffe5607d78c4530ede83bdc .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dd8a7adaa7ca6ac0f2ac5f7bd3da0dd2f9bc19b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/27e91390cbed4a39cc27131cafd50dc79f85694b .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/90f866758fcaddfad6ad9a1d2be5b23c14611452 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c848ebe3cc7523f8dd7d58264464a4d7f27625cb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a533e4d8ddb8a8f239dc64a08c004a4a66b77501 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9b527dd2b8eab73321466d4ae1a85e6d8803df8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/aed7d82c577686f0d648380573d184748c30f54f .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d2525feb4a14c78394b46486eef2431b85c770da .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -O1 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/437380671/appInitialize.o: ../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1eb021d4f1a3a24152f9c39692c2295fddd3ad8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/437380671" 
	@${RM} ${OBJECTDIR}/_ext/437380671/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/437380671/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/437380671/appInitialize.o.d" -o ${OBJECTDIR}/_ext/437380671/appInitialize.o ../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appApplication.o: ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fd491fbdde797d20fd11f78f04dbabb57412cbee .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appApplication.o.d" -o ${OBJECTDIR}/_ext/1484845179/appApplication.o ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appMain.o: ../../../Demo/MonoDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4d7da9f86bf47d6bb71e5f23105f171865d294f5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appMain.o.d" -o ${OBJECTDIR}/_ext/1484845179/appMain.o ../../../Demo/MonoDisplayDemo/Source/appMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appLedService.o: ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3ecb5ee9cb29359a30c151c35f0e5746aacd47c4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appLedService.o.d" -o ${OBJECTDIR}/_ext/1484845179/appLedService.o ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appDisplayService.o: ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8a7f62c916c4bdbf23c9b2143c9fa39d84719861 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1484845179/appDisplayService.o ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4c77408fe42e4dd40e05101692b6cfd240d90c63 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/24ed5dc3c11de52fa8ee04cffbf50e208181dd4e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/84101ba0d16980a49f3b81847e610d4219cb6703 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7c858720098429bcf9c924e1f1e6c0374afbe675 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/baee12186753a789dc151849ed6c59eb25f800df .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3f94d1de4bcf7c2bf85fe04981d2deecfea89101 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/829709677b9b9eea58e27fa7ad35f7a235e47bf0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/290993926ecd833dbbdb9acc09f41165007f6110 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2868d60fde9edc058e610671f2d62db2132a7a88 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/abebe290f3c995899377b7c4fb84f1d69bb3fd85 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/26eba0c7db8d22de3e9ed8616547db189267a78 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/74465f6b062c4dc5bf0f1d8c5cbf630033269e02 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c821f60e8c37359589ba398df006de3dbf876d02 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9fc7ba4d862432c7dfa3138f4abf9a28422b69d7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4134dab2249bfebbe3e74a0ae1dd7801bd98bda8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a40be75d462a2377572d45c05b07dce393a70f57 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/97614a7b6fb45ed2d5420fd0e60cdca1fdff2f82 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/def7a04d89f782e7973a879520f1015beb50bfe8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a20a86148d5d1445cbdee10685df08dc289d50aa .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFontCache.o: ../../../Source/System/Graphics/eosFontCache.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/32860b896ae350991bc9d543f6cd005cd3d82c5a .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFontCache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFontCache.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFontCache.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFontCache.o ../../../Source/System/Graphics/eosFontCache.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/68160a3c6777152a1f7fc36ac4cf5992537c2728 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/76cf294efee3c79c1ecf9cf6d29cfee84601c2d3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o: ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6c59611c971fc408a045225c33ec50f7148b3ff1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/510006700" 
	@${RM} ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o.d 
	@${RM} ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o.d" -o ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/437380671/appInitialize.o: ../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3adab9537ae533688c89462f0dbc44de0ea0fbc2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/437380671" 
	@${RM} ${OBJECTDIR}/_ext/437380671/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/437380671/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/437380671/appInitialize.o.d" -o ${OBJECTDIR}/_ext/437380671/appInitialize.o ../../../Demo/MonoDisplayDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appApplication.o: ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/81700592c5fa80754fce0d926bebd426a5e6cb6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appApplication.o.d" -o ${OBJECTDIR}/_ext/1484845179/appApplication.o ../../../Demo/MonoDisplayDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appMain.o: ../../../Demo/MonoDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/77ffb35e9fcd8b2583933e4bdbae887bebb7c652 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appMain.o.d" -o ${OBJECTDIR}/_ext/1484845179/appMain.o ../../../Demo/MonoDisplayDemo/Source/appMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appLedService.o: ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9824afc34dbbd4ac7fe2c5df4d5f4dc6dd5585d5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appLedService.o.d" -o ${OBJECTDIR}/_ext/1484845179/appLedService.o ../../../Demo/MonoDisplayDemo/Source/appLedService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1484845179/appDisplayService.o: ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4bfc0dc302647715e4721e84ab2d23b859485f3d .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1484845179" 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1484845179/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1484845179/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1484845179/appDisplayService.o ../../../Demo/MonoDisplayDemo/Source/appDisplayService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4c45fe41f65c4f6cf5d243e454f23142b2bc757a .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b1c4434817ec62b5b1286e4c5336e5a00e011aef .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d7844b3ae64ee26327ca96a9879b3143431c6ffb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/212b5c107fcdef6c0778cde6ecd0e02cc86d7119 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9a44144b1bdb006d8fb1c1d6572a94d995ab1766 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2c35c47c27942c272fc93aaac9a970c413a59403 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/26a392b2696c572f9b229871adf4bc073e0d3b7e .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/70de23a19325a81057f32f6d85a50c14667246a0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/edf99e73c6a0bbb091d76221c5aaa59446164723 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/872bd35934a00904157beb2dbc9fb1035c2442fd .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f7e41a69f4b3d815b3ff8ad7ec15bad00644dd60 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/32c0668d914b3b385da7647ad7e569537e76968a .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9e8a0e9b8842d52e385cd968dfeb27e8b63ce6ad .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9243cca03f86e1b3573cf0ab6a9c4bfbb8952bbb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6a6d7de4a8e2f1027e8fa207847426c63655c53b .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7142560cc97f437bdd88449415e37e4f45075592 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4fc7df388026a54982c89808ef1821c4c7c5f2b0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/76297ddd80a3a82bd7c8f51c4483ce1c1ac43a64 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cbddd7778147ffbb50e5fcdd1e04c2008129bc36 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFontCache.o: ../../../Source/System/Graphics/eosFontCache.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/43ec740091e2a270e79e5784dc2247055ba323e1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFontCache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFontCache.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFontCache.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFontCache.o ../../../Source/System/Graphics/eosFontCache.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9ac066c13caf57f809de077895a1b0f71ef0ad63 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8dad3fc93640d1e0803460efa930cb71564f4bcb .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o: ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/448eef4b3e24280a464fa75b9896f7f3308351a8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/5c6b98b8923ce30ee24d180da03fe6585119c89b
	@${MKDIR} "${OBJECTDIR}/_ext/510006700" 
	@${RM} ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o.d 
	@${RM} ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/MonoDisplayDemo/Include" -I"../../../Demo/MonoDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o.d" -o ${OBJECTDIR}/_ext/510006700/eosDisplayDriver_ST7565.o ../../../Source/Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=c++17 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=8192,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=8192,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/MonoDisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
