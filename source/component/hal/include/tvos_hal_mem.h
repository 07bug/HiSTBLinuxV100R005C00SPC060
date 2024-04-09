/**
 * \file
 * \brief Describes the information about the mem module.
 */

#ifndef __TVOS_HAL_MEM_H__
#define __TVOS_HAL_MEM_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"
#include "tvos_hal_vout.h"

#ifdef ANDROID_HAL_MODULE_USED
#include <hardware/hardware.h>
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_MEM */
/** @{ */  /** <!-- [HAL_MEM] */

#define MEM_HARDWARE_MODULE_ID      "mem"
#define MEM_HARDWARE_MEM0           "mem0"
#define MEM_HEADER_VERSION          (1)
#define MEM_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, MEM_HEADER_VERSION)

#define IN
#define OUT
#define INVALID_MEM_HANDLE (MEM_HANDLE)NULL //��Ч���

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_MEM */
/** @{ */  /** <!-- [HAL_MEM] */

#ifdef ANDROID_HAL_MODULE_USED
/** memory module *//** CNcomment:memoryģ�� */
typedef struct _MEM_MODULE_S
{
    struct hw_module_t common;
} MEM_MODULE_S;
#endif

/**Struct of memory type*/
/**CNcomment: �ڴ�����   */
typedef enum _E_MEM_USAGE
{
    E_MEM_USEAGE_VES,          /**<used for video es buffer*//**<CNcomment: ������Ƶes����buffer*/
    E_MEM_USEAGE_VES_SECURE,   /**<used for video es secure buffer*//**<CNcomment: ������Ƶes����buffer*/
    E_MEM_USEAGE_VES_BUT
} E_MEM_USAGE;

typedef enum _E_FRAME_MEM_USAGE
{
    E_MEM_USEAGE_VO,         /**<used for video frame to VDP*//**<CNcomment:  ������Ƶ��ʾ��֡�� */
    E_MEM_USEAGE_VO_SECURE,  /**<used for video secure frame to VDP*//**<CNcomment: ������Ƶ��ʾ��֡�� */
    E_MEM_USEAGE_VO_BUT
}E_FRAME_MEM_USAGE;

typedef void* MEM_HANDLE; //�ڴ���


/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_MEM*/
/** @{*/  /** <!-- -[HAL_MEM]=*/

/**Memory device structure*//** CNcomment:Memory�豸�ṹ*/
typedef struct _MEM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief:alloc mem.CNcomment:�����ڴ� CNend
    \attention \n
    Other functions cannot be useful before mem_alloc, return SUCCESS.
    CNcomment: ������ӿ�֮ǰ, ����������������ȷ����.CNend
    \param[in] eUsage���ڴ�ʹ�ó�������
    \param[in] u32Size: �����С mem size.CNcomment:�����С CNend
    \param[in] pszName: mem�� mem name.CNcomment:�ڴ����� CNend
    \param[out] hHandle: mem handle.CNcomment:�ڴ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_MEM_ALLOC_NO_MEM no mem.CNcomment:���ڴ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid(useage unsupport or size == 0) .CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::E_MEM_USAGE

    \par example
    \code
    \endcode
    */
    S32  (*mem_alloc) (struct _MEM_DEVICE_S* pstDev,IN E_MEM_USAGE eUsage, IN S32 u32Size, IN CHAR * pszName, OUT MEM_HANDLE* hHandle);

    /**
    \brief:free mem.CNcomment:�ͷ��ڴ� CNend
    \attention \n
    Other functions cannot be useful after mem_free.
    CNcomment: ������ӿ�֮��, ����������������ȷ����.CNend
    \param[in] hHandle: mem handle.CNcomment:�ڴ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_free)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle);

    /**
    \brief:get phy addr of mem.CNcomment:��ȡ�ڴ�������ַ CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle��MEM_HANDLE�ڴ���
    \param[out] ppvPhyAddr: �����ַָ�� mem phyaddr.CNcomment:�����ַ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_phy_addr)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvPhyAddr);

    /**
    \brief:map mem.CNcomment:map�ڴ���û�̬�����ַ CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle��MEM_HANDLE�ڴ���
    \param[out] ppvVirAddr: �û�̬��ַָ�� mem viraddr.CNcomment:�û�̬��ַ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_map)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvVirAddr);

    /**
    \brief:unmap mem.CNcomment:unmap�ڴ� CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle��MEM_HANDLE�ڴ���
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_unmap)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle);
    /**
    \brief:flush cache to mem.CNcomment:cache�е�����д���ڴ� CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle��MEM_HANDLE�ڴ���
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_flush)(struct _MEM_DEVICE_S* pstDev, IN MEM_HANDLE hHandle);
    /**
    \brief:alloc video pic mem.CNcomment:������Ƶͼ���ڴ� CNend
    \attention \n
    .
    CNcomment: .CNend
    \param[in] s32Width: video width.CNcomment:֡�Ŀ� CNend
    \param[in] pszName: video height.CNcomment:֡�ĸ� CNend
    \param[in] eUsage���ڴ�ʹ�ó�������
    \param[in] ePixelFormat: pixel format type.CNcomment:֡���ظ�ʽ CNend
    \param[out] pstVFrame: frame structure.CNcomment:֡�ṹ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_MEM_ALLOC_NO_MEM no mem.CNcomment:���ڴ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::E_FRAME_MEM_USAGE VOUT_FRAME_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*mem_alloc_video_frame)(struct _MEM_DEVICE_S* pstDev,
        IN S32 s32Width, IN S32 s32Height,
        IN VOUT_VIDEO_FORMAT_E ePixelFormat,
        IN E_FRAME_MEM_USAGE eUsage,
        OUT VOUT_FRAME_INFO_S* pstVFrame);
    /**
    \brief:free video pic mem.CNcomment:�ͷ���Ƶͼ���ڴ� CNend
    \attention \n
    .
    CNcomment: .CNend
    \param[out] pstVFrame: frame structure.CNcomment:֡�ṹ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:�����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_FRAME_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*mem_free_video_frame)(struct _MEM_DEVICE_S* pstDev,
        IN VOUT_FRAME_INFO_S* pstVFrame);
}MEM_DEVICE_S;

/**
\brief direct get memory device api, for linux and android.CNcomment:��ȡmemory�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get memory device api��for linux and andorid.
CNcomment:��ȡmemory�豸��linux��androidƽ̨������ʹ��. CNend
\retval  memory device pointer when success.CNcomment:�ɹ�����memory�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::MEM_DEVICE_S

\par example
*/
MEM_DEVICE_S *getMemDevice(void);


//���豸
/**
\brief Open HAL memory module device.CNcomment: ��HAL memoryģ���豸 CNend
\attention \n
Open HAL memory module device( for compatible android HAL).
CNcomment: ��HAL memoryģ���豸(for compatible Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice memory device structure.CNcomment:memory�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::DEMUX_DEVICE_S

\par example
*/
static inline int mem_open(const struct hw_module_t* pstModule, MEM_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, MEM_HARDWARE_MEM0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getMemDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL memory module device.CNcomment:�ر�HAL memoryģ���豸 CNend
\attention \n
Close HAL memory module device(for compatible Android HAL).
CNcomment:�ر�HAL memoryģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice memory device structure.CNcomment:memory�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::MEM_DEVICE_S

\par example
*/
static inline int mem_close(MEM_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

//Լ���������̶�ʵ��ÿ��ʵ������open/close������ÿ��ʵ��open/close������ɶԵ���

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__TVOS_HAL_MEM_H__*/
