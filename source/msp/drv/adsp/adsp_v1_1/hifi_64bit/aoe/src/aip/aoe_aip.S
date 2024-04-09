#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_aip.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AIPCalcProcBlockSize, %function
AIPCalcProcBlockSize:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w2
	mov	w20, w1
	bl	_mcount
	mov	w1, w21
	mov	w0, w20
	bl	UTIL_CalcFrameSize
	mov	w4, 19923
	add	w1, w19, w19, lsl 2
	movk	w4, 0x1062, lsl 16
	mov	w3, 25856
	movk	w3, 0x4, lsl 16
	mov	w2, 48000
	umull	x1, w1, w4
	cmp	w19, w3
	ccmp	w19, w2, 4, ne
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	bne	.L2
	ands	w2, w1, 255
	beq	.L3
	add	w1, w1, 256
	sub	w1, w1, w2
.L3:
	mul	w0, w1, w0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2:
	and	w2, w1, 3
	cbz	w2, .L3
	and	w1, w1, -4
	ldr	x21, [sp, 32]
	add	w1, w1, 4
	ldp	x19, x20, [sp, 16]
	mul	w0, w1, w0
	ldp	x29, x30, [sp], 48
	ret
	.size	AIPCalcProcBlockSize, .-AIPCalcProcBlockSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPDestroyChn, %function
AIPDestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L11
	ldr	x0, [x19, 176]
	str	wzr, [x19, 216]
	cbz	x0, .L13
	bl	RBUF_Destroy
.L13:
	ldr	x0, [x19, 184]
	cbz	x0, .L14
	bl	RBUF_Destroy
.L14:
	ldr	x0, [x19, 208]
	cbz	x0, .L15
	bl	FADE_Destroy
.L15:
	ldr	x0, [x19, 192]
	cbz	x0, .L16
	bl	LSRC_Destroy
.L16:
	ldr	x0, [x19, 200]
	cbz	x0, .L17
	bl	ResamplerFree
.L17:
	ldr	x1, [x19, 280]
	cbz	x1, .L18
	mov	w0, 26
	bl	HI_ADSP_FREE
.L18:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L11:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPDestroyChn, .-AIPDestroyChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPUpdateChnState, %function
AIPUpdateChnState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC0
	add	x1, x0, x19, uxtw 3
	ldr	x20, [x0, w19, uxtw 3]
	ldr	x19, [x1, 64]
	cbz	x19, .L40
	str	wzr, [x19, 220]
	ldr	w0, [x20, 48]
	uxtb	w0, w0
	str	w0, [x19, 224]
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 8, 8
	str	w0, [x19, 228]
	ldr	w0, [x20, 76]
	uxtb	w0, w0
	str	w0, [x19, 240]
	ldr	w0, [x20, 76]
	tbz	x0, 11, .L50
	ldr	w0, [x20, 76]
	tbnz	x0, 11, .L51
.L44:
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 16, 1
	str	w0, [x19, 248]
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 17, 3
	str	w0, [x19, 252]
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 23, 2
	str	w0, [x19, 256]
	cmp	w0, 1
	beq	.L52
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 25, 7
	neg	w0, w0
	str	w0, [x19, 356]
.L46:
	ldr	w0, [x20, 48]
	ubfx	x0, x0, 20, 3
	str	w0, [x19, 360]
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 29, 2
	cbnz	w0, .L47
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 24, 5
	str	w0, [x19, 272]
.L48:
	ldr	w0, [x20]
	ldr	w2, [x19, 112]
	ubfx	x0, x0, 14, 1
	str	w0, [x19, 4]
	ldr	w1, [x19, 296]
	ldr	w0, [x20, 4]
	ubfx	x0, x0, 24, 1
	str	w0, [x19, 312]
	ldr	w0, [x20, 76]
	ubfx	x0, x0, 24, 1
	str	w0, [x19, 316]
	ldr	w0, [x20, 76]
	ubfx	x0, x0, 12, 4
	str	w0, [x19, 324]
	ldr	w0, [x20, 76]
	ubfx	x0, x0, 16, 8
	str	w0, [x19, 328]
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 15, 1
	str	w0, [x19, 320]
	ldr	w0, [x20, 4]
	ubfx	x0, x0, 10, 7
	str	w0, [x19, 172]
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x19, 168]
	ldr	x0, [x19, 184]
	add	x1, x19, 120
	bl	RBUF_UpdateAttr
	ldr	w0, [x20, 84]
	ubfx	x0, x0, 20, 1
	cbz	w0, .L40
	str	w0, [x19, 20]
	ldr	w0, [x20, 84]
	and	w0, w0, -1048577
	str	w0, [x20, 84]
.L40:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L50:
	ldr	w0, [x20, 76]
	ubfx	x0, x0, 8, 3
	str	w0, [x19, 244]
	b	.L44
	.p2align 3
.L47:
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 29, 2
	cmp	w0, 1
	bne	.L48
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 24, 5
	neg	w0, w0
	str	w0, [x19, 272]
	b	.L48
	.p2align 3
.L52:
	mov	w0, 256
	str	w0, [x19, 356]
	b	.L46
	.p2align 3
.L51:
	ldr	w0, [x20, 76]
	ubfx	x0, x0, 8, 3
	neg	w0, w0
	str	w0, [x19, 244]
	b	.L44
	.size	AIPUpdateChnState, .-AIPUpdateChnState
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPGainPcmData, %function
AIPGainPcmData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x29, 56]
	ldr	x0, .LC1
	add	x1, x29, 40
	mov	x2, 20
	ldr	x3, [x0, 48]
	add	x0, x29, 40
	stp	xzr, xzr, [x1]
	add	x1, x20, 220
	blr	x3
	ldr	w2, [x20, 240]
	ldr	w0, [x29, 44]
	add	w0, w2, w0
	cmp	w0, 120
	bhi	.L54
	ldr	w1, [x29, 48]
	mov	w0, 0
	str	wzr, [x29, 44]
	add	w1, w2, w1
	cmp	w1, 120
	bls	.L64
.L56:
	sub	w1, w1, #121
	ldr	w3, [x20, 244]
	str	w1, [x29, 48]
	cmp	w0, 121
	ldp	w2, w1, [x29, 52]
	add	w2, w3, w2
	add	w0, w3, w1
	stp	w2, w0, [x29, 52]
	beq	.L65
.L58:
	add	x2, x29, 40
	mov	x0, x19
	mov	w1, 0
	bl	UTIL_LRGainProcess
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L54:
	ldr	w1, [x29, 48]
	sub	w0, w0, #121
	str	w0, [x29, 44]
	add	w1, w2, w1
	cmp	w1, 120
	bhi	.L56
.L64:
	ldp	w2, w1, [x29, 52]
	ldr	w3, [x20, 244]
	cmp	w0, 121
	str	wzr, [x29, 48]
	add	w2, w3, w2
	add	w0, w3, w1
	stp	w2, w0, [x29, 52]
	bne	.L58
.L65:
	ldr	w1, [x29, 48]
	cmp	w1, 121
	ccmp	w2, wzr, 0, eq
	ccmp	w0, wzr, 0, eq
	bne	.L58
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	AIPGainPcmData, .-AIPGainPcmData
	.align	3
.LC1:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPUpdateTrackLatency, %function
AIPUpdateTrackLatency:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	add	x1, x29, 56
	mov	w0, 0
	bl	AOP_GetChnStatus
	ldr	x0, [x19, 184]
	bl	RBUF_QueryBusy
	ldr	w2, [x19, 112]
	ldr	w1, [x19, 296]
	bl	UTIL_LatencyMs
	mov	w20, w0
	ldr	x0, [x19, 176]
	bl	RBUF_QueryBusy
	ldr	w1, [x19, 300]
	ldr	w2, [x19, 32]
	bl	UTIL_LatencyMs
	add	w0, w20, w0
	ldr	w1, [x29, 88]
	add	w0, w0, w1
	cmp	w0, 999
	bls	.L69
	ldr	w0, [x21, 56]
	orr	w0, w0, 67043328
	str	w0, [x21, 56]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L69:
	ldr	w1, [x21, 56]
	bfi	w1, w0, 16, 10
	str	w1, [x21, 56]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	AIPUpdateTrackLatency, .-AIPUpdateTrackLatency
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPReclaimFifo, %function
AIPReclaimFifo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 184]
	cbz	x0, .L70
	bl	RBUF_QueryBusy
	ldr	w1, [x19, 292]
	cmp	w0, w1
	bcc	.L85
	bl	AOE_GetWKBuf
	ldr	w20, [x19, 292]
	mov	x1, x0
	mov	x21, x0
	ldr	x0, [x19, 184]
	mov	w2, w20
	bl	RBUF_ReadData
	cmp	w20, w0
	bne	.L85
	ldr	w0, [x19, 320]
	cbnz	w0, .L86
.L74:
	ldr	x3, [x19, 384]
	cbz	x3, .L75
	ldr	w2, [x19, 292]
	mov	x1, x21
	ldr	w0, [x19, 380]
	blr	x3
.L75:
	ldr	x0, [x19, 184]
	bl	RBUF_Flush
	ldr	w2, [x19, 292]
	mov	x1, 0
	ldr	x0, [x19, 184]
	bl	RBUF_WriteData
.L70:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L85:
	ldr	x0, [x19, 184]
	bl	RBUF_Flush
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L86:
	ldr	x0, [x19, 208]
	mov	w2, 6
	mov	w1, 2
	bl	FADE_Active
	ldr	x0, [x19, 208]
	mov	w2, 256
	mov	x1, x21
	bl	FADE_OutProcess
	b	.L74
	.size	AIPReclaimFifo, .-AIPReclaimFifo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetPcmType
	.type	AIP_GetPcmType, %function
AIP_GetPcmType:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC2
	ldr	x0, [x0, w19, uxtw 3]
	cbz	x0, .L90
	ldr	w0, [x0]
	ubfx	x0, x0, 11, 3
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L90:
	mov	w0, 5
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_GetPcmType, .-AIP_GetPcmType
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetRbfFiFoAttr
	.type	AIPGetRbfFiFoAttr, %function
AIPGetRbfFiFoAttr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, .LC3
	add	x0, x19, 104
	ldr	x20, [x1, w20, uxtw 3]
	ldr	w1, [x20, 4]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L94
	ldr	w1, [x20, 4]
	add	x0, x19, 108
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L94
	ldr	w1, [x20, 4]
	add	x0, x19, 112
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L94
	ldr	w1, [x20, 4]
	add	x0, x19, 116
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L94
	ldr	w1, [x20, 4]
	add	x0, x29, 76
	ubfx	x1, x1, 10, 7
	bl	AOE_REG_ReadBufLatencyMs
	mov	w22, w0
	cbnz	w0, .L94
	ldr	w0, [x29, 76]
	cmp	w0, 80
	bhi	.L94
	ldp	w1, w0, [x19, 104]
	bl	UTIL_CalcFrameSize
	str	wzr, [x19, 120]
	ldr	w2, [x19, 112]
	mov	w23, w0
	mov	w1, w0
	str	wzr, [x19, 160]
	mov	w0, 80
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x19, 136]
	ldr	w2, [x29, 76]
	add	x0, x20, 68
	str	w2, [x19, 172]
	add	x20, x20, 72
	stp	x0, x20, [x19, 144]
	mov	w0, w2
	ldr	w2, [x19, 112]
	mov	w1, w23
	str	w23, [x19, 164]
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x19, 168]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L94:
	mov	w22, -1
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	AIPGetRbfFiFoAttr, .-AIPGetRbfFiFoAttr
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetRbfInAttr
	.type	AIPGetRbfInAttr, %function
AIPGetRbfInAttr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC4
	add	x0, x20, 24
	ldr	x19, [x1, w19, uxtw 3]
	ldr	w1, [x19]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L98
	ldr	w1, [x19]
	add	x0, x20, 28
	ubfx	x1, x1, 2, 3
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L98
	ldr	w1, [x19]
	add	x0, x20, 32
	ubfx	x1, x1, 5, 4
	bl	AOE_REG_ReadSampelRate
	cbz	w0, .L101
	ldr	w0, [x19]
	ubfx	x0, x0, 5, 4
	cmp	w0, 15
	beq	.L105
.L101:
	ldr	w1, [x19]
	add	x0, x20, 36
	ubfx	x1, x1, 9, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L98
	ldr	w1, [x19]
	mov	x0, x20
	ubfx	x1, x1, 11, 3
	bl	AOE_REG_ReadPcmType
	mov	w21, w0
	cbnz	w0, .L98
	ldr	w2, [x19]
	ldp	w1, w0, [x20, 24]
	ubfx	x2, x2, 14, 1
	str	w2, [x20, 4]
	bl	UTIL_CalcFrameSize
	mov	w1, 1
	str	w1, [x20, 48]
	add	x1, x20, 48
	mov	x2, 0
	ldr	w4, [x19, 16]
	ldr	w3, [x19, 20]
	bfi	x2, x4, 0, 32
	bfi	x2, x3, 32, 32
	str	x2, [x1, 8]
	ldr	w2, [x19, 24]
	ubfx	x2, x2, 0, 24
	str	w2, [x1, 16]
	ldr	w3, [x19, 24]
	tbnz	x3, 24, .L106
	add	x4, x19, 28
	add	x3, x19, 36
	stp	x4, x3, [x1, 24]
.L103:
	ldr	w3, [x19, 24]
	stp	w0, w2, [x1, 44]
	str	wzr, [x1, 52]
	ubfx	x0, x3, 24, 1
	str	w0, [x1, 40]
	mov	w2, 16
	mov	w1, 8
	mov	w0, 2
	stp	w2, w1, [x20, 12]
	str	w0, [x20, 20]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L106:
	ldr	w6, [x19, 28]
	mov	x4, 0
	ldr	w5, [x19, 32]
	mov	x3, 0
	bfi	x4, x6, 0, 32
	bfi	x4, x5, 32, 32
	str	x4, [x1, 24]
	ldr	w5, [x19, 36]
	ldr	w4, [x19, 40]
	bfi	x3, x5, 0, 32
	bfi	x3, x4, 32, 32
	str	x3, [x1, 32]
	b	.L103
	.p2align 3
.L105:
	ldr	w0, [x19, 12]
	mov	w1, 56928
	movk	w1, 0x2, lsl 16
	ubfx	x0, x0, 0, 24
	str	w0, [x20, 32]
	sub	w0, w0, #4000
	cmp	w0, w1
	bhi	.L98
	ldr	w0, [x20, 28]
	cmp	w0, 2
	bhi	.L98
	ldr	w0, [x20, 24]
	cmp	w0, 16
	beq	.L101
.L98:
	mov	w21, -1
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AIPGetRbfInAttr, .-AIPGetRbfInAttr
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetChnCreateAttr
	.type	AIPGetChnCreateAttr, %function
AIPGetChnCreateAttr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	x1, x20
	mov	w0, w19
	bl	AIPGetRbfInAttr
	cbnz	w0, .L108
	mov	x1, x20
	mov	w0, w19
	bl	AIPGetRbfFiFoAttr
.L108:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPGetChnCreateAttr, .-AIPGetChnCreateAttr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPIsChnAttrChange
	.type	AIPIsChnAttrChange, %function
AIPIsChnAttrChange:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC5
	mov	w0, w19
	add	x1, x29, 32
	add	x19, x2, x19, uxtw 3
	ldr	x19, [x19, 64]
	bl	AIPGetChnCreateAttr
	ldp	w0, w5, [x29, 56]
	ldp	w3, w1, [x29, 64]
	ldp	w6, w7, [x19, 24]
	ldp	w4, w2, [x19, 32]
	cmp	w6, w0
	cset	w0, ne
	cmp	w7, w5
	csinc	w0, w0, w0, eq
	cmp	w4, w3
	ldp	w6, w4, [x19]
	ldp	w5, w3, [x29, 32]
	csinc	w0, w0, w0, eq
	cmp	w2, w1
	csinc	w0, w0, w0, eq
	ldr	x2, [x19, 56]
	ldr	x1, [x29, 88]
	cmp	w6, w5
	csinc	w0, w0, w0, eq
	ldr	w6, [x19, 64]
	ldr	w5, [x29, 96]
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	ldr	w4, [x19, 88]
	ldr	w3, [x29, 120]
	cmp	x2, x1
	csinc	w0, w0, w0, eq
	cmp	w6, w5
	ldp	w2, w6, [x19, 104]
	ldp	w1, w5, [x29, 136]
	csinc	w0, w0, w0, eq
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	ldr	w4, [x19, 112]
	ldr	w3, [x29, 144]
	cmp	w2, w1
	csinc	w0, w0, w0, eq
	ldr	w2, [x19, 116]
	ldr	w1, [x29, 148]
	cmp	w6, w5
	csinc	w0, w0, w0, eq
	cmp	w4, w3
	csinc	w0, w0, w0, eq
	cmp	w2, w1
	ldr	x19, [sp, 16]
	csinc	w0, w0, w0, eq
	ldp	x29, x30, [sp], 208
	ret
	.size	AIPIsChnAttrChange, .-AIPIsChnAttrChange
	.align	3
.LC5:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPCreateChn
	.type	AIPCreateChn, %function
AIPCreateChn:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC6
	add	x1, x29, 128
	mov	w0, w21
	stp	xzr, xzr, [x29, 56]
	ldr	x20, [x2, w21, uxtw 3]
	stp	xzr, xzr, [x29, 72]
	bl	AIPGetChnCreateAttr
	cbnz	w0, .L129
	mov	w1, 400
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L113
	ldr	x22, .LC7
	mov	x2, 400
	mov	w1, 0
	ldr	x3, [x22, 40]
	blr	x3
	ldr	x3, [x22, 48]
	mov	x2, 176
	add	x1, x29, 128
	mov	x0, x19
	blr	x3
	str	w21, [x19, 304]
	add	x0, x29, 72
	add	x1, x29, 176
	bl	RBUF_Create_EXT
	ldr	x0, [x29, 72]
	cbz	x0, .L113
	ldr	w1, [x29, 164]
	str	x0, [x19, 176]
	cbz	w1, .L152
	str	wzr, [x20, 60]
	ldr	w0, [x20, 64]
	and	w0, w0, -65536
	str	w0, [x20, 64]
.L115:
	mov	w1, 768
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	str	x0, [x19, 280]
	cbz	x0, .L113
	ldr	w0, [x29, 164]
	cbz	w0, .L116
	ldr	w1, [x19]
.L117:
	ldr	w0, [x20, 8]
	cmp	w1, 4
	ubfx	x0, x0, 15, 1
	str	w0, [x19, 320]
	beq	.L153
.L127:
	mov	w0, 6144
	str	w0, [x19, 396]
.L128:
	ldp	w2, w1, [x19, 24]
	ldr	w0, [x19, 32]
	mov	w4, 256
	mov	w3, 3
	str	w4, [x19, 356]
	str	w3, [x19, 360]
	stp	wzr, wzr, [x19, 220]
	str	wzr, [x19, 228]
	str	wzr, [x19, 252]
	bl	AIPCalcProcBlockSize
	str	w0, [x19, 288]
	ldp	w2, w1, [x19, 104]
	ldr	w0, [x19, 112]
	bl	AIPCalcProcBlockSize
	str	w0, [x19, 292]
	ldr	w1, [x19, 104]
	ldr	w0, [x19, 108]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 296]
	ldr	w1, [x19, 24]
	ldr	w0, [x19, 28]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 300]
	mov	w1, 1
	str	w1, [x19, 216]
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L116:
	ldr	w0, [x29, 160]
	ldr	w1, [x29, 240]
	cmp	w0, w1
	beq	.L118
	mov	w2, 32000
	cmp	w0, w2
	beq	.L119
	bls	.L154
	mov	w2, 22664
	movk	w2, 0x1, lsl 16
	cmp	w0, w2
	beq	.L119
	bhi	.L123
.L119:
	mov	w2, 1
	ldr	w3, [x29, 232]
	str	w2, [x19, 308]
	mov	w4, 0
	ldr	w2, [x29, 236]
	bl	ResamplerCreate
	cbz	x0, .L113
	ldr	w1, [x29, 240]
	str	x0, [x19, 200]
.L118:
	ldp	w3, w4, [x29, 232]
	add	x0, x29, 56
	mov	w2, w1
	bl	LSRC_Create
	ldr	x0, [x29, 56]
	cbz	x0, .L113
	str	x0, [x19, 192]
	str	wzr, [x20, 80]
	ldr	w0, [x19]
	cbnz	w0, .L155
	ldr	w0, [x20, 8]
	ubfx	x0, x0, 15, 1
	str	w0, [x19, 320]
	b	.L127
	.p2align 3
.L152:
	add	x0, x29, 80
	add	x1, x29, 248
	bl	RBUF_Create
	ldr	x0, [x29, 80]
	cbz	x0, .L113
	add	x1, x29, 88
	str	x0, [x19, 184]
	bl	RBUF_QueryInfo
	ldrh	w1, [x29, 104]
	ldr	w0, [x20, 64]
	bfi	w0, w1, 0, 16
	str	w0, [x20, 64]
	b	.L115
	.p2align 3
.L129:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	x0, 0
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L154:
	mov	w2, 12000
	cmp	w0, w2
	beq	.L119
	bls	.L119
	b	.L119
	.p2align 3
.L153:
	mov	w0, 24576
	str	w0, [x19, 396]
	b	.L128
	.p2align 3
.L113:
	mov	x0, x19
	bl	AIPDestroyChn
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L155:
	ldp	w2, w3, [x29, 152]
	ldr	w1, [x29, 160]
	add	x0, x29, 64
	bl	FADE_Create
	ldr	x0, [x29, 64]
	cbz	x0, .L113
	ldr	w1, [x19]
	str	x0, [x19, 208]
	str	wzr, [x19, 268]
	b	.L117
	.p2align 3
.L123:
	b	.L119
	.size	AIPCreateChn, .-AIPCreateChn
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC7:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnCtx
	.type	AIPFlushChnCtx, %function
AIPFlushChnCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 200]
	cbz	x0, .L157
	bl	ResampleFlush
.L157:
	ldr	x0, [x19, 192]
	cbz	x0, .L158
	bl	LSRC_Flush
.L158:
	ldr	x0, [x19, 208]
	str	wzr, [x19, 276]
	cbz	x0, .L156
	mov	w2, 8
	mov	w1, 1
	bl	FADE_Active
.L156:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnCtx, .-AIPFlushChnCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AIPFlushChn, %function
AIPFlushChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	tbnz	x19, 0, .L188
.L170:
	tbz	x19, 1, .L171
	ldr	x0, [x20, 176]
	cbz	x0, .L171
	bl	RBUF_Flush
.L171:
	tbz	x19, 2, .L169
	ldr	x0, [x20, 184]
	cbz	x0, .L169
	bl	RBUF_Flush
.L169:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L188:
	mov	x0, x20
	bl	AIPFlushChnCtx
	b	.L170
	.size	AIPFlushChn, .-AIPFlushChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnRufIn
	.type	AIPFlushChnRufIn, %function
AIPFlushChnRufIn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 176]
	cbz	x0, .L189
	bl	RBUF_Flush
.L189:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnRufIn, .-AIPFlushChnRufIn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPFlushChnFifo
	.type	AIPFlushChnFifo, %function
AIPFlushChnFifo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 184]
	cbz	x0, .L194
	bl	RBUF_Flush
.L194:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPFlushChnFifo, .-AIPFlushChnFifo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPGetChnCmd
	.type	AIPGetChnCmd, %function
AIPGetChnCmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC8
	ldr	x0, [x0, w20, uxtw 3]
	ldr	w1, [x0, 8]
	tbz	x1, 3, .L208
	mov	w0, 4
.L200:
	str	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L208:
	ldr	w0, [x0, 8]
	ldr	x1, .LC9
	and	w0, w0, 3
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx202
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx202:
	.section	.rodata
	.align	0
	.align	2
.L202:
	.byte	(.L207 - .Lrtx202) / 4
	.byte	(.L203 - .Lrtx202) / 4
	.byte	(.L204 - .Lrtx202) / 4
	.byte	(.L205 - .Lrtx202) / 4
	.text
	.p2align 3
.L207:
	mov	w0, 0
	b	.L200
	.p2align 3
.L205:
	mov	w0, 3
	b	.L200
	.p2align 3
.L204:
	mov	w0, 2
	b	.L200
	.p2align 3
.L203:
	mov	w0, 1
	b	.L200
	.size	AIPGetChnCmd, .-AIPGetChnCmd
	.align	3
.LC8:
	.xword	.LANCHOR0
	.align	3
.LC9:
	.xword	.L202
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIPAckChnCmd
	.type	AIPAckChnCmd, %function
AIPAckChnCmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC10
	ldr	x0, [x0, w19, uxtw 3]
	ldr	w2, [x0, 8]
	tbnz	x2, 3, .L209
	ldr	w2, [x0, 8]
	bfi	w2, w20, 4, 4
	str	w2, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L209:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIPAckChnCmd, .-AIPAckChnCmd
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_Init
	.type	AIP_Init, %function
AIP_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w22, 121
	add	x21, x19, 768
	bl	_mcount
	ldr	x20, .LC13
	ldr	x24, .LC14
	mov	w23, 5
	add	x20, x20, 64
	.p2align 2
.L212:
	ldr	x3, [x24, 40]
	mov	x0, x19
	str	x19, [x20, -64]
	mov	x2, 96
	mov	w1, 0
	blr	x3
	ldr	w0, [x19, 8]
	orr	w0, w0, 8
	str	w0, [x19, 8]
	ldr	w0, [x19, 8]
	bfi	w0, w22, 8, 7
	str	w0, [x19, 8]
	ldr	w0, [x19]
	bfi	w0, w23, 11, 3
	str	w0, [x19], 96
	str	xzr, [x20], 8
	cmp	x19, x21
	bne	.L212
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	AIP_Init, .-AIP_Init
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_DeInit
	.type	AIP_DeInit, %function
AIP_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC15
	add	x19, x20, 64
	add	x20, x20, 128
	.p2align 2
.L215:
	ldr	x0, [x19]
	bl	AIPDestroyChn
	str	xzr, [x19], 8
	cmp	x19, x20
	bne	.L215
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_DeInit, .-AIP_DeInit
	.align	3
.LC15:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_Process
	.type	AIP_Process, %function
AIP_Process:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	mov	w22, 0
	bl	_mcount
	ldr	x24, .LC19
	ldr	x25, .LC17
	ldr	x23, .LC18
	mov	x27, x24
	add	x19, x25, 64
	.p2align 2
.L284:
	ldr	x21, [x19, -64]
	ldr	w0, [x21, 8]
	tbnz	x0, 3, .L355
	ldr	w0, [x21, 8]
	and	w0, w0, 3
	ldrb	w0, [x23,w0,uxtw]
	adr	x1, .Lrtx221
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx221:
	.section	.rodata
	.align	0
	.align	2
.L221:
	.byte	(.L220 - .Lrtx221) / 4
	.byte	(.L222 - .Lrtx221) / 4
	.byte	(.L223 - .Lrtx221) / 4
	.byte	(.L224 - .Lrtx221) / 4
	.text
	.p2align 3
.L223:
	ldr	x20, [x19]
	cbz	x20, .L286
	ldr	w21, [x20, 216]
	cmp	w21, 1
	beq	.L360
.L237:
	mov	w0, 2
	str	wzr, [x20, 392]
	str	w0, [x20, 20]
	ldr	x0, [x19, -64]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L355
.L241:
	ldr	w1, [x0, 8]
	and	w1, w1, -241
.L356:
	str	w1, [x0, 8]
	ldr	w1, [x0, 8]
	orr	w1, w1, 8
	str	w1, [x0, 8]
.L355:
	ldr	x20, [x19]
.L232:
	cbz	x20, .L286
.L285:
	ldr	w21, [x20, 216]
	cmp	w21, 1
	beq	.L361
.L286:
	add	w22, w22, 1
	add	x19, x19, 8
	cmp	w22, 8
	bne	.L284
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L222:
	ldr	x28, [x19]
	cmp	x28, xzr
	mov	x20, x28
	ccmp	x21, xzr, 4, ne
	cset	w0, eq
	cbnz	w0, .L232
	ldr	w1, [x28, 216]
	mov	x0, x21
	sub	w2, w1, #1
	cmp	w2, 1
	bls	.L362
.L239:
	ldr	w1, [x0, 8]
	tbz	x1, 3, .L241
	ldr	x20, [x19]
	b	.L232
	.p2align 3
.L224:
	ldr	x20, [x19]
	cbz	x20, .L286
	ldr	w21, [x20, 216]
	cmp	w21, 1
	beq	.L363
	cmp	w21, 2
	bne	.L237
	mov	w1, 7
	mov	x0, x20
	bl	AIPFlushChn
	b	.L237
	.p2align 3
.L220:
	ldr	x20, [x19]
	cbz	x20, .L354
	ldr	w0, [x20, 216]
	cbz	w0, .L364
	cmp	w0, 2
	beq	.L365
.L229:
	ldr	w0, [x21, 8]
	tbnz	x0, 3, .L233
	ldr	w0, [x21, 8]
	and	w0, w0, -241
	str	w0, [x21, 8]
	ldr	w0, [x21, 8]
	orr	w0, w0, 8
	str	w0, [x21, 8]
	ldr	x20, [x19]
	b	.L232
	.p2align 3
.L361:
	mov	w0, w22
	bl	AIPUpdateChnState
	ldr	x28, [x19]
	ldr	x26, [x19, -64]
	cmp	x28, xzr
	ccmp	x26, xzr, 4, ne
	beq	.L244
	ldr	w0, [x28, 20]
	cmp	w0, 1
	bls	.L244
	ldr	x0, [x28, 176]
	bl	RBUF_QueryBusy
	cbz	w0, .L244
	ldr	w3, [x28, 32]
	mov	w5, 19923
	ldr	w2, [x28, 92]
	movk	w5, 0x1062, lsl 16
	mul	w4, w2, w3
	ldr	w2, [x26, 84]
	ldr	w3, [x26, 84]
	and	w1, w2, 1023
	ldr	w2, [x28, 20]
	ubfx	x3, x3, 10, 10
	mul	w1, w1, w4
	umull	x1, w1, w5
	lsr	x1, x1, 38
	cmp	w0, w1
	ccmp	w2, 2, 0, cc
	beq	.L244
	mul	w3, w3, w4
	umull	x1, w3, w5
	lsr	x1, x1, 38
	cmp	w0, w1
	ccmp	w2, 3, 0, cc
	beq	.L244
	ldr	x0, [x28, 208]
	mov	w1, w21
	mov	w2, 8
	str	w21, [x28, 20]
	bl	FADE_Active
	.p2align 2
.L244:
	ldr	w0, [x20, 36]
	cbnz	w0, .L286
	mov	w0, w22
	bl	AIPUpdateChnState
	ldr	w0, [x20, 20]
	cmp	w0, 1
	beq	.L366
.L260:
	ldr	x20, [x19]
	ldr	x21, [x19, -64]
	ldr	x0, [x20, 184]
	bl	RBUF_QueryBusy
	ldr	w2, [x20, 112]
	ldr	w1, [x20, 296]
	bl	UTIL_LatencyMs
	ldr	w1, [x21, 4]
	bfi	w1, w0, 17, 7
	mov	x0, x20
	str	w1, [x21, 4]
	mov	x1, x21
	bl	AIPUpdateTrackLatency
	str	xzr, [x20, 384]
	mov	w0, 6
	str	w0, [x20, 380]
	b	.L286
	.p2align 3
.L366:
	ldr	w0, [x20, 312]
	cmp	w0, 1
	beq	.L260
	ldr	w0, [x20, 316]
	cbnz	w0, .L247
	ldr	w0, [x20, 332]
	cmp	w0, 1
	beq	.L367
.L257:
	ldr	w1, [x20, 276]
	ldr	w0, [x20, 296]
	ldr	w21, [x20, 292]
	mul	w2, w1, w0
	cmp	w2, w21
	bcs	.L368
	ldr	w2, [x20, 36]
	mov	w28, w21
	cbz	w2, .L369
.L261:
	ldr	x0, [x20, 176]
	bl	RBUF_QueryBusy
	cmp	w0, w28
	bcc	.L260
	cbz	w28, .L260
	ldr	x0, [x20, 184]
	cbz	x0, .L260
	mov	w1, w21
	bl	RBUF_CheckFree
	cbz	w0, .L260
	cbz	w21, .L260
	bl	AOE_GetWKBuf
	mov	x1, x0
	str	x0, [x29, 120]
	mov	w2, w28
	ldr	w0, [x20, 300]
	mov	x3, 0
	ldr	w4, [x20, 24]
	str	w4, [x29, 136]
	udiv	w0, w28, w0
	ldr	w4, [x20, 28]
	str	w4, [x29, 140]
	ldr	w4, [x20, 32]
	str	w0, [x29, 132]
	str	w4, [x29, 144]
	ldr	x0, [x20, 176]
	ldr	w4, [x20, 36]
	str	w28, [x29, 128]
	str	w4, [x29, 148]
	bl	RBUF_ReadDataDma
	ldr	w0, [x20, 36]
	cbz	w0, .L370
.L267:
	ldr	w0, [x20, 248]
	cmp	w0, 1
	beq	.L371
.L279:
	ldr	w0, [x20, 276]
	ldr	w2, [x20, 296]
	ldr	w28, [x20, 292]
	mul	w2, w0, w2
	cbnz	w2, .L372
.L280:
	ldr	w0, [x29, 128]
	cbz	w28, .L282
	cmp	w28, w0
	csel	w28, w28, w0, ls
	cbz	w28, .L282
	ldr	x0, [x20, 184]
	mov	w2, w28
	ldr	x1, [x29, 120]
	bl	RBUF_WriteData
	ldr	w0, [x29, 128]
.L282:
	subs	w21, w0, w28
	beq	.L283
	ldr	x1, [x29, 120]
	uxtw	x2, w21
	ldr	x0, [x20, 280]
	ldr	x3, [x24, 48]
	add	x1, x1, x28, uxtw
	blr	x3
.L283:
	ldr	w0, [x20, 296]
	udiv	w0, w21, w0
	str	w0, [x20, 276]
	ldr	w0, [x20, 392]
	add	w0, w0, 1
	str	w0, [x20, 392]
	b	.L260
	.p2align 3
.L233:
	ldr	x20, [x19]
	b	.L285
	.p2align 3
.L364:
	mov	w0, w22
	bl	AIPIsChnAttrChange
	cbnz	w0, .L373
	mov	w0, 1
	str	w0, [x20, 216]
	ldr	x0, [x19]
.L226:
	cbz	x0, .L230
	ldr	x21, [x19, -64]
	b	.L229
	.p2align 3
.L362:
	cmp	w1, 1
	beq	.L374
.L240:
	mov	x0, x28
	mov	w1, 3
	bl	AIPFlushChn
	str	wzr, [x28, 216]
	mov	w0, 2
	str	w0, [x28, 20]
	str	wzr, [x21, 80]
	str	wzr, [x28, 392]
	ldr	x0, [x19, -64]
	b	.L239
	.p2align 3
.L230:
	ldr	x0, [x19, -64]
	ldr	w1, [x0, 8]
	tbnz	x1, 3, .L286
	ldr	w1, [x0, 8]
	mov	w2, 1
	bfi	w1, w2, 4, 4
	b	.L356
	.p2align 3
.L373:
	ldr	x0, [x19]
	bl	AIPDestroyChn
.L354:
	mov	w0, w22
	bl	AIPCreateChn
	str	x0, [x19]
	b	.L226
	.p2align 3
.L363:
	mov	x0, x20
	bl	AIPReclaimFifo
	mov	x0, x20
	mov	w1, 3
	bl	AIPFlushChn
	ldr	x0, [x20, 208]
	mov	w1, w21
	mov	w2, 8
	bl	FADE_Active
	b	.L237
	.p2align 3
.L360:
	mov	x0, x20
	bl	AIPReclaimFifo
	mov	x0, x20
	mov	w1, w21
	bl	AIPFlushChn
	mov	w0, 2
	str	w0, [x20, 216]
	b	.L237
	.p2align 3
.L365:
	ldr	x0, [x20, 208]
	mov	w1, 1
	mov	w2, 8
	str	w1, [x20, 216]
	bl	FADE_Active
	ldr	x0, [x19]
	b	.L226
.L247:
	ldr	w0, [x20, 332]
	cbz	w0, .L250
	ldr	w0, [x20, 336]
.L251:
	ldr	w21, [x20, 292]
	str	w0, [x29, 116]
	ldr	w0, [x20, 324]
	mov	w1, w21
	bl	AOP_QueryRbfFree
	cbz	w0, .L257
	ldr	x0, [x20, 176]
	add	x1, x29, 116
	bl	RBUF_QueryBusy_ProvideRptr
	cmp	w21, w0
	bhi	.L257
	bl	AOE_GetWKBuf
	mov	x1, x0
	str	x0, [x29, 120]
	add	x3, x29, 116
	ldr	w0, [x20, 300]
	mov	w2, w21
	ldr	w4, [x20, 24]
	str	w4, [x29, 136]
	udiv	w0, w21, w0
	ldr	w4, [x20, 28]
	str	w4, [x29, 140]
	ldr	w4, [x20, 32]
	str	w0, [x29, 132]
	str	w4, [x29, 144]
	ldr	x0, [x20, 176]
	ldr	w4, [x20, 36]
	str	w21, [x29, 128]
	str	w4, [x29, 148]
	bl	RBUF_ReadDataDma
	ldr	w0, [x20, 256]
	cmp	w0, 1
	beq	.L375
.L254:
	add	x1, x29, 120
	mov	x0, x20
	bl	AIPGainPcmData
	ldr	w1, [x20, 252]
	sub	w0, w1, #1
	cmp	w0, 6
	bls	.L376
.L255:
	ldr	w0, [x20, 248]
	cmp	w0, 1
	beq	.L377
.L256:
	ldr	w0, [x20, 324]
	add	x1, x29, 120
	bl	AOP_WriteRbfData
	ldr	w0, [x29, 116]
	str	w0, [x20, 336]
	b	.L257
.L368:
	ldr	x0, [x20, 184]
	cbz	x0, .L260
	mov	w1, w21
	bl	RBUF_CheckFree
	cbz	w0, .L260
	cbz	w21, .L260
	ldr	x1, [x20, 280]
	ldr	w2, [x20, 292]
	ldr	x0, [x20, 184]
	bl	RBUF_WriteData
	ldr	w0, [x20, 292]
	ldr	w1, [x20, 296]
	udiv	w1, w0, w1
	ldr	w0, [x20, 276]
	sub	w0, w0, w1
	str	w0, [x20, 276]
	b	.L260
.L374:
	mov	x0, x28
	bl	AIPReclaimFifo
	b	.L240
.L250:
	ldp	w1, w0, [x20, 104]
	mov	w21, 19923
	movk	w21, 0x1062, lsl 16
	bl	UTIL_CalcFrameSize
	ldr	w2, [x20, 32]
	ldr	w1, [x20, 328]
	mul	w1, w1, w2
	mul	w0, w1, w0
	add	x1, x29, 152
	umull	x21, w0, w21
	ldr	x0, [x20, 176]
	lsr	x21, x21, 32
	lsr	w21, w21, 6
	bl	RBUF_QueryInfo
	ldr	w0, [x29, 184]
	ldr	w1, [x29, 160]
	cmp	w21, w0
	ldr	w2, [x29, 168]
	csel	w21, w21, w0, ls
	add	w0, w1, w21
	cmp	w2, w0
	bhi	.L357
	sub	w0, w1, w2
	add	w0, w0, w21
.L357:
	mov	w1, 1
	str	w0, [x20, 336]
	str	w1, [x20, 332]
	b	.L251
.L367:
	str	wzr, [x20, 332]
	b	.L257
.L369:
	udiv	w0, w21, w0
	ldr	w2, [x20, 112]
	ldp	w3, w4, [x20, 104]
	sub	w28, w0, w1
	mov	w1, w2
	ldr	x0, [x20, 192]
	bl	LSRC_UpdateChange
	ldr	w1, [x20, 272]
	ldr	x0, [x20, 192]
	bl	LSRC_SetSpeedAdjust
	ldr	x0, [x20, 192]
	mov	w1, w28
	bl	LSRC_GetMinInputNum
	ldr	x2, [x20, 200]
	cbz	x2, .L263
	mov	w1, w0
	mov	x0, x2
	bl	ResamplerGetMinInputNum
.L263:
	and	w1, w0, 3
	cbz	w1, .L264
	and	w0, w0, -4
	add	w0, w0, 4
.L264:
	ldr	w28, [x20, 300]
	mul	w28, w0, w28
	b	.L261
.L370:
	ldp	w28, w21, [x20, 104]
	ldr	w0, [x29, 140]
	cmp	w21, w0
	beq	.L268
	bls	.L269
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w21
	bl	UTIL_UpmixPcmData
.L268:
	ldr	w0, [x29, 136]
	cmp	w28, w0
	beq	.L270
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w28
	bl	UTIL_UnifyBitDepthPcmData
.L270:
	ldr	x0, [x20, 200]
	cbz	x0, .L271
	ldr	w21, [x20, 112]
	bl	AOE_GetWKBuf
	ldr	w3, [x29, 132]
	mov	x2, x0
	mov	x28, x0
	ldr	w4, [x29, 144]
	ldr	x1, [x29, 120]
	mov	w6, 1
	ldr	x0, [x20, 200]
	mov	w5, w21
	bl	ResamplerProcessFrame
	str	w0, [x29, 132]
	ldr	w1, [x29, 136]
	ldr	w0, [x29, 140]
	str	x28, [x29, 120]
	str	w21, [x29, 144]
	bl	UTIL_CalcFrameSize
	ldr	w1, [x29, 132]
	mul	w0, w1, w0
	str	w0, [x29, 128]
.L271:
	ldr	x0, [x20, 192]
	cbz	x0, .L273
	ldr	w1, [x20, 304]
	ldr	x21, [x25, x1, lsl 3]
	bl	LSRC_CheckDoSRC
	cbz	w0, .L273
	ldr	w3, [x29, 132]
	str	w3, [x29, 108]
	bl	AOE_GetWKBuf
	mov	x2, x0
	mov	x28, x0
	ldr	w3, [x29, 108]
	ldr	x1, [x29, 120]
	ldr	x0, [x20, 192]
	bl	LSRC_ProcessFrame
	str	w0, [x29, 132]
	ldr	w1, [x29, 136]
	ldr	w0, [x29, 140]
	str	x28, [x29, 120]
	bl	UTIL_CalcFrameSize
	ldr	w1, [x29, 132]
	mul	w0, w1, w0
	str	w0, [x29, 128]
	ldr	w0, [x21, 80]
	add	w0, w0, 1
	str	w0, [x21, 80]
.L273:
	ldr	w0, [x20, 256]
	cmp	w0, 1
	beq	.L378
.L275:
	add	x1, x29, 120
	mov	x0, x20
	bl	AIPGainPcmData
	ldr	w1, [x20, 252]
	sub	w0, w1, #1
	cmp	w0, 6
	bls	.L379
.L276:
	ldr	x0, [x20, 208]
	cbz	x0, .L267
	ldr	w1, [x20, 320]
	cbnz	w1, .L380
	mov	w2, 8
	mov	w1, 0
	bl	FADE_Active
	b	.L267
.L372:
	ldr	x0, [x20, 184]
	sub	w28, w28, w2
	ldr	x1, [x20, 280]
	bl	RBUF_WriteData
	b	.L280
.L371:
	ldr	w2, [x29, 128]
	mov	w1, 0
	ldr	x3, [x27, 40]
	ldr	x0, [x29, 120]
	blr	x3
	b	.L279
.L269:
	bl	AOE_GetWKBuf
	mov	x1, x0
	add	x2, x29, 120
	mov	w0, w21
	bl	UTIL_DownmixPcmData
	b	.L268
.L380:
	ldp	w2, w3, [x29, 136]
	ldr	w1, [x29, 144]
	bl	FADE_Flush
	ldr	w2, [x29, 132]
	ldr	x0, [x20, 208]
	ldr	x1, [x29, 120]
	bl	FADE_InProcess
	b	.L267
.L377:
	ldr	x0, .LC19
	mov	w1, 0
	ldr	w2, [x29, 128]
	ldr	x3, [x0, 40]
	ldr	x0, [x29, 120]
	blr	x3
	b	.L256
.L376:
	ldr	w2, [x20, 104]
	add	x0, x29, 120
	bl	UTIL_ChannelModeProcess
	b	.L255
.L375:
	add	x1, x20, 340
	add	x0, x29, 120
	bl	UTIL_DRE_16BIT_Process
	b	.L254
.L379:
	ldr	w2, [x20, 104]
	add	x0, x29, 120
	bl	UTIL_ChannelModeProcess
	b	.L276
.L378:
	add	x1, x20, 340
	add	x0, x29, 120
	bl	UTIL_DRE_16BIT_Process
	b	.L275
	.size	AIP_Process, .-AIP_Process
	.align	3
.LC17:
	.xword	.LANCHOR0
	.align	3
.LC18:
	.xword	.L221
	.align	3
.LC19:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetChnStatus
	.type	AIP_GetChnStatus, %function
AIP_GetChnStatus:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC20
	add	x20, x0, x20, uxtw 3
	ldr	x0, [x20, 64]
	cbz	x0, .L384
	ldr	w1, [x0, 216]
	str	w1, [x19]
	ldr	w1, [x0, 4]
	str	w1, [x19, 4]
	ldr	w1, [x0]
	str	w1, [x19, 8]
	ldr	w1, [x0, 396]
	str	w1, [x19, 12]
	ldr	w0, [x0, 312]
	str	w0, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L384:
	str	wzr, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_GetChnStatus, .-AIP_GetChnStatus
	.align	3
.LC20:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_CheckDataStatusStop
	.type	AIP_CheckDataStatusStop, %function
AIP_CheckDataStatusStop:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC21
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L387
	ldr	w0, [x0, 20]
	ldr	x19, [sp, 16]
	cmp	w0, 2
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L387:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_CheckDataStatusStop, .-AIP_CheckDataStatusStop
	.align	3
.LC21:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryFiFoInfo
	.type	AIP_QueryFiFoInfo, %function
AIP_QueryFiFoInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC22
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L392
	ldr	w1, [x0, 312]
	cbz	w1, .L393
	ldr	w1, [x0, 216]
	cmp	w1, 1
	beq	.L394
.L392:
	ldr	x3, .LC23
	mov	x2, 40
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 40]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L393:
	ldr	x0, [x0, 184]
	mov	x1, x20
	bl	RBUF_QueryInfo
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L394:
	ldr	x0, [x0, 176]
	mov	x1, x20
	bl	RBUF_QueryInfo
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryFiFoInfo, .-AIP_QueryFiFoInfo
	.align	3
.LC22:
	.xword	.LANCHOR0
	.align	3
.LC23:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryFiFoBusy
	.type	AIP_QueryFiFoBusy, %function
AIP_QueryFiFoBusy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC24
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L398
	ldr	w1, [x0, 312]
	cbz	w1, .L399
	ldr	x0, [x0, 176]
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L399:
	ldr	x0, [x0, 184]
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L398:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryFiFoBusy, .-AIP_QueryFiFoBusy
	.align	3
.LC24:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_QueryBusy
	.type	AIP_QueryBusy, %function
AIP_QueryBusy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC25
	add	x19, x0, x19, uxtw 3
	ldr	x1, [x19, 64]
	cbz	x1, .L403
	ldr	x2, [x1, 176]
	cbz	x2, .L403
	ldr	w1, [x1, 20]
	mov	w0, 0
	cmp	w1, 1
	beq	.L405
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L403:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L405:
	mov	x0, x2
	bl	RBUF_QueryBusy
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_QueryBusy, .-AIP_QueryBusy
	.align	3
.LC25:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_ReadDataComplete
	.type	AIP_ReadDataComplete, %function
AIP_ReadDataComplete:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x2, .LC26
	add	x0, x2, x20, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L406
	ldr	w0, [x19, 312]
	cbz	w0, .L412
	ldr	x0, [x19, 176]
	mov	w1, w21
	bl	RBUF_ReadDataComplete
.L406:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L412:
	ldr	x0, [x19, 184]
	mov	w1, w21
	ldr	x20, [x2, w20, uxtw 3]
	bl	RBUF_ReadDataComplete
	ldr	x0, [x19, 184]
	bl	RBUF_QueryBusy
	ldr	w2, [x19, 112]
	ldr	w1, [x19, 296]
	bl	UTIL_LatencyMs
	ldr	w2, [x20, 4]
	mov	x1, x20
	bfi	w2, w0, 17, 7
	mov	x0, x19
	str	w2, [x20, 4]
	bl	AIPUpdateTrackLatency
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AIP_ReadDataComplete, .-AIP_ReadDataComplete
	.align	3
.LC26:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_UnderFlowCalc
	.type	AIP_UnderFlowCalc, %function
AIP_UnderFlowCalc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC27
	ldr	x1, [x0, w19, uxtw 3]
	cbz	x1, .L413
	ldr	w0, [x1, 64]
	ldr	w2, [x1, 64]
	lsr	w0, w0, 16
	add	w0, w0, 1
	uxth	w0, w0
	bfi	w2, w0, 16, 16
	str	w2, [x1, 64]
.L413:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_UnderFlowCalc, .-AIP_UnderFlowCalc
	.align	3
.LC27:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetRingIn
	.type	AIP_GetRingIn, %function
AIP_GetRingIn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC28
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L420
	ldr	x0, [x0, 176]
.L419:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L420:
	mov	x0, 0
	b	.L419
	.size	AIP_GetRingIn, .-AIP_GetRingIn
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_MuteRawData
	.type	AIP_MuteRawData, %function
AIP_MuteRawData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC29
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L421
	ldr	x0, [x0, 176]
	cbz	x0, .L421
	mov	w1, w20
	bl	RBUF_MuteRawData
.L421:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_MuteRawData, .-AIP_MuteRawData
	.align	3
.LC29:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_GetMuteStatus
	.type	AIP_GetMuteStatus, %function
AIP_GetMuteStatus:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC30
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L431
	ldr	w0, [x0, 248]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L431:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_GetMuteStatus, .-AIP_GetMuteStatus
	.align	3
.LC30:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_ContinueOutputCnt
	.type	AIP_ContinueOutputCnt, %function
AIP_ContinueOutputCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC31
	ldr	x0, [x0, w19, uxtw 3]
	cbz	x0, .L432
	ldr	w1, [x0, 88]
	add	w1, w1, 1
	str	w1, [x0, 88]
.L432:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AIP_ContinueOutputCnt, .-AIP_ContinueOutputCnt
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_ContinueOutput
	.type	AIP_ContinueOutput, %function
AIP_ContinueOutput:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	x20, .LC32
	add	x0, x20, x21, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L437
	ldr	w0, [x19, 36]
	cbz	w0, .L440
	cmp	w22, 1
	beq	.L462
	ldr	w0, [x19, 20]
	cmp	w0, 1
	beq	.L463
.L437:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L440:
	ldr	w0, [x19, 392]
	cmp	w0, 4
	bhi	.L445
	ldr	w0, [x19, 216]
	cmp	w0, 1
	beq	.L437
.L445:
	ldr	w0, [x19, 20]
	and	w1, w0, -3
	cmp	w1, 1
	bne	.L437
	cmp	w0, 1
	beq	.L464
.L446:
	cmp	w22, 1
	bne	.L437
	ldr	w2, [x19, 396]
	mov	x1, 0
	ldr	x0, [x19, 184]
	bl	RBUF_WriteData
	ldr	x0, [x20, w21, uxtw 3]
	cbz	x0, .L437
	ldr	w1, [x0, 88]
	add	w1, w1, 1
	str	w1, [x0, 88]
	b	.L437
	.p2align 3
.L463:
	mov	w0, 2
	cbnz	w22, .L447
	str	w0, [x19, 20]
.L465:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L462:
	ldr	x0, [x20, w21, uxtw 3]
	cbz	x0, .L442
	ldr	w1, [x0, 88]
	add	w1, w1, 1
	str	w1, [x0, 88]
.L442:
	ldr	w0, [x19, 20]
	cmp	w0, 1
	bne	.L437
.L447:
	mov	w0, 3
	str	w0, [x19, 20]
	b	.L465
	.p2align 3
.L464:
	mov	w1, 3
	mov	x0, x19
	str	w1, [x19, 20]
	bl	AIPReclaimFifo
	mov	x0, x19
	bl	AIPFlushChnCtx
	cbnz	w22, .L446
	str	wzr, [x19, 392]
	b	.L437
	.size	AIP_ContinueOutput, .-AIP_ContinueOutput
	.align	3
.LC32:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AIP_RegReclaimFun
	.type	AIP_RegReclaimFun, %function
AIP_RegReclaimFun:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	cmp	w19, 7
	bhi	.L469
	ldr	x0, .LC33
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L469
	str	w21, [x0, 380]
	str	x20, [x0, 384]
	mov	w0, 0
.L467:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L469:
	mov	w0, -1
	b	.L467
	.size	AIP_RegReclaimFun, .-AIP_RegReclaimFun
	.align	3
.LC33:
	.xword	.LANCHOR0
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stAipRm, %object
	.size	g_stAipRm, 128
g_stAipRm:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
