/***********************************************************************
*
* Copyright (c) 2006 Hisilicon - All Rights Reserved
*
* File: $bitstream.c$
* Date: $2006/11/30$
* Revision: $v1.0$
* Purpose: a general bit stream manipulation tool,
*          can be adopted by multi video standards.
*
* Change History:
*
* Date             Change
* ====             ======
* 2006/11/30       Original
*
* Dependencies:
*
************************************************************************/

#include "bitstream.h"


static UINT8 CalcZeroNum[256] =
{
    8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

#if 1
UINT32 ZerosMS_32(UINT32 data)
{
    UINT32 i, ZeroNum = 0, tmpZeroNum = 0;
    UINT32 tmpdata = 0;

    for (i=4; i>0; i--)
    {
        tmpdata = (data & 0xff000000) >> 24;
        tmpZeroNum = (UINT32)CalcZeroNum[tmpdata];
        ZeroNum += tmpZeroNum;
        if (8 != tmpZeroNum)
        {
            break;
        }
        data = data<<8;
    }

    return ZeroNum;
}
#endif

/******************************************************/
VOID BsInit( BS *pBS, UINT8 *pInput, SINT32 length )
{
    UINT32 Data;

    pBS->pHead    = ( UINT8 *)(((UINT32)pInput)&0xfffffffc);
    pBS->pTail    = pBS->pHead + 8;
    pBS->BsLen    = length;

    Data = *(UINT32*)pBS->pHead;
    pBS->Bufa     = ENDIAN32( Data );
    Data = *(UINT32*)(pBS->pHead+4);
    pBS->Bufb     = ENDIAN32( Data );

    pBS->BufPos   = (((UINT32)pInput)&0x3)<<3;
    pBS->TotalPos = 0;

    return;
}

/******************************************************/
SINT32  BsPos( BS *pBS )
{
    return( pBS->TotalPos );
}

/******************************************************/
SINT32  BsGet( BS *pBS, SINT32 nBits )
{
    UINT32 Data;

    Data = BsShow( pBS, nBits );
    BsSkip( pBS, nBits );

    return(Data);
}

/******************************************************/
SINT32  BsShow( BS *pBS, SINT32 nBits )
{
    SINT32 ABBufPos = nBits + pBS->BufPos;
    UINT32 Data, Data1;

    if( ABBufPos > 32 )
    {
        Data  = pBS->Bufa << pBS->BufPos;   //( ABBufPos - 32 );
        Data1 = pBS->Bufb >> (32-pBS->BufPos);
        Data |= Data1;
        Data >>= (32-nBits);
    }
    else
    {
        Data  = (pBS->Bufa << pBS->BufPos) >> (32 - nBits);
    }

    return(Data);
}

/******************************************************/
SINT32  BsSkip( BS *pBS, SINT32 nBits )
{
    SINT32 ABBufPos = nBits + pBS->BufPos;
    UINT32 Data1;

    pBS->TotalPos += nBits;

    if( ABBufPos >= 32 )
    {
        pBS->BufPos   =  ABBufPos - 32;

        pBS->Bufa = pBS->Bufb;
        Data1 = *(UINT32*)pBS->pTail;
        pBS->Bufb = ENDIAN32( Data1 );

        pBS->pTail += 4;
    }
    else
    {
        pBS->BufPos   += nBits;
    }

    return( nBits );
}

/******************************************************/
SINT32  BsBack( BS *pBS, SINT32 nBits )
{
    SINT32 PredBufPos;
    UINT32 Data1;

    if( nBits > pBS->TotalPos )
        nBits = pBS->TotalPos;

    PredBufPos     = (SINT32)pBS->BufPos - nBits;
    pBS->TotalPos -= nBits;

    if( PredBufPos >= 0 )
    {
        pBS->BufPos = PredBufPos;
    }
    else
    {
        pBS->pTail  -= 4;
        pBS->Bufb   = pBS->Bufa;
        Data1 = *(UINT32*)(pBS->pTail - 8);
        pBS->Bufa = ENDIAN32( Data1 );

        pBS->BufPos = PredBufPos + 32;

    }
    return( nBits );
}


SINT32  BsBitsToNextByte( BS *pBS )
{
    SINT32  SkipLen, AlignPos;
    AlignPos = (pBS->TotalPos + 7) & 0xfffffff8;
    SkipLen  = AlignPos - pBS->TotalPos;
    return SkipLen;
}


/******************************************************/
SINT32  BsToNextByte( BS *pBS )
{
    SINT32  SkipLen, AlignPos;
    AlignPos = (pBS->TotalPos + 7) & 0xfffffff8;
    SkipLen  = AlignPos - pBS->TotalPos;

    BsSkip( pBS, SkipLen );
    return SkipLen;
}


/******************************************************/
SINT32  BsResidBits( BS *pBS )
{
    return( 8*pBS->BsLen - pBS->TotalPos );
}

/******************************************************/
SINT32  BsIsByteAligned( BS *pBS )
{
    if( pBS->TotalPos & 7 )
        return(0);
    else
        return(1);
}

/******************************************************/
SINT32  BsNextBitsByteAligned( BS *pBS, SINT32 nBits )
{    // 'nBits' should <= 24, otherwise may be wrong.
    UINT32 BitsToByte, Data;

    BitsToByte = 8 - (pBS->TotalPos & 7);
    if( BitsToByte == 0 )
        if( BsShow( pBS, 8 ) == 0x7f )
            BitsToByte = 8;

    BsSkip( pBS, BitsToByte );
    Data = BsShow( pBS, nBits );
    BsBack( pBS, BitsToByte );

    return( Data );
}

/******************************************************/
//����Ծֻ��֤��������׼ȷ��,���ܱ�֤bufa��bufb�ж�����Ч����(�������ڰ��߽�ʱ)
SINT32 BsLongSkip(BS *pBS, SINT32 nBits)
{
    UINT32 bits,words;
    if(nBits==0)
    {
        return 0;
    }
    if(nBits<=64)
    {
        if(nBits>32)
        {
            BsSkip(pBS, 32);
            nBits-=32;
        }
        BsSkip(pBS, nBits);
    }
    else
    {
         bits = (32-pBS->BufPos);
         pBS->TotalPos+=bits;
         pBS->BufPos = 0;
         nBits -= bits;
         words = nBits/32;
         bits = nBits&0x1f;
         pBS->pTail += 4*(words-1);
         pBS->Bufa = ENDIAN32(*(UINT32 *)pBS->pTail);
         pBS->pTail+=4;
         pBS->Bufb = ENDIAN32(*(UINT32 *)pBS->pTail);
         pBS->pTail+=4;
         pBS->TotalPos += (words*32);

         if (bits>0)
         {
             BsSkip(pBS,bits);
         }
    }
    return nBits;
}

//������BsSkip,ֻ�ǲ���totalpos�м���,���ڷ�32λ���������������λ�õ���
//��������bit����������.��Ϊ����bsinit�ǰ�32λ������ʵ�ֵ�,���ܶ����������ĵ�bit
SINT32  BsSkipWithoutCount( BS *pBS, SINT32 nBits )
{
    SINT32 ABBufPos = nBits + pBS->BufPos;
    UINT32 Data1;

    if( ABBufPos >= 32 )
    {
        pBS->BufPos   =  ABBufPos - 32;

        pBS->Bufa = pBS->Bufb;
        Data1 = *(UINT32*)pBS->pTail;
        pBS->Bufb = ENDIAN32( Data1 );

        pBS->pTail += 4;
    }
    else
    {
        pBS->BufPos   += nBits;
    }

    return( nBits );
}

UINT8* BsGetNextBytePtr( BS *pBS )
{
    UINT8* ptr;
    SINT32 BitsInBufa;

    BitsInBufa = (32-pBS->BufPos);
    ptr = ((UINT8*)(pBS->pTail)) - (4+BitsInBufa/8);

    return( ptr );
}

