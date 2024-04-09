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
#define INVALID_MEM_HANDLE (MEM_HANDLE)NULL //无效句柄

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_MEM */
/** @{ */  /** <!-- [HAL_MEM] */

#ifdef ANDROID_HAL_MODULE_USED
/** memory module *//** CNcomment:memory模块 */
typedef struct _MEM_MODULE_S
{
    struct hw_module_t common;
} MEM_MODULE_S;
#endif

/**Struct of memory type*/
/**CNcomment: 内存类型   */
typedef enum _E_MEM_USAGE
{
    E_MEM_USEAGE_VES,          /**<used for video es buffer*//**<CNcomment: 用于视频es流的buffer*/
    E_MEM_USEAGE_VES_SECURE,   /**<used for video es secure buffer*//**<CNcomment: 用于视频es流的buffer*/
    E_MEM_USEAGE_VES_BUT
} E_MEM_USAGE;

typedef enum _E_FRAME_MEM_USAGE
{
    E_MEM_USEAGE_VO,         /**<used for video frame to VDP*//**<CNcomment:  用于视频显示的帧存 */
    E_MEM_USEAGE_VO_SECURE,  /**<used for video secure frame to VDP*//**<CNcomment: 用于视频显示的帧存 */
    E_MEM_USEAGE_VO_BUT
}E_FRAME_MEM_USAGE;

typedef void* MEM_HANDLE; //内存句柄


/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_MEM*/
/** @{*/  /** <!-- -[HAL_MEM]=*/

/**Memory device structure*//** CNcomment:Memory设备结构*/
typedef struct _MEM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief:alloc mem.CNcomment:分配内存 CNend
    \attention \n
    Other functions cannot be useful before mem_alloc, return SUCCESS.
    CNcomment: 在这个接口之前, 其他函数都不能正确运行.CNend
    \param[in] eUsage：内存使用场景类型
    \param[in] u32Size: 分配大小 mem size.CNcomment:分配大小 CNend
    \param[in] pszName: mem名 mem name.CNcomment:内存名字 CNend
    \param[out] hHandle: mem handle.CNcomment:内存句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_MEM_ALLOC_NO_MEM no mem.CNcomment:无内存 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid(useage unsupport or size == 0) .CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::E_MEM_USAGE

    \par example
    \code
    \endcode
    */
    S32  (*mem_alloc) (struct _MEM_DEVICE_S* pstDev,IN E_MEM_USAGE eUsage, IN S32 u32Size, IN CHAR * pszName, OUT MEM_HANDLE* hHandle);

    /**
    \brief:free mem.CNcomment:释放内存 CNend
    \attention \n
    Other functions cannot be useful after mem_free.
    CNcomment: 在这个接口之后, 其他函数都不能正确运行.CNend
    \param[in] hHandle: mem handle.CNcomment:内存句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_free)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle);

    /**
    \brief:get phy addr of mem.CNcomment:获取内存的物理地址 CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle：MEM_HANDLE内存句柄
    \param[out] ppvPhyAddr: 物理地址指针 mem phyaddr.CNcomment:物理地址 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_phy_addr)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvPhyAddr);

    /**
    \brief:map mem.CNcomment:map内存的用户态虚拟地址 CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle：MEM_HANDLE内存句柄
    \param[out] ppvVirAddr: 用户态地址指针 mem viraddr.CNcomment:用户态地址 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_map)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvVirAddr);

    /**
    \brief:unmap mem.CNcomment:unmap内存 CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle：MEM_HANDLE内存句柄
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_unmap)(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle);
    /**
    \brief:flush cache to mem.CNcomment:cache中的数据写入内存 CNend
    \attention \n
    ...
    CNcomment: ....CNend
    \param[in] hHandle：MEM_HANDLE内存句柄
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*mem_flush)(struct _MEM_DEVICE_S* pstDev, IN MEM_HANDLE hHandle);
    /**
    \brief:alloc video pic mem.CNcomment:分配视频图像内存 CNend
    \attention \n
    .
    CNcomment: .CNend
    \param[in] s32Width: video width.CNcomment:帧的宽 CNend
    \param[in] pszName: video height.CNcomment:帧的高 CNend
    \param[in] eUsage：内存使用场景类型
    \param[in] ePixelFormat: pixel format type.CNcomment:帧像素格式 CNend
    \param[out] pstVFrame: frame structure.CNcomment:帧结构 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_MEM_ALLOC_NO_MEM no mem.CNcomment:无内存 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief:free video pic mem.CNcomment:释放视频图像内存 CNend
    \attention \n
    .
    CNcomment: .CNend
    \param[out] pstVFrame: frame structure.CNcomment:帧结构 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:输入参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
\brief direct get memory device api, for linux and android.CNcomment:获取memory设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get memory device api，for linux and andorid.
CNcomment:获取memory设备，linux和android平台都可以使用. CNend
\retval  memory device pointer when success.CNcomment:成功返回memory设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::MEM_DEVICE_S

\par example
*/
MEM_DEVICE_S *getMemDevice(void);


//打开设备
/**
\brief Open HAL memory module device.CNcomment: 打开HAL memory模块设备 CNend
\attention \n
Open HAL memory module device( for compatible android HAL).
CNcomment: 打开HAL memory模块设备(for compatible Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice memory device structure.CNcomment:memory设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
\brief Close HAL memory module device.CNcomment:关闭HAL memory模块设备 CNend
\attention \n
Close HAL memory module device(for compatible Android HAL).
CNcomment:关闭HAL memory模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice memory device structure.CNcomment:memory设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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

//约束：单进程多实例每个实例都能open/close，但是每个实例open/close都必须成对调用

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__TVOS_HAL_MEM_H__*/
