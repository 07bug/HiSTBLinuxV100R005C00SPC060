
/***********************************************************************
*
* Copyright (c) 2006 Hisilicon - All Rights Reserved
*
* File: $basedef.h$
* Date: $2006/11/30$
* Revision: $v1.0$
* Purpose: basic definition common in the whole project
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2006/11/30                              Original
*
* Dependencies:
*
************************************************************************/

#ifndef __BASETYPE_DEFS__
#define __BASETYPE_DEFS__

#ifdef __cplusplus
extern "C" {
#endif

//#include "sysconfig.h"
//#include "vfmw_osal.h"

/*************************************************************************
 *	This software supports the following platform. Platform is defined in
 *  the according compile environment( eg. use '-D' in the makefile ).

 *      ENV_ARMLINUX_KERNEL     --- final version
 *************************************************************************/


/*************************************************************************
 *	compile switches.
 *************************************************************************/

#define H264_ENABLE
#define MVC_ENABLE
#define MPEG2_ENABLE
#define AVS_ENABLE
#define MPEG4_ENABLE
#define REAL8_ENABLE
#define REAL9_ENABLE
#define VC1_ENABLE
#define DIVX3_ENABLE
#define VP6_ENABLE
#define VP8_ENABLE
#define HEVC_ENABLE

//typedef UINT32    PHYADDR;

/*************************************************************************
 * macro
 *************************************************************************/

#if defined(VFMW_DPRINT_SUPPORT) && defined(ENV_ARMLINUX_KERNEL)
#define REC_POS(Data)  DBG_AddTrace( (SINT8*)__FUNCTION__, __LINE__, (SINT32)Data)
#else
#define REC_POS(Data)
#endif

/* MAX()/MIN(): �����С */
#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))
#define ABS(x)            (( (x) <  0  ) ? -(x) : (x))
#define SIGN(a)           (( (a)<0 ) ? (-1) : (1))
#define MEDIAN(a, b, c)   ((a) + (b) + (c) - MIN((a), MIN((b), (c))) - MAX((a), MAX((b), (c))))

#define CLIP1(high, x)             (MAX( MIN((x), high), 0))
#define CLIP3(low, high, x)        (MAX( MIN((x), high), low))
#define CLIP255(x)                 (MAX( MIN((x), 255), 0))
#ifdef TV_SUPPORT_HIS5V100
#define TV_ALIGN_8BIT_YSTRIDE(w)   ((((w)%256)==0)?(w):(((((w)/256)%2)==0)?((((w)/256)+1)*256):((((w)/256)+2)*256)))
#endif

#if defined(ENV_ARMLINUX_KERNEL)
#ifndef  HI_ADVCA_FUNCTION_RELEASE
#define pos()  dprint(PRN_ALWS,"%s: L%d\n", __FUNCTION__, __LINE__ )
#else
#define pos()
#endif
#endif

/* =============== ����ƽ̨����ĺ궨�� ================ */
#if 0
/* _LOG(): ��LOG�ļ��д�ӡ��Ϣ */
#ifdef  LOG_PRINT_ON
#if defined( ENV_ARMLINUX_KERNEL )  /* ARMLINUX �ں�̬�汾 */
#define _LOG(...)                                       \
    if( 0 != g_LogEnable )                                  \
    {                                                       \
        UINT8 logchar[500];                                 \
        snprintf(logchar, 500, __VA_ARGS__ );               \
        vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite(logchar, strlen(logchar) + 1, g_fpLog);   \
    }
//�ں�̬����ʱ��֧�ִ������Ĺ��ܣ���Ϊ�������������ļ� �ķ���
#define _FWRITE
#endif
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif	//end of "#ifndef __BASETYPE_DEFS__"

