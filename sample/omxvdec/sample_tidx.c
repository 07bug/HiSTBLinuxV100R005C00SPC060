
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "sample_tidx.h"


static int TIDX_FrameTypeChartoSINT32(char type)
{
    int g_FrameType;

    if(type == 'I')
    {
        g_FrameType = 0;    // 0 ��ʾ֡������Ϊ I
    }
    else if(type == 'P')
    {
        g_FrameType = 1;    // 1 ��ʾ֡������Ϊ P
    }
    else if(type == 'B')
    {
        g_FrameType = 2;    // 2 ��ʾ֡������Ϊ B
    }
    else
    {
        g_FrameType = -1;
    }
    return g_FrameType;
}


/***********************************************************/
/*              ��λ����������֡��Ϣ����                 */
/***********************************************************/
static void TIDX_ResetFrameInfoTidx(FRAME_INFO_S *pFrameInfo)
{
    int i;

    /*���ϴ��ļ���Ϣ�е���Ϣ���*/
    for(i = 0 ; i < MAX_LOAD_TIDX_NUM ; i++)
    {
        memset(&(pFrameInfo[i]) , -1 , sizeof(FRAME_INFO_S));
    }
}


/***********************************************************/
/*             ��.tidx�ļ��ж�ȡһ��֡��Ϣ                 */
/***********************************************************/
int ReadFrameInfoFromtidx(STR_CONTEXT_S *pstContext)
{
    int i;
    int total_frame_num = 0;
    char *pFrameInfoBuf,*pFrameInfo;
    char type;
    char fieldtype;

    /*���ϴ��ļ���Ϣ�е���Ϣ���*/
    TIDX_ResetFrameInfoTidx(pstContext->stFrameInfotidx);

    /*tidx�ļ�Ϊ��*/
    if(NULL == pstContext->fptidxFile)
    {
        return PACK_ERR;
    }

    /*����������Ϣ*/
    if(!feof(pstContext->fptidxFile))
    {
        pFrameInfoBuf = (char *)malloc(1024);
        for(i = 0 ; i < MAX_LOAD_TIDX_NUM ; i++)
        {
			if (fgets(pFrameInfoBuf, 1024, pstContext->fptidxFile) == NULL)
            {
                break;
            }
            pFrameInfo = pFrameInfoBuf;
			sscanf(pFrameInfo, "%d", &(pstContext->stFrameInfotidx[i].FrameNum));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
			sscanf(pFrameInfo, "%x", &(pstContext->stFrameInfotidx[i].Frameoffset));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
			sscanf(pFrameInfo, "%d", &(pstContext->stFrameInfotidx[i].FrameSize));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%ld", (long *)&(pstContext->stFrameInfotidx[i].FramePts));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%c", &type);
			pstContext->stFrameInfotidx[i].FrameType = TIDX_FrameTypeChartoSINT32(type);
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].FrameStructure));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%c", &fieldtype);
            pstContext->stFrameInfotidx[i].TopFieldType = TIDX_FrameTypeChartoSINT32(fieldtype);
            pFrameInfo++;
            sscanf(pFrameInfo,"%c", &fieldtype);
            pstContext->stFrameInfotidx[i].BtmFieldType = TIDX_FrameTypeChartoSINT32(fieldtype);
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].TopFieldCrc));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%x", &(pstContext->stFrameInfotidx[i].BtmFieldCrc));
            while(*pFrameInfo != ' ')pFrameInfo++;
            while(*pFrameInfo == ' ')pFrameInfo++;
            sscanf(pFrameInfo,"%d", &(pstContext->stFrameInfotidx[i].NVOPFlag));

            if (1 == pstContext->stFrameInfotidx[i].NVOPFlag)
            {
                pstContext->NvopFrameNum++;
                pstContext->stFrameInfotidx[i].FramePts = -1;
            }
            else
            {
                pstContext->stFrameInfotidx[i].FramePts -= pstContext->NvopFrameNum;
                total_frame_num++;
            }
            if( feof(pstContext->fptidxFile))
            {
                break;
            }
        }
        /*�ͷ�FrameInfoBuf*/
        free(pFrameInfoBuf);
    }

    pstContext->TotalFrameNum = total_frame_num;

    return PACK_OK;
}

