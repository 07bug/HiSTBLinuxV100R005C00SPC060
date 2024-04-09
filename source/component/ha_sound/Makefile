#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../..
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#       variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

objects:=

ifeq ($(CFG_HI_SONIC_SUPPORT),y)
objects+= hi_sonic
endif

objects_clean:=${addsuffix _clean,${objects}}
objects_install:=${addsuffix _install,${objects}}
objects_uninstall:=${addsuffix _uninstall,${objects}}

ifeq (${obj},)
depends:=$(objects)
else
depends:=${obj}
endif
depends_clean:=$(addsuffix _clean,${depends})
depends_install:=$(addsuffix _install,${depends})
depends_uninstall:=$(addsuffix _uninstall,${depends})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall 
all:    ${depends}

clean:  ${depends_clean}

install:${depends_install}

uninstall:${depends_uninstall}

#==================================================================
#                          modules
#==================================================================
.PHONY: ${objects} ${objects_clean} ${objects_install} ${objects_uninstall}

${objects}:
	make -C $@ all 

${objects_clean}:
	make -C $(patsubst %_clean,%,$@) clean

${objects_install}:
	make -C $(patsubst %_install,%,$@) install

${objects_uninstall}:
	make -C $(patsubst %_uninstall,%,$@) uninstall