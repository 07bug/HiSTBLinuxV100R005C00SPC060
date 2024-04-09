#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_engine.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	ENGINECheckAipData, %function
ENGINECheckAipData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w1, w3, [x19, 32]
	ldr	w5, [x19, 40]
	cmp	w1, wzr
	ccmp	w3, wzr, 4, ne
	beq	.L2
	mov	w0, 0
	cbz	w1, .L3
	uxtw	x4, w1
	uxtw	x7, w5
	mov	w1, 0
	.p2align 2
.L5:
	asr	x2, x4, x1
	asr	x6, x7, x1
	tbz	x2, 0, .L7
	tbz	x6, 0, .L25
	orr	w0, w0, 1
.L7:
	add	w1, w1, 1
	cmp	w1, 8
	bne	.L5
.L3:
	cbz	w3, .L8
.L26:
	uxtw	x3, w3
	mov	w1, 0
	uxtw	x5, w5
	.p2align 2
.L11:
	asr	x2, x3, x1
	asr	x4, x5, x1
	tbz	x2, 0, .L9
	tbz	x4, 0, .L10
	orr	w0, w0, 2
.L9:
	add	w1, w1, 1
	cmp	w1, 8
	bne	.L11
.L8:
	and	w0, w0, 1
.L12:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2:
	mov	w0, 1
	cbnz	w5, .L12
	ldr	w0, [x19, 176]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L10:
	and	w0, w0, -3
	b	.L8
	.p2align 3
.L25:
	and	w0, w0, -2
	cbz	w3, .L8
	b	.L26
	.size	ENGINECheckAipData, .-ENGINECheckAipData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEDestroyChn, %function
ENGINEDestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L27
	ldr	w0, [x19, 12]
	cbz	w0, .L36
.L29:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L27:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L36:
	ldr	x1, [x19, 112]
	cbz	x1, .L29
	mov	w0, 26
	bl	HI_ADSP_FREE
	str	xzr, [x19, 112]
	b	.L29
	.size	ENGINEDestroyChn, .-ENGINEDestroyChn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEOutRawFrame, %function
ENGINEOutRawFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w22, w2
	bl	_mcount
	mov	w0, w19
	bl	AIP_GetRingIn
	mov	x20, x0
	mov	w0, w21
	bl	AOP_GetRingOut
	mov	x21, x0
	mov	w0, w19
	bl	AIP_GetMuteStatus
	cmp	w0, 1
	beq	.L43
.L38:
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L37
	mov	w3, 3
	mov	w2, w22
	mov	x1, x21
	mov	x0, x20
	bl	RBUF_CopyData
.L37:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L43:
	mov	w1, w22
	mov	w0, w19
	bl	AIP_MuteRawData
	b	.L38
	.size	ENGINEOutRawFrame, .-ENGINEOutRawFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEMixData, %function
ENGINEMixData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x23, x2
	bl	_mcount
	str	xzr, [x29, 104]
	add	x0, x29, 72
	add	x2, x29, 88
	mov	x1, x0
	ldp	w24, w22, [x19]
	stp	xzr, xzr, [x0]
	mov	w0, w20
	stp	xzr, xzr, [x2]
	bl	AIP_QueryFiFoInfo
	ldr	w2, [x19, 84]
	ldr	w0, [x29, 96]
	cmp	w0, w2
	bcc	.L44
	ldr	w21, [x29, 92]
	cmp	w21, w2
	bcc	.L48
	ldr	w5, [x19, 88]
	mov	w3, w24
	ldr	w1, [x29, 80]
	mov	x0, x23
	ldr	x4, [x29, 72]
	udiv	w2, w2, w5
	add	x1, x4, x1
	mul	w2, w2, w22
	bl	UTIL_MixerPro
.L47:
	ldr	w1, [x19, 84]
	mov	w0, w20
	bl	AIP_ReadDataComplete
.L44:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L48:
	ldr	w2, [x19, 88]
	mov	w3, w24
	ldr	w0, [x29, 80]
	ldr	x1, [x29, 72]
	udiv	w2, w21, w2
	add	x1, x1, x0
	mov	x0, x23
	mul	w2, w2, w22
	bl	UTIL_MixerPro
	ldp	w2, w4, [x19, 84]
	ldr	x1, [x29, 72]
	mov	w3, w24
	sub	w2, w2, w21
	add	x0, x23, x21, uxtw
	udiv	w2, w2, w4
	mul	w2, w2, w22
	bl	UTIL_MixerPro
	b	.L47
	.size	ENGINEMixData, .-ENGINEMixData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINECheckAopSpace.isra.0, %function
ENGINECheckAopSpace.isra.0:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	uxtw	x19, w2
	mov	w20, w1
	bl	_mcount
	mov	w0, 0
	cbz	w19, .L71
	cbz	w21, .L51
	uxtw	x5, w21
	mov	w3, 0
	uxtw	x2, w19
	.p2align 2
.L53:
	asr	x4, x5, x3
	asr	x1, x2, x3
	tbz	x4, 0, .L55
	tbz	x1, 0, .L73
	orr	w0, w0, 1
.L55:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L53
.L51:
	cbz	w20, .L56
.L75:
	uxtw	x1, w20
	mov	w3, 0
	.p2align 2
.L60:
	asr	x4, x1, x3
	asr	x2, x19, x3
	tbz	x4, 0, .L57
	tbz	x2, 0, .L58
	orr	w0, w0, 2
.L57:
	add	w3, w3, 1
	cmp	w3, 8
	bne	.L60
.L59:
	cbnz	w21, .L61
	and	w0, w0, 2
.L71:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L56:
	cbz	w21, .L74
.L61:
	and	w0, w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L74:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L58:
	and	w0, w0, -3
	b	.L59
	.p2align 3
.L73:
	and	w0, w0, -2
	cbz	w20, .L56
	b	.L75
	.size	ENGINECheckAopSpace.isra.0, .-ENGINECheckAopSpace.isra.0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINECreateChn, %function
ENGINECreateChn:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC1
	ldr	x3, .LC0
	mov	w1, 0
	mov	x2, 28
	add	x0, x29, 64
	ldr	x19, [x3, w21, uxtw 3]
	ldr	x3, [x20, 40]
	blr	x3
	ldr	w1, [x19]
	add	x0, x29, 64
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L94
	ldr	w1, [x19]
	add	x0, x29, 68
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L94
	ldr	w1, [x19]
	add	x0, x29, 72
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L94
	ldr	w1, [x19]
	add	x0, x29, 76
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L94
	mov	w1, 216
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L94
	ldr	x3, [x20, 40]
	mov	x2, 216
	mov	w1, 0
	blr	x3
	ldr	x3, [x20, 48]
	mov	x2, 28
	add	x1, x29, 64
	mov	x0, x19
	blr	x3
	ldp	w1, w0, [x19]
	bl	UTIL_CalcFrameSize
	ldr	w3, [x19, 8]
	mov	w2, 48000
	mov	w1, 19923
	mov	w4, 60928
	cmp	w3, w2
	movk	w1, 0x1062, lsl 16
	add	w2, w3, w3, lsl 2
	movk	w4, 0x2, lsl 16
	ccmp	w3, w4, 4, ne
	umull	x1, w2, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	beq	.L95
	and	w2, w1, 3
	cbz	w2, .L80
	and	w1, w1, -4
	add	w1, w1, 4
.L80:
	mul	w2, w0, w1
	ldp	w1, w0, [x19]
	str	w2, [x19, 84]
	bl	UTIL_CalcFrameSize
	str	w0, [x19, 88]
	ldr	w2, [x19, 84]
	ldr	w1, [x19, 12]
	udiv	w0, w2, w0
	str	w0, [x19, 16]
	cbz	w1, .L96
.L81:
	str	w21, [x19, 80]
	mov	w0, 1
	str	w0, [x19, 92]
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L95:
	and	w2, w1, 255
	cbz	w2, .L80
	and	w1, w1, -256
	add	w1, w1, 256
	b	.L80
.L82:
	mov	x0, x19
	bl	ENGINEDestroyChn
.L94:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	x0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L96:
	ldp	w5, w6, [x19]
	ldr	w4, [x19, 8]
	add	x22, x19, 112
	ldr	x3, [x20, 48]
	mov	x1, x22
	stp	w2, w0, [x19, 120]
	stp	w5, w6, [x19, 128]
	stp	w4, wzr, [x19, 136]
	mov	x2, 32
	str	xzr, [x19, 112]
	add	x0, x19, 144
	blr	x3
	ldr	x3, [x20, 48]
	mov	x1, x22
	mov	x2, 32
	add	x0, x19, 184
	blr	x3
	ldr	w22, [x19, 152]
	ldr	w1, [x19, 120]
	mov	w0, 26
	add	w22, w22, w1, lsl 1
	mov	w1, w22
	bl	HI_ADSP_MALLOC
	mov	x23, x0
	cbz	x0, .L82
	ldr	x3, [x20, 40]
	mov	w1, 0
	uxtw	x2, w22
	blr	x3
	str	x23, [x19, 112]
	ldr	w0, [x19, 120]
	ubfiz	x1, x0, 1, 31
	add	x0, x23, x0, uxtw
	add	x23, x23, x1
	str	x0, [x19, 184]
	str	x23, [x19, 144]
	b	.L81
	.size	ENGINECreateChn, .-ENGINECreateChn
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC1:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ENGINEReclaimIn, %function
ENGINEReclaimIn:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	w19, 5
	bhi	.L100
	ldr	x0, .LC2
	cmp	x20, xzr
	add	x19, x0, x19, uxtw 3
	ldr	x19, [x19, 48]
	ccmp	x19, xzr, 4, ne
	beq	.L100
	ldr	w1, [x19, 84]
	mov	w0, 0
	cmp	w21, w1
	beq	.L102
.L98:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L100:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L102:
	ldr	w2, [x19, 88]
	mov	x1, x20
	ldp	w3, w4, [x19]
	ldr	x0, [x19, 184]
	udiv	w2, w21, w2
	mul	w2, w2, w4
	bl	UTIL_MixerPro
	mov	w1, 7
	mov	w0, w21
	str	w1, [x19, 176]
	b	.L98
	.size	ENGINEReclaimIn, .-ENGINEReclaimIn
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_Process
	.type	ENGINE_Process, %function
ENGINE_Process:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x19, .LC6
	ldr	x25, .LC7
	.p2align 2
.L177:
	ldr	x1, [x19]
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L104
	ldr	w0, [x1, 4]
	ands	w0, w0, 3
	beq	.L106
	cmp	w0, 1
	beq	.L107
	ldr	w0, [x1, 4]
	mov	w2, 4
	bfi	w0, w2, 3, 4
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, w2
	str	w0, [x1, 4]
.L104:
	ldr	x28, [x19, 48]
.L115:
	cbz	x28, .L118
.L111:
	ldr	w0, [x28, 92]
	cmp	w0, 1
	beq	.L262
.L118:
	add	w20, w20, 1
	add	x19, x19, 8
	cmp	w20, 6
	bne	.L177
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L107:
	ldr	x28, [x19, 48]
	cbz	x28, .L118
	ldr	w0, [x28, 92]
	cmp	w0, 1
	beq	.L263
.L116:
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L111
	ldr	w0, [x1, 4]
	and	w0, w0, -121
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, 4
	str	w0, [x1, 4]
	ldr	w0, [x28, 92]
	cmp	w0, 1
	bne	.L118
	.p2align 2
.L262:
	ldr	w0, [x28]
	mov	w23, 0
	str	w0, [x29, 112]
	mov	w24, 0
	ldr	w0, [x28, 4]
	mov	w27, 0
	str	w0, [x29, 100]
	ldr	x21, [x19]
	ldr	w0, [x28, 16]
	str	w0, [x29, 108]
	ldr	w22, [x21, 12]
	stp	wzr, wzr, [x29, 116]
	str	wzr, [x29, 124]
	uxth	w22, w22
	uxth	x26, w22
	b	.L125
	.p2align 3
.L120:
	add	w27, w27, 1
	cmp	w27, 8
	beq	.L264
.L125:
	asr	x0, x26, x27
	tbz	x0, 0, .L120
	mov	w0, w27
	add	x1, x29, 168
	bl	AOP_GetChnStatus
	ldr	w0, [x29, 168]
	cmp	w0, 1
	bne	.L120
	ldr	w0, [x29, 172]
	cmp	w0, 1
	mov	x0, 1
	lsl	x5, x0, x27
	beq	.L265
	ldr	w0, [x29, 124]
	orr	w0, w0, w5
	str	w0, [x29, 124]
.L122:
	ldr	w1, [x29, 112]
	ldr	w0, [x29, 176]
	cmp	w1, w0
	beq	.L266
.L123:
	orr	w24, w24, w5
.L124:
	ldr	w0, [x29, 108]
	ldr	w1, [x29, 184]
	str	w5, [x29, 104]
	mul	w1, w0, w1
	mov	w0, w27
	add	w27, w27, 1
	bl	AOP_QueryRbfFree
	cmp	w0, wzr
	ldr	w5, [x29, 104]
	orr	w5, w23, w5
	csel	w23, w5, w23, ne
	cmp	w27, 8
	bne	.L125
	.p2align 2
.L264:
	ldr	w0, [x29, 120]
	str	w0, [x28, 48]
	ldr	w0, [x29, 124]
	str	w0, [x28, 52]
	ldr	w0, [x29, 116]
	stp	wzr, w22, [x28, 40]
	stp	wzr, wzr, [x28, 32]
	stp	w24, w23, [x28, 60]
	str	w0, [x28, 56]
	mov	w22, 0
	ldr	w0, [x21, 8]
	uxth	w0, w0
	str	w0, [x28, 28]
	b	.L137
	.p2align 3
.L126:
	add	w22, w22, 1
	cmp	w22, 8
	beq	.L136
.L268:
	ldr	w0, [x28, 28]
.L137:
	uxtw	x0, w0
	asr	x0, x0, x22
	tbz	x0, 0, .L126
	mov	w0, w22
	add	x1, x29, 136
	bl	AIP_GetChnStatus
	ldr	w0, [x29, 136]
	cmp	w0, 1
	beq	.L267
.L128:
	ldr	w1, [x28, 80]
	mov	w0, w22
	mov	x2, x25
	add	w22, w22, 1
	bl	AIP_RegReclaimFun
	cmp	w22, 8
	bne	.L268
.L136:
	ldr	w0, [x21, 4]
	ubfx	x0, x0, 13, 1
	str	w0, [x28, 72]
	ldr	w0, [x21, 4]
	ubfx	x0, x0, 14, 1
	str	w0, [x28, 76]
	ldr	x22, [x19, 48]
	ldr	w0, [x22, 44]
	uxtw	x1, w0
	tbnz	x0, 0, .L187
	mov	w21, 1
	.p2align 2
.L140:
	asr	x0, x1, x21
	tbnz	x0, 0, .L139
	add	w21, w21, 1
	cmp	w21, 8
	bne	.L140
.L148:
	ldr	w0, [x22, 12]
	cbnz	w0, .L269
	ldp	w0, w1, [x22, 48]
	ldr	w2, [x22, 64]
	bl	ENGINECheckAopSpace.isra.0
	cbz	w0, .L118
	mov	x0, x22
	bl	ENGINECheckAipData
	cbz	w0, .L118
	mov	w0, 5
	str	w0, [x29, 168]
	ldr	x0, .LC8
	mov	w1, 0
	ldr	w2, [x22, 120]
	ldr	x3, [x0, 40]
	ldr	x0, [x22, 112]
	blr	x3
	ldr	w0, [x22, 176]
	cbz	w0, .L154
	cmp	w0, 7
	ldr	x0, [x22, 112]
	beq	.L270
	ldr	x1, .LC8
	ldr	w2, [x22, 84]
	ldr	x3, [x1, 40]
	mov	w1, 0
	blr	x3
.L156:
	ldr	w0, [x22, 176]
	sub	w0, w0, #1
	str	w0, [x22, 176]
.L154:
	mov	w21, 0
	b	.L160
	.p2align 3
.L158:
	add	w21, w21, 1
	cmp	w21, 8
	beq	.L271
.L160:
	ldr	w0, [x22, 28]
	asr	x0, x0, x21
	tbz	x0, 0, .L158
	mov	w0, w21
	add	x1, x29, 168
	bl	AIP_GetPcmType
	ldr	w0, [x29, 168]
	cmp	w0, 1
	bhi	.L158
	ldr	x2, [x22, 112]
	mov	w1, w21
	mov	x0, x22
	bl	ENGINEMixData
	b	.L158
	.p2align 3
.L106:
	ldr	x0, [x19, 48]
	cbz	x0, .L272
	ldr	w2, [x0, 92]
	cbz	w2, .L273
.L113:
	mov	w2, 1
	str	w2, [x0, 92]
	ldr	w2, [x1, 4]
	tbnz	x2, 2, .L185
	mov	x3, x0
.L112:
	ldr	w0, [x1, 4]
	mov	x28, x3
	and	w0, w0, -121
	str	w0, [x1, 4]
	ldr	w0, [x1, 4]
	orr	w0, w0, 4
	str	w0, [x1, 4]
	b	.L115
	.p2align 3
.L267:
	ldr	w0, [x29, 140]
	cmp	w0, 1
	beq	.L274
	ldr	w1, [x28, 36]
	mov	x0, 1
	lsl	x0, x0, x22
	orr	w0, w1, w0
	str	w0, [x28, 36]
.L130:
	ldr	w0, [x28, 12]
	cbz	w0, .L131
	ldr	w23, [x28, 84]
	mov	w0, w22
	bl	AIP_QueryBusy
	cmp	w23, w0
	bhi	.L128
	cbz	w23, .L128
.L276:
	ldr	w1, [x28, 40]
	mov	x0, 1
	lsl	x0, x0, x22
	orr	w0, w1, w0
	str	w0, [x28, 40]
	b	.L128
	.p2align 3
.L131:
	mov	w0, w22
	add	x1, x29, 168
	bl	AIP_GetChnStatus
	ldr	w23, [x28, 120]
	ldr	w0, [x29, 168]
	cmp	w0, 1
	beq	.L275
	mov	w0, w22
	bl	AIP_QueryFiFoBusy
	cmp	w0, w23
	bcc	.L128
.L278:
	cbnz	w23, .L276
	b	.L128
	.p2align 3
.L185:
	mov	x28, x0
	b	.L115
	.p2align 3
.L266:
	ldr	w1, [x29, 100]
	ldr	w0, [x29, 180]
	cmp	w1, w0
	bne	.L123
	ldr	w0, [x29, 116]
	orr	w0, w0, w5
	str	w0, [x29, 116]
	b	.L124
	.p2align 3
.L273:
	bl	ENGINEDestroyChn
	mov	w0, w20
	bl	ENGINECreateChn
	str	x0, [x19, 48]
	cbz	x0, .L114
	ldr	x1, [x19]
	b	.L113
	.p2align 3
.L269:
	ldr	w0, [x22, 44]
	uxtw	x1, w0
	tbnz	x0, 0, .L178
	mov	w21, 1
	.p2align 2
.L150:
	asr	x0, x1, x21
	tbnz	x0, 0, .L149
	add	w21, w21, 1
	cmp	w21, 8
	bne	.L150
	ldr	w0, [x22, 28]
	uxtw	x1, w0
	tbnz	x0, 0, .L118
	mov	w2, 1
.L182:
	mov	w23, 1
	b	.L153
	.p2align 3
.L151:
	add	w23, w23, 1
	cmp	w23, 8
	beq	.L118
.L153:
	asr	x0, x1, x23
	tbz	x0, 0, .L151
	cmp	w23, 8
	cset	w0, eq
.L152:
	orr	w2, w0, w2
	cbnz	w2, .L118
.L183:
	ldp	w0, w1, [x22, 48]
	ldr	w2, [x22, 64]
	bl	ENGINECheckAopSpace.isra.0
	cbz	w0, .L118
	mov	x0, x22
	bl	ENGINECheckAipData
	cbz	w0, .L118
	ldr	w2, [x22, 84]
	mov	w0, w23
	mov	w1, w21
	bl	ENGINEOutRawFrame
	mov	w0, w21
	bl	AOP_ProcDelayCompensation
	b	.L118
	.p2align 3
.L263:
	str	wzr, [x28, 92]
	b	.L116
	.p2align 3
.L139:
	cmp	w21, 8
	beq	.L148
.L138:
	mov	w0, w21
	add	x1, x29, 168
	bl	AOP_GetChnStatus
	ldr	w0, [x29, 200]
	cmp	w0, 4
	bhi	.L148
	mov	w23, 0
	b	.L147
	.p2align 3
.L143:
	add	w23, w23, 1
	cmp	w23, 8
	beq	.L148
.L147:
	ldr	w0, [x22, 28]
	asr	x0, x0, x23
	tbz	x0, 0, .L143
	ldr	w0, [x22, 40]
	asr	x0, x0, x23
	tbnz	x0, 0, .L143
	mov	w0, w23
	bl	AIP_CheckDataStatusStop
	cmp	w0, 1
	beq	.L143
	mov	w0, w23
	add	x1, x29, 136
	bl	AIP_GetChnStatus
	ldr	w0, [x29, 136]
	sub	w0, w0, #1
	cmp	w0, 1
	bhi	.L143
	ldr	w1, [x22, 72]
	mov	w0, w23
	bl	AIP_ContinueOutput
	ldr	w0, [x22, 12]
	cbnz	w0, .L277
	ldr	w0, [x22, 72]
	cbz	w0, .L143
	mov	w0, w23
	bl	AIP_QueryFiFoBusy
	ldr	w1, [x22, 84]
	cmp	w0, w1
	bcc	.L143
	ldr	w1, [x22, 40]
	mov	x0, 1
	lsl	x0, x0, x23
	orr	w0, w1, w0
	str	w0, [x22, 40]
	b	.L143
	.p2align 3
.L274:
	ldr	w1, [x28, 32]
	mov	x0, 1
	lsl	x0, x0, x22
	orr	w0, w1, w0
	str	w0, [x28, 32]
	b	.L130
	.p2align 3
.L265:
	ldr	w0, [x29, 120]
	orr	w0, w0, w5
	str	w0, [x29, 120]
	b	.L122
	.p2align 3
.L275:
	ldr	w0, [x29, 184]
	cmp	w0, 1
	lsl	w0, w23, 1
	csel	w23, w0, w23, ne
	mov	w0, w22
	bl	AIP_QueryFiFoBusy
	cmp	w0, w23
	bcc	.L128
	b	.L278
	.p2align 3
.L149:
	ldr	w0, [x22, 28]
	cmp	w21, 8
	cset	w2, eq
	uxtw	x1, w0
	tbz	x0, 0, .L182
	mov	w0, 0
	mov	w23, 0
	b	.L152
	.p2align 3
.L272:
	mov	w0, w20
	bl	ENGINECreateChn
	str	x0, [x19, 48]
	mov	x28, x0
	cbz	x0, .L114
	mov	w0, 1
	str	w0, [x28, 92]
	mov	x3, x28
	ldr	x1, [x19]
	ldr	w0, [x1, 4]
	tbnz	x0, 2, .L111
	b	.L112
	.p2align 3
.L114:
	ldr	x0, [x19]
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L118
	ldr	w1, [x0, 4]
	mov	w2, 3
	bfi	w1, w2, 3, 4
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L118
.L187:
	mov	w21, 0
	b	.L138
.L271:
	mov	w0, 5
	str	w0, [x29, 168]
	ldr	w0, [x22, 12]
	cbnz	w0, .L118
	mov	w21, 0
	b	.L164
	.p2align 3
.L162:
	add	w21, w21, 1
	cmp	w21, 8
	beq	.L163
.L164:
	ldr	w0, [x22, 28]
	asr	x0, x0, x21
	tbz	x0, 0, .L162
	mov	w0, w21
	add	x1, x29, 168
	bl	AIP_GetPcmType
	ldr	w0, [x29, 168]
	cmp	w0, 2
	bne	.L162
	ldr	x2, [x22, 112]
	mov	w1, w21
	mov	x0, x22
	bl	ENGINEMixData
.L163:
	ldp	w26, w1, [x22, 48]
	ldr	w0, [x22, 12]
	stp	w26, w1, [x29, 128]
	cbnz	w0, .L118
	mov	x28, 0
	add	x23, x22, 112
	add	x24, x22, 144
.L166:
	cbz	w26, .L176
	uxtw	x26, w26
	mov	w21, 0
	b	.L175
	.p2align 3
.L171:
	add	w21, w21, 1
	cmp	w21, 8
	beq	.L176
.L175:
	asr	x0, x26, x21
	tbz	x0, 0, .L171
	mov	w0, w21
	bl	AOP_WriteBuffProcTryCnt
	mov	w0, w21
	add	x1, x29, 168
	bl	AOP_GetChnStatus
	ldr	w0, [x22, 64]
	asr	x0, x0, x21
	tbz	x0, 0, .L171
	mov	w0, w21
	bl	AOP_WriteBuffProcOKCnt
	ldr	w0, [x22, 68]
	mov	x2, 32
	cbz	w0, .L173
	ldr	w0, [x29, 188]
	cbz	w0, .L279
.L173:
	ldr	x0, .LC8
	mov	x1, x23
	ldr	x3, [x0, 48]
	add	x0, x29, 136
	blr	x3
.L174:
	mov	w0, w21
	add	x1, x29, 136
	bl	AOP_WriteRbfData
	mov	w0, w21
	bl	AOP_ProcDelayCompensation
	b	.L171
	.p2align 3
.L176:
	add	x28, x28, 4
	cmp	x28, 8
	beq	.L118
	add	x0, x29, 128
	ldr	w26, [x28, x0]
	b	.L166
.L270:
	ldp	w1, w2, [x22, 84]
	ldr	w3, [x22]
	udiv	w1, w1, w2
	ldr	w2, [x22, 4]
	mul	w2, w1, w2
	ldr	x1, [x22, 184]
	bl	UTIL_MixerPro
	ldr	x0, .LC8
	mov	w1, 0
	ldr	w2, [x22, 84]
	ldr	x3, [x0, 40]
	ldr	x0, [x22, 184]
	blr	x3
	b	.L156
.L178:
	ldr	w0, [x22, 28]
	mov	w23, 0
	mov	w21, 0
	mov	w2, 0
	uxtw	x1, w0
	tbnz	x0, 0, .L183
	b	.L182
	.p2align 3
.L279:
	ldr	x0, .LC8
	mov	x1, x24
	ldr	x3, [x0, 48]
	add	x0, x29, 136
	blr	x3
	b	.L174
.L277:
	mov	w0, w23
	bl	AIP_QueryBusy
	cbz	w0, .L146
	mov	w2, w0
	mov	w1, w21
	mov	w0, w23
	bl	ENGINEOutRawFrame
.L146:
	ldr	w0, [x22, 72]
	cbz	w0, .L143
	ldr	w3, [x22, 76]
	mov	w0, w21
	ldp	w1, w2, [x29, 144]
	bl	AOP_ContinueOutput
	b	.L143
	.size	ENGINE_Process, .-ENGINE_Process
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC7:
	.xword	ENGINEReclaimIn
	.align	3
.LC8:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_Init
	.type	ENGINE_Init, %function
ENGINE_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w23, 1
	add	x21, x19, 768
	bl	_mcount
	ldr	x20, .LC9
	ldr	x22, .LC10
	add	x20, x20, 48
	.p2align 2
.L281:
	mov	x2, 128
	ldr	x3, [x22, 40]
	str	x19, [x20, -48]
	mov	x0, x19
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	ldr	w0, [x19, -124]
	cmp	x19, x21
	orr	w0, w0, 4
	str	w0, [x19, -124]
	ldr	w0, [x19, -124]
	bfi	w0, w23, 0, 2
	str	w0, [x19, -124]
	str	xzr, [x20], 8
	bne	.L281
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ENGINE_Init, .-ENGINE_Init
	.align	3
.LC9:
	.xword	.LANCHOR0
	.align	3
.LC10:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ENGINE_DeInit
	.type	ENGINE_DeInit, %function
ENGINE_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC11
	add	x19, x20, 48
	add	x20, x20, 96
	.p2align 2
.L284:
	ldr	x0, [x19]
	bl	ENGINEDestroyChn
	str	xzr, [x19], 8
	cmp	x19, x20
	bne	.L284
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ENGINE_DeInit, .-ENGINE_DeInit
	.align	3
.LC11:
	.xword	.LANCHOR0
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stEneRm, %object
	.size	g_stEneRm, 96
g_stEneRm:
	.zero	96
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
