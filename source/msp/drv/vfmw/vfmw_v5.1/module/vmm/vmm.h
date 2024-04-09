#ifndef __HI_DRV_VMM_H__
#define __HI_DRV_VMM_H__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VMM_MAX_NAME_LEN (16)
#define VMM_SUCCESS                     (SINT32)(0)
#define VMM_FAILURE                     (SINT32)(0xFFFFFFFF)
#define ERR_VMM_ALLOC_FAILED            (SINT32)(0xFF000000)
#define ERR_VMM_INIT_FAILED             (SINT32)(0xFF000001)
#define ERR_VMM_INVALID_PARA            (SINT32)(0xFF000002)
#define ERR_VMM_NULL_PTR                (SINT32)(0xFF000003)
#define ERR_VMM_NOT_SUPPORT             (SINT32)(0xFF000004)
#define ERR_VMM_FULL                    (SINT32)(0xFF000005)
#define ERR_VMM_EMPTY                   (SINT32)(0xFF000006)
#define ERR_VMM_NOT_INIT                (SINT32)(0xFF000007)
#define ERR_VMM_NODE_ALREADY_EXIST      (SINT32)(0xFF000008)
#define ERR_VMM_LOCATION_CONFLICT       (SINT32)(0xFF000009)
#define ERR_VMM_NODE_NOT_EXIST          (SINT32)(0xFF00000A)
#define ERR_VMM_INVALID_STATE           (SINT32)(0xFF00000B)

#define VMM_TRUE                        (SINT32)(1)
#define VMM_FALSE                       (SINT32)(0)

/******************************************************************************************************************/
/*      CMD_TYPE                        |         INPUT_PARAM_TYPE        |          OUTPUT_PARAM_TYPE            */
/*----------------------------------------------------------------------------------------------------------------*/
/*     VMM_CMD_Alloc                    |        VMM_BUFFER_S             |            VMM_BUFFER_S               */
/*     VMM_CMD_Release                  |        VMM_BUFFER_S             |            VMM_BUFFER_S               */
/*     VMM_CMD_ReleaseBurst             |        VMM_RLS_BURST_S          |            VMM_RLS_BURST_S            */
/*----------------------------------------------------------------------------------------------------------------*/
/*     VMM_CMD_BLK_Alloc                |        VMM_BUFFER_S             |            VMM_BUFFER_S               */
/*     VMM_CMD_BLK_Release              |        VMM_BUFFER_S             |            NULL                       */
/*     VMM_CMD_BLK_ConfigMemPool        |        VMM_BUFFER_S             |            NULL                       */
/*     VMM_CMD_BLK_Map                  |        VMM_BUFFER_S             |            VMM_BUFFER_S               */
/*     VMM_CMD_BLK_Unmap                |        VMM_BUFFER_S             |            NULL                       */
/*     VMM_CMD_BLK_ConfigMemNode        |        VMM_BUFFER_S             |            NULL                       */
/*     VMM_CMD_BLK_ReleaseBurst         |        VMM_RLS_BURST_S          |            NULL                       */
/*     VMM_CMD_BLK_SetPriorityPolicy    |        undetermined             |            NULL                       */
/*     VMM_CMD_BLK_GetMemNodeInfo       |        undetermined             |            undetermined               */
/*     VMM_CMD_BLK_SetLocation          |        VMM_ATTR_S               |            NULL                       */
/*     VMM_CMD_BLK_CancleCmd            |        VMM_CANCLE_CMD_S         |            NULL                       */
/*----------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    /*memory*/
    VMM_CMD_Alloc = 0,
    VMM_CMD_Release,
    VMM_CMD_ReleaseBurst,

    VMM_CMD_TYPE_BUTT
} VMM_CMD_TYPE_E;

typedef enum
{
    /*memory*/
    VMM_CMD_BLK_Alloc = 0,
    VMM_CMD_BLK_Release,

    /*pre memory*/
    VMM_CMD_BLK_ConfigMemPool,

    VMM_CMD_BLK_Map,
    VMM_CMD_BLK_Unmap,

    /*External configuration frame memory(just one Node)*/
    VMM_CMD_BLK_ConfigMemNode,

    VMM_CMD_BLK_ReleaseBurst,

    VMM_CMD_BLK_SetPriorityPolicy,
    VMM_CMD_BLK_GetMemNodeInfo,

    /*tracker*/
    VMM_CMD_BLK_SetLocation,

    VMM_CMD_BLK_CancleCmd,

    VMM_CMD_BLK_TYPE_BUTT
} VMM_CMD_BLK_TYPE_E;

typedef enum
{
    VMM_CMD_PRIO_MIN = 0,
    VMM_CMD_PRIO_MAX,
    VMM_CMD_PRIO_BUTT
} VMM_CMD_PRIO_E;

typedef enum
{
    /*memory*/
    VMM_MEM_TYPE_SYS_ADAPT = 0,
    VMM_MEM_TYPE_FORCE_MMZ,
    VMM_MEM_TYPE_PRE_ALLOC,
    VMM_MEM_TYPE_EXT_CONFIG,
    VMM_MEM_TYPE_BUTT
} VMM_MEM_TYPE_E;

typedef enum
{
    /*tracker*/
    VMM_LOCATION_INSIDE = 0,
    VMM_LOCATION_OUTSIDE,

    VMM_LOCATION_BUTT,
} VMM_LOCATION_E;

typedef struct
{
    SINT8  BufName[VMM_MAX_NAME_LEN];
    ULONG  pStartVirAddr;
    UADDR  StartPhyAddr;
    UINT32 Size;
    UINT32 SecFlag;
    UINT32 Map;
    UINT32 Cache;
    VMM_MEM_TYPE_E MemType;

    SINT64 PrivID;
} VMM_BUFFER_S;

typedef struct
{
    UADDR          PhyAddr;
    VMM_LOCATION_E Location;
} VMM_ATTR_S;

typedef struct
{
    SINT64         PrivID;
    UINT64         PrivMask;
} VMM_RLS_BURST_S;

typedef struct
{
    VMM_CMD_TYPE_E CmdID;
    SINT64         PrivID;
    UINT64         PrivMask;
} VMM_CANCLE_CMD_S;

typedef SINT32(*PFN_VMM_CALLBACK)(VMM_CMD_TYPE_E CmdID, VOID *pParamOut, SINT32 RetVal);

/*FUNTION*/
SINT32 VMM_ModuleInit(PFN_VMM_CALLBACK pfVmmCallback);

SINT32 VMM_ModuleDeInit(VOID);

SINT32 VMM_SendCommandBlock(VMM_CMD_BLK_TYPE_E CmdID, VOID *pParamInOut);

SINT32 VMM_SendCommand(VMM_CMD_TYPE_E CmdID, VMM_CMD_PRIO_E Proir, VOID *pParamIn);

#ifdef __cplusplus
}
#endif


#endif //__HI_DRV_VMM_H__
