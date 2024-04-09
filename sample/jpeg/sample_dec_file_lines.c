/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : sample_dec_file_lines.c
Version          : Initial Draft
Author           :
Created          : 2017/12/17
Description      :
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     **********************************************/

#include "sample_api.h"

/***************************** Macro Definition     **********************************************/


/***************************** Structure Definition **********************************************/

/********************** Global Variable declaration ************************************************/
DECLARE_SAMPLE_DEC_SETJMP();


/********************** API forward declarations    ***********************************************/
DECLARE_SAMPLE_DEC_ERR_FUNC();

HI_VOID sample_dec_filein_scanlinesout(HI_CHAR *pFileName)
{
     struct jpeg_decompress_struct cinfo;
     JPEG_MYERR_S jerr;

     HI_U32 u32Width    = 0;
     HI_U32 u32Height   = 0;
     HI_U32 u32Stride   = 0;
     HI_U32 u32MemSize  = 0;

     FILE* pInFile  = NULL;

     HI_CHAR *pDecBuf = NULL;
     JSAMPARRAY buffer;

     SAMPLE_TRACE("\n\n==================================================================================================\n");
     SAMPLE_TRACE("decode jpeg file is %s\n",pFileName);
     SAMPLE_TRACE("==================================================================================================\n");

     pInFile = fopen(pFileName,"rb");
     if(NULL == pInFile)
     {
        SAMPLE_TRACE("open jpeg file failure");
        return;
     }

     /**
      ** use ourself error manage function
      **/
     cinfo.err = jpeg_std_error(&jerr.pub);
     jerr.pub.error_exit = SAMPLE_DEC_ERR_FUCNTION;

     if (setjmp(SAMPLE_DEC_SETJMP_BUFFER))
     {
         goto DEC_FINISH;
     }

     /**
      ** create decompress
      **/
     jpeg_create_decompress(&cinfo);

     /**
      ** set stream
      **/
     jpeg_stdio_src(&cinfo, pInFile);

     /**
      ** parse file
      **/
     jpeg_read_header(&cinfo, TRUE);

     /**
      ** set scale and output color space
      **/
     cinfo.scale_num   = 1 ;
     cinfo.scale_denom = 1;
     cinfo.out_color_space = JCS_RGB;

     jpeg_calc_output_dimensions(&cinfo);

     u32Width   = cinfo.output_width;
     u32Height  = cinfo.output_height;
     u32Stride  = u32Width * 4;
     u32MemSize = u32Stride * u32Height;

     if (0 != u32MemSize)
     {
         pDecBuf = (HI_CHAR*)malloc(u32MemSize);
         if (NULL == pDecBuf)
         {
             SAMPLE_TRACE("malloc y mem failure\n");
             goto DEC_FINISH;
         }
         memset(pDecBuf,0,u32MemSize);
     }
     buffer = (*cinfo.mem->alloc_sarray)
           ((j_common_ptr) &cinfo, JPOOL_IMAGE, u32Stride, 1);

     /**
      ** start decode
      **/
     jpeg_start_decompress(&cinfo);

     /**
      ** output the decode data
      **/
     while (cinfo.output_scanline < cinfo.output_height)
     {
         jpeg_read_scanlines(&cinfo,buffer, 1);
         memcpy(&pDecBuf[(u32Stride * (cinfo.output_scanline-1))], buffer[0], u32Stride);
     }

     test_dec_show(u32Width,u32Height,u32Stride,pDecBuf,cinfo.out_color_space);

     /**
      ** finish decode
      **/
     jpeg_finish_decompress(&cinfo);

DEC_FINISH:

     /**
      ** destory decode
      **/
       jpeg_destroy_decompress(&cinfo);

     fclose(pInFile);
     pInFile = NULL;

     if (NULL != pDecBuf)
     {
         free(pDecBuf);
     }
     pDecBuf = NULL;

     return;

}

int main(int argc,char** argv)
{
#ifdef SAMPLE_DEC_DIR
     HI_S32 s32Ret = HI_SUCCESS;
     HI_CHAR pFileName[256] = {0};
     DIR *dir = NULL;
     struct dirent *ptr = NULL;

     dir = opendir(SAMPLE_DEC_JPEG_FILE_DIR);
     if(NULL==dir)
     {
          SAMPLE_TRACE("open jpeg file directory failure \n");
         return HI_FAILURE;
     }
#endif
     Display_Init();

#ifdef SAMPLE_DEC_DIR
     while ((ptr = readdir(dir))!=NULL)
     {
          s32Ret = sample_getjpegfilename(ptr->d_name,pFileName);
          if (HI_FAILURE == s32Ret)
          {
             continue;
          }
          sample_dec_filein_scanlinesout(pFileName);
     }
     closedir(dir);
#else
     sample_dec_filein_scanlinesout(SAMPLE_DEC_JPEG_FILE);
#endif
     Display_DeInit();

     return 0;
}
