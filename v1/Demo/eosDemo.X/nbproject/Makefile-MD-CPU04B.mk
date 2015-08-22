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
ifeq "$(wildcard nbproject/Makefile-local-MD-CPU04B.mk)" "nbproject/Makefile-local-MD-CPU04B.mk"
include nbproject/Makefile-local-MD-CPU04B.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=MD-CPU04B
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
SOURCEFILES_QUOTED_IF_SPACED=../../Source/Modules/eosAdc.c ../../Source/Modules/eosInputs.c ../../Source/Modules/eosLed.c ../../Source/Modules/eosOutputs.c ../../Source/Modules/eosTimers.c ../../Source/Modules/eosVariables.c ../../Source/Modules/eosUsbHost.c ../../Source/Modules/eosI2CMaster.c ../../Source/Modules/eosI2CSlave.c ../../Source/System/eosKernel.c ../../Source/System/eosMemory.c ../../Source/System/eosStart.c ../Hal/Hal_MD-CPU04B.c ../Config.c ../Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1583268659/eosAdc.p1 ${OBJECTDIR}/_ext/1583268659/eosInputs.p1 ${OBJECTDIR}/_ext/1583268659/eosLed.p1 ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1 ${OBJECTDIR}/_ext/1583268659/eosTimers.p1 ${OBJECTDIR}/_ext/1583268659/eosVariables.p1 ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1 ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1 ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1 ${OBJECTDIR}/_ext/1479454979/eosKernel.p1 ${OBJECTDIR}/_ext/1479454979/eosMemory.p1 ${OBJECTDIR}/_ext/1479454979/eosStart.p1 ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1 ${OBJECTDIR}/_ext/1472/Config.p1 ${OBJECTDIR}/_ext/1472/Main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d ${OBJECTDIR}/_ext/1472/Config.p1.d ${OBJECTDIR}/_ext/1472/Main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1583268659/eosAdc.p1 ${OBJECTDIR}/_ext/1583268659/eosInputs.p1 ${OBJECTDIR}/_ext/1583268659/eosLed.p1 ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1 ${OBJECTDIR}/_ext/1583268659/eosTimers.p1 ${OBJECTDIR}/_ext/1583268659/eosVariables.p1 ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1 ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1 ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1 ${OBJECTDIR}/_ext/1479454979/eosKernel.p1 ${OBJECTDIR}/_ext/1479454979/eosMemory.p1 ${OBJECTDIR}/_ext/1479454979/eosStart.p1 ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1 ${OBJECTDIR}/_ext/1472/Config.p1 ${OBJECTDIR}/_ext/1472/Main.p1

# Source Files
SOURCEFILES=../../Source/Modules/eosAdc.c ../../Source/Modules/eosInputs.c ../../Source/Modules/eosLed.c ../../Source/Modules/eosOutputs.c ../../Source/Modules/eosTimers.c ../../Source/Modules/eosVariables.c ../../Source/Modules/eosUsbHost.c ../../Source/Modules/eosI2CMaster.c ../../Source/Modules/eosI2CSlave.c ../../Source/System/eosKernel.c ../../Source/System/eosMemory.c ../../Source/System/eosStart.c ../Hal/Hal_MD-CPU04B.c ../Config.c ../Main.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-MD-CPU04B.mk dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1583268659/eosAdc.p1: ../../Source/Modules/eosAdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosAdc.p1  ../../Source/Modules/eosAdc.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosAdc.d ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosInputs.p1: ../../Source/Modules/eosInputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosInputs.p1  ../../Source/Modules/eosInputs.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosInputs.d ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosLed.p1: ../../Source/Modules/eosLed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosLed.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosLed.p1  ../../Source/Modules/eosLed.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosLed.d ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosOutputs.p1: ../../Source/Modules/eosOutputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosOutputs.p1  ../../Source/Modules/eosOutputs.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosOutputs.d ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosTimers.p1: ../../Source/Modules/eosTimers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosTimers.p1  ../../Source/Modules/eosTimers.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosTimers.d ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosVariables.p1: ../../Source/Modules/eosVariables.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosVariables.p1  ../../Source/Modules/eosVariables.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosVariables.d ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1: ../../Source/Modules/eosUsbHost.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1  ../../Source/Modules/eosUsbHost.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.d ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1: ../../Source/Modules/eosI2CMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1  ../../Source/Modules/eosI2CMaster.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.d ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1: ../../Source/Modules/eosI2CSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1  ../../Source/Modules/eosI2CSlave.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.d ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosKernel.p1: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosKernel.p1  ../../Source/System/eosKernel.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosKernel.d ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosMemory.p1: ../../Source/System/eosMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosMemory.p1  ../../Source/System/eosMemory.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosMemory.d ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosStart.p1: ../../Source/System/eosStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosStart.p1  ../../Source/System/eosStart.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosStart.d ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1: ../Hal/Hal_MD-CPU04B.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360895396 
	@${RM} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1  ../Hal/Hal_MD-CPU04B.c 
	@-${MV} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.d ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Config.p1: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1472/Config.p1  ../Config.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Config.d ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1583268659/eosAdc.p1: ../../Source/Modules/eosAdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosAdc.p1  ../../Source/Modules/eosAdc.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosAdc.d ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosAdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosInputs.p1: ../../Source/Modules/eosInputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosInputs.p1  ../../Source/Modules/eosInputs.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosInputs.d ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosInputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosLed.p1: ../../Source/Modules/eosLed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosLed.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosLed.p1  ../../Source/Modules/eosLed.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosLed.d ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosLed.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosOutputs.p1: ../../Source/Modules/eosOutputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosOutputs.p1  ../../Source/Modules/eosOutputs.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosOutputs.d ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosOutputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosTimers.p1: ../../Source/Modules/eosTimers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosTimers.p1  ../../Source/Modules/eosTimers.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosTimers.d ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosTimers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosVariables.p1: ../../Source/Modules/eosVariables.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosVariables.p1  ../../Source/Modules/eosVariables.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosVariables.d ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosVariables.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1: ../../Source/Modules/eosUsbHost.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1  ../../Source/Modules/eosUsbHost.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.d ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosUsbHost.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1: ../../Source/Modules/eosI2CMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1  ../../Source/Modules/eosI2CMaster.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.d ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosI2CMaster.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1: ../../Source/Modules/eosI2CSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1583268659 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1  ../../Source/Modules/eosI2CSlave.c 
	@-${MV} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.d ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1583268659/eosI2CSlave.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosKernel.p1: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosKernel.p1  ../../Source/System/eosKernel.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosKernel.d ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosKernel.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosMemory.p1: ../../Source/System/eosMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosMemory.p1  ../../Source/System/eosMemory.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosMemory.d ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosMemory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1479454979/eosStart.p1: ../../Source/System/eosStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1479454979 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosStart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1479454979/eosStart.p1  ../../Source/System/eosStart.c 
	@-${MV} ${OBJECTDIR}/_ext/1479454979/eosStart.d ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1479454979/eosStart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1: ../Hal/Hal_MD-CPU04B.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360895396 
	@${RM} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1  ../Hal/Hal_MD-CPU04B.c 
	@-${MV} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.d ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360895396/Hal_MD-CPU04B.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Config.p1: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1472/Config.p1  ../Config.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Config.d ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: (%%n) %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"        -odist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --summary=default,-psect,-class,-mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: (%%n) %%s" "--msgformat=%%f:%%l: advisory: (%%n) %%s"     -odist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/MD-CPU04B
	${RM} -r dist/MD-CPU04B

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
