/**
 * \file tvos_hal_type.h
 * \brief tvos hal  base datatype define.
 * HAL Version: 2.0.10
*/

#ifndef  __TVOS_HAL_TYPE_H__
#define __TVOS_HAL_TYPE_H__

#ifndef HAL_HISI_EXTEND_H
#define HAL_HISI_EXTEND_H
#endif
//#define ANDROID_HAL_MODULE_USED

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_TYPE */
/** @{ */  /** <!-- [HAL_TYPE] */

#ifndef NULL
#define NULL            0L
#endif

#define SUCCESS         0
#define FAILURE         (-1)
#define VOID            void

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_TYPE */
/** @{ */  /** <!-- [HAL_TYPE] */

typedef unsigned char           U8;
typedef signed char             S8;
typedef unsigned short          U16;
typedef unsigned int            U32;
typedef short                   S16;
typedef int                     S32;
typedef unsigned long long      U64;
typedef long long               S64;
typedef char                    CHAR;
typedef unsigned char           UCHAR;
typedef float                   FLOAT;
typedef double                  DOUBLE;
typedef U32                     HANDLE;

#ifndef BOOL
#define BOOL U8
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_TYPE*/
/** @{*/  /** <!-- -HAL_TYPE*/

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TVOS_HAL_TYPE_H__ */
