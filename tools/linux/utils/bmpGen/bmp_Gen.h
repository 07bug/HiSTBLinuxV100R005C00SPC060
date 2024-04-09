/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : bmp_gen.h
Version		    : Initial Draft
Author		    :
Created		    : 2013/06/20
Description	    : ����bmpͼƬͷ�ļ�
Function List 	:


History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file
******************************************************************************/

#ifndef __BMP_GEN_H__
#define __BMP_GEN_H__


/*********************************add include here******************************/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bmpGenerator.h"


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
	   extern "C"
	{
#endif
#endif /* __cplusplus */


			/***************************** Macro Definition ******************************/


            /*************************** Enum Definition ****************************/

            /*************************** Structure Definition ****************************/

			/** λͼͷ�ļ��ṹ��ע���ֽڶ������ **/
			/** __attribute__ ((packed)) �����þ��Ǹ��߱�����ȡ���ṹ
			 ** �ڱ�������е��Ż�����,����ʵ��ռ���ֽ������ж��룬��
			 ** GCC���е��﷨����������Ǹ�����ϵͳû��ϵ�����������й�
			 **/
			typedef struct	tagBITMAPFILEHEADER
			{
				HI_U16 u16Type; 		    /** �ļ����ͣ���Ϊ0x4D42                   **/
				HI_U32 u32Size; 		    /** �ļ���С���������ݼ���ͷ�ļ���Сsizeof **/
				HI_U16 u16Reserved1;		/** ����λ                                 **/
				HI_U16 u16Reserved2;		/** ����λ                                 **/
				HI_U32 u32OffBits;			/** �ļ�ͷ��ʵ��λͼ���ݵ�ƫ����           **/
			}__attribute__((packed)) BMP_BMFHEADER_S;

			/** λͼ��Ϣͷ�ṹ **/
			typedef  struct tagBITMAPINFOHEADER{
				HI_U32 u32Size; 		    /** λͼ��Ϣͷ�Ĵ�С,sizeof(BMP_BMIHEADER_S) 		**/
				HI_U32 u32Width;			/** ͼ����                                 		**/
				HI_U32 u32Height;			/** ͼ��߶�                                 		**/
				HI_U16 u32Planes;			/** λͼλ��������Ϊ1                        		**/
				HI_U16 u32PixbitCount;	    /** ÿ�����ص�λ������RGB8888����32          		**/
				HI_U32 u32Compression;     /** λͼ����ѹ�����ͣ���Ϊ0����ʾ����ѹ��    		**/
				HI_U32 u32SizeImage;		/** λͼ���ݴ�С����Ϊ0                      		**/
				HI_U32 u32XPelsPerMeter;	/** λͼˮƽ�ֱ��ʣ���ͼ������ͬ           		**/
				HI_U32 u32YPelsPerMeter;	/** λͼ��ֱ�ֱ��ʣ���ͼ��߶���ͬ           		**/
				HI_U32 u32ClrUsed;		    /** ˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0   **/
				HI_U32 u32ClrImportant;    /** ��ͼ����ʾ����Ҫ����ɫ����������Ϊ0            **/
			} BMP_BMIHEADER_S;

			/********************** Global Variable declaration **************************/
			/** the bytes of a line gernerated **/
			HI_U32 u32BmpStride;

			/******************************* API declaration *****************************/

			/*****************************************************************************
			* func			: BMP_DATA_GetData
			* description	: ��ȡ��ָ�������ڴ��е�����
			* param[in] 	: NA
			* retval		: NA
			* others:		: NA
			*****************************************************************************/
			HI_VOID * BMP_DATA_GetData(HI_VOID);

			/*****************************************************************************
			* func			: BMP_DATA_GenBmp
			* description	: ����λͼ�ļ�
			* param[in] 	: pDataAddr  ��������ݵ�ַ
			* retval		: NA
			* others:		: NA
			*****************************************************************************/
			HI_BOOL BMP_DATA_GenBmp(HI_VOID *);


            void BMP_DATA_GenYuv(void);



#ifdef __cplusplus

#if __cplusplus

		}
#endif
#endif /* __cplusplus */


#endif /* __BMP_GEN_H__*/
