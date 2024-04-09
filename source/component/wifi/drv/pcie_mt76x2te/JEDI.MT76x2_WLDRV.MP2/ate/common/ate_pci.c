/*
  * Copyright (c) 2016 MediaTek Inc.  All rights reserved.
  *
  * This software is available to you under a choice of one of two
  * licenses.  You may choose to be licensed under the terms of the GNU
  * General Public License (GPL) Version 2, available from the file
  * COPYING in the main directory of this source tree, or the
  * BSD license below:
  *
  *     Redistribution and use in source and binary forms, with or
  *     without modification, are permitted provided that the following
  *     conditions are met:
  *
  *      - Redistributions of source code must retain the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer.
  *
  *      - Redistributions in binary form must reproduce the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer in the documentation and/or other materials
  *        provided with the distribution.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */


#ifdef RTMP_MAC_PCI

#include "rt_config.h"

INT TxDmaBusy(IN PRTMP_ADAPTER pAd)
{
	INT result;
	WPDMA_GLO_CFG_STRUC GloCfg;

	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word); /* disable DMA */
	result = (GloCfg.field.TxDMABusy) ? TRUE : FALSE;

	return result;
}

INT RxDmaBusy(IN PRTMP_ADAPTER pAd)
{
	INT result;
	WPDMA_GLO_CFG_STRUC GloCfg;

	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word); /* disable DMA */
	result = (GloCfg.field.RxDMABusy) ? TRUE : FALSE;

	return result;
}

VOID RtmpDmaEnable(IN PRTMP_ADAPTER pAd, IN INT Enable)
{
	BOOLEAN value;
	ULONG WaitCnt;
	WPDMA_GLO_CFG_STRUC GloCfg;

	value = Enable > 0 ? 1 : 0;

	/* check if DMA is in busy mode or not. */
	WaitCnt = 0;

	while (TxDmaBusy(pAd) || RxDmaBusy(pAd)) {
		RtmpusecDelay(10);

		if (WaitCnt++ > 100)
			break;
	}

	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word); /* disable DMA */
	GloCfg.field.EnableTxDMA = value;
	GloCfg.field.EnableRxDMA = value;
	/* abort all TX rings */
	RTMP_IO_WRITE32(pAd, WPDMA_GLO_CFG, GloCfg.word);
	RtmpOsMsDelay(5);
}

VOID RtmpSoundingDmaEnable(IN PRTMP_ADAPTER pAd, IN INT Enable)
{
	BOOLEAN value;
	ULONG WaitCnt;
	WPDMA_GLO_CFG_STRUC GloCfg;

	value = Enable > 0 ? 1 : 0;

	/* check if DMA is in busy mode or not. */
	WaitCnt = 0;

	while (TxDmaBusy(pAd) || RxDmaBusy(pAd)) {
		RtmpusecDelay(10);

		if (WaitCnt++ > 100)
			break;
	}

	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word); /* disable DMA */
	GloCfg.field.EnableTxDMA = value;
	GloCfg.field.EnableRxDMA = value;
	/* abort all TX rings */
	RTMP_IO_WRITE32(pAd, WPDMA_GLO_CFG, GloCfg.word);
	/* RtmpOsMsDelay(5); */
}

/*
 *========================================================================
 *	Routine Description:
 *		Write TxWI for ATE mode.
 *
 *	Return Value:
 *		None
 *========================================================================
 */
VOID ATEWriteTxWI(IN PRTMP_ADAPTER pAd,
		IN TXWI_STRUC * pOutTxWI,
		IN BOOLEAN FRAG,
		IN BOOLEAN CFACK,
		IN BOOLEAN InsTimestamp,
		IN BOOLEAN AMPDU,
		IN BOOLEAN Ack,
		IN BOOLEAN NSeq,	/* HW new a sequence. */
		IN UCHAR BASize,
		IN UCHAR WCID,
		IN ULONG Length,
		IN UCHAR PID,
		IN UCHAR TID,
		IN UCHAR TxRate,
		IN UCHAR Txopmode,
		IN BOOLEAN CfAck,
		IN HTTRANSMIT_SETTING * pTransmit)
{
	TXWI_STRUC TxWI, *pTxWI;
	UINT8 TXWISize = pAd->chipCap.TXWISize;
	UCHAR bw;
#ifdef SINGLE_SKU_V2
	PATE_INFO pATEInfo = &(pAd->ate);
#endif /* SINGLE_SKU_V2 */

	/* If CCK or OFDM, BW must be 20 */
	bw = (pTransmit->field.MODE <=
	      MODE_OFDM) ? (BW_20) : (pTransmit->field.BW);

	/* OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_SHORT_PREAMBLE_INUSED); */
	NdisZeroMemory(&TxWI, TXWISize);
	pTxWI = &TxWI;

#ifdef RLT_MAC
	if (pAd->chipCap.hif_type == HIF_RLT) {
		struct _TXWI_NMAC *txwi_n = (struct _TXWI_NMAC *)pTxWI;

		txwi_n->FRAG = FRAG;
		txwi_n->CFACK = CFACK;
		txwi_n->TS = InsTimestamp;
		txwi_n->AMPDU = AMPDU;
		txwi_n->ACK = Ack;
		txwi_n->txop = Txopmode;
		txwi_n->NSEQ = NSeq;
		txwi_n->BAWinSize = BASize;
		txwi_n->wcid = WCID;
		txwi_n->MPDUtotalByteCnt = Length;
		txwi_n->BW = bw;
		txwi_n->ShortGI = pTransmit->field.ShortGI;
		txwi_n->STBC = pTransmit->field.STBC;
		txwi_n->MCS = pTransmit->field.MCS;
		txwi_n->PHYMODE = pTransmit->field.MODE;
		txwi_n->CFACK = CfAck;
		txwi_n->MIMOps = 0;
		txwi_n->MpduDensity = 0;
		txwi_n->TxPktId = txwi_n->MCS;

		/* Calculate TxPwrAdj */
		txwi_n->TxPwrAdj = 0;
#ifdef SINGLE_SKU_V2
		if (pATEInfo->bDoSingleSKU)
			RTMP_CHIP_ASIC_SKU_TX_POWER_ADJUST(pAd, txwi_n);
#endif /* SINGLE_SKU_V2 */

		/* increase low rate Tx Power by TXWI */
		RTMP_CHIP_ASIC_TX_POWER_BOOST(pAd, txwi_n);

	}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
	if (pAd->chipCap.hif_type == HIF_RTMP) {
		struct _TXWI_OMAC *txwi_o = (struct _TXWI_OMAC *)pTxWI;

		txwi_o->FRAG = FRAG;
		txwi_o->CFACK = CFACK;
		txwi_o->TS = InsTimestamp;
		txwi_o->AMPDU = AMPDU;
		txwi_o->ACK = Ack;
		txwi_o->txop = Txopmode;
		txwi_o->NSEQ = NSeq;
		txwi_o->BAWinSize = BASize;
		txwi_o->wcid = WCID;
		txwi_o->MPDUtotalByteCnt = Length;
		txwi_o->BW = bw;
		txwi_o->ShortGI = pTransmit->field.ShortGI;
		txwi_o->STBC = pTransmit->field.STBC;
		txwi_o->MCS = pTransmit->field.MCS;
		txwi_o->PHYMODE = pTransmit->field.MODE;
		txwi_o->CFACK = CfAck;
		txwi_o->MIMOps = 0;
		txwi_o->MpduDensity = 0;
		txwi_o->PacketId = txwi_o->MCS;
	}
#endif /* RTMP_MAC */

	NdisMoveMemory(pOutTxWI, &TxWI, TXWISize);
}

/*
 *==========================================================================
 *	Description:
 *		Setup Frame format.
 *	NOTE:
 *		This routine should only be used in ATE mode.
 *==========================================================================
 */
INT ATESetUpFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT pos = 0;
	TXINFO_STRUC *pTxInfo;
	TXD_STRUC *pTxD;
#ifdef RT_BIG_ENDIAN
	TXD_STRUC *pDestTxD;
	UCHAR tx_hw_info[TXD_SIZE];
#endif /* RT_BIG_ENDIAN */
	PNDIS_PACKET pPacket = NULL;
	PUCHAR pDest = NULL;
	PVOID AllocVa = NULL;
	NDIS_PHYSICAL_ADDRESS AllocPa;
	HTTRANSMIT_SETTING TxHTPhyMode;

	RTMP_TX_RING *pTxRing = &pAd->TxRing[QID_AC_BE];
	TXWI_STRUC *pTxWI = (TXWI_STRUC *) pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
	PUCHAR pDMAHeaderBufVA = (PUCHAR) pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
	UINT8 TXWISize = pAd->chipCap.TXWISize;

#ifdef RALINK_QA
	PHEADER_802_11 pHeader80211;
#endif /* RALINK_QA */

	UCHAR bw, sgi, stbc, mcs, phy_mode, frag, cfack, ts, ampdu, ack, nseq,
	    bawinsize, pkt_id, txop;
	USHORT byte_cnt;

	bw = sgi = stbc = mcs = phy_mode = frag = cfack = ts = 0;
	ampdu = ack = nseq = bawinsize = pkt_id = txop = 0;
	byte_cnt = 0;
#ifdef RLT_MAC
	if (pAd->chipCap.hif_type == HIF_RLT) {
		bw = pATEInfo->TxWI.TXWI_N.BW;
		sgi = pATEInfo->TxWI.TXWI_N.ShortGI;
		stbc = pATEInfo->TxWI.TXWI_N.STBC;
		mcs = pATEInfo->TxWI.TXWI_N.MCS;
		phy_mode = pATEInfo->TxWI.TXWI_N.PHYMODE;

		frag = pATEInfo->TxWI.TXWI_N.FRAG;
		cfack = pATEInfo->TxWI.TXWI_N.CFACK,
		    ts = pATEInfo->TxWI.TXWI_N.TS;
		ampdu = pATEInfo->TxWI.TXWI_N.AMPDU;
		ack = pATEInfo->TxWI.TXWI_N.ACK;
		nseq = pATEInfo->TxWI.TXWI_N.NSEQ;
		bawinsize = pATEInfo->TxWI.TXWI_N.BAWinSize;
		byte_cnt = pATEInfo->TxWI.TXWI_N.MPDUtotalByteCnt;
		pkt_id = pATEInfo->TxWI.TXWI_N.TxPktId;
		txop = pATEInfo->TxWI.TXWI_N.txop;
		cfack = pATEInfo->TxWI.TXWI_N.CFACK;
	}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
	if (pAd->chipCap.hif_type == HIF_RTMP) {
		bw = pATEInfo->TxWI.TXWI_O.BW;
		sgi = pATEInfo->TxWI.TXWI_O.ShortGI;
		stbc = pATEInfo->TxWI.TXWI_O.STBC;
		mcs = pATEInfo->TxWI.TXWI_O.MCS;
		phy_mode = pATEInfo->TxWI.TXWI_O.PHYMODE;

		frag = pATEInfo->TxWI.TXWI_O.FRAG;
		cfack = pATEInfo->TxWI.TXWI_O.CFACK,
		    ts = pATEInfo->TxWI.TXWI_O.TS;
		ampdu = pATEInfo->TxWI.TXWI_O.AMPDU;
		ack = pATEInfo->TxWI.TXWI_O.ACK;
		nseq = pATEInfo->TxWI.TXWI_O.NSEQ;
		bawinsize = pATEInfo->TxWI.TXWI_O.BAWinSize;
		byte_cnt = pATEInfo->TxWI.TXWI_O.MPDUtotalByteCnt;
		pkt_id = pATEInfo->TxWI.TXWI_O.PacketId;
		txop = pATEInfo->TxWI.TXWI_O.txop;
		cfack = pATEInfo->TxWI.TXWI_O.CFACK;
	}
#endif /* RTMP_MAC */

	/* fill TxWI */
	TxHTPhyMode.field.BW = bw;
	TxHTPhyMode.field.ShortGI = sgi;
	TxHTPhyMode.field.STBC = stbc;
	TxHTPhyMode.field.MCS = mcs;
	TxHTPhyMode.field.MODE = phy_mode;

	if (pATEInfo->bQATxStart == TRUE) {
		/* always use QID_AC_BE and FIFO_EDCA */
		ATEWriteTxWI(pAd, pTxWI, frag, cfack,
			     ts, ampdu, ack,
			     nseq, bawinsize, 0,
			     byte_cnt, pkt_id, 0, 0, txop, cfack, &TxHTPhyMode);

#ifdef TXBF_SUPPORT
#ifdef RTMP_MAC
		if (IS_RT2883(pAd) || IS_RT3883(pAd) || IS_RT3593(pAd)) {
			/* Must copy rsv bits to actual TxWI */
			/* pTxWI->TXWI_O.Reserved =
			 * pATEInfo->TxWI.TXWI_O.Reserved;
			 */
			pTxWI->TXWI_O.iTxBF = pATEInfo->TxWI.TXWI_O.iTxBF;
			pTxWI->TXWI_O.Sounding = pATEInfo->TxWI.TXWI_O.Sounding;
			pTxWI->TXWI_O.eTxBF = pATEInfo->TxWI.TXWI_O.eTxBF;
			pTxWI->TXWI_O.Autofallback =
			    pATEInfo->TxWI.TXWI_O.Autofallback;
			pTxWI->TXWI_O.NDPSndBW = pATEInfo->TxWI.TXWI_O.NDPSndBW;
			pTxWI->TXWI_O.NDPSndRate =
			    pATEInfo->TxWI.TXWI_O.NDPSndRate;
		}
#endif
#ifdef RLT_MAC
		if (IS_MT76x2(pAd)) {
			/* Must copy rsv bits to actual TxWI */
			pTxWI->TXWI_N.Rsv4 = pATEInfo->TxWI.TXWI_N.Rsv4;
			pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
			pTxWI->TXWI_N.Sounding = pATEInfo->TxWI.TXWI_N.Sounding;
			pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
			/* pTxWI->TXWI_N.Autofallback =
			 * pATEInfo->TxWI.TXWI_N.Autofallback;
			 */
			pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.NDPSndBW;
			pTxWI->TXWI_N.NDPSndRate =
			    pATEInfo->TxWI.TXWI_N.NDPSndRate;
			pTxWI->TXWI_N.TXBF_PT_SCA =
			    pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
		}
#endif
#endif /* TXBF_SUPPORT */
	} else {
		ATEWriteTxWI(pAd, pTxWI, FALSE, FALSE, FALSE, FALSE, FALSE,
			     FALSE, 4, 0, pATEInfo->TxLength, 0, 0, 0,
			     IFS_HTTXOP, FALSE, &TxHTPhyMode);

#ifdef TXBF_SUPPORT
		if (pATEInfo->bTxBF == 1) {
#ifdef RTMP_MAC
			if (IS_RT2883(pAd) || IS_RT3883(pAd) ||
				IS_RT3593(pAd)) {
				/* pTxWI->TXWI_O.Reserved = 0; */

				pTxWI->TXWI_O.Sounding =
				    (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				if (pATEInfo->txSoundingMode) {
					pTxWI->TXWI_O.iTxBF = FALSE;
					pTxWI->TXWI_O.eTxBF = FALSE;
				} else {
					pTxWI->TXWI_O.iTxBF =
					    pATEInfo->TxWI.TXWI_O.iTxBF;
					pTxWI->TXWI_O.eTxBF =
					    pATEInfo->TxWI.TXWI_O.eTxBF;
				}
				pTxWI->TXWI_O.Autofallback =
				    pATEInfo->TxWI.TXWI_O.Autofallback;
				pTxWI->TXWI_O.NDPSndBW =
				    pATEInfo->TxWI.TXWI_O.BW;
				if (pATEInfo->txSoundingMode == 3)
					pTxWI->TXWI_O.NDPSndRate = 2;
				else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_O.NDPSndRate = 1;
				else
					pTxWI->TXWI_O.NDPSndRate = 0;
			}
#endif

#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				pTxWI->TXWI_N.Rsv4 = 0;

				pTxWI->TXWI_N.Sounding =
				    (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				if (pATEInfo->txSoundingMode) {
					pTxWI->TXWI_N.iTxBF = FALSE;
					pTxWI->TXWI_N.eTxBF = FALSE;
				} else {
					pTxWI->TXWI_N.iTxBF =
					    pATEInfo->TxWI.TXWI_N.iTxBF;
					pTxWI->TXWI_N.eTxBF =
					    pATEInfo->TxWI.TXWI_N.eTxBF;
				}
				/* pTxWI->TXWI_N.Autofallback =
				 * pATEInfo->TxWI.TXWI_N.Autofallback;
				 */
				pTxWI->TXWI_N.NDPSndBW =
				    pATEInfo->TxWI.TXWI_N.BW;
				if (pATEInfo->txSoundingMode == 3)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else
					pTxWI->TXWI_N.NDPSndRate = 0;
				pTxWI->TXWI_N.TXBF_PT_SCA =
				    pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
		}
#endif /* TXBF_SUPPORT */
	}

	/* fill 802.11 header */
#ifdef RALINK_QA
	if (pATEInfo->bQATxStart == TRUE) {
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize, pATEInfo->Header,
			       pATEInfo->HLen);
	} else
#endif /* RALINK_QA */
	{
		pATEInfo->HLen = LENGTH_802_11;
#ifdef TXBF_SUPPORT
		TemplateFrame[0] = 0x08;	/* Data */
		TemplateFrame[1] = 0x00;
		if (pATEInfo->bTxBF && pATEInfo->txSoundingMode != 0) {
			/* QoS Data */
			/* pATEInfo->HLen = 32; */
			pATEInfo->HLen = 30;
			TemplateFrame[0] = 0x88;
			TemplateFrame[1] = 0x80;

			switch (pATEInfo->txSoundingMode) {
			case 1:
				/* Data Sounding */
				TemplateFrame[28] =
				    pAd->
				    CommonCfg.ETxBfNoncompress ? 0x80 : 0xc0;
				TemplateFrame[29] = 0x00;
				break;
			case 2:
			case 3:
				/* 2 or 3 Stream NDP */
				TemplateFrame[28] =
				    pAd->
				    CommonCfg.ETxBfNoncompress ? 0x80 : 0xc0;
				TemplateFrame[29] = 0x01; /* NDP Announce */
				break;
			default:
				TemplateFrame[28] = TemplateFrame[29] = 0x0;
			}
		}
#endif /* TXBF_SUPPORT */
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize, TemplateFrame,
			       pATEInfo->HLen);
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize + 4, pATEInfo->Addr1,
			       MAC_ADDR_LEN);
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize + 10, pATEInfo->Addr2,
			       MAC_ADDR_LEN);
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize + 16, pATEInfo->Addr3,
			       MAC_ADDR_LEN);
	}

#ifdef RT_BIG_ENDIAN
	RTMPFrameEndianChange(pAd, (((PUCHAR) pDMAHeaderBufVA) + TXWISize),
			      DIR_READ, FALSE);
#endif /* RT_BIG_ENDIAN */

	/* alloc buffer for payload */
#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		pPacket = RTMP_AllocateRxPacketBuffer(pAd, ((POS_COOKIE)
							    (pAd->OS_Cookie))->
						      pci_dev,
						      pATEInfo->DLen + 0x100,
						      FALSE, &AllocVa,
						      &AllocPa);
	} else
#endif /* RALINK_QA */
	{
		pPacket = RTMP_AllocateRxPacketBuffer(pAd, ((POS_COOKIE)
							    (pAd->OS_Cookie))->
						      pci_dev,
						      pATEInfo->TxLength, FALSE,
						      &AllocVa, &AllocPa);
	}

	if (pPacket == NULL) {
		pATEInfo->TxCount = 0;
		DBGPRINT_ERR(("%s : fail to alloc packet space.\n",
			      __func__));
		return -1;
	}

	pTxRing->Cell[TxIdx].pNextNdisPacket = pPacket;
	pDest = (PUCHAR) AllocVa;

#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		GET_OS_PKT_LEN(pPacket) = pATEInfo->DLen;
#ifndef LINUX
		GET_OS_PKT_TOTAL_LEN(pPacket) = pATEInfo->DLen;
#endif /* LIMUX */
	} else
#endif /* RALINK_QA */
	{
		GET_OS_PKT_LEN(pPacket) = pATEInfo->TxLength - pATEInfo->HLen;
#ifndef LINUX
		GET_OS_PKT_TOTAL_LEN(pPacket) =
		    pATEInfo->TxLength - pATEInfo->HLen;
#endif /* LINUX */
	}

	/* prepare frame payload */
#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		/* copy pattern to payload */
		if ((pATEInfo->PLen != 0)) {
			for (pos = 0; pos < pATEInfo->DLen;
			     pos += pATEInfo->PLen) {
				memcpy(GET_OS_PKT_DATAPTR(pPacket) + pos,
				       pATEInfo->Pattern, pATEInfo->PLen);
			}
		}
	} else
#endif /* RALINK_QA */
	{
		for (pos = 0; pos < GET_OS_PKT_LEN(pPacket); pos++) {
			if (pATEInfo->bFixedPayload) {

				pDest[pos] = pATEInfo->Payload;
				/* pDest[pos] = 0xA5; */
			} else {
				pDest[pos] = RandomByte(pAd);
			}
		}
	}

	/* build Tx descriptor */
#ifndef RT_BIG_ENDIAN
	pTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
	pTxInfo =
	    (TXINFO_STRUC *) (pTxRing->Cell[TxIdx].AllocVa + sizeof(TXD_STRUC));
#else
	pDestTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
	NdisMoveMemory(&tx_hw_info[0], (UCHAR *) pDestTxD, TXD_SIZE);
	pTxD = (TXD_STRUC *) &tx_hw_info[0];
	pTxInfo = (TXINFO_STRUC *) (&tx_hw_info[0] + sizeof(TXD_STRUC));
#endif /* !RT_BIG_ENDIAN */

#ifdef RALINK_QA
	if (pATEInfo->bQATxStart == TRUE) {
		/* prepare TxD */
		NdisZeroMemory(pTxD, TXD_SIZE);
		/* build Tx descriptor */
		pTxD->SDPtr0 =
		    RTMP_GetPhysicalAddressLow(pTxRing->Cell[TxIdx].
					       DmaBuf.AllocPa);
		pTxD->SDLen0 = TXWISize + pATEInfo->HLen;
#ifndef RT_SECURE_DMA
		pTxD->SDPtr1 = AllocPa;
#else
		NdisMoveMemory(pAd->TxSecureDMA[QID_AC_BE].AllocVa +
			       (TxIdx * 4096), AllocVa,
			       GET_OS_PKT_LEN(pPacket));
		pTxD->SDPtr1 =
		    pAd->TxSecureDMA[QID_AC_BE].AllocPa + (TxIdx * 4096);
#endif
		pTxD->SDLen1 = GET_OS_PKT_LEN(pPacket);
		pTxD->LastSec0 = (pTxD->SDLen1 == 0) ? 1 : 0;
		pTxD->LastSec1 = 1;
		ral_write_txd(pAd, pTxD, pTxInfo, FALSE, FIFO_EDCA);

		pDest = (PUCHAR) pTxWI;
		pDest += TXWISize;
		pHeader80211 = (PHEADER_802_11) pDest;

		/* modify sequence number... */
		if (pATEInfo->TxDoneCount == 0)
			pATEInfo->seq = pHeader80211->Sequence;
		else
			pHeader80211->Sequence = ++pATEInfo->seq;
	} else
#endif /* RALINK_QA */
	{
		TX_BLK txblk;

		txblk.SrcBufLen = GET_OS_PKT_LEN(pPacket);
		txblk.pSrcBufData = AllocVa;
		NdisZeroMemory(pTxD, TXD_SIZE);
		/* build Tx descriptor */
		pTxD->SDPtr0 =
		    RTMP_GetPhysicalAddressLow(pTxRing->Cell[TxIdx].
					       DmaBuf.AllocPa);
		pTxD->SDLen0 = TXWISize + pATEInfo->HLen /* LENGTH_802_11 */;
#ifndef RT_SECURE_DMA
		pTxD->SDPtr1 =
		    PCI_MAP_SINGLE(pAd, &txblk, 0, 1, RTMP_PCI_DMA_TODEVICE);
#else
		NdisMoveMemory(pAd->TxSecureDMA[QID_AC_BE].AllocVa +
			       (TxIdx * 4096), AllocVa,
			       GET_OS_PKT_LEN(pPacket));
		pTxD->SDPtr1 =
		    pAd->TxSecureDMA[QID_AC_BE].AllocPa + (TxIdx * 4096);
#endif
		pTxD->SDLen1 = GET_OS_PKT_LEN(pPacket);
		pTxD->LastSec0 = (pTxD->SDLen1 == 0) ? 1 : 0;
		pTxD->LastSec1 = 1;
		ral_write_txd(pAd, pTxD, pTxInfo, FALSE, FIFO_EDCA);
	}

#ifdef RT_BIG_ENDIAN
	RTMPWIEndianChange(pAd, (PUCHAR) pTxWI, TYPE_TXWI);
	RTMPFrameEndianChange(pAd, (((PUCHAR) pDMAHeaderBufVA) + TXWISize),
			      DIR_WRITE, FALSE);
	RTMPDescriptorEndianChange((PUCHAR) pTxD, TYPE_TXD);
	WriteBackToDescriptor((PUCHAR) pDestTxD, (PUCHAR) pTxD, FALSE,
			      TYPE_TXD);
#endif /* RT_BIG_ENDIAN */
/* #endif */
	return 0;
}

INT ATESetUpNDPAFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT pos = 0;
	TXINFO_STRUC *pTxInfo;
	TXD_STRUC *pTxD;
#ifdef RT_BIG_ENDIAN
	TXD_STRUC *pDestTxD;
	UCHAR tx_hw_info[TXD_SIZE];
#endif /* RT_BIG_ENDIAN */
	PNDIS_PACKET pPacket = NULL;
	PUCHAR pDest = NULL;
	PVOID AllocVa = NULL;
	NDIS_PHYSICAL_ADDRESS AllocPa;
	HTTRANSMIT_SETTING TxHTPhyMode;
	UCHAR *buf;
	VHT_NDPA_FRAME *vht_ndpa;
	SNDING_STA_INFO *sta_info;

	RTMP_TX_RING *pTxRing = &pAd->TxRing[QID_AC_BE];
	TXWI_STRUC *pTxWI = (TXWI_STRUC *) pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
	PUCHAR pDMAHeaderBufVA = (PUCHAR) pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
	UINT8 TXWISize = pAd->chipCap.TXWISize;

#ifdef RALINK_QA
	PHEADER_802_11 pHeader80211;
#endif /* RALINK_QA */

	UCHAR bw, sgi, stbc, mcs, phy_mode, frag, cfack, ts, ampdu, ack, nseq,
	    bawinsize, pkt_id, txop;
	USHORT byte_cnt;

	bw = sgi = stbc = mcs = phy_mode = frag = cfack = ts = 0;
	ampdu = ack = nseq = bawinsize = pkt_id = txop = 0;
	byte_cnt = 0;

#ifdef RLT_MAC
	if (pAd->chipCap.hif_type == HIF_RLT) {
		bw = pATEInfo->TxWI.TXWI_N.BW;
		sgi = pATEInfo->TxWI.TXWI_N.ShortGI;
		stbc = pATEInfo->TxWI.TXWI_N.STBC;
		mcs = pATEInfo->TxWI.TXWI_N.MCS;
		phy_mode = pATEInfo->TxWI.TXWI_N.PHYMODE;

		frag = pATEInfo->TxWI.TXWI_N.FRAG;
		cfack = pATEInfo->TxWI.TXWI_N.CFACK,
		    ts = pATEInfo->TxWI.TXWI_N.TS;
		ampdu = pATEInfo->TxWI.TXWI_N.AMPDU;
		ack = pATEInfo->TxWI.TXWI_N.ACK;
		nseq = pATEInfo->TxWI.TXWI_N.NSEQ;
		bawinsize = pATEInfo->TxWI.TXWI_N.BAWinSize;
		byte_cnt = pATEInfo->TxWI.TXWI_N.MPDUtotalByteCnt;
		pkt_id = pATEInfo->TxWI.TXWI_N.TxPktId;
		txop = pATEInfo->TxWI.TXWI_N.txop;
		cfack = pATEInfo->TxWI.TXWI_N.CFACK;
	}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
	if (pAd->chipCap.hif_type == HIF_RTMP) {
		bw = pATEInfo->TxWI.TXWI_O.BW;
		sgi = pATEInfo->TxWI.TXWI_O.ShortGI;
		stbc = pATEInfo->TxWI.TXWI_O.STBC;
		mcs = pATEInfo->TxWI.TXWI_O.MCS;
		phy_mode = pATEInfo->TxWI.TXWI_O.PHYMODE;

		frag = pATEInfo->TxWI.TXWI_O.FRAG;
		cfack = pATEInfo->TxWI.TXWI_O.CFACK,
		    ts = pATEInfo->TxWI.TXWI_O.TS;
		ampdu = pATEInfo->TxWI.TXWI_O.AMPDU;
		ack = pATEInfo->TxWI.TXWI_O.ACK;
		nseq = pATEInfo->TxWI.TXWI_O.NSEQ;
		bawinsize = pATEInfo->TxWI.TXWI_O.BAWinSize;
		byte_cnt = pATEInfo->TxWI.TXWI_O.MPDUtotalByteCnt;
		pkt_id = pATEInfo->TxWI.TXWI_O.PacketId;
		txop = pATEInfo->TxWI.TXWI_O.txop;
		cfack = pATEInfo->TxWI.TXWI_O.CFACK;
	}
#endif /* RTMP_MAC */

	/* fill TxWI */
	TxHTPhyMode.field.BW = bw;
	TxHTPhyMode.field.ShortGI = sgi;
	TxHTPhyMode.field.STBC = stbc;
	TxHTPhyMode.field.MCS = mcs;
	TxHTPhyMode.field.MODE = phy_mode;

	if (pATEInfo->bQATxStart == TRUE) {
		/* always use QID_AC_BE and FIFO_EDCA */
		ATEWriteTxWI(pAd, pTxWI, frag, cfack,
			     ts, ampdu, ack,
			     nseq, bawinsize, 0,
			     byte_cnt, pkt_id, 0, 0, txop, cfack, &TxHTPhyMode);

#ifdef TXBF_SUPPORT
#ifdef RTMP_MAC
		if (IS_RT2883(pAd) || IS_RT3883(pAd) || IS_RT3593(pAd)) {
			/* Must copy rsv bits to actual TxWI */
			/* pTxWI->TXWI_O.rsv = pATEInfo->TxWI.TXWI_O.rsv; */
			pTxWI->TXWI_O.iTxBF = pATEInfo->TxWI.TXWI_O.iTxBF;
			pTxWI->TXWI_O.Sounding = pATEInfo->TxWI.TXWI_O.Sounding;
			pTxWI->TXWI_O.eTxBF = pATEInfo->TxWI.TXWI_O.eTxBF;
			pTxWI->TXWI_O.Autofallback =
			    pATEInfo->TxWI.TXWI_O.Autofallback;
			pTxWI->TXWI_O.NDPSndBW = pATEInfo->TxWI.TXWI_O.NDPSndBW;
			pTxWI->TXWI_O.NDPSndRate =
			    pATEInfo->TxWI.TXWI_O.NDPSndRate;
		}
#endif
#ifdef RLT_MAC
		if (IS_MT76x2(pAd)) {
			/* Must copy rsv bits to actual TxWI */
			pTxWI->TXWI_N.Rsv4 = pATEInfo->TxWI.TXWI_N.Rsv4;
			pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
			pTxWI->TXWI_N.Sounding = pATEInfo->TxWI.TXWI_N.Sounding;
			pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
			/* pTxWI->TXWI_N.Autofallback =
			 * pATEInfo->TxWI.TXWI_N.Autofallback;
			 */
			pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.NDPSndBW;
			pTxWI->TXWI_N.NDPSndRate =
			    pATEInfo->TxWI.TXWI_N.NDPSndRate;
			pTxWI->TXWI_N.TXBF_PT_SCA =
			    pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
		}
#endif
#endif /* TXBF_SUPPORT */
	} else {
		ATEWriteTxWI(pAd, pTxWI, FALSE, FALSE, FALSE, FALSE, FALSE,
			     FALSE, 4, 0, pATEInfo->TxLength, 0, 0, 0,
			     IFS_HTTXOP, FALSE, &TxHTPhyMode);

#ifdef TXBF_SUPPORT
		if (pATEInfo->bTxBF == 1) {
#ifdef RTMP_MAC
			if (IS_RT2883(pAd) || IS_RT3883(pAd) ||
				IS_RT3593(pAd)) {
				/* pTxWI->TXWI_O.rsv = 0; */
				pTxWI->TXWI_O.iTxBF =
				    pATEInfo->TxWI.TXWI_O.iTxBF;
				pTxWI->TXWI_O.Sounding =
				    (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				pTxWI->TXWI_O.eTxBF =
				    pATEInfo->TxWI.TXWI_O.eTxBF;
				pTxWI->TXWI_O.Autofallback =
				    pATEInfo->TxWI.TXWI_O.Autofallback;
				pTxWI->TXWI_O.NDPSndBW =
				    pATEInfo->TxWI.TXWI_O.BW;
				if (pATEInfo->txSoundingMode == 3)
					pTxWI->TXWI_O.NDPSndRate = 1;
				else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_O.NDPSndRate = 1;
				else
					pTxWI->TXWI_O.NDPSndRate = 0;
			}
#endif

#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				pTxWI->TXWI_N.Rsv4 = 0;
				pTxWI->TXWI_N.iTxBF =
				    pATEInfo->TxWI.TXWI_N.iTxBF;
				pTxWI->TXWI_N.Sounding =
				    (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				pTxWI->TXWI_N.eTxBF =
				    pATEInfo->TxWI.TXWI_N.eTxBF;
				/* pTxWI->TXWI_N.Autofallback =
				 * pATEInfo->TxWI.TXWI_N.Autofallback;
				 */
				pTxWI->TXWI_N.NDPSndBW =
				    pATEInfo->TxWI.TXWI_N.BW;
				if (pATEInfo->txSoundingMode == 3)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else
					pTxWI->TXWI_N.NDPSndRate = 0;

				pTxWI->TXWI_N.TXBF_PT_SCA =
				    pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
		}
#endif /* TXBF_SUPPORT */
	}

	/* fill 802.11 header */
#ifdef RALINK_QA
	if (pATEInfo->bQATxStart == TRUE) {
		NdisMoveMemory(pDMAHeaderBufVA + TXWISize, pATEInfo->Header,
			       pATEInfo->HLen);
	} else
#endif /* RALINK_QA */
	{
		buf = (pDMAHeaderBufVA + TXWISize);
		vht_ndpa = (VHT_NDPA_FRAME *) buf;
		pATEInfo->HLen = sizeof(VHT_NDPA_FRAME);
		vht_ndpa->fc.Type = FC_TYPE_CNTL;
		vht_ndpa->fc.SubType = SUBTYPE_VHT_NDPA;
		COPY_MAC_ADDR(vht_ndpa->ra, pATEInfo->Addr1);
		COPY_MAC_ADDR(vht_ndpa->ta, pATEInfo->Addr3);
		hex_dump("NDPA Frame", buf, pATEInfo->HLen);
		/* Currnetly we only support 1 STA for a VHT DNPA */
		sta_info = vht_ndpa->sta_info;
		sta_info->aid12 = 1;
		sta_info->fb_type = SNDING_FB_SU;
		sta_info->nc_idx = 0;
		vht_ndpa->token.token_num = 0;
		vht_ndpa->duration = 100;
	}

#ifdef RT_BIG_ENDIAN
	RTMPFrameEndianChange(pAd, (((PUCHAR) pDMAHeaderBufVA) + TXWISize),
			      DIR_READ, FALSE);
#endif /* RT_BIG_ENDIAN */

	/* alloc buffer for payload */
#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		pPacket = RTMP_AllocateRxPacketBuffer(pAd, ((POS_COOKIE)
							    (pAd->OS_Cookie))->
						      pci_dev,
						      pATEInfo->DLen + 0x100,
						      FALSE, &AllocVa,
						      &AllocPa);
	} else
#endif /* RALINK_QA */
	{
		pPacket = RTMP_AllocateRxPacketBuffer(pAd, ((POS_COOKIE)
							    (pAd->OS_Cookie))->
						      pci_dev,
						      pATEInfo->TxLength, FALSE,
						      &AllocVa, &AllocPa);
	}

	if (pPacket == NULL) {
		pATEInfo->TxCount = 0;
		DBGPRINT_ERR(("%s : fail to alloc packet space.\n",
			      __func__));
		return -1;
	}

	pTxRing->Cell[TxIdx].pNextNdisPacket = pPacket;
	pDest = (PUCHAR) AllocVa;

#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		GET_OS_PKT_LEN(pPacket) = pATEInfo->DLen;
#ifndef LINUX
		GET_OS_PKT_TOTAL_LEN(pPacket) = pATEInfo->DLen;
#endif /* LIMUX */
	} else
#endif /* RALINK_QA */
	{
		GET_OS_PKT_LEN(pPacket) = pATEInfo->TxLength - pATEInfo->HLen;
#ifndef LINUX
		GET_OS_PKT_TOTAL_LEN(pPacket) =
		    pATEInfo->TxLength - pATEInfo->HLen;
#endif /* LINUX */
	}

	/* prepare frame payload */
#ifdef RALINK_QA
	if ((pATEInfo->bQATxStart == TRUE) && (pATEInfo->DLen != 0)) {
		/* copy pattern to payload */
		if ((pATEInfo->PLen != 0)) {
			for (pos = 0; pos < pATEInfo->DLen;
			     pos += pATEInfo->PLen) {
				memcpy(GET_OS_PKT_DATAPTR(pPacket) + pos,
				       pATEInfo->Pattern, pATEInfo->PLen);
			}
		}
	} else
#endif /* RALINK_QA */
	{
		for (pos = 0; pos < GET_OS_PKT_LEN(pPacket); pos++)
			pDest[pos] = 0x00;
	}

	/* build Tx descriptor */
#ifndef RT_BIG_ENDIAN
	pTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
	pTxInfo =
	    (TXINFO_STRUC *) (pTxRing->Cell[TxIdx].AllocVa + sizeof(TXD_STRUC));
#else
	pDestTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
	NdisMoveMemory(&tx_hw_info[0], (UCHAR *) pDestTxD, TXD_SIZE);
	pTxD = (TXD_STRUC *) &tx_hw_info[0];
	pTxInfo = (TXINFO_STRUC *) (&tx_hw_info[0] + sizeof(TXD_STRUC));
#endif /* !RT_BIG_ENDIAN */
#ifdef RALINK_QA
	if (pATEInfo->bQATxStart == TRUE) {
		/* prepare TxD */
		NdisZeroMemory(pTxD, TXD_SIZE);
		/* build Tx descriptor */
		pTxD->SDPtr0 =
		    RTMP_GetPhysicalAddressLow(pTxRing->Cell[TxIdx].
					       DmaBuf.AllocPa);
		pTxD->SDLen0 = TXWISize + pATEInfo->HLen;
#ifndef RT_SECURE_DMA
		pTxD->SDPtr1 = AllocPa;
#else
		NdisMoveMemory(pAd->TxSecureDMA[QID_AC_BE].AllocVa +
			       (TxIdx * 4096), AllocVa,
			       GET_OS_PKT_LEN(pPacket));
		pTxD->SDPtr1 =
		    pAd->TxSecureDMA[QID_AC_BE].AllocPa + (TxIdx * 4096);
#endif
		pTxD->SDLen1 = GET_OS_PKT_LEN(pPacket);
		pTxD->LastSec0 = (pTxD->SDLen1 == 0) ? 1 : 0;
		pTxD->LastSec1 = 1;
		ral_write_txd(pAd, pTxD, pTxInfo, FALSE, FIFO_EDCA);

		pDest = (PUCHAR) pTxWI;
		pDest += TXWISize;
		pHeader80211 = (PHEADER_802_11) pDest;

		/* modify sequence number... */
		if (pATEInfo->TxDoneCount == 0)
			pATEInfo->seq = pHeader80211->Sequence;
		else
			pHeader80211->Sequence = ++pATEInfo->seq;
	} else
#endif /* RALINK_QA */
	{
		TX_BLK txblk;

		txblk.SrcBufLen = GET_OS_PKT_LEN(pPacket);
		txblk.pSrcBufData = AllocVa;
		NdisZeroMemory(pTxD, TXD_SIZE);
		/* build Tx descriptor */
		pTxD->SDPtr0 =
		    RTMP_GetPhysicalAddressLow(pTxRing->Cell[TxIdx].
					       DmaBuf.AllocPa);
		pTxD->SDLen0 = TXWISize + pATEInfo->HLen /* LENGTH_802_11 */;
#ifndef RT_SECURE_DMA
		pTxD->SDPtr1 =
		    PCI_MAP_SINGLE(pAd, &txblk, 0, 1, RTMP_PCI_DMA_TODEVICE);
#else
		NdisMoveMemory(pAd->TxSecureDMA[QID_AC_BE].AllocVa +
			       (TxIdx * 4096), AllocVa,
			       GET_OS_PKT_LEN(pPacket));
		pTxD->SDPtr1 =
		    pAd->TxSecureDMA[QID_AC_BE].AllocPa + (TxIdx * 4096);
#endif
		pTxD->SDLen1 = GET_OS_PKT_LEN(pPacket);
		pTxD->LastSec0 = (pTxD->SDLen1 == 0) ? 1 : 0;
		pTxD->LastSec1 = 1;
		ral_write_txd(pAd, pTxD, pTxInfo, FALSE, FIFO_EDCA);
	}

#ifdef RT_BIG_ENDIAN
	RTMPWIEndianChange(pAd, (PUCHAR) pTxWI, TYPE_TXWI);
	RTMPFrameEndianChange(pAd, (((PUCHAR) pDMAHeaderBufVA) + TXWISize),
			      DIR_WRITE, FALSE);
	RTMPDescriptorEndianChange((PUCHAR) pTxD, TYPE_TXD);
	WriteBackToDescriptor((PUCHAR) pDestTxD, (PUCHAR) pTxD, FALSE,
			      TYPE_TXD);
#endif /* RT_BIG_ENDIAN */

	return 0;
}
#endif /* RTMP_MAC_PCI */
