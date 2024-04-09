#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "omx_dbg.h"

#include "omx_allocator.h"

#include "hi_common.h"

#define OMXVENC_ALLOC_SIZE_LIMIT   (33554432)   //4096*4096*2

OMX_S32 alloc_contigous_buffer(OMX_U32 buf_size, OMX_U32 align,venc_user_info *pvenc_buf)
{
    HI_MMZ_BUF_S stBuf;
    OMX_S32 ret;
    venc_user_info *puser_buf = pvenc_buf;
    if (!puser_buf)
    {
        DEBUG_PRINT_ERROR("%s() invalid param\n", __func__);
        return -1;
    }

    if (buf_size > OMXVENC_ALLOC_SIZE_LIMIT)
    {
        DEBUG_PRINT_ERROR("%s() buf_size = %lu to large than MaxLimit(%d)\n", __func__, buf_size, OMXVENC_ALLOC_SIZE_LIMIT);
        return -1;
    }

    buf_size = (buf_size + align - 1) & ~(align - 1);
    if (PORT_DIR_INPUT == puser_buf->user_buf.dir)
    {
        snprintf(stBuf.bufname, 16, "%s", "OMXVENC_ETB");
    }
    else
    {
        snprintf(stBuf.bufname, 16, "%s", "OMXVENC_FTB");
    }

    stBuf.bufsize = buf_size;

    ret = HI_MMZ_Malloc(&stBuf);
    if(0 != ret)
    {
        DEBUG_PRINT("~~~~~~ERROR: HI_MMZ_Malloc Failed!! Ret:%ld\n",ret);
        return -1;
    }
    puser_buf->ion_handle     = NULL;
    puser_buf->bufferaddr      = stBuf.user_viraddr;
    puser_buf->user_buf.bufferaddr_Phy = stBuf.phyaddr;
    puser_buf->user_buf.buffer_size    = stBuf.bufsize;

    puser_buf->user_buf.data_len        = 0;
    puser_buf->user_buf.offset          = 0;
    puser_buf->user_buf.pmem_fd          = 0;
    puser_buf->user_buf.mmaped_size      = stBuf.bufsize;

    return 0;
}

void free_contigous_buffer(venc_user_info*puser_buf)

{
    HI_MMZ_BUF_S stBuf;
    OMX_S32 ret;

    if (!puser_buf)
    {
        DEBUG_PRINT_ERROR("%s() invalid param\n", __func__);
        return;
    }

    memset(&stBuf, 0, sizeof(HI_MMZ_BUF_S));
    stBuf.user_viraddr = puser_buf->bufferaddr;
    stBuf.phyaddr      = puser_buf->user_buf.bufferaddr_Phy;
    stBuf.bufsize      = puser_buf->user_buf.buffer_size;

    ret = HI_MMZ_Free(&stBuf);
    if( 0 != ret)
    {
        DEBUG_PRINT_ERROR("~~~~~~ERROR: HI_MMZ_Free (%s) Failed!! Ret:%ld\n",stBuf.bufname,ret);
    }

    return ;
}


