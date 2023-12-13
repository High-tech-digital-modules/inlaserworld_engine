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

LIBS_NAME=libplugin

FLAGS += -fPIC 

LIB_SRCS =                                                               \
../src/custom_variables_map.c                                            \
$(SDK_ROOT)/raspberry/apps/lasergame/include/engine/engine_functions.cpp \
$(SDK_ROOT)/raspberry/lib/plugin_base/src/plugin.c                                                                                             

LIB_INC =                                                                \
-I../include                                                             \
-I../src                                                                 \
-I$(SDK_ROOT)/raspberry/apps/lasergame/include/engine                    \
-I$(SDK_ROOT)/raspberry/lib/fmod_common/include          				 \
-I$(SDK_ROOT)/3rdParty/rapidjson-1.1.0/include

LIB_LIBS =                                                               \
-L$(SDK_ROOT)/raspberry/lib/fmod_common/$(ODIR)                          \
-lfmod                                                   				 \

-include ../SUBMODULES.mk

CUSTOM_DEP_TARGET = plugin.o
CUSTOM_DEP_DEPENDENCIES = $(SDK_ROOT)/raspberry/lib/plugin_base/src/plugin.c \
../src/main.c
