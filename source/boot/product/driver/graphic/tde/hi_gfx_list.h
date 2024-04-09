/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_list.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : CNcomment: TDE����ʹ��CNend\n
Function List      :
History            :
Date                           Author                     Modification
2018/01/01                     sdk                         Created file
************************************************************************************************/
#ifndef _HI_GFX_LIST_H
#define _HI_GFX_LIST_H

/*********************************add include here**********************************************/


/***************************** Macro Definition ************************************************/

/*************************** Structure Definition **********************************************/
struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(list_name) { &(list_name), &(list_name) }

#define LIST_HEAD(list_name) \
    struct list_head list_name = LIST_HEAD_INIT(list_name)

#define INIT_LIST_HEAD(pttr) do { \
    (pttr)->next = (pttr); (pttr)->prev = (pttr); \
} while (0)


/********************** Global Variable declaration ********************************************/

/******************************* API declaration ***********************************************/
void __list_add(struct list_head *pnew,struct list_head *pprev,struct list_head *pnext);

void list_add(struct list_head *pnew, struct list_head *pHead);

void list_add_tail(struct list_head *pnew, struct list_head *pHead);

void __list_del(struct list_head *pprev, struct list_head *pnext);

void list_del(struct list_head *pentry);

void list_del_init(struct list_head *pentry);

int list_empty(struct list_head *pHead);

#define list_entry(pttr, type, hmember) \
    ((type *)((char *)(pttr)-(unsigned long)(&((type *)0)->hmember)))

#endif/**_HI_GFX_LIST_H**/
