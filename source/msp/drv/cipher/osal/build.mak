CIPHER_CFLAGS += -I$(CIPHER_DIR)/osal/include

CIPHER_OBJS   += osal/drv_osal_init.o \
                 osal/drv_osal_sys.o  \
                 osal/drv_osal_tee.o
