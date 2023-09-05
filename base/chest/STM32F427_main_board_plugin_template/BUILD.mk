ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
x := $(shell $(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/process_functions.sh)
endif
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
ifndef GAME_TEMPLATE_ID
GAME_TEMPLATE_ID=0
$(warning GAME_TEMPLATE_ID is not set, GAME_TEMPLATE_ID is set to 0)
endif
endif
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
y := $(shell $(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/parse_custom_variables.sh $(GAME_TEMPLATE_ID) 1)
y := $(shell $(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/parse_libraries.sh $(GAME_TEMPLATE_ID))
z := $(shell (makeheaders ../src/custom_variables_map.c || touch ../src/custom_variables_map.h))
endif
endif

PLUGIN = 1

ifneq (, $(findstring -linux, $(ODIR)))
LIBS_NAME=libplugin


FLAGS += -fPIC -D SIMULATION -D PLUGIN_CODE -fpermissive 


LIB_SRCS =                                                                 \
../src/custom_variables_map.c                                              \
$(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/plugin_init.c          \
$(SDK_ROOT)/firmware/stm/32F427/lib/plugin_def/src/engine_def.c            \


LIB_INC =                                                                  \
-I../src/plugin                                                            \
-I../src                                                                   \
-I../src/engine                                                            \
-I$(SDK_ROOT)/firmware/stm/32F427/include/plugin                           \
-I$(SDK_ROOT)/firmware/stm/32F427/include/engine                           \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/Device/ST/STM32F4xx/Include    \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/CMSIS/Include                  \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/STM32F4xx_StdPeriph_Driver/inc \

else 

FLAGS += -D PLUGIN_CODE  
APP_NAME=plugin

APP_SRCS =                                                                 \
../src/custom_variables_map.c                                              \
$(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/plugin_init.c          \
$(SDK_ROOT)/firmware/stm/32F427/lib/plugin_def/src/engine_def.c            \


APP_INC =                                                                  \
-I../src/plugin                                                            \
-I../src                                                                   \
-I../src/engine                                                            \
-I$(SDK_ROOT)/firmware/stm/32F427/include/plugin                           \
-I$(SDK_ROOT)/firmware/stm/32F427/include/engine                           \
-I$(SDK_ROOT)/firmware/stm/32F427/include                                  \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/Device/ST/STM32F4xx/Include    \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/CMSIS/Include                  \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/STM32F4xx_StdPeriph_Driver/inc \

endif

-include ../SUBMODULES.mk
