#include "omx_venc_buf_mng.h"
#include <string.h>

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

HI_VOID OMX_VENC_BsOpenBitStream(tBitStream *pBS, HI_U32 *pBuffer)
{
    HI_U32 test = 1;

    if ((pBS == NULL) || (pBuffer == NULL))
    {
        return;
    }

    memset(pBS, 0, sizeof(tBitStream));
    pBS->pBuff = pBuffer;

    pBS->tU32a = 0;
    pBS->tU32b = 0;
    pBS->tBits = 0;

    pBS->totalBits  = 0;
    pBS->bBigEndian = ! * (HI_U8 *)&test;
}

HI_VOID OMX_VENC_BsPutBits31(tBitStream *pBS, HI_U32 code, HI_U32 bits)
{
    if (pBS == NULL)
    {
        return;
    }

    pBS->totalBits += bits;

    if (pBS->pBuff != NULL)
    {
        code <<= (32 - bits);
        pBS->tU32b |= (code >> pBS->tBits);
        pBS->tBits += bits;

        if (pBS->tBits >= 32)
        {
            pBS->tBits -= 32;
            bits -= pBS->tBits;
            *pBS->pBuff++ = (pBS->bBigEndian ? pBS->tU32b : REV32(pBS->tU32b));
            pBS->tU32b = (code << bits);
        }
    }
}

HI_VOID OMX_VENC_BsPutBits32(tBitStream *pBS, HI_U32 code, HI_U32 bits)
{
    if (pBS == NULL)
    {
        return;
    }

    pBS->totalBits += bits;

    if (pBS->pBuff != NULL)
    {
        code <<= (32 - bits);
        pBS->tU32b |= (code >> pBS->tBits);
        pBS->tBits += bits;

        if (pBS->tBits >= 32)
        {
            pBS->tBits -= 32;
            bits -= pBS->tBits;
            *pBS->pBuff++ = (pBS->bBigEndian ? pBS->tU32b : REV32(pBS->tU32b));
            pBS->tU32b = ((code << (bits - 1)) << 1);
        }
    }
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

