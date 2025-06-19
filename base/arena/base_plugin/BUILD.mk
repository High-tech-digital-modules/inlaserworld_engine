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
y := $(shell $(SDK_ROOT)/raspberry/lib/plugin_base/src/parse_custom_variables.sh $(GAME_TEMPLATE_ID) 1)
y := $(shell $(SDK_ROOT)/raspberry/lib/plugin_base/src/parse_libraries.sh $(GAME_TEMPLATE_ID))
z := $(shell (makeheaders ../src/custom_variables_map.c || touch ../src/custom_variables_map.h))
endif
endif

ifdef SIMULATION_PLUGIN
FLAGS+=-DSIMULATION_PLUGIN
endif

ifneq (, $(findstring -rasp, $(ODIR)))
ifneq (, $(findstring -rasp64, $(ODIR)))
CPU = arm64
else
CPU = arm
endif
else
CPU = x86_64
endif

LIBS_NAME=libplugin

FLAGS += -fPIC 

LIB_SRCS =                                                               \
../src/custom_variables_map.c                                            \
../src/sound_set_map.c                                                   \
$(wildcard ../src/extra/*.c)                                             \
$(SDK_ROOT)/raspberry/apps/lasergame/include/engine/engine_functions.cpp \
$(SDK_ROOT)/raspberry/lib/plugin_base/src/plugin.c                                                                                             

LIB_INC =                                                                \
-I../include                                                             \
-I../src                                                                 \
-I$(SDK_ROOT)/3rdParty/fmodstudioapi20210linux/api/core/inc              \
-I$(SDK_ROOT)/raspberry/apps/lasergame/include/engine                    \
-I$(SDK_ROOT)/raspberry/lib/fmod_common/include          				 \
-I$(SDK_ROOT)/3rdParty/rapidjson-1.1.0/include

LIB_LIBS =                                                               \
-L$(SDK_ROOT)/raspberry/lib/fmod_common/$(ODIR)                          \
-L$(SDK_ROOT)/3rdParty/fmodstudioapi20210linux/api/core/lib/$(CPU)       \
-lfmod                                                   				 \

-include ../SUBMODULES.mk

CUSTOM_DEP_TARGET = plugin.o
CUSTOM_DEP_DEPENDENCIES = $(SDK_ROOT)/raspberry/lib/plugin_base/src/plugin.c \
$(wildcard ../src/extra/*.c)                                                 \
../src/main.c
