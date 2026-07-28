################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1853668350: ../empty.syscfg
	@echo 'SysConfig - building file: "$<"'
	"D:/ti/ccs2100/sysconfig_1.26.2/sysconfig_cli.bat" -s "D:/ti/ccs2100/mspm0_sdk_2_11_00_07/.metadata/product.json" --script "C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0/empty.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1853668350 ../empty.syscfg
device.opt: build-1853668350
device.cmd.genlibs: build-1853668350
ti_msp_dl_config.c: build-1853668350
ti_msp_dl_config.h: build-1853668350
Event.dot: build-1853668350

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0" -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0/Debug" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source" -g -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0" -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0/Debug" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source" -g -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0" -I"C:/Users/sangbet/workspace_ccstheia/NUEDC2026_mspm0/Debug" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"D:/ti/ccs2100/mspm0_sdk_2_11_00_07/source" -g -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


