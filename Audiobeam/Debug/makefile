################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./include/all_pass.obj" \
"./include/bass.obj" \
"./include/high.obj" \
"./include/mid.obj" \
"./include/filter/msp_biquad_cascade_df1_q15.obj" \
"./include/filter/msp_biquad_df1_q15.obj" \
"./include/lea/msp_lea_flags.obj" \
"./include/lea/msp_lea_init.obj" \
"./include/lea/msp_lea_isr.obj" \
"./include/lea/msp_lea_patch.obj" \
"./include/utility/msp_copy_q15.obj" \
"./include/utility/msp_fill_q15.obj" \
"./include/vector/msp_add_q15.obj" \
"./include/vector/msp_scale_q15.obj" \
"../lnk_msp430fr5994.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include include/subdir_vars.mk
-include include/filter/subdir_vars.mk
-include include/lea/subdir_vars.mk
-include include/utility/subdir_vars.mk
-include include/vector/subdir_vars.mk
-include subdir_rules.mk
-include include/subdir_rules.mk
-include include/filter/subdir_rules.mk
-include include/lea/subdir_rules.mk
-include include/utility/subdir_rules.mk
-include include/vector/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Audiobeam.out \

EXE_OUTPUTS__QUOTED += \
"Audiobeam.out" \

BIN_OUTPUTS += \
Audiobeam.hex \

BIN_OUTPUTS__QUOTED += \
"Audiobeam.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Audiobeam.out"

# Tool invocations
Audiobeam.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"Audiobeam.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccs930/ccs/ccs_base/msp430/include" -i"C:/ti/ccs930/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccs930/ccs/ccs_base/msp430/lib/FR59xx" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/lib" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/include" --priority --reread_libs --define=_MPU_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Audiobeam_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "Audiobeam.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Audiobeam.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "Audiobeam.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "include\all_pass.obj" "include\bass.obj" "include\high.obj" "include\mid.obj" "include\filter\msp_biquad_cascade_df1_q15.obj" "include\filter\msp_biquad_df1_q15.obj" "include\lea\msp_lea_flags.obj" "include\lea\msp_lea_init.obj" "include\lea\msp_lea_isr.obj" "include\lea\msp_lea_patch.obj" "include\utility\msp_copy_q15.obj" "include\utility\msp_fill_q15.obj" "include\vector\msp_add_q15.obj" "include\vector\msp_scale_q15.obj" 
	-$(RM) "main.d" "include\all_pass.d" "include\bass.d" "include\high.d" "include\mid.d" "include\filter\msp_biquad_cascade_df1_q15.d" "include\filter\msp_biquad_df1_q15.d" "include\lea\msp_lea_flags.d" "include\lea\msp_lea_init.d" "include\lea\msp_lea_isr.d" "include\lea\msp_lea_patch.d" "include\utility\msp_copy_q15.d" "include\utility\msp_fill_q15.d" "include\vector\msp_add_q15.d" "include\vector\msp_scale_q15.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

