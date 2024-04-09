/**
 \file
 \brief sutitle queue
 \author Shenzhen Hisilicon Co., Ltd.
 \version 1.0
 \author
 \date 2010-03-10
 */

#ifndef __SO_QUEUE_H__
#define __SO_QUEUE_H__

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hi_type.h"
#include "hi_unf_so.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifdef __LITEOS__
extern void *hi_malloc(HI_MOD_ID_E ModId, HI_U32 boundary, HI_U32 size, HI_BOOL nocache);
extern void  hi_free(HI_MOD_ID_E ModId, void *ptr, HI_BOOL nocache);
#define SO_MALLOC(size)  (hi_malloc(HI_ID_SUBT, 0,(size), HI_FALSE))
#define SO_FREE(ptr) \
do \
{ \
    if ((ptr)) \
    { \
        hi_free(HI_ID_SUBT, (ptr), HI_FALSE); \
        (ptr) = NULL; \
    } \
} while (0)

#else

#include "hi_unf_version.h"

#if (UNF_VERSION_CODE >= UNF_VERSION(3, 5))
#include "hi_mpi_mem.h"
#ifndef HI_MALLOC
#define HI_MALLOC malloc
#endif
#ifndef HI_FREE
#define HI_FREE free
#endif
#define HI_MEMSO_MALLOC(u32Size)    (HI_MALLOC(u32Size))
#define HI_MEMSO_FREE(pvMemAddr)    (HI_FREE(pvMemAddr))
#else
#define HI_MEMSO_MALLOC(u32Size)    (malloc(u32Size))
#define HI_MEMSO_FREE(pvMemAddr)    (free(pvMemAddr))
#endif

#define SO_MALLOC(size)  (HI_MEMSO_MALLOC(size))
#define SO_FREE(ptr) \
do \
{ \
    if ((ptr)) \
    { \
        HI_MEMSO_FREE((ptr)); \
        (ptr) = NULL; \
    } \
} while (0)
#endif


#define SO_RETURN(val, ret, printstr) \
do \
{ \
    if ((val)) \
    { \
        return (ret); \
    } \
} while (0)

#define SO_CALL_RETURN(val, fun, ret) \
do \
{ \
    if ((val)) \
    { \
        fun; \
        return (ret); \
    } \
} while (0)

#define SO_MEMSET  memset
#define SO_MEMMOVE memmove
#define SO_MEMCPY  memcpy

#define SO_SLEEP(ms)  \
    do{\
        struct timespec  _ts;\
        _ts.tv_sec = (ms) >= 1000 ? (ms)/1000 : 0;\
        _ts.tv_nsec =  (_ts.tv_sec > 0) ? ((ms)%1000)*1000000LL : (ms) * 1000000LL;\
        (HI_VOID)nanosleep(&_ts, NULL);\
    }while (0)

#define SO_NORMAL_BUFF_SIZE   (1024)

typedef HI_VOID* SO_QUEUE_HANDLE;
typedef HI_UNF_SO_SUBTITLE_INFO_S SO_INFO_S;


/**
\brief create queue
\attention \n
if the size of used buffer is larger than bufsize and the number of node is larger than maxNodeNum, then
can not put node in queue.
\param[in] bufsize bytes of the queue
\param[in] maxNodeNum max number of node in the queue
\param[out] handle handle of the queue

\retval ::HI_SUCCESS if success
\retval ::HI_FAILURE no memory

\see \n
non
*/
HI_S32 SO_QueueInit( HI_U32 bufsize, HI_U32 maxNodeNum, SO_QUEUE_HANDLE *handle );

/**
\brief destroy the queue
\attention \n
non
\param[in] handle handle of the queue

\retval ::HI_SUCCESS success
\retval ::HI_FAILURE queue no exist

\see \n
non
*/
HI_S32 SO_QueueDeinit(SO_QUEUE_HANDLE handle);

/**
\brief free the node in the queue
\attention \n
non
\param[in] handle handle of the queue
\param[in] pstInfo node info

\retval ::HI_SUCCESS success
\retval ::HI_FAILURE node no exist

\see \n
non
*/
HI_S32 SO_QueueFree( SO_QUEUE_HANDLE handle, SO_INFO_S *pstInfo );

/**
\brief get a node
\attention \n
non
\param[in] handle handle of the queue
\param[out] pstInfo node info of getting

\retval ::HI_SUCCESS success
\retval ::HI_FAILURE queue is empty

\see \n
non
*/
HI_S32 SO_QueueGet(SO_QUEUE_HANDLE handle, SO_INFO_S *pstInfo);

/**
\brief get a node, but no delete the node in the queue
\attention \n
non
\param[in] handle handle of the queue
\param[out] pstInfo node info

\retval ::HI_SUCCESS success
\retval ::HI_FAILURE queue is empty

\see \n
non
*/
HI_S32 SO_QueueGetNodeInfoNotDel(SO_QUEUE_HANDLE handle, SO_INFO_S *pstInfo);

/**
\brief insert a node
\attention \n
non
\param[in] handle handle of the queue
\param[out] pstInfo node info

\retval ::HI_SUCCESS success
\retval ::HI_FAILURE no memory or param invalid

\see \n
non
*/
HI_S32 SO_QueuePut(SO_QUEUE_HANDLE handle, const SO_INFO_S *pstInfo);

/**
\brief reset the queue, delete all nodes
\attention \n
non
\param[in] handle handle of the queue

\retval ::HI_SUCCESS success

\see \n
non
*/
HI_S32 SO_QueueReset( SO_QUEUE_HANDLE handle );

/**
\brief reset the queue, delete nodes by pts
\attention \n
non
\param[in] handle handle of the queue

\retval ::HI_SUCCESS successs

\see \n
non
*/
HI_S32 SO_QueueReset_ByPts( SO_QUEUE_HANDLE handle, HI_S64 s64Pts );

/**
\brief remove all nodes
\attention \n
non
\param[in] handle handle of the queue

\retval ::HI_SUCCESS success

\see \n
non
*/
HI_S32 SO_QueueRemove(SO_QUEUE_HANDLE handle);

/**
\brief get total number of the nodes
\attention \n
non
\param[in] handle handle of the queue

\retval ::HI_SUCCESS

\see \n
non
*/
HI_S32  SO_QueueNum(SO_QUEUE_HANDLE handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SO_QUEUE_H__ */

