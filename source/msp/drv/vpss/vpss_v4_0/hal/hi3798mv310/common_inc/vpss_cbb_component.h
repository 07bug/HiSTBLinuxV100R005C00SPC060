//����ÿ����Ŀ�߼��ܹ�ö�٣���������ͨ��ö�٣��㷨ģ��ö�٣�����ģ��ö�ٵ�

#ifndef __VPSS_CBB_COMPONENT_H__
#define __VPSS_CBB_COMPONENT_H__

#include "hi_type.h"
#include "hi_reg_common.h"

typedef enum
{
    CBB_FRAME_READ_NX2 = 0x0,//cf
    CBB_FRAME_READ_NX1,//p1
    CBB_FRAME_READ_CUR,//p2
    CBB_FRAME_READ_REF,//p3
    CBB_FRAME_READ_REE,//p3i

    CBB_FRAME_WRITE_VHD0,//out0
    CBB_FRAME_WRITE_RFR,//nr_rfr
    CBB_FRAME_WRITE_CUE,//di_rfr

    CBB_FRAME_BUTT,
} CBB_FRAME_CHANNEL_E;


typedef enum
{
    CBB_INFO_DEI_ST = 0,//di rst,wst
    CBB_INFO_PRJ_V,//prjv
    CBB_INFO_PRJ_H,//prjh
    CBB_INFO_DI,//di cnt
    CBB_INFO_RGMV,      //
    CBB_INFO_TNRRGMV,
    CBB_INFO_BLKMV,
    CBB_INFO_BLKMT,
    CBB_INFO_TNR_MAD,   //mad_w,
    CBB_INFO_SNR_MAD,   //  snr_mad_r
    CBB_INFO_STT,       //����ģ���ͳ�ƻ�дͨ��
    CBB_INFO_BUTT,
} CBB_INFO_CHANNEL_E;

typedef enum
{
    CBB_INFO_WBC_ALL,
    CBB_INFO_WBC_RWZB,  //����ָ��
    CBB_INFO_WBC_BUTT,
} CBB_CALC_INFO_E; //�߼������д��Ϣ

typedef enum
{
    CBB_FUNC_VC1,           //������������vc������id
    CBB_FUNC_VHD0_CROP,
    CBB_FUNC_VHD0_VPZME,    //����
    CBB_FUNC_VHD0_ZME,
    CBB_FUNC_VHD0_LBOX,
    //CBB_FUNC_VHD0_MIRROR,
    CBB_FUNC_VHD0_FLIP,
    CBB_FUNC_VHD0_UV,
    CBB_FUNC_TUNNEL_IN,
    CBB_FUNC_TUNNEL_OUT, //����
    CBB_FUNC_TRANS,
    CBB_FUNC_SMMU,
    CBB_FUNC_ROTATION_Y,
    CBB_FUNC_ROTATION_C,
    CBB_FUNC_SPEED_UP_4PIXEL,
    CBB_FUNC_CTS10BIT,
    CBB_FUNC_FDIFRO,
    CBB_FUNC_BUTT,
} CBB_FUNC_E;

/*
ON/OFF
mode: user defaut random
para: pq_struct
*/



typedef enum
{
    CBB_ISR_NODE_COMPLETE = 0,  //raw_eof
    CBB_ISR_TIMEOUT,            //raw_timeout
    CBB_ISR_BUS_WRITE_ERR,      //raw_bus_w_err
    CBB_ISR_LIST_COMPLETE,      //raw_eof_end
    CBB_ISR_VHD0_TUNNEL,        //raw_vhd0_tunl
    CBB_ISR_DCMP_ERR,           //raw_dcmp_err
    CBB_ISR_BUS_READ_ERR,       //raw_bus_r_err

    CBB_ISR_SMMU_S_MIN,
    CBB_ISR_SMMU_S_TLBMISS  = CBB_ISR_SMMU_S_MIN,       //ints_tlbmiss_stat
    CBB_ISR_SMMU_S_PTW_TRANS,   //ints_ptw_trans_stat
    CBB_ISR_SMMU_S_TLBINVALID_RD,   //ints_tlbinvalid_rd_msk
    CBB_ISR_SMMU_S_TLBINVALID_WR,   //ints_tlbinvalid_wr_msk

    CBB_ISR_SMMU_NS_MIN,
    CBB_ISR_SMMU_NS_TLBMISS = CBB_ISR_SMMU_NS_MIN,  //ints_tlbmiss_stat
    CBB_ISR_SMMU_NS_PTW_TRANS,  //ints_ptw_trans_stat
    CBB_ISR_SMMU_NS_TLBINVALID_RD,  //ints_tlbinvalid_rd_msk
    CBB_ISR_SMMU_NS_TLBINVALID_WR,  //ints_tlbinvalid_wr_msk

    CBB_ISR_BUTT,
} CBB_ISR_E;

#endif
