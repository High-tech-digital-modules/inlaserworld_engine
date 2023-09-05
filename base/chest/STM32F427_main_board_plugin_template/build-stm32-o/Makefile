ifndef SDK_ROOT
SDK_ROOT:=$(shell pwd | grep -o ".*/laser_sdk")
endif
ifndef SDK_ROOT
$(error SDK_ROOT is not set, please set env varible pointing to laser_sdk)
endif
include $(SDK_ROOT)/build/nbuild/targets/coordinator.mk
