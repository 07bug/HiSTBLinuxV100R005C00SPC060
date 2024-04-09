#ifndef __DRV_PDM_IOCTL_H__
#define __DRV_PDM_IOCTL_H__

#include "hi_type.h"
#include "hi_drv_pdm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMD_PDM_GET_DATA                _IOWR(HI_ID_PDM, IOC_PDM_GET_RESERVE_MEM_DATA, PDM_GET_DATA_S)
#define CMD_PDM_COMPAT_GET_DATA         _IOWR(HI_ID_PDM, IOC_PDM_GET_RESERVE_MEM_DATA, PDM_COMPAT_GET_DATA_S)
#define CMD_PDM_GET_RESERVE_MEM_INFO    _IOWR(HI_ID_PDM, IOC_PDM_GET_RESERVE_MEM_INFO, PDM_RESERVE_MEM_INFO_S)

typedef enum hiIOC_PDM_E
{
    IOC_PDM_GET_RESERVE_MEM_DATA = 0,
    IOC_PDM_GET_RESERVE_MEM_INFO,

    IOC_PDM_BUTT
}IOC_PDM_E;

typedef struct tagPDM_GET_DATA
{
    HI_CHAR  BufName[MAX_BUFFER_NAME_SIZE];
    HI_U8    *BufAddr;
    HI_U32   BufLenth;
}PDM_GET_DATA_S;

typedef struct tagPDM_COMPAT_GET_DATA
{
    HI_CHAR BufName[MAX_BUFFER_NAME_SIZE];
    HI_U32  BufAddr;
    HI_U32  BufLenth;
}PDM_COMPAT_GET_DATA_S;

typedef struct tagPDM_RESERVE_MEM_INFO
{
    HI_CHAR BufName[MAX_BUFFER_NAME_SIZE];
    HI_U32  PhyAddr;
    HI_U32  Size;
}PDM_RESERVE_MEM_INFO_S;

#ifdef __cplusplus
}
#endif

#endif

