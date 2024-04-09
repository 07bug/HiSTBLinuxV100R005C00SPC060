#ifndef __VMM_MSGLIST_MANAGER_H__
#define __VMM_MSGLIST_MANAGER_H__

#include "vmm.h"
#include "vmm_osal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union
{
    VMM_BUFFER_S    BufRec;
    VMM_RLS_BURST_S RlsBurst;
} InputParam;

typedef struct
{
    VMM_CMD_TYPE_E CmdID;
    InputParam     Param;
    SINT64         PrivID;    /*for ReleaseBurst fast*/
    UINT32         Tick;
} Msg_Data_S;

typedef struct
{
    struct list_head list;

    /*payload*/
    Msg_Data_S  Data;
} Msg_Node_S;

typedef struct
{
    UINT32         CmdValid;
    VMM_CMD_TYPE_E CmdID;
    UINT32         PrivIDValid;
    SINT64         PrivID;
    UINT64         PrivMask;
} Msg_Delete_S;

SINT32  VMM_Msglist_Init(VOID);

VOID    VMM_Msglist_Deinit(VOID);

SINT32  VMM_Msglist_AddNode(Msg_Data_S *pData, VMM_CMD_PRIO_E Proir);

SINT32  VMM_Msglist_TakeOutNode(Msg_Data_S *pData);   //the node which be taken out should be deleted at the same time

SINT32  VMM_Msglist_DeleteSpecifiedNode(Msg_Delete_S *pRlsBurst);

SINT32  VMM_Msglist_IsEmpty(VOID);

SINT32  VMM_Msglist_ReadProc(VOID *p);

#ifdef __cplusplus
}
#endif

#endif  // __VMM_MSGLIST_MANAGER_H__
