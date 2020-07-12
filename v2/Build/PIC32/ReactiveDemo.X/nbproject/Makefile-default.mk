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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/ReactiveDemo/Source/appMain.cpp ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/System/Collections/eosContainer.cpp ../../../Source/OSAL/Default/osalHeap.c ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosErrorHandler.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/14588625/appMain.o ${OBJECTDIR}/_ext/1723254923/appInitialize.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/362649274/osalHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/14588625/appMain.o.d ${OBJECTDIR}/_ext/1723254923/appInitialize.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/362649274/osalHeap.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/14588625/appMain.o ${OBJECTDIR}/_ext/1723254923/appInitialize.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/362649274/osalHeap.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o

# Source Files
SOURCEFILES=../../../Demo/ReactiveDemo/Source/appMain.cpp ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/System/Collections/eosContainer.cpp ../../../Source/OSAL/Default/osalHeap.c ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosErrorHandler.cpp



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362649274/osalHeap.o: ../../../Source/OSAL/Default/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/362649274" 
	@${RM} ${OBJECTDIR}/_ext/362649274/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/362649274/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/362649274/osalHeap.o.d" -o ${OBJECTDIR}/_ext/362649274/osalHeap.o ../../../Source/OSAL/Default/osalHeap.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/362649274/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362649274/osalHeap.o: ../../../Source/OSAL/Default/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/362649274" 
	@${RM} ${OBJECTDIR}/_ext/362649274/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/362649274/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/362649274/osalHeap.o.d" -o ${OBJECTDIR}/_ext/362649274/osalHeap.o ../../../Source/OSAL/Default/osalHeap.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/362649274/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/14588625/appMain.o: ../../../Demo/ReactiveDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/14588625" 
	@${RM} ${OBJECTDIR}/_ext/14588625/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/14588625/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/14588625/appMain.o.d" -o ${OBJECTDIR}/_ext/14588625/appMain.o ../../../Demo/ReactiveDemo/Source/appMain.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/14588625/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1723254923/appInitialize.o: ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1723254923" 
	@${RM} ${OBJECTDIR}/_ext/1723254923/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1723254923/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1723254923/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1723254923/appInitialize.o ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1723254923/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/14588625/appMain.o: ../../../Demo/ReactiveDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/14588625" 
	@${RM} ${OBJECTDIR}/_ext/14588625/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/14588625/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/14588625/appMain.o.d" -o ${OBJECTDIR}/_ext/14588625/appMain.o ../../../Demo/ReactiveDemo/Source/appMain.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/14588625/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1723254923/appInitialize.o: ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1723254923" 
	@${RM} ${OBJECTDIR}/_ext/1723254923/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1723254923/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1723254923/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1723254923/appInitialize.o ../../../Demo/ReactiveDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1723254923/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/ReactiveDemo/Include" -I"../../../Library/PIC32/Harmony/Framework" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=1024,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ReactiveDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
