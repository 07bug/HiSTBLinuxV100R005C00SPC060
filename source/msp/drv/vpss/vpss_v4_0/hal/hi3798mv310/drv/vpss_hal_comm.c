//#include "xdp_kernel_head.h"
#include "vpss_hal_comm.h"
//#include "xdp_env_common.h"

////===================================
//// global var
////===================================
//S_VPSS_REGS_TYPE* pstVPSSRegMemVir[XDP_MAX_NODE_NUM];
//
//HI_U32 u32NodePhyAddr[XDP_MAX_NODE_NUM];
//
//S_VPSS_REGS_TYPE* pstVPSSRegLogic;
//
//
////===================================
//// func
////===================================
//
//
//
HI_S32 VPSS_RegWrite(HI_ULONG a, HI_U32 b)
{
    volatile HI_U32 *addr = (HI_U32 *)a;

    *addr = b;
    return HI_SUCCESS;
}

HI_U32 VPSS_RegRead(volatile HI_U32 *a)
{
    volatile HI_U32 *addr = (HI_U32 *)a;

    return (*(addr));
}
//
//
//S_VPSS_REGS_TYPE* VPSS_HAL_GetVpssNode(HI_U32 u32HandleNo)
//{
//    S_VPSS_REGS_TYPE* pstVPSSReg = NULL;
//
//    if(u32HandleNo >= XDP_MAX_NODE_NUM)
//    {
//        XDP_PRINT("VPSS HandleNo=%d is over range!\n",u32HandleNo);
//        return NULL;
//    }
//
//    if(pstVPSSRegMemVir[u32HandleNo] == NULL)
//    {
//        XDP_PRINT("pstVPSSRegMem[%d] is NULL!\n",u32HandleNo);
//        return NULL;
//    }
//
//    pstVPSSReg = pstVPSSRegMemVir[u32HandleNo];
//
//    return pstVPSSReg;
//}
//
//HI_S32 VPSS_HAL_SetVpssNode(HI_U8* pu8VirAddr)
//{
//    HI_U32 ii=0;
//
//    XDP_CHECK_NULL_PTR(pu8VirAddr);
//
//    for(ii=0; ii<XDP_MAX_NODE_NUM; ii++)
//    {
//        pstVPSSRegMemVir[ii] = (S_VPSS_REGS_TYPE *)(pu8VirAddr+ALIGN_16BTYE(sizeof(S_VPSS_REGS_TYPE))*ii);
//    }
//
//    return HI_SUCCESS;
//}
//
//S_VPSS_REGS_TYPE* VPSS_HAL_GetLocalVpssReg(HI_VOID)
//{
//    S_VPSS_REGS_TYPE* pstVPSSReg = NULL;
//
//    pstVPSSReg = pstVPSSRegLogic;
//
//    return pstVPSSReg;
//}
//
//HI_S32 VPSS_HAL_SetLocalVpssReg(S_VPSS_REGS_TYPE* pstVpssReg)
//{
//    XDP_CHECK_NULL_PTR(pstVpssReg);
//    pstVPSSRegLogic = pstVpssReg;
//
//    return HI_SUCCESS;
//}
//
//HI_U32 VPSS_HAL_GetVpssNodePhyAddr(HI_U32 u32HandleNo)
//{
//    return u32NodePhyAddr[u32HandleNo];
//}
//
//HI_VOID VPSS_HAL_SetVpssNodePhyAddr(HI_U32 u32PhyAddr)
//{
//    HI_U32 ii=0;
//    for(ii=0; ii<XDP_MAX_NODE_NUM; ii++)
//    {
//        u32NodePhyAddr[ii] = u32PhyAddr+ALIGN_16BTYE(sizeof(S_VPSS_REGS_TYPE))*ii;
//      XDP_PRINT_INFO("node addr = 0x%x\n",u32NodePhyAddr[ii]);
//    }
//}
