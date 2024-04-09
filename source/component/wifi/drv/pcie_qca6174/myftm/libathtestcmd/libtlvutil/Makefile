LOCAL_PATH=.
SRC = \
				  templete/_cmd_txParmTxtTemplate.c \
				  templete/_cmd_txParmBinTemplate.c \
				  templete/_cmd_rxParmTxtTemplate.c \
				  templete/_cmd_rxParmBinTemplate.c \
				  templete/_cmd_calParmTxtTemplate.c \
				  templete/_cmd_calParmBinTemplate.c \
				  templete/_cmd_calDoneParmTxtTemplate.c \
				  templete/_cmd_calDoneParmBinTemplate.c \
				  templete/_cmd_rspGenericParmTxtTemplate.c \
				  templete/_cmd_rspGenericParmBinTemplate.c \
				  templete/_cmd_submitreportParmTxtTemplate.c \
				  templete/_cmd_submitreportParmBinTemplate.c \
				  templete/_cmd_pmParmTxtTemplate.c \
				  templete/_cmd_pmParmBinTemplate.c \
				  templete/_cmd_nartCmdParmTxtTemplate.c \
				  templete/_cmd_nartCmdParmBinTemplate.c \
				  templete/_cmd_nartRspParmTxtTemplate.c \
				  templete/_cmd_nartRspParmBinTemplate.c \
				  templete/_cmd_txStatusParmTxtTemplate.c \
				  templete/_cmd_txStatusParmBinTemplate.c \
				  templete/_cmd_rxStatusParmTxtTemplate.c \
				  templete/_cmd_rxStatusParmBinTemplate.c \
				  hex_dump.c testUtil.c parseRxBinCmdTlv.c genTxBinCmdTlv.c cmdParmsTemplate.c \
				  CliTlvCmd_if.c

OBJ = $(SRC:.c=.o)

OUT = libtlvutil.a

default: $(OUT)

INCLUDES += -I $(LOCAL_PATH)/../include \
				-I	$(LOCAL_PATH)/templete \
				-I	$(LOCAL_PATH)/common \
				-I	$(LOCAL_PATH)/defParm \

#CFLAGS = -g
CFLAGS+= -D_HOST_SIM_TESTING -D_FOR_HOST_TESTING 

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(AR) rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) 

