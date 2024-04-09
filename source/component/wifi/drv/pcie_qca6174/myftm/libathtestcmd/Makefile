LOCAL_PATH=$(shell pwd)
SRC = athtestcmdlib.c 

OBJ = $(SRC:.c=.o)

OUT = libathtestcmd.a

default: $(OUT)

INCLUDES += -I$(LOCAL_PATH)/../libtcmd  -I$(LOCAL_PATH)/include -I$(LOCAL_PATH)/libtlvutil  -I$(LOCAL_PATH)/libtlvutil/common

CFLAGS+= 

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(AR) rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) 


