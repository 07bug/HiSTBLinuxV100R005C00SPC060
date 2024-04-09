#include "vdp_drv_coef.h"

#ifndef __DISP_PLATFORM_BOOT__
#if VDP_CBB_FPGA
#include "hi_drv_mmz.h"
#endif
#endif

#if EDA_TEST

extern S_VDP_REGS_TYPE *pVdpReg;
extern void (*HiMemWordWr)(const Cell*);
extern Cell* (*HiMemWordRd)(const Cell*);
extern Cell cell;
#endif

#if VDP_CBB_FPGA
extern MMZ_BUFFER_S stMBufCvm;
extern MMZ_BUFFER_S stMBufInGamma;
extern MMZ_BUFFER_S stMBufInDegamma;
extern MMZ_BUFFER_S stMBufOutGamma;
extern MMZ_BUFFER_S stMBufOutDegamma;
#else
#include "string.h"
#endif

#define  VDP_COEF_PROBE_FILE_EN  1
#define  COEF_DEBUG              0

HI_U8* VDP_DRV_SendCoef(VDP_DRV_COEF_SEND_CFG* stCfg)
{
    HI_U32 ii,kk,nn,mm;
    HI_U8* addr_base               = stCfg->coef_addr;
    HI_U32 addr_offset             = 0;
    HI_U8* addr                    = addr_base;

    HI_U32 cycle_num ;
    HI_U32 total_bit_len           = 0;

    VDP_DRV_U128_S stData128;
    HI_U32 coef_cnt                = 0;

    HI_S32 tmp_data                = 0;
    HI_U32 total_burst_num         = 0;
    //HI_U32 total_burst_cycle_num   = 0;
    //HI_U32 lut_cnt                 = 0;
    //HI_U32 max_num_each_burst      = 0;
    HI_U32 max_len                 = 0;
    //HI_U32 cycle_cnt               = 0;


	addr_base  = stCfg->coef_addr;


    //----------------------------------------------------------------------
    //data type convertion
    //----------------------------------------------------------------------

	addr = addr_base;

	cycle_num = stCfg->cycle_num ;

    for(ii=0;ii<stCfg->lut_num;ii++)
    {
        total_bit_len = total_bit_len + stCfg->coef_bit_length[ii];
    }

    //send data
    max_len = VDP_DRV_FindMax( stCfg->lut_length , stCfg->lut_num) ;
//    cycle_num = (128 * stCfg->burst_num) / total_bit_len ;

    if(stCfg->burst_num == 1)
    {
        total_burst_num = (max_len + cycle_num -1)/cycle_num;

        if(stCfg->data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(kk=0; kk<total_burst_num; kk++)
            {
                memset((void*)&stData128, 0 , sizeof(stData128));
                for(mm=0 ; mm<cycle_num ; mm++)
                {
                    coef_cnt = kk * cycle_num + mm ;
                    for(nn=0; nn < stCfg->lut_num ; nn++)
                    {
                        if(coef_cnt < stCfg->lut_length[nn])
                        {
                            tmp_data = ((HI_S16**)stCfg->p_coef_array)[nn][coef_cnt];
                        }
                        else
                        {
                            tmp_data = 0;
                        }
                        VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
                    }
                }
                addr = addr_base + addr_offset;
                addr_offset = addr_offset + 16;
                VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
            }
        }
        else if(stCfg->data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(kk=0; kk<total_burst_num; kk++)
            {
                memset((void*)&stData128, 0 , sizeof(stData128));
                for(mm=0 ; mm<cycle_num ; mm++)
                {
                    coef_cnt = kk * cycle_num + mm ;
                    for(nn=0; nn < stCfg->lut_num ; nn++)
                    {
                        if(coef_cnt < stCfg->lut_length[nn])
                        {
                            tmp_data = ((HI_U16**)stCfg->p_coef_array)[nn][coef_cnt];
                        }
                        else
                        {
                            tmp_data = 0;
                        }
                        VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
                    }
                }
                addr = addr_base + addr_offset;
                addr_offset = addr_offset + 16;
                VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
            }
        }
		else if(stCfg->data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(kk=0; kk<total_burst_num; kk++)
            {
                memset((void*)&stData128, 0 , sizeof(stData128));
                for(mm=0 ; mm<cycle_num ; mm++)
                {
                    coef_cnt = kk * cycle_num + mm ;
                    for(nn=0; nn < stCfg->lut_num ; nn++)
                    {
                        if(coef_cnt < stCfg->lut_length[nn])
                        {
                            tmp_data = ((HI_U32**)stCfg->p_coef_array)[nn][coef_cnt];
                        }
                        else
                        {
                            tmp_data = 0;
                        }
                        VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
                    }
                }
                addr = addr_base + addr_offset;
                addr_offset = addr_offset + 16;
                VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
            }
        }
        else if(stCfg->data_type == DRV_COEF_DATA_TYPE_S32)
		{
			for(kk=0; kk<total_burst_num; kk++)
			{
				memset((void*)&stData128, 0 , sizeof(stData128));
				for(mm=0 ; mm<cycle_num ; mm++)
				{
					coef_cnt = kk * cycle_num + mm ;
					for(nn=0; nn < stCfg->lut_num ; nn++)
					{
						if(coef_cnt < stCfg->lut_length[nn])
						{
							tmp_data = ((HI_S32**)stCfg->p_coef_array)[nn][coef_cnt];
						}
						else
						{
							tmp_data = 0;
						}
						VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
					}
				}
				addr = addr_base + addr_offset;
				addr_offset = addr_offset + 16;
				VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
			}
		}
        else if(stCfg->data_type == DRV_COEF_DATA_TYPE_S8)
		{
			for(kk=0; kk<total_burst_num; kk++)
			{
				memset((void*)&stData128, 0 , sizeof(stData128));
				for(mm=0 ; mm<cycle_num ; mm++)
				{
					coef_cnt = kk * cycle_num + mm ;
					for(nn=0; nn < stCfg->lut_num ; nn++)
					{
						if(coef_cnt < stCfg->lut_length[nn])
						{
							tmp_data = ((HI_S8**)stCfg->p_coef_array)[nn][coef_cnt];
						}
						else
						{
							tmp_data = 0;
						}
						VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
					}
				}
				addr = addr_base + addr_offset;
				addr_offset = addr_offset + 16;
				VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
			}
		}
        else if(stCfg->data_type == DRV_COEF_DATA_TYPE_U8)
		{
			for(kk=0; kk<total_burst_num; kk++)
			{
				memset((void*)&stData128, 0 , sizeof(stData128));
				for(mm=0 ; mm<cycle_num ; mm++)
				{
					coef_cnt = kk * cycle_num + mm ;
					for(nn=0; nn < stCfg->lut_num ; nn++)
					{
						if(coef_cnt < stCfg->lut_length[nn])
						{
							tmp_data = ((HI_U8**)stCfg->p_coef_array)[nn][coef_cnt];
						}
						else
						{
							tmp_data = 0;
						}
						VDP_DRV_Push128(&stData128, tmp_data, stCfg->coef_bit_length[nn]);
					}
				}
				addr = addr_base + addr_offset;
				addr_offset = addr_offset + 16;
				VDP_DRV_WriteDDR(stCfg->sti_type,stCfg->fp_coef,addr,&stData128);
			}
		}

    }

    return (addr_base + addr_offset);

}

HI_S32 VDP_DRV_Push128(VDP_DRV_U128_S* pstData128, HI_U32 coef_data, HI_U32 bit_len)
{

    coef_data = coef_data & (0xFFFFFFFF >> (32-bit_len));

    if(pstData128->depth < 32)
    {
        if((pstData128->depth + bit_len) <= 32)
        {
            pstData128->data0 = (coef_data << pstData128->depth) | pstData128->data0;
        }
        else
        {
            pstData128->data0 = (coef_data << pstData128->depth) | pstData128->data0;
            pstData128->data1 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 32 && pstData128->depth < 64)
    {
        if((pstData128->depth + bit_len) <= 64)
        {
            pstData128->data1 = (coef_data << pstData128->depth%32) | pstData128->data1;
        }
        else
        {
            pstData128->data1 = (coef_data << pstData128->depth%32) | pstData128->data1;
            pstData128->data2 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 64 && pstData128->depth < 96)
    {
        if((pstData128->depth + bit_len) <= 96)
        {
            pstData128->data2 = (coef_data << pstData128->depth%32) | pstData128->data2;
        }
        else
        {
            pstData128->data2 = (coef_data << pstData128->depth%32) | pstData128->data2;
            pstData128->data3 = coef_data >> (32 - pstData128->depth%32);
        }
    }
    else if(pstData128->depth >= 96)
    {
        if((pstData128->depth + bit_len) <= 128)
        {
            pstData128->data3 = (coef_data << (pstData128->depth%32)) | pstData128->data3;
        }
    }

    pstData128->depth = pstData128->depth + bit_len;

    if(pstData128->depth <= 128)
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

}


HI_U32 VDP_DRV_FindMax(HI_U32* u32Array, HI_U32 num)
{
    HI_U32 ii;
    HI_U32 u32TmpData = u32Array[0];

    for(ii=1;ii<num;ii++)
    {
        if(u32TmpData < u32Array[ii])
        {
            u32TmpData = u32Array[ii];
        }
    }
    return u32TmpData;
}

HI_U32 VDP_DRV_WriteDDR(STI_FILE_TYPE_E enStiType, FILE* fp_coef ,HI_U8* addr, VDP_DRV_U128_S * pstData128 )
{
    HI_U32 ii=0;
    HI_U32 u32DataArr[4]={pstData128->data0,pstData128->data1,pstData128->data2,pstData128->data3};
    HI_U8* pu8AddrTmp=0;

    HI_U32     uDataTemp = 0;
    for(ii=0;ii<4;ii++)
    {
        pu8AddrTmp = addr + ii*4;
        uDataTemp = u32DataArr[ii];
		*(HI_U32 *)pu8AddrTmp  = uDataTemp;
    }

    return 0;
}



