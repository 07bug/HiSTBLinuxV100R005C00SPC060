/***********************************************************************************
*              Copyright 2013 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: HiIOFile.cpp
* Description: ini file parser.
*
***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//#include "hi_common.h"

#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"

#include "ini_iofile.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define INIFILE_CHECK_PTR(ptr)\
    do{\
        if (NULL == ptr)\
        {\
            HAL_ERROR("ERROR_NULL_PTR");\
            return ERROR_NULL_PTR;\
        }\
    }while(0)

#define INIFILE_CHECK_PARA(val )           \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HAL_ERROR("Invalid Parameter"); \
            return ERROR_INVALID_PARAM;                                    \
        };                                                   \
    } while (0)

#define INIFILE_DOFUNC_RETURN(func)                            \
    do{                                         \
        S32 s32LogRet = 0 ;                        \
        s32LogRet = func ;                            \
        if(s32LogRet != SUCCESS)                   \
        {                                        \
            HAL_ERROR("%s fail:%d" , #func, s32LogRet);          \
            return s32LogRet;                        \
        };                                       \
    }while(0)


#define INI_SKIP_BLANK_BEFORE_SECTION(u32index, pcBuff) \
    if (((0 != (u32index)) && (!isNewLine( *((pcBuff) + (u32index) - 1)))) || (!isLeftBracket( *((pcBuff) + (u32index))))) \
    {           \
        (u32index)++;   \
        continue;    \
    }

#define INI_SKIP_BLANK_AFTER_SECTION(u32index, pcBuff) \
    while (isSpace( *((pcBuff) + (u32index)))) \
    {    \
        (u32index)++; \
    }

#define INI_CHECK_DIFF_SECTION(bDiff, u32index) \
    if ((bDiff)) \
    {    \
        (u32index)++; \
        continue; \
    }

static CHAR s_szFileName[MAX_VALID_FILE_NAME_LEN];
static CHAR*  s_pcFileBuf;
static U32 s_u32FileSize;

static pthread_mutex_t s_mutex;

/***********************************************************************************
* Function:         loadIniFile
* Description:     load an ini file to buf
* Input:              pFileName     :the file to load
*                        pBuf     :the buf to load the ini file
* Output:            u32FileSize    :size of the ini file
* Return:            SUCCESS: load ini file success
*                        FAILURE:load failed
***********************************************************************************/

static S32 loadIniFile(const CHAR* pszFileName, CHAR* pcBuf, U32* pu32FileSize)
{
    FILE* pFile = NULL;
    U32 u32ReadLength = 0;
    U32 u32FileLength = 0;
    S32 s32Ret = FAILURE;

    INIFILE_CHECK_PARA(NULL == pszFileName);
    INIFILE_CHECK_PARA(NULL == pcBuf);
    INIFILE_CHECK_PARA(NULL == pu32FileSize);

    *pu32FileSize = 0;

    pFile = fopen(pszFileName, "r");
    if (NULL == pFile)
    {
        HAL_ERROR("[loadIniFile]:fopen file %s failed!\n", pszFileName);
        return FAILURE;
    }

    s32Ret = fseek(pFile, 0L, SEEK_END);
    u32FileLength = ftell(pFile);

    if ((MAX_FILE_SIZE < u32FileLength) || u32FileLength == 0)
    {
        HAL_ERROR("[loadIniFile]:file exceed the max length\n");
        fclose(pFile);
        return FAILURE;
    }

    *pu32FileSize = u32FileLength;

    s32Ret = fseek(pFile, 0L, SEEK_SET);

    u32ReadLength = fread(pcBuf, 1, *pu32FileSize, pFile);
    if (0 == u32ReadLength)
    {
        HAL_ERROR("[loadIniFile]:fread file %s failed!\n", pszFileName);
        fclose(pFile);
        return FAILURE;
    }

    fclose(pFile);
    s32Ret = SUCCESS;
    HAL_DEBUG("loadIniFile ok....");
    return s32Ret;
}

/***********************************************************************************
* Function:         isNewLine
* Description:     judge whether the new line
* Input:              cChar     :the char to judge
*
* Output:            NA
* Return:            TRUE: is the new line
*                        FALSE:is not the new line
***********************************************************************************/
static BOOL isNewLine(CHAR cChar)
{
    return (('\n' == cChar || '\r' == cChar) ? TRUE : FALSE);
}

/***********************************************************************************
* Function:         isEnd
* Description:     judge whether the end of the file
* Input:              cChar     :the char to judge
*
* Output:            NA
* Return:            TRUE: is the end of the file
*                        FALSE:is not the end of the file
***********************************************************************************/
static BOOL isEnd(CHAR cChar)
{
    return (('\0' == cChar) ? TRUE : FALSE);
}

static BOOL isSpace(CHAR cChar)
{
    return (((' ' == cChar) || ('\r' == cChar) || ('\t' == cChar) || ('\n' == cChar) || ('\v' == cChar) || ('\f' == cChar)) ? TRUE : FALSE);
}

/***********************************************************************************
* Function:         isLeftBracket
* Description:     judge whether the start of a section(the section start of a '[')
* Input:              cChar     :the char to judge
*
* Output:            NA
* Return:            TRUE: is the start of a section
*                        FALSE:is not the start of a section
***********************************************************************************/
static BOOL isLeftBracket(CHAR cChar)
{
    return ((LEFT_BRACKET == cChar) ? TRUE : FALSE);
}

/***********************************************************************************
* Function:         isRightBracket
* Description:     judge whether the end of a section(the section start of a '[')
* Input:              cChar     :the char to judge
*
* Output:            NA
* Return:            TRUE: is the end of a section
*                        FALSE:is not the end of a section
***********************************************************************************/
static BOOL isRightBracket(CHAR cChar )
{
    return ((RIGHT_BRACKET == cChar) ? TRUE : FALSE);
}

/***********************************************************************************
* Function:         parseFile
* Description:     parer the file ,find the start and end information of the section,key,value,if the section
*                       or key is not exist,the function will return failure,this is not an error
* Input:              pszSection     :the section to be found
*                        pszKey          :the key to be found
*                        pszBuf           :For parsing file buf
* Output:            pstFileInfo      :the start and end information of the section,key,value
* Return:            SUCCESS: parse file success
*                        FAILURE:parse file not success
***********************************************************************************/
static S32 parseFile(const CHAR* pszSection, const CHAR* pszKey, CHAR* pszBuf, INI_FILE_INFO_S* pstFileInfo)
{
    CHAR* pcBuf = pszBuf;
    U32 i = 0;
    U32 u32SecStart = 0;
    U32 u32NewLineStart = 0;
    U32 u32SectionLen = strlen(pszSection);
    U32 u32KeyLen = strlen(pszKey);
    BOOL bDiffSection = FALSE;

    /*This is an internal function, so no other parameters are examined*/

    pstFileInfo->s32SectionStart = NOT_FIND;
    pstFileInfo->s32SectionEnd = NOT_FIND;
    pstFileInfo->s32KeyStart = NOT_FIND;
    pstFileInfo->s32KeyEnd = NOT_FIND;
    pstFileInfo->s32ValueStart = NOT_FIND;
    pstFileInfo->s32ValueEnd = NOT_FIND;

    while (FALSE == isEnd(pcBuf[i]))
    {
        /*find the section,'[' is section start flag*/
        INI_SKIP_BLANK_BEFORE_SECTION(i, pcBuf);

        /*skip '['*/
        u32SecStart = i + 1;

        /*find the ']'*/
        do
        {
            i++;
        }while ((!isRightBracket(*(pcBuf + i))) && (!isEnd(*(pcBuf + i))));

        bDiffSection = (BOOL)((0 != strncmp(pcBuf + u32SecStart, pszSection, i - u32SecStart)) || (u32SectionLen != (i - u32SecStart)));
        INI_CHECK_DIFF_SECTION(bDiffSection, i);

        /*skip ']'*/
        i++;
        INI_SKIP_BLANK_AFTER_SECTION(i, pcBuf);

        /*find the section success*/
        pstFileInfo->s32SectionStart = (S32)u32SecStart;
        pstFileInfo->s32SectionEnd = (S32)i;

        while (!((isNewLine(*(pcBuf + i - 1))) && (isLeftBracket(*(pcBuf + i)))) && (!isEnd(*(pcBuf + i))))
        {
            U32 j = 0;
            U32 k = 0;
            U32 u32KeyStart = 0;

            /*get a new line*/
            u32NewLineStart = i;

            while ((!isNewLine(*(pcBuf + i))) && (!isEnd(*(pcBuf + i))))
            {
                i++;
            }

            /*now i  is equal to end of the line*/
            j = u32NewLineStart;

            /* Skip over space char before key*/
            INI_SKIP_BLANK_AFTER_SECTION(j, pcBuf);

            /*skip over comment*/
            if (';' == *(pcBuf + j))
            {
                i++;
                continue;
            }

            u32KeyStart = j;

            while ((j < i) && (*(pcBuf + j) != '='))
            {
                j++;

                if ('=' != *(pcBuf + j))
                {
                    continue;
                }

                /*now, j is point beore '='*/
                k = 0;

                while ((!isSpace(*(pcBuf + u32KeyStart + k))) && ('=' != *(pcBuf + u32KeyStart + k)))
                {
                    k++;
                }

                if ((k != u32KeyLen) || (0 != strncmp(pszKey, pcBuf + u32KeyStart, u32KeyLen)))
                {
                    continue;
                }

                /*find the key ok*/
                pstFileInfo->s32KeyStart = (S32)u32KeyStart;
                pstFileInfo->s32KeyEnd = (S32)(u32KeyStart + u32KeyLen);

                j++;

                /*now, j is point after '='*/
                /*Skip over space char before value */
                while ((isSpace(*(pcBuf + j))) && (j <= i))
                {
                    j++;
                }

                pstFileInfo->s32ValueStart = (S32)j;
                k = j;

                /*';' is use for explanatory note*/
                while ((';' != *(pcBuf + j)) && (j <= i))
                {
                    /*skip space char behind value*/
                    if (!isSpace(*(pcBuf + j)))
                    {
                        k = j + 1;
                    }

                    j++;
                }

                pstFileInfo->s32ValueEnd = (S32)k;
                return SUCCESS;
            }

            i++;
        }
    }

    return FAILURE;
}

/***********************************************************************************
* Function:         iniReadString
* Description:     read a string from a file buffer,if parse file failed or string exceed the max length,which will
*                       return failure
* Input:              pszSection     :the section to be found
*                        pszKey          :the key to be found
*                        pcFileBuf       :For parsing file buf
* Output:            pcValue         :the value of the key
* Return:            SUCCESS: read success
*                        FAILURE  : read not success
***********************************************************************************/
static S32 iniReadString(const CHAR* pszSection, const CHAR* pszKey, CHAR* pcValue, CHAR* pcFileBuf)
{
    U32 u32CpCount = 0;
    INI_FILE_INFO_S stIniFileInfo;

    /*check parameters*/
    INIFILE_CHECK_PARA(NULL == pszSection);
    INIFILE_CHECK_PARA(NULL == pszKey);
    INIFILE_CHECK_PARA(0 == strlen(pszSection));
    INIFILE_CHECK_PARA(0 == strlen(pszKey));
    INIFILE_CHECK_PARA(NULL == pcValue);
    INIFILE_CHECK_PARA(NULL == pcFileBuf);

    INIFILE_DOFUNC_RETURN(parseFile(pszSection, pszKey, pcFileBuf, &stIniFileInfo));

    u32CpCount = (U32)(stIniFileInfo.s32ValueEnd - stIniFileInfo.s32ValueStart);

    if (MAX_VALID_STRING_LEN <= u32CpCount)
    {
        HAL_ERROR("[iniReadString]:string exceed the max length !!!!\n");
        return FAILURE;
    }

    memset(pcValue, 0, u32CpCount);
    memcpy(pcValue, pcFileBuf + stIniFileInfo.s32ValueStart, u32CpCount);
    *(pcValue + u32CpCount) = '\0';

    return SUCCESS;
}

/***********************************************************************************
* Function:         iniReadInt
* Description:     read a int value from a file buffer,if call iniReadString failed which will return failure
* Input:              pszSection     :the section to be found
*                        pszKey          :the key to be found
*                        pcFileBuf       :For parsing file buf
* Output:            ps32Value         :the value of the key
* Return:            SUCCESS: read success
*                        FAILURE  : read not success
***********************************************************************************/
static S32 iniReadInt(const CHAR* pszSection, const CHAR* pszKey, S32*  ps32Value, CHAR* pcFileBuf)
{
    CHAR acValue[MAX_VALID_STRING_LEN] = {0};

    INIFILE_CHECK_PARA(NULL == ps32Value);

    if (SUCCESS == iniReadString(pszSection, pszKey, acValue, pcFileBuf))
    {
        *ps32Value = (S32)strtoul(acValue, 0, 0);
        HAL_DEBUG("[%s].%s = %d\n", pszSection, pszKey, *ps32Value);
        return SUCCESS;
    }
    else
    {
        *ps32Value = 0;
        return FAILURE;
    }
}

/***********************************************************************************
* Function:         iniWriteString
* Description:     write a string to a file buffer,and return the new file size
* Input:              pszSection     :the section to be found
*                        pszKey          :the key to be found
*                        pcFileBuf       :the  file buf to be write
*                        pcValue         :the value to be wirte
* Output:            pu32FileSize   :the new file size
* Return:            SUCCESS: write success
*                        FAILURE  : write not success
***********************************************************************************/

static S32 iniWriteString(const CHAR* pszSection, const CHAR* pszKey, CHAR* pcValue, CHAR* pcFileBuf,
                              U32* pu32FileSize)
{
    CHAR* pacWriteBuf = NULL;
    U32 u32SectionLen = 0;
    U32 u32KeyLen     = 0;
    U32 u32ValueLen   = 0;
    S32 s32FileAddlen = 0;/*the length of ini file has added*/
    INI_FILE_INFO_S stFileInfo;

    /*check parameters*/

    INIFILE_CHECK_PARA(NULL == pszSection);
    INIFILE_CHECK_PARA(NULL == pszKey);
    INIFILE_CHECK_PARA(NULL == pcValue);
    INIFILE_CHECK_PARA(NULL == pcFileBuf);
    INIFILE_CHECK_PARA(NULL == pu32FileSize);

    u32SectionLen = strlen(pszSection);
    u32KeyLen = strlen(pszKey);

    INIFILE_CHECK_PARA(0 == u32SectionLen);
    INIFILE_CHECK_PARA(0 == u32KeyLen);

    u32ValueLen = strlen(pcValue);

    INIFILE_CHECK_PARA(u32ValueLen > MAX_VALID_STRING_LEN);

    pacWriteBuf = (CHAR*)malloc(MAX_FILE_SIZE);

    INIFILE_CHECK_PARA(NULL == pacWriteBuf);

    memset(pacWriteBuf, 0, MAX_FILE_SIZE);

    /*parseFile maybe return failure*/
    (void)parseFile(pszSection, pszKey, pcFileBuf, &stFileInfo);

    if (NOT_FIND == stFileInfo.s32SectionStart)
    {
        HAL_DEBUG("[iniWriteString]: not find section %s.now add it\n", pszSection);
        if ((0 != *pu32FileSize) && (*pu32FileSize <= MAX_FILE_SIZE))
        {
            memcpy(pacWriteBuf, pcFileBuf, *pu32FileSize);
        }

        /*not find the section, then add the new section at end of the file*/
        if (MAX_FILE_SIZE > *pu32FileSize)
        {
            snprintf(pacWriteBuf + *pu32FileSize, MAX_FILE_SIZE - *pu32FileSize, "\n[%s]\n%s=%s\n", pszSection, pszKey, pcValue);
        }

        s32FileAddlen = (S32)(u32SectionLen + u32KeyLen + u32ValueLen + 6); /*6 are \n, [, ],\n,=,\n   */
    }
    else if (NOT_FIND == stFileInfo.s32KeyStart)
    {
        /*not find the key, then add the new key & value at end of the section*/

        HAL_DEBUG("[iniWriteString]: find section %s, but not find key %s, now add it\n", pszSection, pszKey);
        if ((0 < stFileInfo.s32SectionEnd) && (stFileInfo.s32SectionEnd <= MAX_FILE_SIZE))
        {
            memcpy(pacWriteBuf, pcFileBuf, (U32)stFileInfo.s32SectionEnd);
        }

        if (MAX_FILE_SIZE > (U32)stFileInfo.s32SectionEnd)
        {
            snprintf(pacWriteBuf + (U32)stFileInfo.s32SectionEnd, MAX_FILE_SIZE - (U32)stFileInfo.s32SectionEnd, "%s=%s\n", pszKey, pcValue);
        }

        if (MAX_FILE_SIZE > ((U32)stFileInfo.s32SectionEnd + u32KeyLen + u32ValueLen + 2))
        {

            snprintf(pacWriteBuf + (U32)stFileInfo.s32SectionEnd + u32KeyLen + u32ValueLen + 2, MAX_FILE_SIZE - ((U32)stFileInfo.s32SectionEnd + u32KeyLen + u32ValueLen + 2), pcFileBuf
                 + (U32)stFileInfo.s32SectionEnd, *pu32FileSize - (U32)stFileInfo.s32SectionEnd);
        }

        s32FileAddlen = (S32)(u32KeyLen + u32ValueLen + 2); /*2 are =,\n*/
    }
    else
    {
        /*update value with new value*/

        HAL_DEBUG("[iniWriteString]:find the key %s, value:%s\n", pszKey, pcValue);
        if ((0 < stFileInfo.s32ValueStart) && (stFileInfo.s32ValueStart <= MAX_FILE_SIZE))
        {
            memcpy(pacWriteBuf, pcFileBuf, (U32)stFileInfo.s32ValueStart);
        }

        if ((0 < u32ValueLen) && (((U32)stFileInfo.s32ValueStart + u32ValueLen) <= MAX_FILE_SIZE))
        {
            memcpy(pacWriteBuf + (U32)stFileInfo.s32ValueStart, pcValue, u32ValueLen);
        }

        if (((U32)stFileInfo.s32ValueEnd < *pu32FileSize) && (((U32)stFileInfo.s32ValueStart + u32ValueLen  + *pu32FileSize - (U32)stFileInfo.s32ValueEnd) <= MAX_FILE_SIZE))
        {
            memcpy(pacWriteBuf + (U32)stFileInfo.s32ValueStart + u32ValueLen, pcFileBuf + (U32)stFileInfo.s32ValueEnd,
                *pu32FileSize - (U32)stFileInfo.s32ValueEnd);
        }

        s32FileAddlen = (S32)(u32ValueLen - ((U32)stFileInfo.s32ValueEnd - (U32)stFileInfo.s32ValueStart));
    }

    pacWriteBuf[MAX_FILE_SIZE - 1] = '\0';

    *pu32FileSize += (U32)s32FileAddlen;
    if (MAX_FILE_SIZE < *pu32FileSize)
    {
        HAL_ERROR("[iniWriteString]:File length exceeds the maximum limit\n ");
        free(pacWriteBuf);
        pacWriteBuf = NULL;
        return FAILURE;
    }

    /*update the new data to buffer*/
    memcpy(pcFileBuf, pacWriteBuf, *pu32FileSize);
    free(pacWriteBuf);
    pacWriteBuf = NULL;
    return SUCCESS;
}

/***********************************************************************************
* Function:         updateIniFile
* Description:     update the data of file buffer to the ini file
* Input:              pszFileName   :the path of ini file
*                        pcBuf            :file buffer
*
* Return:            SUCCESS: update  success
*                        FAILURE  : update not success
***********************************************************************************/
static S32 updateIniFile(const CHAR* pszFileName, const CHAR* pcBuf)
{
    FILE* pFile = NULL;

    INIFILE_CHECK_PARA(NULL == pszFileName);
    INIFILE_CHECK_PARA(NULL == pcBuf );

    pFile = fopen(pszFileName, "w");
    if (NULL == pFile)
    {
        HAL_ERROR("[iniUpdateFile]:fopen error! \n");
        return FAILURE;
    }

    if (-1 == fputs(pcBuf, pFile))
    {
        fclose(pFile);
        HAL_ERROR("[iniUpdateFile]:fputs error! \n");
        return FAILURE;
    }

    fclose(pFile);

    return SUCCESS;
}

S32 Ini_IOFile_Init()
{
    HAL_DEBUG("enter Ini_IOFile_Init .\n");

    memset(s_szFileName, '\0', MAX_VALID_FILE_NAME_LEN);

    s_pcFileBuf   = NULL;
    s_u32FileSize = 0;

    pthread_mutex_init(&s_mutex, NULL);

    return SUCCESS;
}

S32 Ini_IOFile_DeInit()
{
    HAL_DEBUG("enter Ini_IOFile_DeInit .\n");
    if (NULL != s_pcFileBuf)
    {
        free (s_pcFileBuf);
        s_pcFileBuf = NULL;
    }

    return SUCCESS;
}

/***********************************************************************************
* Function:         Ini_IOFile_LoadFile
* Description:     load ini file
* Input:              pszFileName   :the path of ini file*
*
* Return:            SUCCESS: load  success
*                        FAILURE  : load  not success
***********************************************************************************/
S32 Ini_IOFile_LoadFile(const CHAR* pszFileName)
{
    U32 u32FileNameLen = 0;

    HAL_DEBUG("enter loadFile .\n");

    INIFILE_CHECK_PARA(NULL == pszFileName);

    u32FileNameLen = strlen(pszFileName);

    INIFILE_CHECK_PARA(u32FileNameLen >= MAX_VALID_FILE_NAME_LEN);

    if (NULL != s_pcFileBuf)
    {
        free (s_pcFileBuf);
    }

    s_pcFileBuf = (CHAR*)malloc (MAX_FILE_SIZE);

    INIFILE_CHECK_PARA(NULL == s_pcFileBuf);

    memset(s_pcFileBuf, 0x0, MAX_FILE_SIZE);
    if (FAILURE == loadIniFile(pszFileName, s_pcFileBuf, &s_u32FileSize))
    {
        free(s_pcFileBuf);
        s_pcFileBuf = NULL;
        return FAILURE;
    }

    memcpy(s_szFileName, pszFileName, u32FileNameLen);
    *(s_szFileName + u32FileNameLen) = '\0';

    return SUCCESS;
}

/***********************************************************************************
* Function:         Ini_IOFile_GetValue
* Description:     read a int value from pszSection:pszKey,if pszSection is null,use default section,if read
*                       value failed ,return the default value
* Input:              pszKey              :key
*                        s32DefaultValue :default value
*                        pszSection         :section
* Return:            s32Result           :the read value
*
***********************************************************************************/
S32 Ini_IOFile_GetValue(CHAR* pszKey, S32 s32DefaultValue, CHAR* pszSection)
{
    S32 s32Result = 0;

    INIFILE_CHECK_PARA(NULL == pszKey);

    if (NULL == pszSection)
    {
        pszSection = (CHAR*)"default";
    }

    if (FAILURE == iniReadInt(pszSection, pszKey, &s32Result, s_pcFileBuf))
    {
        HAL_DEBUG("getValue: Parser %s:%s failed, use default value:%d\n", pszSection, pszKey, s32DefaultValue);
        s32Result = s32DefaultValue;
    }

    return s32Result;
}

/***********************************************************************************
* Function:        Ini_IOFile_SetValue
* Description:    write a int value to pszSection:pszKey,if pszSection is null,use default section,if pszSection
*                      or pszKey is not exist,add it,if exist ,update the value of the key
* Input:              pszKey              :key
*                        s32Value           :the value to be wirte
*                        pszSection         :section
* Return:            SUCCESS     :set success
*                        FAILURE       :set not success
***********************************************************************************/
S32 Ini_IOFile_SetValue(CHAR* pszKey, S32 s32Value, CHAR* pszSection)
{
    CHAR acValue[MAX_VALID_STRING_LEN];

    INIFILE_CHECK_PARA(NULL == pszKey);

    if (NULL == pszSection)
    {
        pszSection = (CHAR*)"default";
    }

    snprintf(acValue, MAX_VALID_STRING_LEN, "%d", s32Value);

    pthread_mutex_lock(&s_mutex);

    if (FAILURE == iniWriteString(pszSection, pszKey, acValue, s_pcFileBuf, &s_u32FileSize))
    {
        HAL_ERROR("setValue:set value failed, [section:key]=[%s:%s]\n", pszSection, pszKey);
        pthread_mutex_unlock(&s_mutex);
        return FAILURE;
    }

    /*update new data to file*/
    if (FAILURE == updateIniFile(s_szFileName, s_pcFileBuf))
    {
        HAL_ERROR("setValue:updateIniFile failed\n");
        pthread_mutex_unlock(&s_mutex);
        return FAILURE;
    }

    pthread_mutex_unlock(&s_mutex);
    return SUCCESS;
}

/***********************************************************************************
* Function:         Ini_IOFile_GetString
* Description:     read a string from pszSection:pszKey,if pszSection is null,use default section,if read
*                       string failed ,return the default value
* Input:              pszKey              :key
*                        pszDefaultValue :default value
*                        pszSection         :section
* Return:            s32Result           :the read value
*
***********************************************************************************/
CHAR* Ini_IOFile_GetString(CHAR* pszKey, const CHAR* pszDefaultValue, CHAR* pszSection)
{
    U32 u32Len = 0;
    static CHAR szStringValue[MAX_VALID_STRING_LEN];

    if (NULL == pszKey)
    {
        HAL_ERROR("getString:key is NULL .\n");
        return NULL;
    }

    if (NULL == pszSection)
    {
        pszSection = (CHAR*)"default";
    }

    memset(szStringValue, '\0', sizeof(szStringValue));
    if (FAILURE == iniReadString(pszSection, pszKey, szStringValue, s_pcFileBuf))
    {
        if (NULL != pszDefaultValue)
        {
            u32Len = strlen(pszDefaultValue);
            if (MAX_VALID_STRING_LEN < u32Len)
            {
                u32Len = MAX_VALID_STRING_LEN - 1;
                HAL_DEBUG("getString:default string exceed the max length.\n");
            }

            memcpy(szStringValue, pszDefaultValue, u32Len);
        }
        else
        {
            memcpy(szStringValue, "defaultvalue", strlen("defaultvalue"));
        }

        HAL_DEBUG("getString :iniReadString failed, [%s:%s], use default value %s\n", pszSection, pszKey, szStringValue);
    }

    return szStringValue;
}

/***********************************************************************************
* Function:        Ini_IOFile_SetString
* Description:    write a string to pszSection:pszKey,if pszSection is null,use default section,if pszSection
*                      or pszKey is not exist,add it,if exist ,update the value of the key
* Input:              pszKey              :key
*                        pszValue           :the value to be wirte
*                        pszSection         :section
* Return:            SUCCESS     :set success
*                        FAILURE       :set not success
***********************************************************************************/
S32 Ini_IOFile_SetString(CHAR* pszKey, CHAR* pszValue, CHAR* pszSection)
{
    INIFILE_CHECK_PARA(NULL == pszKey);

    if (NULL == pszSection)
    {
        pszSection = (CHAR*)"default";
    }

    pthread_mutex_lock(&s_mutex);
    if (FAILURE == iniWriteString(pszSection, pszKey, pszValue, s_pcFileBuf, &s_u32FileSize))
    {
        HAL_ERROR("setString:iniWriteString failed, [section:key]=[%s:%s]\n", pszSection, pszKey);
        pthread_mutex_unlock(&s_mutex);
        return FAILURE;
    }

    /*update new data to file*/
    if (FAILURE == updateIniFile(s_szFileName, s_pcFileBuf))
    {
        HAL_ERROR("setString:updateIniFile failed\n");
        pthread_mutex_unlock(&s_mutex);
        return FAILURE;
    }

    pthread_mutex_unlock(&s_mutex);
    return SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */
