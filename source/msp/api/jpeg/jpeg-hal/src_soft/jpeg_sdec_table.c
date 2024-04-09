/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_sdec_table.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : get table
Function List    :


History          :
Date                  Author                 Modification
2018/01/01            sdk                    Created file
***************************************************************************************************/

/***************************** add include here****************************************************/

/***************************** Macro Definition ***************************************************/
#define  LU                 0
#define  CH                 1
#define  MAX_TAB            2

#define CAI_JPEG_SWAP(a,b)  do{ a=a+b; b=a-b; a=a-b; } while(0)

/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/
#if 0
static HI_U32 gs_HuffDcTab[12]   = {0x200200,   0x201302,    0x202303,    0x306304,
                                    0x40e305,   0x51e306,    0x63e40e,    0x77e51e,
                                    0x8fe63e,   0x9fe77e,    0xafe8fe,    0xbfe9fe
                                   };

static HI_U32 gs_HufAcMinTab[8]  = {0x0,        0xa040a04,   0x38183a1a,  0xf678f878,
                                    0xf6f4f6f6, 0xf4f6f4f6,  0xe0f0e0f0,  0x88c282c0
                                   };

static HI_U32 gs_HufAcBaseTab[8] = {0x0,        0xf9fef9fe,  0xd1edcfec,  0x1a951793,
                                    0x2520211c, 0x302a2c26,  0x48000000,  0xa367a364
                                   };

static HI_U32 gs_HufAcSymbolTab[256] = {0x1,     0x102,   0x203,   0x300,   0x1104,  0x411,   0x505,   0x2112,
                                        0x3121,  0x631,   0x1241,  0x4106,  0x5113,  0x751,   0x6161,  0x7107,
                                        0x1322,  0x2271,  0x3214,  0x8132,  0x881,   0x1491,  0x42a1,  0x9108,
                                        0xa123,  0xb142,  0xc1b1,  0x9c1,   0x2315,  0x3352,  0x52d1,  0xf0f0,
                                        0x1524,  0x6233,  0x7262,  0xd172,  0xa82,   0x1609,  0x240a,  0x3416,
                                        0xe117,  0x2518,  0xf119,  0x171a,  0x1825,  0x1926,  0x1a27,  0x2628,
                                        0x2729,  0x282a,  0x2934,  0x2a35,  0x3536,  0x3637,  0x3738,  0x3839,
                                        0x393a,  0x3a43,  0x4344,  0x4445,  0x4546,  0x4647,  0x4748,  0x4849,
                                        0x494a,  0x4a53,  0x5354,  0x5455,  0x5556,  0x5657,  0x5758,  0x5859,
                                        0x595a,  0x5a63,  0x6364,  0x6465,  0x6566,  0x6667,  0x6768,  0x6869,
                                        0x696a,  0x6a73,  0x7374,  0x7475,  0x7576,  0x7677,  0x7778,  0x7879,
                                        0x797a,  0x7a83,  0x8284,  0x8385,  0x8486,  0x8587,  0x8688,  0x8789,
                                        0x888a,  0x8992,  0x8a93,  0x9294,  0x9395,  0x9496,  0x9597,  0x9698,
                                        0x9799,  0x989a,  0x99a2,  0x9aa3,  0xa2a4,  0xa3a5,  0xa4a6,  0xa5a7,
                                        0xa6a8,  0xa7a9,  0xa8aa,  0xa9b2,  0xaab3,  0xb2b4,  0xb3b5,  0xb4b6,
                                        0xb5b7,  0xb6b8,  0xb7b9,  0xb8ba,  0xb9c2,  0xbac3,  0xc2c4,  0xc3c5,
                                        0xc4c6,  0xc5c7,  0xc6c8,  0xc7c9,  0xc8ca,  0xc9d2,  0xcad3,  0xd2d4,
                                        0xd3d5,  0xd4d6,  0xd5d7,  0xd6d8,  0xd7d9,  0xd8da,  0xd9e1,  0xdae2,
                                        0xe2e3,  0xe3e4,  0xe4e5,  0xe5e6,  0xe6e7,  0xe7e8,  0xe8e9,  0xe9ea,
                                        0xeaf1,  0xf2f2,  0xf3f3,  0xf4f4,  0xf5f5,  0xf6f6,  0xf7f7,  0xf8f8,
                                        0xf9f9,  0xfafa,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                                        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0
                                       };
#else
static const JPEG_HUFF_TBL gs_u8DefaultDC[2] = {
  			 {
			 	/** luma DC */{0x00,
  			     0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
			    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B},0
  			  },
			 {
				/** chrom DC */{0x01,
			     0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
			    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B},0
			 }
		};
static const JPEG_HUFF_TBL gs_u8DefaultAC[2] = {
  	        {
				/** luma AC */{0x10,
				 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7D},
				{0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
				 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
				 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
				 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
				 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
				 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
				 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
				 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
				 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
				 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
				 0xF9, 0xFA},0
  			},
		    {
				/** chrom AC */{0x11,
				 0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77},
				{0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
				 0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0,
				 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26,
				 0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
				 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
				 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
				 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
				 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
				 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
				 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
				 0xF9, 0xFA},0
			}
		};

#endif

/***************************** API forward declarations *******************************************/
static inline HI_VOID JPEG_SDEC_GetQuantTable(JPEG_IMG_INFO_S *pstImgInfo);
static inline HI_VOID JPEG_SDEC_GetHuffmanTable(JPEG_IMG_INFO_S *pstImgInfo);
static inline HI_VOID JPEG_SDEC_GetHuffmanDcTable(JPEG_IMG_INFO_S *pstImgInfo);

static inline HI_VOID JPEG_SDEC_GetHuffmanAcTable(JPEG_IMG_INFO_S *pstImgInfo);
static inline HI_VOID JPEG_SDEC_DcTableForReg(JPEG_HUFF_TBL* pDcHuffmanTable, HI_U32 HuffCode[], HI_U32 MaxIndex, HI_U32 TabNum, JPEG_IMG_INFO_S *pstImgInfo);

static inline HI_U32 JPEG_SDEC_HuffmanDcDec(const JPEG_HUFF_TBL *huff_tbl, unsigned int bit[256]);
static inline HI_U32 JPEG_SDEC_HuffmanAcDec(const JPEG_HUFF_TBL *huff_tbl);


/******************************* API realization **************************************************/
static inline HI_VOID JPEG_SDEC_GetTable(JPEG_IMG_INFO_S *pstImgInfo)
{
    JPEG_SDEC_GetQuantTable(pstImgInfo);
    JPEG_SDEC_GetHuffmanTable(pstImgInfo);
    return;
}

static inline HI_VOID JPEG_SDEC_GetQuantTable(JPEG_IMG_INFO_S *pstImgInfo)
{
     HI_U16 *QCr = NULL;
     HI_U16 *QCb = NULL;
     HI_U16 *QY  = NULL;
     HI_U32 Cnt = 0;
     HI_S32 quant_tbl_no[MAX_NUM_QUANT_TBLS] = {0};

     HI_U16 T81ProtocolLuQuantTable[HI_DCT_SIZE2] = {
                                       16, 11, 10, 16, 24, 40, 51, 61,
                                       12, 12, 14, 19, 26, 58, 60, 55,
                                       14, 13, 16, 24, 40, 57, 69, 56,
                                       14, 17, 22, 29, 51, 87, 80, 62,
                                       18, 22, 37, 56, 68, 109,103,77,
                                       24, 35, 55, 64, 81, 104,113,92,
                                       49, 64, 78, 87, 103,121,120,101,
                                       72, 92, 95, 98, 112,100,103,99
                                      };
     HI_U16 T81ProtocolChQuantTable[HI_DCT_SIZE2] = {
                                         17, 18, 24, 47, 99, 99, 99, 99,
                                         18, 21, 26, 66, 99, 99, 99, 99,
                                         24, 26, 56, 99, 99, 99, 99, 99,
                                         47, 66, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99,
                                         99, 99, 99, 99, 99, 99, 99, 99
                                        };


     if (pstImgInfo->num_components > HI_JPEG_MAX_COMPONENT_NUM)
     {
         return;
     }

     if (HI_FALSE == pstImgInfo->QuantTbl[0].bHasQuantTbl)
     {
         QY  = (unsigned short *)T81ProtocolLuQuantTable;
         QCb = (unsigned short *)T81ProtocolChQuantTable;
         QCr = (unsigned short *)T81ProtocolChQuantTable;
     }
     else
     {
         for (Cnt = 0; Cnt < pstImgInfo->num_components; Cnt++)
         {
              quant_tbl_no[Cnt] = ((pstImgInfo->stComponentInfo[Cnt].QuantTblNo < 0 || pstImgInfo->stComponentInfo[Cnt].QuantTblNo >= MAX_NUM_QUANT_TBLS)) ? (0) : (pstImgInfo->stComponentInfo[Cnt].QuantTblNo);
         }

         if (HI_FALSE == pstImgInfo->QuantTbl[quant_tbl_no[0]].bHasQuantTbl)
         {
             return;
         }
         QY  = pstImgInfo->QuantTbl[quant_tbl_no[0]].quantval;
         QCb = (HI_FALSE == pstImgInfo->QuantTbl[quant_tbl_no[1]].bHasQuantTbl) ? (QY)  : (pstImgInfo->QuantTbl[quant_tbl_no[1]].quantval);
         QCr = (HI_FALSE == pstImgInfo->QuantTbl[quant_tbl_no[2]].bHasQuantTbl) ? (QCb) : (pstImgInfo->QuantTbl[quant_tbl_no[2]].quantval);
     }

     for (Cnt = 0; Cnt < HI_DCT_SIZE2; Cnt++)
     {
         pstImgInfo->QuantTab[Cnt] = QY[Cnt] + (QCb[Cnt] << 8) + (QCr[Cnt] << 16);
     }

     return;
}


static inline HI_VOID JPEG_SDEC_GetHuffmanTable(JPEG_IMG_INFO_S *pstImgInfo)
{
    JPEG_SDEC_GetHuffmanDcTable(pstImgInfo);
    JPEG_SDEC_GetHuffmanAcTable(pstImgInfo);
    return;
}

static inline HI_VOID JPEG_SDEC_GetHuffmanDcTable(JPEG_IMG_INFO_S *pstImgInfo)
{
    HI_U32 huffcode[MAX_TAB][256]  = {{0}};
    HI_U32 max_idx[MAX_TAB]        = {0};
    HI_U8 *pLuDcDefaultTable = (HI_U8*)&(gs_u8DefaultDC[0]);
    HI_U8 *pChDcDefaultTable = (HI_U8*)&(gs_u8DefaultDC[1]);
    JPEG_HUFF_TBL DcHuffmanTablePtr[MAX_TAB] = { { {0}, {0}, 0} };

    if ((HI_FALSE == pstImgInfo->DcHuffTbl[0].bHasHuffTbl) || (HI_TRUE == pstImgInfo->DcHuffTbl[2].bHasHuffTbl))
    {
        pLuDcDefaultTable += 1;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU].bits[1]), pLuDcDefaultTable, 16);
        pLuDcDefaultTable += 16;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU].huffval[0]), pLuDcDefaultTable, 12);

        pChDcDefaultTable += 1;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH].bits[1]), pChDcDefaultTable, 16);
        pChDcDefaultTable += 16;
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH].huffval[0]), pChDcDefaultTable, 12);
    }
    else
    {
        HI_GFX_Memcpy(&(DcHuffmanTablePtr[LU]), &(pstImgInfo->DcHuffTbl[0]), sizeof(DcHuffmanTablePtr[LU]));
        if (HI_FALSE == pstImgInfo->DcHuffTbl[1].bHasHuffTbl)
        {
           HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH]),&(pstImgInfo->DcHuffTbl[0]),sizeof(DcHuffmanTablePtr[LU]));
        }
        else
        {
            HI_GFX_Memcpy(&(DcHuffmanTablePtr[CH]),&(pstImgInfo->DcHuffTbl[1]),sizeof(DcHuffmanTablePtr[LU]));
        }
    }

    max_idx[LU] = JPEG_SDEC_HuffmanDcDec(&DcHuffmanTablePtr[LU], huffcode[LU]);
    max_idx[CH] = JPEG_SDEC_HuffmanDcDec(&DcHuffmanTablePtr[CH], huffcode[CH]);

    JPEG_SDEC_DcTableForReg(&DcHuffmanTablePtr[LU], huffcode[LU], max_idx[LU],LU,pstImgInfo);
    JPEG_SDEC_DcTableForReg(&DcHuffmanTablePtr[CH], huffcode[CH], max_idx[CH],CH,pstImgInfo);

    return;
}

static inline HI_VOID JPEG_SDEC_DcTableForReg(JPEG_HUFF_TBL* pDcHuffmanTable, HI_U32 HuffCode[], HI_U32 MaxIndex, HI_U32 TabNum, JPEG_IMG_INFO_S *pstImgInfo)
{
    HI_U32 sum_syms  = 0;
    HI_U32 syms      = 0;
    HI_U32 temp      = 0;
    HI_U32 index     = 0;
    HI_U32 index1    = 0;
    HI_U32 dc_hufflen[12] = {0};
    HI_U32 dc_sym[12]     = {0};

    if (MaxIndex > 16)
    {
       return;
    }

    for (index = 0; index < MaxIndex; index++)
    {
       syms = pDcHuffmanTable->bits[index + 1];
       sum_syms += syms;
       while ((syms--) && (temp < 12))
       {
           dc_hufflen[temp] = index + 1;
           dc_sym[temp] = pDcHuffmanTable->huffval[temp];
           temp++;
       }
    }

    if (sum_syms > 12)
    {
       return;
    }

    for (index = 0; index < sum_syms; index++)
    {
       for (index1 = index + 1; index1 < sum_syms; index1++)
       {
           if (dc_sym[index] > dc_sym[index1])
           {
               CAI_JPEG_SWAP(dc_sym[index],     dc_sym[index1]);
               CAI_JPEG_SWAP(dc_hufflen[index], dc_hufflen[index1]);
               CAI_JPEG_SWAP(HuffCode[index],   HuffCode[index1]);
           }
       }

       if (dc_sym[index] >= 12)
       {
           return;
       }
    }


    for (index = 0;index < sum_syms; index++)
    {
        *(pstImgInfo->HuffDcTab + dc_sym[index]) = (0 == TabNum) ?
                                                   ( ((*(pstImgInfo->HuffDcTab + dc_sym[index])) & 0xfffff000)
                                                    | ((dc_hufflen[index] & 0xf) << 8) \
                                                    | ((HuffCode[index] & 0xff))) :
                                                   (  ((*(pstImgInfo->HuffDcTab + dc_sym[index])) & 0xff000fff)
                                                    | ((dc_hufflen[index] & 0xf) << 20) \
                                                    | ((HuffCode[index] & 0xff) << 12));

    }

    return;
}


static inline HI_VOID JPEG_SDEC_GetHuffmanAcTable(JPEG_IMG_INFO_S *pstImgInfo)
{
     HI_U32 TabNum = 0;
     HI_U32 index = 0;
     HI_U32 pre_index = 0;
     HI_U32 sum_syms = 0;
     HI_U32 syms = 0;

     HI_U32 min_tab[MAX_TAB][16]    = {{0}};
     HI_U32 base_tab[MAX_TAB][16]   = {{0}};
     HI_U32 max_idx[MAX_TAB]        = {0};

     JPEG_HUFF_TBL AcHuffmanTablePtr[MAX_TAB] = { { {0}, {0}, 0} };

     HI_U8 *pLuAcDefaultTable = (HI_U8*)&(gs_u8DefaultAC[0]);
     HI_U8 *pChAcDefaultTable = (HI_U8*)&(gs_u8DefaultAC[1]);

     if ((HI_FALSE == pstImgInfo->AcHuffTbl[0].bHasHuffTbl) || (HI_TRUE == pstImgInfo->AcHuffTbl[2].bHasHuffTbl))
     {
         pLuAcDefaultTable += 1;
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].bits[0]),0,17);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU].bits[1]), pLuAcDefaultTable, 16);

         pLuAcDefaultTable += 16;
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU].huffval[0]), pLuAcDefaultTable, 162);

         pChAcDefaultTable += 1;
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].bits[0]),0,17);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH].bits[1]), pChAcDefaultTable, 16);

         pChAcDefaultTable += 16;
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH].huffval[0]), pChAcDefaultTable, 162);
     }
     else
     {
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].bits[0]),0,17);
         HI_GFX_Memset(&(AcHuffmanTablePtr[LU].huffval[0]),0,256);
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].bits[0]),0,17);
         HI_GFX_Memset(&(AcHuffmanTablePtr[CH].huffval[0]),0,256);
         HI_GFX_Memcpy(&(AcHuffmanTablePtr[LU]), &(pstImgInfo->AcHuffTbl[0]), sizeof(AcHuffmanTablePtr[LU]));

         if (HI_FALSE == pstImgInfo->AcHuffTbl[1].bHasHuffTbl)
         {
             HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH]),&(pstImgInfo->AcHuffTbl[0]),sizeof(AcHuffmanTablePtr[LU]));
         }
         else
         {
             HI_GFX_Memcpy(&(AcHuffmanTablePtr[CH]),&(pstImgInfo->AcHuffTbl[1]),sizeof(AcHuffmanTablePtr[LU]));
         }
     }

     max_idx[LU] = JPEG_SDEC_HuffmanAcDec(&AcHuffmanTablePtr[0]);
     max_idx[CH] = JPEG_SDEC_HuffmanAcDec(&AcHuffmanTablePtr[1]);

     for (TabNum = 0; TabNum < MAX_TAB; TabNum++)
     {
          sum_syms = 0;
          for (index = 0; index < 16; index++)
          {
              syms = AcHuffmanTablePtr[TabNum].bits[index + 1];
              pre_index = index?(index - 1):(0);

              if (index < max_idx[TabNum])
              {
                  min_tab[TabNum][index] = (min_tab[TabNum][pre_index] + AcHuffmanTablePtr[TabNum].bits[index]) << 1;
                  if (syms)
                  {
                      base_tab[TabNum][index] = sum_syms - min_tab[TabNum][index];
                  }
                  sum_syms += AcHuffmanTablePtr[TabNum].bits[index+1];
              }
              else
              {
                  min_tab[TabNum][index] = ~0;
              }
          }

          if (sum_syms > 256)
          {
             return;
          }

          for (index = 0; index < sum_syms; index++)
          {
              pstImgInfo->HufAcSymbolTab[index] |= (0 == TabNum) ?
                                                   ((unsigned int)(AcHuffmanTablePtr[LU].huffval[index])):
                                                   ((unsigned int)(AcHuffmanTablePtr[CH].huffval[index]) << 8);
          }
     }

     for (index = 0; index < 8;index++)
     {
         pstImgInfo->HufAcMinTab[index] =   ( (min_tab[CH][2 * index + 1] & 0xff) << 24)
                                            | ((min_tab[CH][2 * index] & 0xff) << 16)
                                            | ((min_tab[LU][2 * index + 1] & 0xff) << 8)
                                            | ((min_tab[LU][2 * index] & 0xff));

         pstImgInfo->HufAcBaseTab[index] =  ( (base_tab[CH][2 * index + 1] & 0xff) << 24)
                                            | ((base_tab[CH][2 * index] & 0xff) << 16)
                                            | ((base_tab[LU][2 * index + 1] & 0xff) << 8)
                                            | ((base_tab[LU][2 * index] & 0xff));
     }

     return;
}

static inline HI_U32 JPEG_SDEC_HuffmanDcDec(const JPEG_HUFF_TBL *huff_tbl, unsigned int bit[256])
{
    HI_U32 idx     = 0;
    HI_U32 cnt     = 0;
    HI_U32 loc     = 0;
    HI_U32 value   = 0;
    HI_U32 max_idx = 0;

    HI_GFX_Memset(bit,0,sizeof(bit[0]));

    for (idx = 1; idx < 17; idx++)
    {
       if (0 == huff_tbl->bits[idx])
       {
          value <<= 1;
          continue;
       }

       max_idx = idx;

       for (cnt = huff_tbl->bits[max_idx]; cnt > 0 && loc < 256; cnt--)
       {
           bit[loc] = value;
           loc++;
           value++;
       }

       value <<= 1;
    }

    return max_idx;
}

static inline HI_U32 JPEG_SDEC_HuffmanAcDec(const JPEG_HUFF_TBL *huff_tbl)
{
    HI_U32 index   = 0;
    HI_U32 max_idx = 0;

    for (index = 1; index < 17; index++)
    {
       if (0 == huff_tbl->bits[index])
       {
        continue;
       }
       max_idx = index;
    }

    return max_idx;
}
