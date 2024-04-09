/******************************************************************************

  Copyright (C), 2005-2006, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_argparser.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/7/1
  Last Modified :
  Description   : Argument parser
  Function List :
  History       :
  1.Date        : 2005/7/27
    Modification: Created file

  2.Date        : 2006/4/7
    Modification: modify for HI3510 Demo
******************************************************************************/

#ifndef __HI_ARGPARSER_H__
#define __HI_ARGPARSER_H__

//#include "hi_head.h"

#include "hi_type.h"
//#include "svr_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TABL "    "
//#ifndef HI_ADVCA_FUNCTION_RELEASE

typedef enum hiARG_TYPE_E
{
    /** ARG_TYPE_NO_PARA��ARG_TYPE_NO_OPT�ǻ���ѡ��*/
    /** ARG_TYPE_STRING��ARG_TYPE_CHAR��ARG_TYPE_INT��ARG_TYPE_FLOAT �ǻ���ѡ��*/
    ARG_TYPE_MUST       = 0x1,   /*�Ƿ��Ǳ���ѡ��*/
    ARG_TYPE_NO_OPT     = 0x2,   /*����û��ѡ��(-XXX), ֻ��һ������ֵ*/
    ARG_TYPE_NO_PARA    = 0x4,   /*����, ��������*/
    ARG_TYPE_STRING     = 0x8,   /*�ַ���*/
    ARG_TYPE_CHAR       = 0x10,  /*�ַ���*/
    ARG_TYPE_INT        = 0x20,  /*����*/
    ARG_TYPE_INT64      = 0x40,  /*64λ����*/
    ARG_TYPE_FLOAT      = 0x80,  /*������*/
    ARG_TYPE_HELP       = 0x100, /**/
    ARG_TYPE_SINGLE     = 0x200, /*���ڸ�ѡ�������������ѡ����򷵻ؽ�������*/
    ARG_TYPE_END        = 0x400,
    ARG_TYPE_BUTT       = 0x800,
    ARG_TYPE_4BYTE      = 0xFFFFFFFF
} ARG_TYPE_E;

typedef struct hiARGOPT_STRUCT_S
{
    const HI_CHAR*        pszOpt;         /** Option ����,��:"cmd -XXX"�е�"XXX" */
    HI_U32          u32Type;        /** Use demo_arg_type,����ͬʱѡ�񼸸�ֵ�İ�λ��,
                                        ��:ARG_TYPE_MUST|ARG_TYPE_NO_OPT|ARG_TYPE_STRING
                                        �����ѡ��Ϊ��������ֵ�ҿ��Բ�����ѡ��,ֵΪ�ַ���������.
                                    */
    const HI_CHAR*        pszValueRegion; /** ��ѡֵ��ȡֵ��Χ,��Χ����ȷ����Ӧ�ø���,
                                        �����ֵΪ�����������ֵ��Ӧ�ý���.
                                        1)��ѡֵ��ʽ      :   "1|2|3|all";
                                            �÷�ʽ������:string,char,int
                                        2)ȡֵ��Χ��ʽ    :   "0~10","1~","~12","a~z","a~";
                                            �÷�ʽ������:char,int,float
                                        3)��ѡȡֵ��Χ��ʽ:   "~-12|0~10|20","~a|c~e|x~y|X~Y";
                                            �÷�ʽ������:int,char,float
                                        string  ֻ���� 1)��ʽ;
                                        float,char,int���� 1)2)3)��ʽ
                                    */
    HI_CHAR         s8Isset;        /** 1: be set, 0 not set */
    HI_U8           au8resv[3];
    const HI_CHAR*        pszHelpMsg;
    HI_VOID*        pValue;
    HI_U32          u32ValueBuffersize;/*pValueָ��ռ䳤��*/
} ARG_OPT_S;

HI_S32  HI_ARG_Parser(int argc, const char **argv, ARG_OPT_S *opts);
HI_VOID HI_ARG_PrintOpt(ARG_OPT_S *pOpt);

HI_VOID HI_ARG_StrToArg(HI_CHAR* pSrc, int* argc, HI_CHAR** argv);
HI_VOID HI_ARG_ClearOpts(ARG_OPT_S *opts);
HI_VOID HI_ARG_PrintHelp(HI_U32 u32Handle, ARG_OPT_S *opts);
HI_S32  HI_ARG_OptIsSet(const HI_CHAR *opt_name, ARG_OPT_S *opts);

//#endif/*HI_ADVCA_FUNCTION_RELEASE*/

#define ARG_S4 "    "     /*4 space*/
#define HI_ARG_MAX_OPT_NAME_LEN (256) // define option name length for strncmp

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* ARGPARSER_H__ */
