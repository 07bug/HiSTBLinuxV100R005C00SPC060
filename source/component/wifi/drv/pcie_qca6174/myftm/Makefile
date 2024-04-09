
export TOOLCHAIN=
export CROSS_COMPILE=arm-histbv300-linux-
#export KERNELPATH=/lib/modules/${shell uname -r}/build
export KERNELARCH=arm
export TOOLPREFIX=${CROSS_COMPILE}

export MAKEARCH=make ARCH=$(KERNELARCH) CROSS_COMPILE=$(TOOLPREFIX)

export CC=$(TOOLPREFIX)gcc
export AR=$(TOOLPREFIX)ar
export LD=$(TOOLPREFIX)ld

export MYFTM_TOPDIR=$(shell pwd)/
export LIBNL32_TOPDIR=${MYFTM_TOPDIR}/libnl-3.2.25
#export LIBNL32_TOPDIR=${MYFTM_TOPDIR}/libnl-1.1.4
export LIBTCMD_TOPDIR=$(MYFTM_TOPDIR)/libtcmd
export LIBTLVUTIL_TOPDIR=$(MYFTM_TOPDIR)/libathtestcmd/libtlvutil
export LIBATHTESTCMD_TOPDIR=$(MYFTM_TOPDIR)/libathtestcmd

export MYFTM_MYFTM=$(MYFTM_TOPDIR)/myftm

# Use local libnl library or not
export BUILD_LIBNL=y
export INCLUDE_LIBNL32_HEADER=${MYFTM_TOPDIR}/libnl-3.2.25/include
export INCLUDE_LIBNL32_LIB=-lm ${MYFTM_TOPDIR}/libnl-3.2.25/lib/.libs/libnl-3.a
export INCLUDE_LIBNL32_GENL_LIB =-lm ${MYFTM_TOPDIR}/libnl-3.2.25/lib/.libs/libnl-genl-3.a


default: myftm

clean: myftm_clean  libtlvutil_clean  libtcmd_clean  libathtestcmd_clean libtlvutil_clean

myftm: myftm_clean libnl libtcmd libathtestcmd  libtlvutil
	@echo Build myftm
	cd $(MYFTM_MYFTM) && ${MAKEARCH} 

myftm_clean:
	@echo clean myftm
	cd $(MYFTM_MYFTM) && ${MAKEARCH} clean

libtlvutil: libtlvutil_clean
	@echo Build libtlvutil
	cd $(LIBTLVUTIL_TOPDIR) && ${MAKEARCH}

libtlvutil_clean:
	@echo clean libtlvutil
	cd $(LIBTLVUTIL_TOPDIR) && ${MAKEARCH} clean

libtcmd: libtcmd_clean
	@echo Build libtcmd
	cd $(LIBTCMD_TOPDIR) && ${MAKEARCH}

libtcmd_clean:
	@echo clean libtcmd
	cd $(LIBTCMD_TOPDIR) && ${MAKEARCH} clean


libathtestcmd: libathtestcmd_clean
	@echo Build libathtestcmd
	cd $(LIBATHTESTCMD_TOPDIR) && ${MAKEARCH}

libathtestcmd_clean:
	@echo clean libathtestcmd
	cd $(LIBATHTESTCMD_TOPDIR) && ${MAKEARCH} clean

libnl_config:
	@echo Config libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && \
	./configure --host=$(KERNELARCH) CC=$(TOOLPREFIX)gcc AR=$(TOOLPREFIX)ar LD=$(TOOLPREFIX)ld

libnl: libnl_config libnl_clean
	@echo Build libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && \
	${MAKEARCH}

libnl_clean:
	@echo Clean libnl1-3.2.25
	cd $(LIBNL32_TOPDIR) && ${MAKEARCH} clean
