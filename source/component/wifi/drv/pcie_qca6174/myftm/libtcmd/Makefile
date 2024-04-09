LOCAL_PATH=.
SRC = libtcmd.c  nl80211.c  os.c

OBJ = $(SRC:.c=.o)

OUT = libtcmd.a

default: $(OUT)

INCLUDES += -I. -I$(INCLUDE_LIBNL32_HEADER) 
#INCLUDES += -I$(INCLUDE_LIBNL32_HEADER) 

#CFLAGS+= -DWLAN_API_NL80211 -DLIBNL_2 -DCONFIG_AR6002_REV6
CFLAGS+= -DWLAN_API_NL80211  -DLIBNL_2 

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(AR) rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) 

