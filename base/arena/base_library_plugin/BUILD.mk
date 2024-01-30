#INLASERWORLD_LIBRARY DO NOT REMOVE USED FOR PACKAGE SYNC
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
ifndef GAME_TEMPLATE_ID
GAME_TEMPLATE_ID_=$(shell pwd | grep -o -P '(?<=plugins/).*(?=/arena)')
else
GAME_TEMPLATE_ID_=$(shell pwd | grep -o -P '(?<=gameTemplates/).*(?=/arena)')
endif
endif
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleansub)
y := $(shell $(SDK_ROOT)/raspberry/lib/plugin_base/src/parse_custom_variables.sh $(GAME_TEMPLATE_ID_) 0)
y := $(shell mkdir ../include)
z := $(shell (makeheaders ../src/main.c || touch ../src/main.h) && mv ../src/main.h ../include/library_$(GAME_TEMPLATE_ID_).h)
z := $(shell rm -f ../include/custom_variables_map.h && (makeheaders ../src/custom_variables_map.c || touch ../src/custom_variables_map.h) && mv ../src/custom_variables_map.h ../include/custom_variables_map_$(GAME_TEMPLATE_ID_).h && ln -s ../include/custom_variables_map_$(GAME_TEMPLATE_ID_).h ../src/custom_variables_map.h)
endif
endif

ifneq (, $(findstring -rasp, $(ODIR)))
CPU = armhf
else
CPU = x86_64
endif

LIB_NAME=lib_$(GAME_TEMPLATE_ID_).a

FLAGS += -fPIC

LIB_SRCS =                                                               \
../src/custom_variables_map.c                                            \
$(SDK_ROOT)/raspberry/lib/plugin_library_base/src/plugin_library.c                                                                                             

LIB_INC =                                                                \
-I../include                                                             \
-I../src                                                                 \
-I$(SDK_ROOT)/3rdParty/fmodstudioapi11005linux/api/lowlevel/inc          \
-I$(SDK_ROOT)/raspberry/apps/lasergame/include/engine                    \
-I$(SDK_ROOT)/raspberry/lib/fmod_common/include          				 \
-I$(SDK_ROOT)/3rdParty/rapidjson-1.1.0/include

LIB_LIBS =                                                               \

CUSTOM_DEP_TARGET = plugin_library.o
CUSTOM_DEP_DEPENDENCIES = $(SDK_ROOT)/raspberry/lib/plugin_library_base/src/plugin_library.c \
../src/main.c