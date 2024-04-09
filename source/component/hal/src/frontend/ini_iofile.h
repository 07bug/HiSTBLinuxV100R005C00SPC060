/***********************************************************************************
*              Copyright 2013 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: HiIOFile.h
* Description: ini file parser.
*
* History:
* Version   Date                Author     DefectNum    Description
* main\1    2013-02-04   d66707     NULL         Create this file.
***********************************************************************************/
#ifndef __Ini_IOFile_H__
#define __Ini_IOFile_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct tagINI_FILE_INFO_S
{
    S32 s32SectionStart;
    S32 s32SectionEnd;
    S32 s32KeyStart;
    S32 s32KeyEnd;
    S32 s32ValueStart;
    S32 s32ValueEnd;
} INI_FILE_INFO_S;

#define NOT_FIND (-1)
#define MAX_VALID_STRING_LEN (512)
#define MAX_VALID_FILE_NAME_LEN (512)
#define MAX_FILE_SIZE (1024 * 1024)
#define LEFT_BRACKET ('[')
#define RIGHT_BRACKET (']')

S32   Ini_IOFile_Init();
S32   Ini_IOFile_DeInit();
S32   Ini_IOFile_LoadFile(const CHAR* pszFileName);
S32   Ini_IOFile_GetValue(CHAR* pszKey, S32 s32DefaultValue, CHAR* pszSectio);
S32   Ini_IOFile_SetValue(CHAR* pszKey, S32 s32DefaultValue, CHAR* pszSection);
CHAR* Ini_IOFile_GetString( CHAR* pszKey, const CHAR* pszDefaultValue, CHAR* pszSection);
S32   Ini_IOFile_SetString(CHAR* pszKey, CHAR* pszValue, CHAR* pszSection);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif // __Ini_IOFile_H__
