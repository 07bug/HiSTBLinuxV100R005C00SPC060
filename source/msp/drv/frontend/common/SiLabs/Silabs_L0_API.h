#ifndef _L0_API_H_
#define _L0_API_H_
/*
****************************************************************************************
 Change log:

 As from V3.4.5
 Adding STRING_APPEND_SAFE to replace snprintf, since this function behaves differently
   between platforms when called with snprintf(msg, 1000, "%s%d", msg, value);
   Under Windows: the text for value is APPENDED to msg
   Under Linux:   the text for value is REPLACING the original msg.

 As from V3.3.9:
  Changing comment related to using #define SiTRACES_FEATURES     SiTRACES_MINIMAL
    WARNING : the minimal features mode disables tracing functions in the extern file

****************************************************************************************/

/* Un-comment the line below to compile for non-windows platforms (such as Linux) */
#define NO_WIN32
#define LINUX_ST_SDK2_I2C
#define HISILICON_I2C

#ifdef    NO_WIN32
  /* Linux: includes for non-Windows platform */
#ifdef    LINUX_ST_SDK2_I2C
  #ifdef    HISILICON_I2C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include "hi_type.h"
#include "hi_drv_i2c.h"
#include "hi_drv_gpioi2c.h"
  #else
    #include "i2c_wrapper.h"
    STCHIP_Error_t Chip_I2cWrite   (STCHIP_Handle_t hChip, u_int8_t ChipAddress,    unsigned char *Data, int NbData);
    STCHIP_Error_t Chip_I2cRead    (STCHIP_Handle_t hChip, u_int8_t ChipAddress,    unsigned char *Data, int NbData);
  #endif /* HISILICON_I2C */
#endif /* LINUX_ST_SDK2_I2C */

#ifndef   LINUX_ST_SDK2_I2C
  #include <stdlib.h>
  #include <stdio.h>
  #include <time.h>
  #include <sys/time.h>
  #include <string.h>
  #include <stdarg.h>
  #ifndef   NO_MATH_H_APPLICATION
    #include <math.h>
  #endif /* NO_MATH_H_APPLICATION */
/* <porting> Comment the line below to avoid using the Cypress chip for USB communication under Linux */
  #define   LINUX_USB_Capability
/* <porting> Comment the line below to avoid using I2C under Linux */
/*  #define   LINUX_I2C_Capability */
  #ifdef    LINUX_I2C_Capability
    #include <stdio.h>
    #include <linux/i2c-dev.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <string.h>
    int Linux_I2C_readByte  (signed   int adapter_nr, unsigned char address, unsigned char indexSize, unsigned char * pucAddressBuffer, signed   int iNbBytes, unsigned char * pucDataBuffer);
    int Linux_I2C_writeByte (signed   int adapter_nr, unsigned char address                                                           , signed   int iNbBytes, unsigned char * pucBuffer);
  #endif /* LINUX_I2C_Capability */
#endif /* LINUX_ST_SDK2_I2C */

#endif /* NO_WIN32 */

#ifndef   NO_WIN32
  /* includes for Windows */
  #include <windows.h>
  #include <time.h>
  #include <stdio.h>
/* <porting> Comment the line below to avoid using the Cypress chip for USB communication */
  #define   USB_Capability
#endif /* NO_WIN32 */

/* Uncomment the following line to activate all traces in the code */
//#define  SiTRACES

/* Uncomment the following line to activate SPI FW download */
#ifndef   LINUX_ST_SDK2_I2C
  #define  FW_DOWNLOAD_OVER_SPI
#endif /* LINUX_ST_SDK2_I2C */

/* <porting> Replace  CUSTOM_PRINTF with your print-out function.*/
#ifdef    LINUX_ST_SDK2_I2C
  #define CUSTOM_PRINTF(...)
#else  /* LINUX_ST_SDK2_I2C */
  #define CUSTOM_PRINTF(...)
#endif /* LINUX_ST_SDK2_I2C */

#define ERROR_MESSAGE_MAX_LENGH 1000
#define SILABS_TAG_SIZE           20
#define CHECK_FOR_ERRORS  if (L0_ErrorMessage()) CUSTOM_PRINTF("\n\n**************\n%s**************\n\n\n", L0_error_message);

/* <porting> Replace  STRING_APPEND_SAFE with whatever you need to append a new string to an existing one like the C printf function does. */
#define STRING_APPEND_SAFE(str,len,...)  snprintf(str+strlen(str), len-strlen(str), __VA_ARGS__);

#ifdef    SiTRACES
  #define SiERROR(error_message)         SiTRACE("%s",error_message); L0_StoreError( error_message );
  /* Porting: Select which of the following lines will allow you to display the function names */
  /* Porting: __FUNCTION__ is defined by GCC                                                   */
  /* Porting: __func__     is defined by C99 (it is not defined for VisualStudio 6)            */
  /* Porting: ""           will not display the function names, but will work on all platforms */
#ifndef   SiTAG
  #define SiTAG ""
#endif /* SiTAG */
#ifndef   SiLEVEL
  #define SiLEVEL 32
#endif /* SiLEVEL */

 /* #define SiTRACE(...)        SiTraceFunction(SiLEVEL, SiTAG, __FILE__, __LINE__, ""           ,__VA_ARGS__ ) */
 /* #define SiTRACE_X(...)      SiTraceFunction(     32,    "", __FILE__, __LINE__, ""           ,__VA_ARGS__ ) */
    #define SiTRACE(...)        SiTraceFunction(SiLEVEL, SiTAG, __FILE__, __LINE__, __FUNCTION__ ,__VA_ARGS__ )
    #define SiTRACE_X(...)      SiTraceFunction(     32,    "", __FILE__, __LINE__, __FUNCTION__ ,__VA_ARGS__ )
  /*#define SiTRACE             CUSTOM_PRINTF  */
  /*#define SiTRACE_X           CUSTOM_PRINTF  */
  /*#define SiTRACE(...)   */       /* nothing */
  /*#define SiTRACE_X(...) */       /* nothing */

  /* Replace 'SiTRACES_FULL' by 'SiTRACES_MINIMAL' in the following line to de-activate full features mode */
  /* WARNING : the minimal features mode disables tracing functions in the extern file                     */
  #define SiTRACES_FULL                  1
  #define SiTRACES_MINIMAL               0
#ifdef    LINUX_ST_SDK2_I2C
  #define SiTRACES_FEATURES     SiTRACES_MINIMAL
#else  /* LINUX_ST_SDK2_I2C */
  #define SiTRACES_FEATURES     SiTRACES_FULL
#endif /* LINUX_ST_SDK2_I2C */
  #define SiLOGS   SiTRACE
#else /* SiTRACES */
  #define SiTRACE(...)               /* empty */
  #define SiTRACE_X(...)             /* empty */
  #define SiTraceConfiguration(...)  /* empty */
  #define SiLOGS                     CUSTOM_PRINTF
#ifdef    LINUX_ST_SDK2_I2C
  #define SiERROR(error_message)     CUSTOM_PRINTF("%s",error_message)
#else  /* LINUX_ST_SDK2_I2C */
  #define SiERROR(error_message)     SiTRACE("%s", error_message); SiLOGS( error_message );
#endif /* LINUX_ST_SDK2_I2C */
#endif /* SiTRACES */

#define TRACES_PRINTF                SiTRACE
#define ALLOCATION_ERROR_MESSAGE     SiTRACE
#define TREAT_ERROR_MESSAGE          SiTRACE
#define TRACES_ERR                   SiTRACE
#define TRACES_TRACE                 SiTRACE
#define TRACES_SHOW                  SiTRACE
#define TRACES_USE                   SiTRACE
/*#define RWTRACES*/
#ifdef RWTRACES
/*    #warning "register-level traces activated (RWTRACES defined)" */
  #define L1_READ(ptr,  register)     L0_ReadRegisterTrace  (ptr->i2c, #register,     register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_SIGNED)
  #define L1_WRITE(ptr, register, v ) L0_WriteRegisterTrace (ptr->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
  #define L1_READ(ptr,  register)     L0_ReadRegister       (ptr->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_SIGNED)
  #define L1_WRITE(ptr, register, v ) L0_WriteRegister      (ptr->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

typedef enum _CONNECTION_TYPE
{
    SIMU = 0,
    USB,
    CUSTOMER,
    LINUX_I2C,
    LINUX_USB,
#ifdef    LINUX_ST_SDK2_I2C
    LINUX_KERNEL_I2C,
#endif /* LINUX_ST_SDK2_I2C */
    none
}  CONNECTION_TYPE;

typedef struct _L0_Context
{
    unsigned char   address;
    signed   int    indexSize;
    CONNECTION_TYPE connectionType;
    signed   int    trackWrite;
    signed   int    trackRead;
    signed   int    mustReadWithoutStop;
    unsigned char   tag_index;
             char   tag[SILABS_TAG_SIZE];
    unsigned int	u32I2cChannel;
    unsigned int	u32TunerId;
#ifdef    LINUX_I2C_Capability
    signed   int     adapter_nr;
#endif /* LINUX_I2C_Capability */
#ifdef    LINUX_ST_SDK2_I2C
  #ifdef HISILICON_I2C
    HI_U8 channel;
  #else
    STCHIP_Handle_t SDK2_i2c_Chip;
  #endif
#endif /* LINUX_ST_SDK2_I2C */
} L0_Context;

/* Layer 1 core types definitions */
typedef enum _ErrorCode
{
    Error_CODE_BASE                 = 2000,
    Error_INCORRECT_NB_READ,       /* 2001 */
    Error_INCORRECT_NB_WRITTEN,    /* 2002 */
    Error_DLL_LOAD,                /* 2003 */
    Error_ENUM_VAL_UNKNOWN,        /* 2004 */
    Error_COULD_NOT_WRITE_ITEM,    /* 2005 */
    Error_REGISTER_TYPE_UNKNOWN,   /* 2006 */
    Error_ENUM_OUT_OF_RANGE,       /* 2007 */
    Error_TYPE_IS_NOT_ENUMERATE,   /* 2008 */
    Error_VALUE_NOT_IN_ENUM_LIST,  /* 2009 */
    Error_COULD_NOT_UPDATE_ITEM,   /* 2010 */
    Error_VALUE_OUT_OF_RANGE,      /* 2011 */
    Error_UNKNOW_REGISTER,         /* 2012 */
    Error_READ_TRACES_ERROR,       /* 2013 */
    Error_WRITE_TRACES_ERROR,      /* 2014 */
    Error_UNKNOWN_COMMAND,         /* 2015 */
    Error_BUFFER_DOES_NOT_CONTAIN_REQUIRED_DATA         /* 2016 */
} ErrorCode;

typedef struct L1_Context {
  L0_Context *i2c;
  void       *specific;
} L1_Context;


#ifdef __cplusplus
extern "C" {
#endif

    #ifdef    SiTRACES
    void            SiTraceDefaultConfiguration(void);
    signed   int    SiTraceLevel               (signed   int bitfield, unsigned char on_off);
    void            SiTraceFunction            (unsigned char level, const char *tag, const char *name,          int linenumber, const char *func, const char *fmt, ...);
    const char*     SiTraceConfiguration       (const char *config);
    #else
    #define SiTraceDefaultConfiguration(...) /* empty */
    #endif /* SiTRACES */

    extern    char   *L0_error_message;

    signed   int     system_wait    (int time_ms);
    signed   int     system_time    (void);

    signed   int     strcmp_nocase  (const char* str1, const char* str2);
    signed   int     strcmp_nocase_n(const char* str1, const char* str2, unsigned int n);
    signed   int     L0_StoreTag    (const char *tag);
    signed   int     L0_StoreError  (const char *message);
    signed   int     L0_ErrorMessage(void);

    void             L0_Init              (unsigned int u32TunerId,L0_Context* i2c,unsigned int u32I2cChannel); /* initialize the Layer 0 DLL. It sets the layer 0 context parameters to startup values. It must be called first. It is automatically called by the Layer 1 init function.*/
    signed   int     L0_Connect           (L0_Context* i2c, CONNECTION_TYPE connType); /* Select the connection mode */
    const    char*   L0_InterfaceType     (L0_Context* i2c);
    signed   int     L0_SetAddress        (L0_Context* i2c, unsigned int add, int addSize); /* set the IP's i2c address. It must be called only once at startup, as the IP's address is not expected to change over time.*/
    signed   int     L0_ReadBytes         (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer) ;/* read  iNbBytes bytes from the IP. A buffer large enough to hold the values needs to be reserved by the upper layer.*/
    signed   int     L0_WriteBytes        (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer); /* write iNbBytes bytes in the IP. The referenced buffer contains the bytes to be written.*/
    void             L0_TrackRead         (L0_Context* i2c, unsigned int track); /* toggle the read traces. Useful for debug purposes, mostly to control that data read in the IP is properly translated to the above layers.*/
    void             L0_TrackWrite        (L0_Context* i2c, unsigned int track); /* toggle the write traces at the lower possible layer. Useful for debug purposes, to check the i2C bus data sent to the IP.*/

    signed   int     L0_ReadRawBytes      (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer);
    signed   int     L0_WriteRawBytes     (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer);

    signed   int     L0_ReadCommandBytes  (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer);
    signed   int     L0_WriteCommandBytes (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer);

    signed   long    L0_ReadRegister      (L0_Context *i2c,                           unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned);
    signed   long    L0_ReadRegisterTrace (L0_Context *i2c, char* name,               unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned);
    signed   long    L0_WriteRegister     (L0_Context *i2c,                           unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned char alone, long Value);
    signed   long    L0_WriteRegisterTrace(L0_Context *i2c, char* name, char* valtxt, unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned char alone, long Value);

    signed   int     L0_ReadString        (L0_Context* i2c, char *readString, unsigned char *pbtDataBuffer);
    signed   int     L0_WriteString       (L0_Context* i2c, char *writeString);
    const    char*   Si_I2C_TAG_TEXT      (void);

    signed   int     L0_FastI2C           (void);
    signed   int     L0_SlowI2C           (void);
    signed   int     L0_EnableSPI         (unsigned char  SPI_config);
    signed   int     L0_LoadSPIoverPortA  (unsigned char *SPI_data, unsigned char  length, unsigned short index);
    signed   int     L0_LoadSPIoverGPIF   (unsigned char *SPI_data, int  length);
    signed   int     L0_DisableSPI        (void);

#ifdef    USB_Capability
    signed   int     L0_Cypress_Process   (const char *cmd, const char *text, double dval, double *retdval, char **rettxt);
    signed   int     L0_Cypress_Configure (const char *cmd, const char *text, double dval, double *retdval, char **rettxt);
    signed   int     L0_Cypress_Cget      (const char *cmd, const char *text, double dval, double *retdval, char **rettxt);
    signed   int     L0_Cypress_VendorCmd (unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int   len);
    signed   int     L0_Cypress_VendorRead(unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int *plen);
#endif /* USB_Capability*/

#ifdef __cplusplus
}
#endif

#endif /* _L0_API_H_*/

