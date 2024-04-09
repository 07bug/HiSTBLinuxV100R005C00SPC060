#include "vdp_gen_coef.h"
#if EDA_TEST
#include "vdp_sti.h"
#endif

#if EDA_TEST
static HI_U32 VDP_DRV_uGetRand(HI_U32 max, HI_U32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;
    HI_U32 u32_rand_data = 0;

    if(max > min)
    {
        u32_max_data = max;
        u32_min_data = min;
    }
    else
    {
        u32_max_data = min;
        u32_min_data = max;
    }

    u32_rand_data = u32_min_data + rand()%((HI_U64)u32_max_data + 1 - u32_min_data);

    return (u32_rand_data);
}

static HI_S32 VDP_DRV_sGetRand(HI_S32 max, HI_S32 min)
{
    HI_U32 u32_max_data = 0;
    HI_U32 u32_min_data = 0;

    HI_S32 s32_return_data = 0;

    if(((max == 0)&&(min == 0)) || (min == max))
    {
#if EDA_TEST
        cout << "Error, Worng sRand seed!" << endl;
#endif
    }
    else if(((max >= 0)&&(min > 0)) || ((max > 0)&&(min >= 0)))
    {
        if(max > min)
        {
            u32_max_data = max;
            u32_min_data = min;
        }
        else
        {
            u32_max_data = min;
            u32_min_data = max;
        }

        s32_return_data = (u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else if(((max <= 0)&&(min < 0)) || ((max < 0)&&(min <= 0)))
    {
        if(abs(max) > abs(min))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        s32_return_data = -(u32_min_data + rand()%(u32_max_data + 1 - u32_min_data));
    }
    else
    {
        if((max > 0)&&(min < 0))
        {
            u32_max_data = abs(max);
            u32_min_data = abs(min);
        }
        else
        {
            u32_max_data = abs(min);
            u32_min_data = abs(max);
        }

        if(rand()%2 == 0)
        {
            s32_return_data = -(rand()%(u32_min_data + 1));
        }
        else
        {
            s32_return_data =    rand()%(u32_max_data + 1);
        }
    }

    return s32_return_data;
}

//add coef up sort
static HI_S32 VDP_DRV_CoefUpSortU8(const void *a, const void *b)
{
    return ((HI_S32)*(HI_U8 *)a - (HI_S32)*(HI_U8 *)b) ;
}

static HI_S32 VDP_DRV_CoefUpSortS8(const void *a, const void *b)
{
    return ((HI_S32)*(HI_S8 *)a - (HI_S32)*(HI_S8 *)b) ;
}

static HI_S32 VDP_DRV_CoefUpSortU16(const void *a, const void *b)
{
    return ((HI_S32)*(HI_U16 *)a - (HI_S32)*(HI_U16 *)b) ;
}

static HI_S32 VDP_DRV_CoefUpSortS16(const void *a, const void *b)
{
    return ((HI_S32)*(HI_S16 *)a - (HI_S32)*(HI_S16 *)b) ;
}

static HI_S32 VDP_DRV_CoefUpSortU32(const void *a, const void *b)
{
    if(*(HI_U32 *)a > *(HI_U32 *)b)
        return 1 ;
    else if(*(HI_U32 *)a == *(HI_U32 *)b)
        return 0 ;
    else
        return -1;
}

static HI_S32 VDP_DRV_CoefUpSortS32(const void *a, const void *b)
{
    return (*(HI_S32 *)a - *(HI_S32 *)b) ;
}
#endif

HI_U32 VDP_DRV_GenCoef(VDP_DRV_COEF_GEN_CFG* stCfg)
{
    HI_U32 ii=0;
	#if EDA_TEST
    HI_S32 tmp_data=0;
    #endif

    if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_TYP)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U8*)stCfg->p_coef_new)[ii] = ((HI_U8*)stCfg->p_coef)[ii];
            }
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S8*)stCfg->p_coef_new)[ii] = ((HI_S8*)stCfg->p_coef)[ii];
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U16*)stCfg->p_coef_new)[ii] = ((HI_U16*)stCfg->p_coef)[ii];
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S16*)stCfg->p_coef_new)[ii] = ((HI_S16*)stCfg->p_coef)[ii];
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_U32*)stCfg->p_coef_new)[ii] = ((HI_U32*)stCfg->p_coef)[ii];
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                ((HI_S32*)stCfg->p_coef_new)[ii] = ((HI_S32*)stCfg->p_coef)[ii];
            }

        }

    }
#if EDA_TEST
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_RAN)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_uGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_ZRO)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = 0;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_MIN)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_min;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_MAX)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = stCfg->coef_max;
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

        }

    }
    else if(stCfg->coef_data_mode == VDP_RM_COEF_MODE_UP)
    {
        if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_U8) , VDP_DRV_CoefUpSortU8);

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S8)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S8*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S8) , VDP_DRV_CoefUpSortS8);

        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U16*)stCfg->p_coef_new)[ii] = tmp_data;
            }
            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_U16) , VDP_DRV_CoefUpSortU16);
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S16)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S16*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S16) , VDP_DRV_CoefUpSortS16);
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_U32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_uGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_U32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new    , stCfg->length , sizeof(HI_U32) , VDP_DRV_CoefUpSortU32);
        }
        else if(stCfg->coef_data_type == DRV_COEF_DATA_TYPE_S32)
        {
            for(ii=0;ii<stCfg->length;ii++)
            {
                tmp_data = VDP_DRV_sGetRand(stCfg->coef_min,stCfg->coef_max);
                ((HI_S32*)stCfg->p_coef_new)[ii] = tmp_data;
            }

            qsort(stCfg->p_coef_new     , stCfg->length , sizeof(HI_S32) , VDP_DRV_CoefUpSortS32);
        }
    }

    else
    {
        printf("Error, VDP_DRV_GenCoef don't support this mode!\n");
    }
#endif
    return 0;

}






