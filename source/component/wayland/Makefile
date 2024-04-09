#===============================================================================
# export variable
#===============================================================================
SDK_DIR ?= $(shell cd $(CURDIR) && /bin/pwd)
include $(SDK_DIR)/base.mak

#===============================================================================
# objects
#===============================================================================
objects :=
objects += component

ifneq ($(WL_PRODUCT_FILE),y)
objects += weston
endif

ifneq ($(WL_PRODUCT_FILE),y)
#objects += test
endif

ifneq ($(WL_PRODUCT_FILE),y)
#objects += qt
endif

objects_clean := $(addsuffix _clean, $(objects))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#     rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PHONY := all clean

all:${objects}

clean:${objects_clean}
#	$(AT)rm -rf $(WL_OUT_DIR)/obj
#	$(AT)rm -rf $(WL_OUT_DIR)/weston

#==================================================================
#                          modules
#==================================================================
.PHONY: ${objects} ${objects_clean}

$(objects):
	$(AT)make -C $@

$(objects_clean):
	$(AT)make -C $(patsubst %_clean,%,$@) clean
