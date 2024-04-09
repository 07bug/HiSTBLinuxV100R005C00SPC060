/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_string.h
 * Description   : �ַ�����������ͷ�ļ�
 *
 * History       :
 * Version     Date          DefectNum    Modification:
 * 1.1         2009-2-27     NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_STRINT_H__
#define __HI_ADPT_STRINT_H__

#include "hi_type.h"
#include "hi_adp_interface.h"
#include <string.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * macro
 *----------------------------------------------*/

#if HI_OS_TYPE == HI_OS_LINUX
#elif HI_OS_TYPE == HI_OS_WIN32

    #define strcasecmp      _stricmp
    #define strncasecmp     _strnicmp
    #define strdup          _strdup
    #define atoll           _atoi64

#endif
//HI_SIZE_T strlen(const char *s);
/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/

/*���ַ���תΪȫ��д*/
HI_CHAR* HI_StrToUper(HI_CHAR *szSource);

/*ת��nptrΪint32 value*/
HI_S32 HI_StrToInt32(const HI_CHAR *nptr, HI_S32 *value);

/*�ϲ�����ַ���,���һ����������ΪHI_NULL_PTR*/
//HI_CHAR* HI_StrConcat (const HI_CHAR *string1, ...);

/*----------------------------------------------*
 * ��ʽ���ַ��������ӿ�
 *----------------------------------------------*/

//HI_S32 HI_Snprintf(HI_CHAR *str, HI_SIZE_T size, const HI_CHAR *format, ...);

//HI_S32 HI_VSnprintf(HI_CHAR *str, HI_SIZE_T size, const HI_CHAR *format, HI_VA_LIST argList);

/* Write formatted output to stdout. */
//HI_S32  HI_Printf (const HI_CHAR *format, ...);

/* Read formatted input from stdin.*/
//HI_S32 HI_Scanf (const HI_CHAR * format, ...);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ADPT_STRINT_H__ */
