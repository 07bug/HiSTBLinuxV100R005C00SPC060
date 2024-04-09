/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co.
, Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published
or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : linux_list.h
Version             :   Initial Draft
Author              :
Created             :  2015/08/27
Description         : so queue list
******************************************************************************/

#ifndef __SO_LIST_H
#define __SO_LIST_H

#include "hi_type.h"

#ifndef __LITEOS__
#if HI_OS_TYPE == HI_OS_WIN32
#define INLINE __inline
#elif HI_OS_TYPE == HI_OS_LINUX
#define INLINE inline
#endif
#endif

struct list_head {
    struct list_head *next;
    struct list_head *prev;
};


/***************************** Macro Definition ******************************/


#define INIT_LIST_HEAD(ptr) do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)




/******************************* API declaration *****************************/

INLINE void __list_add(struct list_head * const pstSoNew,
                        struct list_head *pstSoPrev,
                        struct list_head *pstSoNext)
{
    pstSoNext->prev = pstSoNew;
    pstSoNew->next = pstSoNext;
    pstSoNew->prev = pstSoPrev;
    pstSoPrev->next = pstSoNew;
}

INLINE void list_add_tail(struct list_head * const pstSoNew, struct list_head *pstSoHead)
{
    __list_add(pstSoNew, pstSoHead->prev, pstSoHead);
}



INLINE void __list_del(struct list_head *pstSoPrev, struct list_head *pstSoNext)
{
    pstSoNext->prev = pstSoPrev;
    pstSoPrev->next = pstSoNext;
}


INLINE void list_del(struct list_head *pstSoEntry)
{
    __list_del(pstSoEntry->prev, pstSoEntry->next);
    pstSoEntry->next = HI_NULL_PTR;
    pstSoEntry->prev = HI_NULL_PTR;
}


INLINE int list_empty(struct list_head const * const pstSoHead)
{
    return (pstSoHead->next == pstSoHead);
}


#define list_entry(pstSoPtr, type, pstSoMember) \
    ((type *)((unsigned long)(pstSoPtr)-((unsigned long)(&((type *)1)->pstSoMember) - 1)))


#define list_for_each_entry_safe(pstSoPos, n, pstSoHead, pstSoMember) \
    for (pstSoPos = list_entry((pstSoHead)->next, typeof(*pstSoPos), pstSoMember), \
         n = list_entry(pstSoPos->pstSoMember.next, typeof(*pstSoPos), pstSoMember); \
         &pstSoPos->pstSoMember != (pstSoHead);  \
         pstSoPos = n, n = list_entry(n->pstSoMember.next, typeof(*n), pstSoMember))


#endif
