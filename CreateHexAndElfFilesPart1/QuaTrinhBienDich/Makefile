# sharing basic makefile

PRO_DIR		:= .
PROJ_NAME	:= GPIO
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
SRC_DIR 	:= $(PRO_DIR)/src
LINKER_FILE	:= $(PRO_DIR)/linker/stm32f1_discovery.ld

COMPILER_DIR 	:= C:/GCC

CC				:= $(COMPILER_DIR)/bin/arm-none-eabi-gcc
ASM				:= $(COMPILER_DIR)/bin/arm-none-eabi-as
LD				:= $(COMPILER_DIR)/bin/arm-none-eabi-ld

SOURCE_FILES := $(foreach DIR,$(SRC_DIR),$(notdir $(wildcard $(DIR)/*.c)))
FILE_TO_LINK := $(SOURCE_FILES:.c=.o)
SOURCE_FILES := $(foreach DIR,$(SRC_DIR),$(notdir $(wildcard $(DIR)/*.S)))
FILE_TO_LINK += $(SOURCE_FILES:.S=.o)
FILE_TO_LINK := $(foreach FILE, $(FILE_TO_LINK),$(OUTPUT_PATH)/$(FILE))

CC_OPT			:= -march=armv7-m -mcpu=cortex-m3 -c -O0 -g -mthumb -I$(INC_DIR)
ASM_OPT			:= -march=armv7-m -mcpu=cortex-m3 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.S
	@echo "compile $(SRC_DIR)/startup_ARMCM0.S file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(OUTPUT_PATH)/$(PROJ_NAME).elf" "$(OUTPUT_PATH)/$(PROJ_NAME).hex"
	size $(OUTPUT_PATH)/$(PROJ_NAME).elf
clean:
	@rm -rf $(OUTPUT_PATH)/*



	
Preprocessing: $(SRC_DIR)/main.c
	$(CC) $(CC_OPT) -E $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.c
Compilation: $(OUTPUT_PATH)/main.c
	$(CC) $(CC_OPT) -S $(OUTPUT_PATH)/main.c -o $(OUTPUT_PATH)/main.s
Asemble: $(OUTPUT_PATH)/main.s
	$(ASM) $(ASM_OPT) $(OUTPUT_PATH)/main.s -o $(OUTPUT_PATH)/main.o
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o
Linker: $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o $(LINKER_FILE)
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf








