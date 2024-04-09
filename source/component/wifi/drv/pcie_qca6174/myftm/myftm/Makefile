LOCAL_PATH=$(shell pwd)
SRC = myftm_wlan.c  myftm_main.c 

OBJ = $(SRC:.c=.o)

OUT = myftm

default: $(OUT)
	#cp -f $(LOCAL_PATH)/$(OUT) ../
	@echo myftm is ready to use.

INCLUDES += -I$(LOCAL_PATH)/../libtcmd -I$(LOCAL_PATH)/../libathtestcmd -I$(LOCAL_PATH)/../libtlvutil  -I$(LOCAL_PATH)/../libtlvutil/common

CFLAGS+= -DCONFIG_FTM_WLAN_AUTOLOAD 
CFLAGS+= -DCONFIG_FTM_WLAN
CFLAGS+= -DBOARD_HAS_ATH_WLAN_AR6320 
#CFLAGS+= -DDEBUG


#LIBS+= ../libnl-3.2.25/lib/.libs/libnl-3.a  ../libtcmd/libtcmd.a ../libathtestcmd/libtlvutil/libtlvutil.a ../libathtestcmd/libathtestcmd.a

LIBS+= ../libathtestcmd/libathtestcmd.a  ../libtcmd/libtcmd.a  ../libathtestcmd/libtlvutil/libtlvutil.a  ../libnl-3.2.25/lib/.libs/libnl-3.a  ../libnl-3.2.25/lib/.libs/libnl-genl-3.a


##try libnl-1
#LIBS+= ../libathtestcmd/libathtestcmd.a  ../libtcmd/libtcmd.a  ../libathtestcmd/libtlvutil/libtlvutil.a  ../libnl-1.1.4/lib/libnl.a


.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -static -pthread -lm -lrt -ldl -o $@

clean:
	rm -f $(OBJ) $(OUT) 

