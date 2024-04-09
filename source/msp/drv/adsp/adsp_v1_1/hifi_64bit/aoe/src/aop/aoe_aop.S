#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"aoe_aop.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	AOPFlushChnBuf
	.type	AOPFlushChnBuf, %function
AOPFlushChnBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 136]
	cbz	x0, .L1
	bl	RBUF_Flush
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOPFlushChnBuf, .-AOPFlushChnBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_ProcDelayCompensation
	.type	AOP_ProcDelayCompensation, %function
AOP_ProcDelayCompensation:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC0
	add	x0, x2, x21, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L7
	ldr	w0, [x19, 144]
	cbz	w0, .L7
	ldr	w0, [x19, 156]
	cmp	w0, 1
	beq	.L42
	ldr	w20, [x19, 148]
	cmp	w20, 9
	bhi	.L43
.L7:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L43:
	ldr	x0, [x19, 136]
	add	x1, x29, 56
	ldr	x21, [x2, w21, uxtw 3]
	bl	RBUF_QueryInfo
	ldp	w1, w0, [x19, 48]
	bl	UTIL_CalcFrameSize
	mov	w3, w0
	ldr	w0, [x19, 56]
	mov	w2, 19923
	movk	w2, 0x1062, lsl 16
	mul	w20, w20, w0
	umull	x2, w20, w2
	lsr	x2, x2, 32
	lsr	w2, w2, 6
	and	w0, w2, 3
	cbz	w0, .L15
	and	w2, w2, -4
	add	w2, w2, 4
.L15:
	ldp	w1, w0, [x19, 48]
	mul	w20, w3, w2
	bl	UTIL_CalcFrameSize
	ldr	w3, [x19, 56]
	mov	w1, 19923
	movk	w1, 0x1062, lsl 16
	lsl	w2, w3, 3
	add	w3, w2, w3, lsl 1
	umull	x1, w3, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	and	w2, w1, 3
	cbz	w2, .L16
	and	w1, w1, -4
	add	w1, w1, 4
.L16:
	ldr	w2, [x29, 80]
	cmp	w20, w2
	bcc	.L7
	sub	w2, w20, w2
	madd	w2, w0, w1, w2
	cbz	w2, .L7
	ldr	w3, [x29, 88]
	mov	x1, 0
	ldr	x0, [x19, 136]
	cmp	w2, w3
	csel	w2, w2, w3, ls
	bl	RBUF_WriteData
	ldr	w0, [x21, 100]
	add	w0, w0, 1
	str	w0, [x21, 100]
	b	.L7
	.p2align 3
.L42:
	add	x0, x29, 56
	ldr	x21, [x2, w21, uxtw 3]
	str	xzr, [x29, 88]
	add	x1, x29, 56
	stp	xzr, xzr, [x0]
	add	x0, x29, 72
	stp	xzr, xzr, [x0]
	ldr	w0, [x21, 4]
	orr	w0, w0, 1048576
	str	w0, [x21, 4]
	ldr	x0, [x19, 136]
	bl	RBUF_QueryInfo
	ldr	x0, [x19, 136]
	cbz	x0, .L10
	bl	RBUF_Flush
.L10:
	ldp	w1, w0, [x19, 48]
	ldr	w20, [x19, 152]
	bl	UTIL_CalcFrameSize
	mov	w22, w0
	ldr	w0, [x19, 56]
	mov	w2, 19923
	movk	w2, 0x1062, lsl 16
	mul	w20, w20, w0
	umull	x2, w20, w2
	lsr	x2, x2, 32
	lsr	w2, w2, 6
	and	w0, w2, 3
	cbz	w0, .L11
	and	w2, w2, -4
	add	w2, w2, 4
.L11:
	ldp	w1, w0, [x19, 48]
	mul	w22, w22, w2
	ldr	w20, [x19, 148]
	bl	UTIL_CalcFrameSize
	ldr	w2, [x19, 56]
	mov	w1, 19923
	movk	w1, 0x1062, lsl 16
	mul	w20, w20, w2
	umull	x1, w20, w1
	lsr	x1, x1, 32
	lsr	w1, w1, 6
	and	w2, w1, 3
	cbz	w2, .L12
	and	w1, w1, -4
	add	w1, w1, 4
.L12:
	ldr	w2, [x29, 80]
	mul	w3, w0, w1
	cmp	w22, w2
	bhi	.L13
	sub	w2, w2, w22
	add	w3, w3, w2
.L13:
	ldr	w2, [x29, 88]
	mov	x1, 0
	ldr	x0, [x19, 136]
	cmp	w2, w3
	csel	w2, w2, w3, ls
	bl	RBUF_WriteData
	ldr	w0, [x21, 100]
	add	w0, w0, 1
	str	w0, [x21, 100]
	ldr	w0, [x19, 148]
	stp	w0, wzr, [x19, 152]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	AOP_ProcDelayCompensation, .-AOP_ProcDelayCompensation
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_DestroyChn
	.type	AOP_DestroyChn, %function
AOP_DestroyChn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1
	add	x0, x0, x20, uxtw 3
	ldr	x19, [x0, 64]
	cbz	x19, .L44
	ldr	w0, [x19, 132]
	cmp	w0, 1
	beq	.L50
.L46:
	ldr	x0, [x19, 136]
	bl	RBUF_Destroy
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L44:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L50:
	mov	w0, w20
	bl	CAST_Destroy
	b	.L46
	.size	AOP_DestroyChn, .-AOP_DestroyChn
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_Init
	.type	AOP_Init, %function
AOP_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x23
	add	x22, x23, 1024
	bl	_mcount
	ldr	x20, .LC4
	ldr	x21, .LC5
	add	x20, x20, 64
	.p2align 2
.L52:
	mov	x2, 128
	ldr	x3, [x21, 40]
	str	x19, [x20, -64]
	mov	x0, x19
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	ldr	w0, [x19, -124]
	cmp	x19, x22
	orr	w0, w0, 4
	str	w0, [x19, -124]
	str	xzr, [x20], 8
	bne	.L52
	mov	x0, x23
	bl	CAST_Init
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	AOP_Init, .-AOP_Init
	.align	3
.LC4:
	.xword	.LANCHOR0
	.align	3
.LC5:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_DeInit
	.type	AOP_DeInit, %function
AOP_DeInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x20, .LC6
	add	x20, x20, 64
	.p2align 2
.L55:
	mov	w0, w19
	add	w19, w19, 1
	bl	AOP_DestroyChn
	str	xzr, [x20], 8
	cmp	w19, 8
	bne	.L55
	mov	w0, w19
	bl	CAST_DeInit
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_DeInit, .-AOP_DeInit
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_Process
	.type	AOP_Process, %function
AOP_Process:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	mov	w21, 0
	add	x23, x29, 100
	bl	_mcount
	ldr	x20, .LC7
	ldr	x22, .LC8
	b	.L81
	.p2align 3
.L74:
	add	w21, w21, 1
	add	x20, x20, 8
	cmp	w21, 8
	beq	.L101
.L81:
	ldr	x19, [x20]
	ldr	w0, [x19, 4]
	tbnz	x0, 2, .L82
	ldr	w0, [x19, 4]
	ands	w0, w0, 3
	beq	.L60
	cmp	w0, 1
	beq	.L61
	ldr	w0, [x19, 4]
	mov	w1, 4
	bfi	w0, w1, 3, 4
	str	w0, [x19, 4]
	ldr	w0, [x19, 4]
	orr	w0, w0, w1
	str	w0, [x19, 4]
	.p2align 2
.L82:
	ldr	x19, [x20, 64]
	cbz	x19, .L74
	ldr	w0, [x19, 144]
	str	wzr, [x19, 160]
	cmp	w0, 1
	bne	.L74
	ldr	x24, [x20]
	str	wzr, [x19, 20]
	ldr	w0, [x24, 12]
	uxtb	w0, w0
	str	w0, [x19, 24]
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 8, 8
	str	w0, [x19, 28]
	ldr	w0, [x24, 12]
	tbnz	x0, 19, .L76
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 16, 3
	str	w0, [x19, 32]
	str	w0, [x19, 36]
	ldr	w0, [x24, 12]
	tbnz	x0, 30, .L78
.L103:
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 24, 6
	str	w0, [x19, 40]
.L79:
	ldr	w0, [x24, 12]
	ldr	w1, [x19, 48]
	ubfx	x0, x0, 31, 1
	str	w0, [x19, 44]
	ldr	w0, [x24, 4]
	ubfx	x0, x0, 8, 1
	str	w0, [x19, 128]
	ldr	w0, [x19, 52]
	ldr	w26, [x24]
	ubfx	x26, x26, 20, 12
	str	w26, [x19, 124]
	bl	UTIL_CalcFrameSize
	mov	w1, w0
	ldr	w2, [x19, 56]
	mov	w0, w26
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x19, 120]
	ldr	x0, [x19, 136]
	add	x1, x19, 72
	bl	RBUF_UpdateAttr
	ldr	w0, [x24, 4]
	ldr	w1, [x19, 152]
	ubfx	x0, x0, 21, 9
	str	w0, [x19, 148]
	cmp	w0, w1
	beq	.L80
	mov	w0, 1
	str	w0, [x19, 156]
.L80:
	ldr	x0, [x19, 136]
	add	w21, w21, 1
	add	x20, x20, 8
	bl	RBUF_QueryBusy
	mov	w24, w0
	ldp	w1, w0, [x19, 48]
	bl	UTIL_CalcFrameSize
	mov	w1, w0
	ldr	w2, [x19, 56]
	mov	w0, w24
	bl	UTIL_LatencyMs
	str	w0, [x19, 160]
	cmp	w21, 8
	bne	.L81
.L101:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L61:
	mov	w0, w21
	bl	AOP_DestroyChn
	str	xzr, [x20, 64]
	ldr	x0, [x20]
.L72:
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L74
.L86:
	ldr	w1, [x0, 4]
	and	w1, w1, -121
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L82
	.p2align 3
.L60:
	str	xzr, [x29, 88]
	add	x0, x29, 96
	ldr	w1, [x19]
	and	w1, w1, 3
	bl	AOE_REG_ReadBitDepth
	cbnz	w0, .L65
	ldr	w1, [x19]
	mov	x0, x23
	ubfx	x1, x1, 2, 2
	bl	AOE_REG_ReadChannel
	cbnz	w0, .L65
	ldr	w1, [x19]
	add	x0, x29, 104
	ubfx	x1, x1, 4, 4
	bl	AOE_REG_ReadSampelRate
	cbnz	w0, .L65
	ldr	w1, [x19]
	add	x0, x29, 108
	ubfx	x1, x1, 8, 2
	bl	AOE_REG_ReadDataFormat
	cbnz	w0, .L65
	ldr	w1, [x19]
	add	x0, x29, 84
	ubfx	x1, x1, 20, 12
	bl	AOE_REG_ReadBufLatencyMs
	cbnz	w0, .L65
	ldr	w2, [x19]
	ldp	w1, w0, [x29, 96]
	ubfx	x2, x2, 10, 1
	str	w2, [x29, 112]
	bl	UTIL_CalcFrameSize
	mov	w1, 1
	str	w1, [x29, 120]
	mov	x2, 0
	ldr	w1, [x19, 24]
	ubfx	x1, x1, 24, 1
	str	w1, [x29, 160]
	ldr	w4, [x19, 16]
	ldr	w3, [x19, 20]
	bfi	x2, x4, 0, 32
	bfi	x2, x3, 32, 32
	str	x2, [x29, 128]
	ldr	w2, [x19, 24]
	ubfx	x2, x2, 0, 24
	str	w2, [x29, 136]
	cbz	w1, .L63
	ldr	w2, [x19, 28]
	mov	x1, 0
	bfi	x1, x2, 0, 32
	ldr	w2, [x19, 32]
	bfi	x1, x2, 32, 32
	str	x1, [x29, 144]
	mov	x1, 0
	ldr	w2, [x19, 36]
	bfi	x1, x2, 0, 32
	ldr	w2, [x19, 40]
	bfi	x1, x2, 32, 32
	str	x1, [x29, 152]
.L64:
	ldr	w3, [x29, 84]
	mov	w1, w0
	ldr	w2, [x29, 104]
	str	w0, [x29, 164]
	mov	w0, w3
	str	w3, [x29, 172]
	bl	UTIL_LatencyMs2ByteSize
	str	w0, [x29, 168]
	add	x1, x29, 120
	add	x0, x29, 88
	bl	RBUF_Create
	ldr	x0, [x29, 88]
	cbz	x0, .L65
	mov	w1, 168
	mov	w0, 26
	bl	HI_ADSP_MALLOC
	mov	x19, x0
	cbz	x0, .L66
	ldr	x3, [x22, 40]
	mov	x2, 168
	mov	w1, 0
	add	x24, x0, 48
	blr	x3
	ldr	x3, [x22, 48]
	add	x1, x29, 96
	mov	x2, 80
	mov	x0, x24
	blr	x3
	ldr	x0, [x29, 88]
	str	x0, [x19, 136]
	ldr	x0, [x20]
	ldr	w1, [x0, 4]
	tbnz	x1, 19, .L102
.L67:
	str	wzr, [x19, 132]
.L84:
	mov	w0, 121
	stp	wzr, wzr, [x19, 16]
	stp	wzr, w0, [x19]
	stp	w0, wzr, [x19, 8]
	stp	w0, w0, [x19, 24]
	stp	wzr, wzr, [x19, 32]
	stp	wzr, wzr, [x19, 148]
	mov	w0, 1
	str	w0, [x19, 144]
	str	x19, [x20, 64]
.L69:
	ldr	x0, [x20]
	ldr	w1, [x0, 4]
	tbz	x1, 2, .L86
	b	.L82
.L104:
.L70:
.L71:
	mov	x1, x19
	mov	w0, 26
	bl	HI_ADSP_FREE
.L66:
	ldr	x0, [x29, 88]
	bl	RBUF_Destroy
	.p2align 2
.L65:
	ldr	x0, [x20]
	str	xzr, [x20, 64]
	ldr	w1, [x0, 4]
	tbnz	x1, 2, .L72
	ldr	w1, [x0, 4]
	mov	w2, 1
	bfi	w1, w2, 3, 4
	str	w1, [x0, 4]
	ldr	w1, [x0, 4]
	orr	w1, w1, 4
	str	w1, [x0, 4]
	b	.L69
	.p2align 3
.L63:
	add	x1, x19, 28
	add	x19, x19, 36
	stp	x1, x19, [x29, 144]
	b	.L64
	.p2align 3
.L76:
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 16, 3
	neg	w0, w0
	str	w0, [x19, 32]
	str	w0, [x19, 36]
	ldr	w0, [x24, 12]
	tbz	x0, 30, .L103
.L78:
	ldr	w0, [x24, 12]
	ubfx	x0, x0, 24, 6
	neg	w0, w0
	str	w0, [x19, 40]
	b	.L79
	.p2align 3
.L102:
	ldr	w0, [x0, 4]
	ubfx	x0, x0, 18, 1
	cbz	w0, .L67
	str	w0, [x19, 132]
	add	x1, x19, 72
	ldr	w2, [x19, 48]
	mov	w0, w21
	ldp	w3, w4, [x24, 4]
	bl	CAST_Create
	mov	x24, x0
	cbz	x0, .L104
	ldr	x1, [x19, 136]
	mov	w0, w21
	bl	CAST_SetAopBuf
	str	x24, [x19, 136]
	b	.L84
	.size	AOP_Process, .-AOP_Process
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_GetChnStatus
	.type	AOP_GetChnStatus, %function
AOP_GetChnStatus:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC9
	add	x20, x0, x20, uxtw 3
	ldr	x0, [x20, 64]
	cbz	x0, .L108
	ldr	w1, [x0, 144]
	str	w1, [x19]
	ldr	w1, [x0, 64]
	str	w1, [x19, 4]
	ldr	w1, [x0, 116]
	str	w1, [x19, 16]
	ldr	w1, [x0, 48]
	str	w1, [x19, 8]
	ldr	w1, [x0, 52]
	str	w1, [x19, 12]
	ldr	w1, [x0, 128]
	str	w1, [x19, 20]
	ldr	w1, [x0, 132]
	str	w1, [x19, 24]
	ldr	w1, [x0, 148]
	str	w1, [x19, 28]
	ldr	w0, [x0, 160]
	str	w0, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L108:
	str	wzr, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_GetChnStatus, .-AOP_GetChnStatus
	.align	3
.LC9:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_QueryRbfFree
	.type	AOP_QueryRbfFree, %function
AOP_QueryRbfFree:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC10
	add	x19, x0, x19, uxtw 3
	ldr	x2, [x19, 64]
	cbz	x2, .L111
	ldr	w3, [x2, 144]
	mov	w0, 0
	cbz	w3, .L110
	ldr	x2, [x2, 136]
	cbz	x2, .L110
	mov	w1, w20
	mov	x0, x2
	bl	RBUF_CheckFree
.L110:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L111:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_QueryRbfFree, .-AOP_QueryRbfFree
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteBuffProcTryCnt
	.type	AOP_WriteBuffProcTryCnt, %function
AOP_WriteBuffProcTryCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC11
	add	x0, x0, x19, uxtw 3
	ldr	x0, [x0, 64]
	cbz	x0, .L115
	ldr	w0, [x0, 132]
	cmp	w0, 1
	beq	.L120
.L115:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L120:
	mov	w0, w19
	bl	CAST_FiFoTryCnt
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_WriteBuffProcTryCnt, .-AOP_WriteBuffProcTryCnt
	.align	3
.LC11:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteBuffProcOKCnt
	.type	AOP_WriteBuffProcOKCnt, %function
AOP_WriteBuffProcOKCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC12
	add	x0, x0, x19, uxtw 3
	ldr	x0, [x0, 64]
	cbz	x0, .L121
	ldr	w0, [x0, 132]
	cmp	w0, 1
	beq	.L126
.L121:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L126:
	mov	w0, w19
	bl	CAST_FiFoFreeCnt
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOP_WriteBuffProcOKCnt, .-AOP_WriteBuffProcOKCnt
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_WriteRbfData
	.type	AOP_WriteRbfData, %function
AOP_WriteRbfData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC13
	add	x19, x0, x19, uxtw 3
	ldr	x19, [x19, 64]
	cbz	x19, .L142
	ldr	w1, [x19, 144]
	mov	w0, 0
	cbz	w1, .L128
	ldr	w0, [x20, 28]
	cbz	w0, .L151
.L130:
	ldr	w0, [x19, 132]
	ldr	w2, [x20, 8]
	cmp	w0, 1
	ldr	x1, [x20]
	ldr	x0, [x19, 136]
	beq	.L152
	bl	RBUF_WriteDataDma
.L128:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L151:
	ldr	x0, [x19, 48]
	ldr	x1, [x20, 16]
	cmp	x1, x0
	beq	.L132
	ldr	w0, [x19, 48]
	ldr	w1, [x20, 16]
	cmp	w1, w0
	beq	.L133
	bl	AOE_GetWKBuf
	mov	x1, x0
	ldr	w0, [x19, 48]
	mov	x2, x20
	bl	UTIL_UnifyBitDepthPcmData
.L133:
	ldr	w0, [x19, 52]
	ldr	w1, [x20, 20]
	cmp	w1, w0
	beq	.L132
	bl	AOE_GetWKBuf
	mov	x1, x0
	ldr	w0, [x19, 52]
	mov	x2, x20
	bl	UTIL_UpmixPcmData
.L132:
	ldr	w0, [x19, 44]
	cbz	w0, .L135
	bl	AOE_GetWKBuf
	mov	x21, x0
	ldr	x3, .LC14
	mov	w1, 0
	ldr	w2, [x20, 8]
	ldr	x3, [x3, 40]
	blr	x3
	str	x21, [x20]
.L135:
	ldr	w0, [x19, 4]
	ldr	w1, [x19, 24]
	cmp	w1, w0
	beq	.L153
.L136:
	ldr	w0, [x19, 132]
	cmp	w0, 1
	beq	.L137
	bl	AOE_GetWKBuf
	ldr	x22, .LC14
	ldr	w2, [x20, 8]
	mov	x23, x0
	ldr	x1, [x20]
	add	x21, x19, 20
	ldr	x3, [x22, 48]
	blr	x3
	str	x23, [x20]
	mov	x2, x19
	mov	x0, x20
	ldr	w1, [x19, 40]
	mov	x3, x21
	bl	UTIL_LRFadeGainProcess
	ldr	x3, [x22, 48]
	mov	x2, 20
	mov	x1, x21
	mov	x0, x19
	blr	x3
	b	.L130
	.p2align 3
.L152:
	bl	RBUF_WriteData
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L142:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L153:
	ldr	w0, [x19, 12]
	ldr	w1, [x19, 32]
	cmp	w1, w0
	bne	.L136
	.p2align 2
.L137:
	mov	x0, 121
	ldr	x1, [x19, 24]
	movk	x0, 0x79, lsl 32
	cmp	x1, x0
	bne	.L139
	ldr	x0, [x19, 32]
	cbnz	x0, .L139
	ldr	w0, [x19, 40]
	cbz	w0, .L130
.L139:
	bl	AOE_GetWKBuf
	mov	x21, x0
	ldr	x3, .LC14
	ldr	w2, [x20, 8]
	ldr	x1, [x20]
	ldr	x3, [x3, 48]
	blr	x3
	str	x21, [x20]
	add	x2, x19, 20
	mov	x0, x20
	ldr	w1, [x19, 40]
	bl	UTIL_LRGainProcess
	b	.L130
	.size	AOP_WriteRbfData, .-AOP_WriteRbfData
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	g_AdspOsalFunc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_GetRingOut
	.type	AOP_GetRingOut, %function
AOP_GetRingOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC15
	add	x19, x0, x19, uxtw 3
	ldr	x0, [x19, 64]
	cbz	x0, .L156
	ldr	x0, [x0, 136]
.L155:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L156:
	mov	x0, 0
	b	.L155
	.size	AOP_GetRingOut, .-AOP_GetRingOut
	.align	3
.LC15:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOP_ContinueOutput
	.type	AOP_ContinueOutput, %function
AOP_ContinueOutput:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w22, w3
	bl	_mcount
	ldr	x0, .LC17
	add	x19, x0, x19, uxtw 3
	ldr	x19, [x19, 64]
	cbz	x19, .L157
	cmp	w20, 4
	beq	.L165
	cmp	w20, 3
	beq	.L166
.L157:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L165:
	cmp	w22, 1
	ldr	x1, .LC16
	beq	.L161
	mov	w20, 1544
.L160:
	ldr	x0, [x19, 136]
	mov	w2, w20
	bl	RBUF_WriteDataDma
	ldr	x0, [x19, 136]
	sub	w2, w21, w20
	mov	x1, 0
	bl	RBUF_WriteDataDma
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L161:
	mov	w20, 3260
	add	x1, x1, 1544
	b	.L160
	.p2align 3
.L166:
	ldr	x1, .LC18
	mov	w2, 2568
	ldr	x0, [x19, 136]
	add	x1, x1, 456
	bl	RBUF_WriteDataDma
	ldr	x0, [x19, 136]
	sub	w2, w21, #2568
	mov	x1, 0
	bl	RBUF_WriteDataDma
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AOP_ContinueOutput, .-AOP_ContinueOutput
	.align	3
.LC16:
	.xword	.LANCHOR1
	.align	3
.LC17:
	.xword	.LANCHOR0
	.align	3
.LC18:
	.xword	.LANCHOR2
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 4352
	.type	ddp_heard, %object
	.size	ddp_heard, 1544
ddp_heard:
	.hword	-1934
	.hword	19999
	.hword	21
	.hword	1536
	.hword	2935
	.hword	767
	.hword	16263
	.hword	-8159
	.hword	1568
	.hword	0
	.hword	2
	.hword	0
	.hword	7
	.hword	-1727
	.hword	318
	.hword	-11256
	.hword	2056
	.hword	2050
	.hword	514
	.hword	512
	.hword	-32640
	.hword	-32640
	.hword	8224
	.hword	8224
	.hword	2056
	.hword	2056
	.hword	12787
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12353
	.hword	-6313
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12353
	.hword	-1579
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3089
	.hword	-395
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31995
	.hword	-99
	.hword	24382
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	-25
	.hword	22479
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-16391
	.hword	-10455
	.hword	-5998
	.hword	18887
	.hword	95
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-16
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	9
	.hword	5258
	.hword	17698
	.hword	-28344
	.hword	-23470
	.hword	10516
	.hword	-30139
	.hword	8895
	.hword	-1
	.hword	-1
	.hword	-64
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	51
	.hword	13107
	.hword	13107
	.hword	13107
	.hword	13107
	.hword	13107
	.hword	13103
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-8
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	4
	.hword	-30139
	.hword	8849
	.hword	18596
	.hword	21033
	.hword	5258
	.hword	17698
	.hword	-28321
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-16
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	9
	.hword	5258
	.hword	17698
	.hword	-28344
	.hword	-23470
	.hword	10516
	.hword	-30139
	.hword	8895
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-32
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	18
	.hword	10516
	.hword	-30139
	.hword	8849
	.hword	18596
	.hword	21033
	.hword	5258
	.hword	17791
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-1
	.hword	-64
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	36
	.hword	21033
	.hword	5258
	.hword	17698
	.hword	-28344
	.hword	-23470
	.hword	10516
	.hword	-29954
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	16448
	.hword	20772
	.hword	-28096
	.hword	16465
	.hword	9362
	.hword	16448
	.hword	20772
	.hword	-28096
	.hword	16465
	.hword	9362
	.hword	16448
	.hword	20772
	.hword	-28160
	.hword	0
	.hword	0
	.hword	0
	.hword	24528
	.hword	-1342
	.type	atmos_heard, %object
	.size	atmos_heard, 3260
atmos_heard:
	.byte	114
	.byte	-8
	.byte	31
	.byte	78
	.byte	21
	.byte	0
	.byte	-76
	.byte	12
	.byte	119
	.byte	11
	.byte	89
	.byte	6
	.byte	103
	.byte	63
	.byte	-38
	.byte	-31
	.byte	0
	.byte	73
	.byte	1
	.byte	65
	.byte	1
	.byte	7
	.byte	0
	.byte	32
	.byte	0
	.byte	0
	.byte	0
	.byte	16
	.byte	0
	.byte	0
	.byte	-124
	.byte	35
	.byte	-122
	.byte	121
	.byte	97
	.byte	24
	.byte	-4
	.byte	-121
	.byte	-7
	.byte	-22
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-13
	.byte	127
	.byte	-25
	.byte	-85
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	125
	.byte	62
	.byte	-50
	.byte	-1
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	58
	.byte	-1
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-33
	.byte	-25
	.byte	-22
	.byte	-4
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	127
	.byte	-97
	.byte	-82
	.byte	-13
	.byte	-29
	.byte	83
	.byte	-39
	.byte	-128
	.byte	27
	.byte	-14
	.byte	111
	.byte	-121
	.byte	60
	.byte	30
	.byte	-18
	.byte	120
	.byte	-18
	.byte	-18
	.byte	-32
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	-35
	.byte	-35
	.byte	-74
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-33
	.byte	-74
	.byte	107
	.byte	62
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	62
	.byte	27
	.byte	112
	.byte	67
	.byte	-29
	.byte	-19
	.byte	-113
	.byte	-57
	.byte	-35
	.byte	29
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	59
	.byte	0
	.byte	-69
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-25
	.byte	-37
	.byte	107
	.byte	-51
	.byte	-42
	.byte	90
	.byte	-81
	.byte	-75
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-61
	.byte	-25
	.byte	-56
	.byte	103
	.byte	29
	.byte	110
	.byte	120
	.byte	-68
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-20
	.byte	-5
	.byte	125
	.byte	1
	.byte	103
	.byte	-128
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-49
	.byte	0
	.byte	24
	.byte	-16
	.byte	-15
	.byte	14
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-17
	.byte	-13
	.byte	7
	.byte	-100
	.byte	-3
	.byte	-13
	.byte	71
	.byte	-98
	.byte	108
	.byte	-128
	.byte	13
	.byte	-7
	.byte	-73
	.byte	-61
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-97
	.byte	13
	.byte	-72
	.byte	33
	.byte	-15
	.byte	118
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-31
	.byte	-13
	.byte	-28
	.byte	-77
	.byte	14
	.byte	55
	.byte	60
	.byte	-34
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-10
	.byte	125
	.byte	-66
	.byte	0
	.byte	51
	.byte	-64
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	103
	.byte	-128
	.byte	12
	.byte	-8
	.byte	120
	.byte	7
	.byte	-29
	.byte	-15
	.byte	119
	.byte	-57
	.byte	119
	.byte	119
	.byte	0
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	14
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-74
	.byte	-19
	.byte	109
	.byte	-37
	.byte	-7
	.byte	-74
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	3
	.byte	-50
	.byte	-2
	.byte	-7
	.byte	35
	.byte	-49
	.byte	-1
	.byte	-61
	.byte	56
	.byte	88
	.byte	73
	.byte	0
	.byte	-32
	.byte	10
	.byte	-128
	.byte	-4
	.byte	24
	.byte	1
	.byte	17
	.byte	62
	.byte	0
	.byte	15
	.byte	-100
	.byte	3
	.byte	112
	.byte	0
	.byte	-128
	.byte	0
	.byte	-1
	.byte	0
	.byte	0
	.byte	1
	.byte	-33
	.byte	1
	.byte	0
	.byte	2
	.byte	-127
	.byte	3
	.byte	0
	.byte	-12
	.byte	-5
	.byte	7
	.byte	0
	.byte	-24
	.byte	-5
	.byte	14
	.byte	8
	.byte	-16
	.byte	-9
	.byte	29
	.byte	16
	.byte	-32
	.byte	-48
	.byte	1
	.byte	64
	.byte	126
	.byte	84
	.byte	0
	.byte	16
	.byte	-58
	.byte	60
	.byte	10
	.byte	32
	.byte	16
	.byte	4
	.byte	-127
	.byte	32
	.byte	8
	.byte	0
	.byte	65
	.byte	2
	.byte	-82
	.byte	10
	.byte	-72
	.byte	43
	.byte	-32
	.byte	-82
	.byte	-128
	.byte	9
	.byte	0
	.byte	-121
	.byte	-103
	.byte	-82
	.byte	104
	.byte	-51
	.byte	52
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	50
	.byte	-51
	.byte	48
	.byte	30
	.byte	-51
	.byte	108
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	67
	.byte	62
	.byte	-19
	.byte	112
	.byte	-57
	.byte	-29
	.byte	29
	.byte	-113
	.byte	-35
	.byte	-35
	.byte	-36
	.byte	-35
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	59
	.byte	-74
	.byte	-69
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-51
	.byte	-25
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	103
	.byte	-61
	.byte	110
	.byte	-56
	.byte	-68
	.byte	29
	.byte	-15
	.byte	120
	.byte	-69
	.byte	-29
	.byte	-69
	.byte	-69
	.byte	-128
	.byte	-69
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.byte	0
	.byte	119
	.byte	119
	.byte	-37
	.byte	118
	.byte	-74
	.byte	109
	.byte	124
	.byte	-37
	.byte	-83
	.byte	-7
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-8
	.byte	124
	.byte	-7
	.byte	108
	.byte	-61
	.byte	13
	.byte	-113
	.byte	-73
	.byte	60
	.byte	30
	.byte	119
	.byte	119
	.byte	119
	.byte	119
	.byte	0
	.byte	112
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	0
	.byte	-18
	.byte	-18
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-97
	.byte	111
	.byte	-83
	.byte	53
	.byte	90
	.byte	107
	.byte	-66
	.byte	-42
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	125
	.byte	-97
	.byte	47
	.byte	-128
	.byte	12
	.byte	-80
	.byte	-29
	.byte	-15
	.byte	-114
	.byte	-57
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-35
	.byte	29
	.byte	-37
	.byte	-35
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	-26
	.byte	-13
	.byte	-83
	.byte	-75
	.byte	90
	.byte	107
	.byte	-49
	.byte	-41
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	25
	.byte	-32
	.byte	3
	.byte	-2
	.byte	-34
	.byte	1
	.byte	120
	.byte	60
	.byte	-35
	.byte	-15
	.byte	-35
	.byte	-35
	.byte	-64
	.byte	-35
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	0
	.byte	-69
	.byte	-69
	.byte	109
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-66
	.byte	109
	.byte	-42
	.byte	124
	.byte	-83
	.byte	-75
	.byte	90
	.byte	107
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	125
	.byte	62
	.byte	-128
	.byte	-13
	.byte	127
	.byte	-2
	.byte	-56
	.byte	-77
	.byte	-82
	.byte	-16
	.byte	0
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	0
	.byte	-112
	.byte	-49
	.byte	59
	.byte	-36
	.byte	-15
	.byte	120
	.byte	-57
	.byte	-29
	.byte	119
	.byte	119
	.byte	119
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	14
	.byte	-19
	.byte	-18
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-13
	.byte	-7
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-25
	.byte	107
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-39
	.byte	-16
	.byte	27
	.byte	-14
	.byte	111
	.byte	-121
	.byte	60
	.byte	30
	.byte	-18
	.byte	120
	.byte	-18
	.byte	-18
	.byte	-32
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	-35
	.byte	-35
	.byte	-74
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-33
	.byte	-74
	.byte	107
	.byte	62
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	62
	.byte	27
	.byte	112
	.byte	67
	.byte	-29
	.byte	-19
	.byte	-113
	.byte	-57
	.byte	-35
	.byte	29
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	59
	.byte	0
	.byte	-69
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-25
	.byte	-37
	.byte	107
	.byte	-51
	.byte	-42
	.byte	90
	.byte	-81
	.byte	-75
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-33
	.byte	-25
	.byte	11
	.byte	96
	.byte	3
	.byte	-20
	.byte	120
	.byte	60
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	6
	.byte	-8
	.byte	-128
	.byte	127
	.byte	119
	.byte	-64
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-32
	.byte	124
	.byte	-97
	.byte	63
	.byte	-14
	.byte	-20
	.byte	3
	.byte	60
	.byte	-56
	.byte	103
	.byte	29
	.byte	110
	.byte	120
	.byte	-68
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	108
	.byte	-8
	.byte	13
	.byte	-7
	.byte	-73
	.byte	-61
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-97
	.byte	13
	.byte	-72
	.byte	33
	.byte	-15
	.byte	118
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-17
	.byte	-13
	.byte	5
	.byte	-80
	.byte	1
	.byte	-10
	.byte	60
	.byte	-98
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	3
	.byte	124
	.byte	-64
	.byte	63
	.byte	59
	.byte	96
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	112
	.byte	-66
	.byte	-49
	.byte	31
	.byte	121
	.byte	-10
	.byte	1
	.byte	30
	.byte	-28
	.byte	-77
	.byte	14
	.byte	55
	.byte	60
	.byte	-34
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	54
	.byte	124
	.byte	-122
	.byte	124
	.byte	-37
	.byte	-31
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	-49
	.byte	-122
	.byte	-36
	.byte	-112
	.byte	120
	.byte	59
	.byte	-29
	.byte	-15
	.byte	119
	.byte	-57
	.byte	119
	.byte	119
	.byte	0
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	14
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-74
	.byte	-19
	.byte	109
	.byte	-37
	.byte	-7
	.byte	-74
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	2
	.byte	-40
	.byte	0
	.byte	-5
	.byte	30
	.byte	-49
	.byte	120
	.byte	60
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-32
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-35
	.byte	1
	.byte	-35
	.byte	-35
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	62
	.byte	-33
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	124
	.byte	-83
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	1
	.byte	62
	.byte	-32
	.byte	-97
	.byte	29
	.byte	48
	.byte	-57
	.byte	-29
	.byte	29
	.byte	-113
	.byte	-35
	.byte	-35
	.byte	-36
	.byte	-35
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	59
	.byte	-74
	.byte	-69
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-51
	.byte	-25
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	56
	.byte	-33
	.byte	-25
	.byte	15
	.byte	60
	.byte	-5
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-112
	.byte	113
	.byte	21
	.byte	-8
	.zero	4
	.type	dd_heard, %object
	.size	dd_heard, 2568
dd_heard:
	.hword	-1934
	.hword	19999
	.hword	1
	.hword	20480
	.hword	2935
	.hword	3061
	.hword	9264
	.hword	-7684
	.hword	1216
	.hword	16129
	.hword	-27299
	.hword	5201
	.hword	17695
	.hword	-3157
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-13922
	.hword	-15501
	.hword	-50
	.hword	-20577
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24791
	.hword	-30999
	.hword	14335
	.hword	15038
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-23052
	.hword	14143
	.hword	-790
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3481
	.hword	19051
	.hword	32755
	.hword	-21529
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6198
	.hword	-27867
	.hword	32255
	.hword	-12615
	.hword	20366
	.hword	9288
	.hword	-28382
	.hword	17408
	.hword	0
	.hword	7
	.hword	30961
	.hword	-7225
	.hword	30583
	.hword	30583
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	3822
	.hword	-4371
	.hword	-18725
	.hword	28086
	.hword	-1549
	.hword	23254
	.hword	-19027
	.hword	27623
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-4096
	.hword	0
	.hword	239
	.hword	7740
	.hword	30958
	.hword	-4370
	.hword	-4384
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	1
	.hword	-8739
	.hword	-8778
	.hword	-9363
	.hword	-18721
	.hword	15979
	.hword	23254
	.hword	-19027
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	0
	.hword	0
	.hword	7651
	.hword	-14449
	.hword	7645
	.hword	-8739
	.hword	-9216
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	59
	.hword	-17477
	.hword	-18725
	.hword	28086
	.hword	-9241
	.hword	-12949
	.hword	23254
	.hword	-19025
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6208
	.hword	0
	.hword	3
	.hword	-17288
	.hword	-3613
	.hword	-17477
	.hword	-17477
	.hword	-32768
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	1911
	.hword	30582
	.hword	-9363
	.hword	-18725
	.hword	31993
	.hword	-21141
	.hword	23254
	.hword	-18957
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-2048
	.hword	0
	.hword	119
	.hword	-28898
	.hword	15479
	.hword	30583
	.hword	30576
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	-4370
	.hword	-4389
	.hword	28086
	.hword	-9361
	.hword	-24779
	.hword	-21141
	.hword	23254
	.hword	-16772
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	0
	.hword	0
	.hword	3824
	.hword	8064
	.hword	-32768
	.hword	0
	.hword	0
	.hword	3825
	.hword	-7225
	.hword	-28946
	.hword	-4370
	.hword	-4608
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	29
	.hword	-8739
	.hword	-9363
	.hword	-18725
	.hword	28147
	.hword	-6475
	.hword	-21141
	.hword	23255
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3104
	.hword	0
	.hword	1
	.hword	-8644
	.hword	30961
	.hword	-8739
	.hword	-8739
	.hword	-16384
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	955
	.hword	-17477
	.hword	28086
	.hword	-9363
	.hword	-16772
	.hword	-10571
	.hword	-21141
	.hword	23289
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31744
	.hword	0
	.hword	59
	.hword	-14449
	.hword	7739
	.hword	-17477
	.hword	-17480
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	30583
	.hword	30573
	.hword	-18725
	.hword	28087
	.hword	-12390
	.hword	-10571
	.hword	-21141
	.hword	24382
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-32768
	.hword	0
	.hword	1912
	.hword	-3613
	.hword	-14473
	.hword	30583
	.hword	30464
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	14
	.hword	-4370
	.hword	-4682
	.hword	-9363
	.hword	-18695
	.hword	-3238
	.hword	-10571
	.hword	-21141
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1552
	.hword	0
	.hword	0
	.hword	-4322
	.hword	15480
	.hword	-4370
	.hword	-4370
	.hword	-8192
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	477
	.hword	-8739
	.hword	-18725
	.hword	28086
	.hword	-8386
	.hword	27482
	.hword	-10571
	.hword	-21124
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15872
	.hword	0
	.hword	29
	.hword	-8129
	.hword	256
	.hword	0
	.hword	0
	.hword	29
	.hword	-7225
	.hword	-28899
	.hword	-8739
	.hword	-8740
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	15291
	.hword	-17482
	.hword	-9363
	.hword	-18725
	.hword	-6195
	.hword	27482
	.hword	-10571
	.hword	-20577
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-16384
	.hword	0
	.hword	956
	.hword	30961
	.hword	-7237
	.hword	-17477
	.hword	-17536
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	7
	.hword	30583
	.hword	30427
	.hword	28086
	.hword	-9348
	.hword	-1619
	.hword	27482
	.hword	-10571
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31992
	.hword	0
	.hword	0
	.hword	30607
	.hword	7740
	.hword	30583
	.hword	30583
	.hword	28672
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	238
	.hword	-4370
	.hword	-9363
	.hword	-18725
	.hword	28575
	.hword	13741
	.hword	27482
	.hword	-10562
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24832
	.hword	0
	.hword	14
	.hword	-3613
	.hword	-14450
	.hword	-4370
	.hword	-4370
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	7645
	.hword	-8741
	.hword	28086
	.hword	-9363
	.hword	-3098
	.hword	-19027
	.hword	27482
	.hword	-10289
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-8192
	.hword	0
	.hword	478
	.hword	15480
	.hword	-3619
	.hword	-8739
	.hword	-8768
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	3
	.hword	-17477
	.hword	-17555
	.hword	-18725
	.hword	28094
	.hword	31958
	.hword	-19027
	.hword	27482
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	0
	.hword	0
	.hword	15296
	.hword	32258
	.hword	2
	.hword	13056
	.hword	-17629
	.hword	-26289
	.hword	-991
	.hword	6727
	.hword	31487
	.hword	29080
	.hword	-23057
	.hword	-29454
	.hword	-4832
	.hword	23813
	.hword	-15679
	.hword	-11646
	.hword	-27644
	.hword	-9193
	.hword	-11496
	.hword	27765
	.hword	-4564
	.hword	28748
	.hword	22386
	.hword	-9652
	.hword	32025
	.hword	-26586
	.hword	-12207
	.hword	-25464
	.hword	-16311
	.hword	0
	.hword	0
	.hword	7651
	.hword	-14449
	.hword	7645
	.hword	-8739
	.hword	-9216
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	59
	.hword	-17477
	.hword	-18725
	.hword	28086
	.hword	-9241
	.hword	-12949
	.hword	23254
	.hword	-19025
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6208
	.hword	0
	.hword	3
	.hword	-17288
	.hword	-3613
	.hword	-17477
	.hword	-17477
	.hword	-32768
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	1911
	.hword	30582
	.hword	-9363
	.hword	-18725
	.hword	31993
	.hword	-21141
	.hword	23254
	.hword	-18957
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-2048
	.hword	0
	.hword	119
	.hword	-28898
	.hword	15479
	.hword	30583
	.hword	30576
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	-4370
	.hword	-4389
	.hword	28086
	.hword	-9361
	.hword	-24779
	.hword	-21141
	.hword	23254
	.hword	-16772
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	0
	.hword	0
	.hword	3825
	.hword	-7225
	.hword	-28946
	.hword	-4370
	.hword	-4608
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	29
	.hword	-8739
	.hword	-9363
	.hword	-18725
	.hword	28147
	.hword	-6475
	.hword	-21141
	.hword	23255
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3104
	.hword	0
	.hword	1
	.hword	-8644
	.hword	30961
	.hword	-8739
	.hword	-8739
	.hword	-16384
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	955
	.hword	-17477
	.hword	28086
	.hword	-9363
	.hword	-16772
	.hword	-10571
	.hword	-21141
	.hword	23289
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31744
	.hword	0
	.hword	59
	.hword	-16258
	.hword	512
	.hword	600
	.hword	212
	.hword	9149
	.hword	13105
	.hword	-22729
	.hword	16036
	.hword	-15202
	.hword	-26341
	.hword	11106
	.hword	30344
	.hword	-29965
	.hword	1241
	.hword	-27967
	.hword	29184
	.hword	-3268
	.hword	-3349
	.hword	24020
	.hword	-19572
	.hword	-32519
	.hword	-6959
	.hword	3355
	.hword	-18517
	.hword	-19798
	.hword	23307
	.hword	8213
	.hword	-33
	.hword	1998
	.hword	-10983
	.hword	5956
	.hword	3239
	.hword	487
	.hword	-11141
	.hword	29479
	.hword	23683
	.hword	7796
	.hword	-10576
	.hword	-19906
	.hword	29171
	.hword	-8203
	.hword	23610
	.hword	22025
	.hword	-13961
	.hword	-14870
	.hword	-6248
	.hword	-8952
	.hword	0
	.hword	0
	.hword	7651
	.hword	-14449
	.hword	7645
	.hword	-8739
	.hword	-9216
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	59
	.hword	-17477
	.hword	-18725
	.hword	28086
	.hword	-9241
	.hword	-12949
	.hword	23254
	.hword	-19025
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6208
	.hword	0
	.hword	3
	.hword	-17288
	.hword	-3613
	.hword	-17477
	.hword	-17477
	.hword	-32768
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	1911
	.hword	30582
	.hword	-9363
	.hword	-18725
	.hword	31993
	.hword	-21141
	.hword	23254
	.hword	-18957
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-2048
	.hword	0
	.hword	119
	.hword	-28898
	.hword	15479
	.hword	30583
	.hword	30576
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	-4370
	.hword	-4389
	.hword	28086
	.hword	-9361
	.hword	-24779
	.hword	-21141
	.hword	23254
	.hword	-16772
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	0
	.hword	0
	.hword	3825
	.hword	-7225
	.hword	-28946
	.hword	-4370
	.hword	-4608
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	29
	.hword	-8739
	.hword	-9363
	.hword	-18725
	.hword	28147
	.hword	-6475
	.hword	-21141
	.hword	23255
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3104
	.hword	0
	.hword	1
	.hword	-8644
	.hword	30961
	.hword	-8739
	.hword	-8739
	.hword	-16384
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	955
	.hword	-17477
	.hword	28086
	.hword	-9363
	.hword	-16772
	.hword	-10571
	.hword	-21141
	.hword	23289
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31744
	.hword	0
	.hword	59
	.hword	-16258
	.hword	512
	.hword	599
	.hword	229
	.hword	-28850
	.hword	-11275
	.hword	19144
	.hword	-17594
	.hword	-17413
	.hword	12295
	.hword	-12136
	.hword	-23958
	.hword	31309
	.hword	-32354
	.hword	-21813
	.hword	15570
	.hword	20162
	.hword	17720
	.hword	22754
	.hword	3071
	.hword	-18724
	.hword	-425
	.hword	23134
	.hword	-29073
	.hword	12825
	.hword	11129
	.hword	12221
	.hword	17828
	.hword	17146
	.hword	19487
	.hword	22913
	.hword	-20452
	.hword	26112
	.hword	-7734
	.hword	22312
	.hword	20312
	.hword	7849
	.hword	27384
	.hword	-22221
	.hword	-23847
	.hword	-5514
	.hword	26410
	.hword	-12509
	.hword	10525
	.hword	18920
	.hword	22753
	.hword	18688
	.hword	0
	.hword	29
	.hword	-7225
	.hword	-28899
	.hword	-8739
	.hword	-8740
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	15291
	.hword	-17482
	.hword	-9363
	.hword	-18725
	.hword	-6195
	.hword	27482
	.hword	-10571
	.hword	-20577
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-16384
	.hword	0
	.hword	956
	.hword	30961
	.hword	-7237
	.hword	-17477
	.hword	-17536
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	7
	.hword	30583
	.hword	30427
	.hword	28086
	.hword	-9348
	.hword	-1619
	.hword	27482
	.hword	-10571
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31992
	.hword	0
	.hword	0
	.hword	30607
	.hword	7740
	.hword	30583
	.hword	30583
	.hword	28672
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	238
	.hword	-4370
	.hword	-9363
	.hword	-18725
	.hword	28575
	.hword	13741
	.hword	27482
	.hword	-10562
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-6193
	.hword	-24832
	.hword	0
	.hword	14
	.hword	-3613
	.hword	-14450
	.hword	-4370
	.hword	-4370
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	7645
	.hword	-8741
	.hword	28086
	.hword	-9363
	.hword	-3098
	.hword	-19027
	.hword	27482
	.hword	-10289
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	-1549
	.hword	-8192
	.hword	0
	.hword	478
	.hword	15480
	.hword	-3619
	.hword	-8739
	.hword	-8768
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	3
	.hword	-17477
	.hword	-17555
	.hword	-18725
	.hword	28094
	.hword	31958
	.hword	-19027
	.hword	27482
	.hword	-1549
	.hword	-6193
	.hword	-24770
	.hword	31993
	.hword	-3097
	.hword	-12385
	.hword	15996
	.hword	0
	.hword	0
	.hword	15296
	.hword	29987
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_stAopRm, %object
	.size	g_stAopRm, 128
g_stAopRm:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
