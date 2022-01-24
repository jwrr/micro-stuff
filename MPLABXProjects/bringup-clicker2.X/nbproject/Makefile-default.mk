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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/memory/flash.s mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/example_mcc_usb_cdc.c mcc_generated_files/clock.c mcc_generated_files/traps.c mcc_generated_files/interrupt_manager.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/adc1.c mcc_generated_files/i2c3.c mcc_generated_files/spi2.c mcc_generated_files/tmr3.c main.c flash_wrapper.c usb_wrapper.c disp_wrapper.c gpio_wrapper.c font_wrapper.c dac_wrapper.c adc_wrapper.c timer_wrapper.c trigger_wrapper.c wave_wrapper.c cmd_wrapper.c misc_wrapper.c help_wrapper.c temp_wrapper.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/i2c3.o ${OBJECTDIR}/mcc_generated_files/spi2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/main.o ${OBJECTDIR}/flash_wrapper.o ${OBJECTDIR}/usb_wrapper.o ${OBJECTDIR}/disp_wrapper.o ${OBJECTDIR}/gpio_wrapper.o ${OBJECTDIR}/font_wrapper.o ${OBJECTDIR}/dac_wrapper.o ${OBJECTDIR}/adc_wrapper.o ${OBJECTDIR}/timer_wrapper.o ${OBJECTDIR}/trigger_wrapper.o ${OBJECTDIR}/wave_wrapper.o ${OBJECTDIR}/cmd_wrapper.o ${OBJECTDIR}/misc_wrapper.o ${OBJECTDIR}/help_wrapper.o ${OBJECTDIR}/temp_wrapper.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/i2c3.o.d ${OBJECTDIR}/mcc_generated_files/spi2.o.d ${OBJECTDIR}/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/flash_wrapper.o.d ${OBJECTDIR}/usb_wrapper.o.d ${OBJECTDIR}/disp_wrapper.o.d ${OBJECTDIR}/gpio_wrapper.o.d ${OBJECTDIR}/font_wrapper.o.d ${OBJECTDIR}/dac_wrapper.o.d ${OBJECTDIR}/adc_wrapper.o.d ${OBJECTDIR}/timer_wrapper.o.d ${OBJECTDIR}/trigger_wrapper.o.d ${OBJECTDIR}/wave_wrapper.o.d ${OBJECTDIR}/cmd_wrapper.o.d ${OBJECTDIR}/misc_wrapper.o.d ${OBJECTDIR}/help_wrapper.o.d ${OBJECTDIR}/temp_wrapper.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/memory/flash.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/i2c3.o ${OBJECTDIR}/mcc_generated_files/spi2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/main.o ${OBJECTDIR}/flash_wrapper.o ${OBJECTDIR}/usb_wrapper.o ${OBJECTDIR}/disp_wrapper.o ${OBJECTDIR}/gpio_wrapper.o ${OBJECTDIR}/font_wrapper.o ${OBJECTDIR}/dac_wrapper.o ${OBJECTDIR}/adc_wrapper.o ${OBJECTDIR}/timer_wrapper.o ${OBJECTDIR}/trigger_wrapper.o ${OBJECTDIR}/wave_wrapper.o ${OBJECTDIR}/cmd_wrapper.o ${OBJECTDIR}/misc_wrapper.o ${OBJECTDIR}/help_wrapper.o ${OBJECTDIR}/temp_wrapper.o

# Source Files
SOURCEFILES=mcc_generated_files/memory/flash.s mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device_cdc.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/example_mcc_usb_cdc.c mcc_generated_files/clock.c mcc_generated_files/traps.c mcc_generated_files/interrupt_manager.c mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/system.c mcc_generated_files/adc1.c mcc_generated_files/i2c3.c mcc_generated_files/spi2.c mcc_generated_files/tmr3.c main.c flash_wrapper.c usb_wrapper.c disp_wrapper.c gpio_wrapper.c font_wrapper.c dac_wrapper.c adc_wrapper.c timer_wrapper.c trigger_wrapper.c wave_wrapper.c cmd_wrapper.c misc_wrapper.c help_wrapper.c temp_wrapper.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ1024GB610
MP_LINKER_FILE_OPTION=,--script=p24FJ1024GB610.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/10dbe894b2ca3580f718a89e369e4b40e95353d3 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/9fa4524ad869be5181da0a6e092740f507c6b036 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/f2be106d1484ee3e9e3de72299e6c84a65477ed1 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/d7d5b9db01a5d5554190c5a41fff6224e669979 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/a1c5667b94430ff88b2346d883cf8252dd9fc53e .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o: mcc_generated_files/usb/example_mcc_usb_cdc.c  .generated_files/flags/default/a668ab76e5eaf930cbf3386bfe7b86f69b1f1c92 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/84c7dcf92e4eb6b31391ee7fc6fa1fbd498b1ba9 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/2ab4666e15a3ed41d9b7db9dab7ff3b9f2440d2d .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/ec9f22627186f4f4772eeea2e87c9c9e3c80b34b .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/28f7d63cf09bc20af9b7e199ce6186404e8ee313 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/ef7226a4569077354141e1464f8538f095618889 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/e6800aee987c39edfd078cfcab959bb77c25226 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/fe0217f77b7cda1aca9590aa3abec78eaa5b7e9e .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c3.o: mcc_generated_files/i2c3.c  .generated_files/flags/default/588c80b2896cc89d2b26449c597b5bbe8e09daee .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c3.c  -o ${OBJECTDIR}/mcc_generated_files/i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi2.o: mcc_generated_files/spi2.c  .generated_files/flags/default/227a076ae3fdddc721e48a1adab998d433adfc66 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi2.c  -o ${OBJECTDIR}/mcc_generated_files/spi2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/548f42951d2d7cc82fcfda7b20a56aa6cc258520 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/b4d5f6701d69a6570c7ac8c6f77bfcd80e4a2267 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/flash_wrapper.o: flash_wrapper.c  .generated_files/flags/default/6ec3003734ae09ae2b6c23e6ae64a39948238a00 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/flash_wrapper.o.d 
	@${RM} ${OBJECTDIR}/flash_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  flash_wrapper.c  -o ${OBJECTDIR}/flash_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/flash_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/usb_wrapper.o: usb_wrapper.c  .generated_files/flags/default/e65fa28f7779f565123c9587c7684f063282cf9a .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_wrapper.o.d 
	@${RM} ${OBJECTDIR}/usb_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_wrapper.c  -o ${OBJECTDIR}/usb_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/usb_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/disp_wrapper.o: disp_wrapper.c  .generated_files/flags/default/97a786c4d93f0fcc17b58f5e22314b63d9b47188 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/disp_wrapper.o.d 
	@${RM} ${OBJECTDIR}/disp_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  disp_wrapper.c  -o ${OBJECTDIR}/disp_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/disp_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/gpio_wrapper.o: gpio_wrapper.c  .generated_files/flags/default/20cddb42dc93904a7fb49e11fcfaa364a2aaeff5 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gpio_wrapper.o.d 
	@${RM} ${OBJECTDIR}/gpio_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpio_wrapper.c  -o ${OBJECTDIR}/gpio_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/gpio_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/font_wrapper.o: font_wrapper.c  .generated_files/flags/default/8ed31a3eba79871efde6191e0eee4325f1db97fe .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/font_wrapper.o.d 
	@${RM} ${OBJECTDIR}/font_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  font_wrapper.c  -o ${OBJECTDIR}/font_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/font_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dac_wrapper.o: dac_wrapper.c  .generated_files/flags/default/fba8b8349799b588dbc4548f45ce54599c5719be .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dac_wrapper.o.d 
	@${RM} ${OBJECTDIR}/dac_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dac_wrapper.c  -o ${OBJECTDIR}/dac_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dac_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adc_wrapper.o: adc_wrapper.c  .generated_files/flags/default/eef0289bfa08cfc443a79009683865e9ec19c0f5 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_wrapper.o.d 
	@${RM} ${OBJECTDIR}/adc_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc_wrapper.c  -o ${OBJECTDIR}/adc_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timer_wrapper.o: timer_wrapper.c  .generated_files/flags/default/11f3c94ed3549b700039fa7b7838e29bde57caf5 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer_wrapper.o.d 
	@${RM} ${OBJECTDIR}/timer_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_wrapper.c  -o ${OBJECTDIR}/timer_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/trigger_wrapper.o: trigger_wrapper.c  .generated_files/flags/default/7644159d0bd7062bbee7fbd80ae5b0315ea19c05 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trigger_wrapper.o.d 
	@${RM} ${OBJECTDIR}/trigger_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  trigger_wrapper.c  -o ${OBJECTDIR}/trigger_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/trigger_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/wave_wrapper.o: wave_wrapper.c  .generated_files/flags/default/911651b06301665a9c562318bcbe9fd2d76645f9 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wave_wrapper.o.d 
	@${RM} ${OBJECTDIR}/wave_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  wave_wrapper.c  -o ${OBJECTDIR}/wave_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/wave_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cmd_wrapper.o: cmd_wrapper.c  .generated_files/flags/default/73c3e383aaa3aa22851ebb45d43fec98c354d6e9 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cmd_wrapper.o.d 
	@${RM} ${OBJECTDIR}/cmd_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cmd_wrapper.c  -o ${OBJECTDIR}/cmd_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cmd_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/misc_wrapper.o: misc_wrapper.c  .generated_files/flags/default/b67e228635ebc726fc4c657431f60b20a5e1d137 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/misc_wrapper.o.d 
	@${RM} ${OBJECTDIR}/misc_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  misc_wrapper.c  -o ${OBJECTDIR}/misc_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/misc_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/help_wrapper.o: help_wrapper.c  .generated_files/flags/default/a5f6240fabb8185585f53bd4df3c6405c26cfdf7 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/help_wrapper.o.d 
	@${RM} ${OBJECTDIR}/help_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  help_wrapper.c  -o ${OBJECTDIR}/help_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/help_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temp_wrapper.o: temp_wrapper.c  .generated_files/flags/default/9c84b72ec6cc8d4eb00f5ac247f4aa1bdf76dd09 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temp_wrapper.o.d 
	@${RM} ${OBJECTDIR}/temp_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temp_wrapper.c  -o ${OBJECTDIR}/temp_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temp_wrapper.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/d6b4bacc12c56b31cb023cfc899cb380f427e47f .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/5e9c73def65323be291a6726c6259c8ef4772650 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o: mcc_generated_files/usb/usb_device_cdc.c  .generated_files/flags/default/c181a3a4d49204ca0db305108d97481795b53ea4 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_cdc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/621bf68f8f55b9f23588cf5672b418af5668e059 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/2098934fc833a18ce2490e24ded9547c79b261ab .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o: mcc_generated_files/usb/example_mcc_usb_cdc.c  .generated_files/flags/default/fa19ef4d11418120033915015872d92573f6cd2 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/example_mcc_usb_cdc.c  -o ${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/example_mcc_usb_cdc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/d8c049ceb089f338ad946931d129999a7a1ecf55 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/851bf9c35ac6dbf68324421d4fc6f4ad88969c52 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/25e964abbe80b5df9b2033a53a8e9472e9aaaf2e .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/13afef471408ec5e300c5f8b5aa92387eb156ca2 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/640cb342d5fa3d2f4df1d2e0f49c6bbc6f4ceabb .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/8e9b0dd48e2d96a7bba71b6018862372073e1670 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/flags/default/d51c5060ef776f2cf7b256eb035a68dde7f9f791 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c3.o: mcc_generated_files/i2c3.c  .generated_files/flags/default/5497aaf5bd92a7ac618f3b9f8e99a5f98cd321e .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c3.c  -o ${OBJECTDIR}/mcc_generated_files/i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi2.o: mcc_generated_files/spi2.c  .generated_files/flags/default/ff6ed491e1332c1fb459146c938b7c38ec76ccd5 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi2.c  -o ${OBJECTDIR}/mcc_generated_files/spi2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/e446c99dba8fc9e0de1cf70bd3c1e13955479ea2 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/3aa2416665048e2268998cedbf3509407781ca66 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/flash_wrapper.o: flash_wrapper.c  .generated_files/flags/default/fa217bdf278992cfa3b530729c0b3ff4cc0887eb .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/flash_wrapper.o.d 
	@${RM} ${OBJECTDIR}/flash_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  flash_wrapper.c  -o ${OBJECTDIR}/flash_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/flash_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/usb_wrapper.o: usb_wrapper.c  .generated_files/flags/default/b89f903102d6b1e281fff512c0a92bec5af19828 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_wrapper.o.d 
	@${RM} ${OBJECTDIR}/usb_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_wrapper.c  -o ${OBJECTDIR}/usb_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/usb_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/disp_wrapper.o: disp_wrapper.c  .generated_files/flags/default/7e8d1370620a375a1d2ac55e7b5b2f9eb54d702b .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/disp_wrapper.o.d 
	@${RM} ${OBJECTDIR}/disp_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  disp_wrapper.c  -o ${OBJECTDIR}/disp_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/disp_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/gpio_wrapper.o: gpio_wrapper.c  .generated_files/flags/default/287706ef252fddbe1429cc4e9aa2e3040e6438b .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gpio_wrapper.o.d 
	@${RM} ${OBJECTDIR}/gpio_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpio_wrapper.c  -o ${OBJECTDIR}/gpio_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/gpio_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/font_wrapper.o: font_wrapper.c  .generated_files/flags/default/ed21bb270fd86cf1b48e94833bfaa7e04796eb11 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/font_wrapper.o.d 
	@${RM} ${OBJECTDIR}/font_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  font_wrapper.c  -o ${OBJECTDIR}/font_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/font_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/dac_wrapper.o: dac_wrapper.c  .generated_files/flags/default/3dfc0c7e64b488c8773e57200ab2587a500b4a5d .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dac_wrapper.o.d 
	@${RM} ${OBJECTDIR}/dac_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dac_wrapper.c  -o ${OBJECTDIR}/dac_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/dac_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adc_wrapper.o: adc_wrapper.c  .generated_files/flags/default/bc974f4bee57ea29b0c6992d9f06dfe0b0098752 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_wrapper.o.d 
	@${RM} ${OBJECTDIR}/adc_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc_wrapper.c  -o ${OBJECTDIR}/adc_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timer_wrapper.o: timer_wrapper.c  .generated_files/flags/default/f1284991facfe761c3f7efb37c74b81bcd10b726 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer_wrapper.o.d 
	@${RM} ${OBJECTDIR}/timer_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_wrapper.c  -o ${OBJECTDIR}/timer_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/trigger_wrapper.o: trigger_wrapper.c  .generated_files/flags/default/53e36f0c4e79da826b41ef8405c58285233e59af .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trigger_wrapper.o.d 
	@${RM} ${OBJECTDIR}/trigger_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  trigger_wrapper.c  -o ${OBJECTDIR}/trigger_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/trigger_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/wave_wrapper.o: wave_wrapper.c  .generated_files/flags/default/4da542055d6a5a76bb13ec7f05483bc2117d199d .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wave_wrapper.o.d 
	@${RM} ${OBJECTDIR}/wave_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  wave_wrapper.c  -o ${OBJECTDIR}/wave_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/wave_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/cmd_wrapper.o: cmd_wrapper.c  .generated_files/flags/default/b8fc9482297ea5a36324cae140538656929ba1ab .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cmd_wrapper.o.d 
	@${RM} ${OBJECTDIR}/cmd_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  cmd_wrapper.c  -o ${OBJECTDIR}/cmd_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/cmd_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/misc_wrapper.o: misc_wrapper.c  .generated_files/flags/default/9d1e9d00afee5b71e90672c7d23e8e7a32d683b4 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/misc_wrapper.o.d 
	@${RM} ${OBJECTDIR}/misc_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  misc_wrapper.c  -o ${OBJECTDIR}/misc_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/misc_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/help_wrapper.o: help_wrapper.c  .generated_files/flags/default/85401658789274a75b5a60344e3da68e3ed37d9f .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/help_wrapper.o.d 
	@${RM} ${OBJECTDIR}/help_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  help_wrapper.c  -o ${OBJECTDIR}/help_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/help_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temp_wrapper.o: temp_wrapper.c  .generated_files/flags/default/7b7df7f61c8195b63ab9402bbb667c9a554dce11 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temp_wrapper.o.d 
	@${RM} ${OBJECTDIR}/temp_wrapper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temp_wrapper.c  -o ${OBJECTDIR}/temp_wrapper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temp_wrapper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.s  .generated_files/flags/default/9f4f360981fa295c3d04f982cb8df5662cc7b828 .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/memory/flash.o: mcc_generated_files/memory/flash.s  .generated_files/flags/default/b6a57e9f842cdd260046bfabcfe9a49cefec317a .generated_files/flags/default/b93489a4dc52ce9e4aeb19e103aa4687337b6a59
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/bringup-clicker2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
