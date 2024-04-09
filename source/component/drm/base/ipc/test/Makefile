#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

TESTCASE1_SRC_DIR := testCase1
TESTCASE2_SRC_DIR := testCase2
TESTCASE3_SRC_DIR := testCase3
#TESTCASE4_SRC_DIR := testCase4
#TESTCASE5_SRC_DIR := testCase5

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(TESTCASE1_SRC_DIR) all
	$(AT)make -C $(TESTCASE2_SRC_DIR) all
	$(AT)make -C $(TESTCASE3_SRC_DIR) all
#	$(AT)make -C $(TESTCASE4_SRC_DIR) all
#	$(AT)make -C $(TESTCASE5_SRC_DIR) all

clean:
	$(AT)make -C $(TESTCASE1_SRC_DIR) clean
	$(AT)make -C $(TESTCASE2_SRC_DIR) clean
	$(AT)make -C $(TESTCASE3_SRC_DIR) clean
#	$(AT)make -C $(TESTCASE4_SRC_DIR) clean
#	$(AT)make -C $(TESTCASE5_SRC_DIR) clean

