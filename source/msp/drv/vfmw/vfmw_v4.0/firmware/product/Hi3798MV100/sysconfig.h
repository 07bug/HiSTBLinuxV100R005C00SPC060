
#ifndef __VFMW_SYSCONFIG_HEADER__
#define __VFMW_SYSCONFIG_HEADER__

//#define TWO_VDH

/* ����֧�ֵ�ͨ����Ŀ */
#ifdef CFG_MAX_CHAN_NUM
#define MAX_CHAN_NUM CFG_MAX_CHAN_NUM
#else
#define MAX_CHAN_NUM 32
#endif

/*��֧�ֵ�VDH����*/
#if defined(TWO_VDH)
#define MAX_VDH_NUM 2
#else
#define MAX_VDH_NUM 1
#endif

#define MAX_SCD_NUM  MAX_VDH_NUM
#define MAX_DSP_NUM  MAX_SCD_NUM
/* ϵͳ���ƼĴ�����ַ��λ�� */
#define SCD_RESET_REG_PHY_ADDR   0x0   //scd
/* Ӳ������IP�ӿڼĴ�����ַ */
#define VDM_REG_PHY_ADDR       0xf8c30000    // VDM0 �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define VDM_REG_PHY_ADDR_1     0xf8c30000    // VDM1�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define DNR_REG_PHY_ADDR       0x10450000    //DNR
#define SCD_REG_PHY_ADDR       0xf8c3c000    // scd �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define SCD_REG_PHY_ADDR_1     SCD_REG_PHY_ADDR    // scd �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define FOD_REG_PHY_ADDR       0x10150000    // fod �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define BPD_REG_PHY_ADDR       0xf8c60000
#define BTL_REG_PHY_ADDR       0xf8d00000   //0x10450000 // 0x101b0000   //BTL�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ����ʼ��ַ����
#define SYSTEM_REG_RANGE       (1024*1024)
/* �жϺ� */
#define VDM_INT_NUM            (95+32)
#define VDM_INT_NUM_1          (95+32)
#define SCD_INT_NUM            (104+32)

#define BPD_INT_NUM            (99+32)
#define DNR_INT_NUM            (61+32)
#define BTL_INT_NUM            (103+32)
/* ���Ե����Ͽɱ���Ƶ����ʹ�õ�memoryԤ�� */
//#define BOARD_MEM_BASE_ADDR    0x98000000
#define BOARD_MEM_BASE_ADDR    0x08000000
#define BOARD_MEM_TOTAL_SIZE   (72*1024*1024)

#endif
