################################################################################
#    Copyright (C) 2014 Hisilicon STB Development Dept
#    All rights reserved.
#####
#    Create by Cai Zhiyong
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#    http://www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
################################################################################

SRCS-y  += env_if.c task.c app.c

ifneq ($(CONFIG_SUPPORT_CA_RELEASE),y)
SRCS-$(CONFIG_CMDLINE)   += cmd_ca.c
SRCS-$(CONFIG_CA_IF)     += ca_if.c
endif

ifeq ($(TOPDIR)/app/cmd_bsd.c, $(wildcard $(TOPDIR)/app/cmd_bsd.c))
ifeq ($(CFG_HI_BUILD_WITH_PRODUCT),y)
ifeq ($(findstring $(CFG_HI_ADVCA_TYPE),NAGRA),NAGRA)
ifneq ($(CFG_HI_TWOSTAGEBOOT_SUPPORT),y)
    CFLAGS += -I$(COMMON_DIR)/include
    CFLAGS += -I$(TOPDIR)/../product/driver/include
    CFLAGS += -DHI_MINIBOOT_SUPPORT=1
    SRCS-$(CONFIG_CMDLINE) += cmd_bsd.c
endif
endif
endif
endif
