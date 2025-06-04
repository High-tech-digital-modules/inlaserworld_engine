#INLASERWORLD_LIBRARY DO NOT REMOVE USED FOR PACKAGE SYNC
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
ifndef GAME_TEMPLATE_ID
GAME_TEMPLATE_ID_=$(shell pwd | grep -o -P '(?<=plugins/).*(?=/chest)' | sed 's|/|_|g')
else
GAME_TEMPLATE_ID_=$(shell pwd | grep -o -P '(?<=gameTemplates/).*(?=/chest)')
endif
endif
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
y := $(shell $(SDK_ROOT)/firmware/stm/32F427/lib/plugin_base/src/parse_custom_variables.sh $(GAME_TEMPLATE_ID_) 0)
y := $(shell mkdir ../include)
z := $(shell (makeheaders ../src/plugin/plugin_functions.c || touch ../src/plugin/plugin_functions.h) && mv ../src/plugin/plugin_functions.h ../include/library_$(GAME_TEMPLATE_ID_).h)
z := $(shell rm -f ../include/custom_variables_map.h && (makeheaders ../src/custom_variables_map.c || touch ../src/custom_variables_map.h) && mv ../src/custom_variables_map.h ../include/custom_variables_map_$(GAME_TEMPLATE_ID_).h && ln -s ../include/custom_variables_map_$(GAME_TEMPLATE_ID_).h ../src/custom_variables_map.h)
endif
endif

PLUGIN = 1

LIB_NAME=lib_$(GAME_TEMPLATE_ID_).a

LIB_SRCS =                                                                         \
../src/custom_variables_map.c                                                      \
$(SDK_ROOT)/firmware/stm/32F427/lib/plugin_library_base/src/plugin_library_init.c  


LIB_INC =                                                                          \
-I../src/plugin                                                                    \
-I../src                                                                           \
-I../src/engine                                                                    \
-I$(SDK_ROOT)/firmware/stm/32F427/include/plugin                                   \
-I$(SDK_ROOT)/firmware/stm/32F427/include/engine                                   \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/Device/ST/STM32F4xx/Include            \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/CMSIS/Include                          \
-I$(SDK_ROOT)/firmware/stm/32F427/Libraries/STM32F4xx_StdPeriph_Driver/inc         \

ifneq (, $(findstring -linux, $(ODIR)))

FLAGS += -fPIC -D SIMULATION -D PLUGIN_CODE -fpermissive 

else 

FLAGS += -D PLUGIN_CODE 

LIB_INC += -I$(SDK_ROOT)/firmware/stm/32F427/include                               \

endif

CUSTOM_DEP_TARGET = plugin_library_init.o
CUSTOM_DEP_DEPENDENCIES = $(SDK_ROOT)/firmware/stm/32F427/lib/plugin_library_base/src/plugin_library_init.c \
../src/plugin/plugin_functions.c

